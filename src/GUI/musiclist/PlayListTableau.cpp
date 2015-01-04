/***************************************************************
 * Name:      PlayListTableau.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2010-08-22
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "../../../include/gui/musiclist/PlayList.h"

/**
 * @class PlayListTableau
 * @brief Tableau (GUI) dans lequel sont affichés les informations des titres mis dans la liste de lecture. D'une certaine manière, c'est la liste de lecture
 */

BEGIN_EVENT_TABLE(PlayListTableau, wxListCtrl)
    EVT_LIST_ITEM_ACTIVATED(ID_PAGE_PLAYLIST_LISTE, PlayListTableau::ChansonActive)
    EVT_KEY_DOWN(PlayListTableau::OnKey)
    EVT_LIST_BEGIN_DRAG(ID_PAGE_PLAYLIST_LISTE, PlayListTableau::Glisser)
    EVT_RIGHT_DOWN(PlayListTableau::AfficheMenu)
    EVT_MENU(ID_PAGE_PLAYLIST_MENU_LECTURE, PlayListTableau::menuLecture)
    EVT_MENU(ID_PAGE_PLAYLIST_MENU_PAUSE, PlayListTableau::menuPause)
    EVT_MENU(ID_PAGE_PLAYLIST_MENU_SUPPRIMER, PlayListTableau::menuSupprimer)
    EVT_MENU(ID_PAGE_PLAYLIST_MENU_COUPER, PlayListTableau::menuCouper)
    EVT_MENU(ID_PAGE_PLAYLIST_MENU_COLLER, PlayListTableau::menuColler)
    EVT_MENU(ID_PAGE_PLAYLIST_MENU_DETAILS, PlayListTableau::menuDetails)
    EVT_MOUSE_EVENTS(PlayListTableau::MouseEvents)
END_EVENT_TABLE()


const wxEventType wxEVT_VIDER_PANNEAU = wxNewEventType();
const wxEventType wxEVT_LISTE_DETAILS = wxNewEventType();
static wxMutex *s_mutexMAJPlaylist = new wxMutex;

/**
 * Constructeur
 * @param Parent La fenêtre parente
 */
PlayListTableau::PlayListTableau(wxWindow *Parent) : wxListCtrl(Parent, ID_PAGE_PLAYLIST_LISTE, wxDefaultPosition, wxDefaultSize, wxLC_REPORT |  wxLC_HRULES | wxLC_VRULES)
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("PlayListTableau::PlayListTableau - Création"));
    #endif

    InsertColumn(0, _("Nom"),         wxLIST_FORMAT_CENTER,  280);
    InsertColumn(1, _("Artiste"),     wxLIST_FORMAT_LEFT,    150);
    InsertColumn(2, _("Album"),       wxLIST_FORMAT_LEFT,    150);
    InsertColumn(3, _("Titre"),       wxLIST_FORMAT_LEFT,    150);
    InsertColumn(4, _("Durée"),       wxLIST_FORMAT_LEFT,    50);
    InsertColumn(5, _("Année"),       wxLIST_FORMAT_LEFT,    50);
    InsertColumn(6, _("Emplacement"), wxLIST_FORMAT_LEFT,    280);
    InsertColumn(7, _("Genre"),       wxLIST_FORMAT_LEFT,    80);
    InsertColumn(8, _("Ext."),        wxLIST_FORMAT_LEFT,    50);

    SetDropTarget(new DnDCible(this));
    //DragAcceptFiles(true);

    m_menu = new wxMenu;
    m_menu->Append(ID_PAGE_PLAYLIST_MENU_LECTURE,   _("Lire"));
    m_menu->Append(ID_PAGE_PLAYLIST_MENU_PAUSE,     _("Pause"));
    m_menu->Append(ID_PAGE_PLAYLIST_MENU_SUPPRIMER, _("Effacer"));
    m_menu->Append(ID_PAGE_PLAYLIST_MENU_COUPER,    _("Déplacer"));
    m_menu->Append(ID_PAGE_PLAYLIST_MENU_COLLER,    _("Déposer"));
    m_menu->Append(ID_PAGE_PLAYLIST_MENU_DETAILS,   _("Détails"));
    m_couper = false;
}

PlayListTableau::~PlayListTableau()
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("PlayListTableau::~PlayListTableau"));
    #endif
}

/**
 * Efface le contenu de la liste et affiche les données relatives au fichier musique.liste
 */
void PlayListTableau::MAJ()
{
    wxMutexLocker lock(*s_mutexMAJPlaylist);
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("PlayListTableau::MAJ - Début après les tests"));
    #endif

    wxString chaine, extrait;

    if (GetSelectedItemCount() > 0)
        extrait = GetItemText(GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED));

    long ligneVisible = 0;
    if (GetItemCount() >= GetCountPerPage())
        ligneVisible = GetTopItem() + GetCountPerPage()-1;

    DeleteAllItems();

    if (MusicManager::get().getSearchedOrAllMusics().empty())
    {
        return;
    }

    Freeze();

    #if DEBUG
    FichierLog::Get()->Ajouter(_T("PlayListTableau::MAJ - Début du for"));
    #endif

    SetDoubleBuffered(true);
    for (std::vector<Music*>::iterator iter = MusicManager::get().getSearchedOrAllMusics().begin(); iter != MusicManager::get().getSearchedOrAllMusics().end(); ++iter)
    {
//        BDDRequete *req = new BDDRequete(this);

        addLine(**iter);

//        req->AjouterChanson(music->GetFileName(), music->GetYear() == 0 ? _T("") : music->GetStringYear(), music->GetGenres());
//        req->AjouterArtiste(music->GetArtists());

//        if (pos%10 == 5)
//            wxApp::GetInstance()->Yield(false);
    }

    if (!GetSelectedItemCount() && GetTopItem() == 0)
    {
        if (GetItemCount() > 0)
            EnsureVisible(ligneVisible);

        if (!extrait.IsEmpty())
        {
            long ligne = FindItem(-1, extrait);
            SetItemState(ligne, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED);
            EnsureVisible(ligne);
        }
    }
    this->ChangementChanson();

    SetDoubleBuffered(false);
    Thaw();

    #if DEBUG
    FichierLog::Get()->Ajouter(_T("PlayListTableau::MAJ - Fin du for : ") + wxString::Format(_T("%u"), GetItemCount()));
    #endif

    #if DEBUG
    FichierLog::Get()->Ajouter(_T("PlayListTableau::MAJ - Fin"));
    #endif
}

/** @brief Adds a line at the end of the list
 *
 * @param music a music data
 * @return void
 *
 */
void PlayListTableau::addLine(Music& music)
{
    addLine(music, GetItemCount());
}

/** @brief Adds a line at the specified position
 *
 * @param music a music data
 * @param position position to place the line
 * @return void
 *
 */
void PlayListTableau::addLine(Music& music, const int position)
{
    int pos = InsertItem(position, wxEmptyString);
    modifyLine(music, pos);
}

/** @brief Adds a line at the specified position.
 * It creates intermediate lines if needed.
 * @param music a music
 * @param position position to insert
 * @return void
 *
 */
void PlayListTableau::addLineThread(Music& music, const int position)
{
    while (GetItemCount() < position+1)
    {
        InsertItem(GetItemCount(), wxEmptyString);
    }
    modifyLine(music, position);
}

/** @brief Modifies a line in the list
 *
 * @param music a music data
 * @param position line to modify
 * @return void
 *
 */
void PlayListTableau::modifyLine(Music& music, const int position)
{
    SetItem(position, 0, music.GetName());//Nom du fichier
    SetItem(position, 1, music.GetArtists());//Artiste
    SetItem(position, 2, music.GetAlbum());//Album
    SetItem(position, 3, music.GetTitle());//Titre
    SetItem(position, 4, music.GetStringDuration());//Durée
    SetItem(position, 5, music.GetYear() == 0 ? _T("?") : music.GetStringYear());//Année
    SetItem(position, 6, music.GetPath());//Emplacement
    SetItem(position, 7, music.GetGenres());//Genre
    SetItem(position, 8, music.GetExtension());//Extension
}

/**
 * Event. Informe l'application que le titre en cours de lecture doit changer
 */
void PlayListTableau::ChansonActive(wxListEvent &event)
{
    MusicManager::get().playMusicAtInShownCollection(event.GetIndex());
}

/**
 * Évènements clavier
 */
void PlayListTableau::OnKey(wxKeyEvent &event)
{
    if (event.GetKeyCode() == WXK_DELETE)
        SuppressionLigne();
    else if (event.GetKeyCode() == 'A' && event.ControlDown())
        SetItemState(-1, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
    else if ((event.GetKeyCode() == 'R' && event.ControlDown()) || event.GetKeyCode() == WXK_F5)
        MAJ();
    else if (event.ControlDown() && (event.GetKeyCode() == '+' || event.GetKeyCode() == WXK_ADD || event.GetKeyCode() == WXK_NUMPAD_ADD ||
                                     event.GetKeyCode() == '-' || event.GetKeyCode() == WXK_SUBTRACT || event.GetKeyCode() == WXK_NUMPAD_SUBTRACT))
    {
        wxKeyEvent evt(wxEVT_KEY_DOWN);
        evt = event;
        GetParent()->GetEventHandler()->AddPendingEvent(evt);
    }
    else
        event.Skip();
}

/**
 * Évènements souris
 */
void PlayListTableau::MouseEvents(wxMouseEvent &event)
{
    if (event.ControlDown() && event.GetWheelRotation() != 0)
    {
        if (event.GetWheelRotation() < 0)
            MusicManager::get().playNextMusic();
        else
            MusicManager::get().playPreviousMusic();
    }
    else if (event.AltDown() && event.GetWheelRotation() != 0)
    {
        if (event.GetWheelRotation() < 0)
            SliderSon::Get()->SonUp();
        else
            SliderSon::Get()->SonDown();
    }
    else if (event.LeftDown())
    {
        wxPoint pt = event.GetPosition();
        event.Skip();

        int taille = -GetScrollPos(wxHORIZONTAL);
        for (int i = 0; i < 5; i++)
            taille += GetColumnWidth(i);

        if ((pt.x >= taille) && pt.x <= (taille + GetColumnWidth(5)))
        {
            //int flag = wxLIST_HITTEST_ONITEM | wxLIST_HITTEST_ONITEMRIGHT | wxLIST_HITTEST_TOLEFT | wxLIST_HITTEST_TORIGHT;
            //long pos = HitTest(pt, flag);

            //SetItemState(pos, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED);

            //wxLogMessage(wxString::Format(_T("sur année %d, %d %d"), GetColumnWidth(5), pt.x, pt.y));
            // Afficher le menu donnant la liste des noms enregistrés en mémoire
        }
    }
    else
        event.Skip();
}

/**
 * Supprime le titre en cours de lecture de la liste affichée
 * @param titre la structure contenant le nom et la position du titre dans le fichier musique.liste (donc aussi dans le tableau)
 */
void PlayListTableau::supprimerNomLigne(ChansonNomPos titre)
{
    wxMutexLocker lock(*s_mutexMAJPlaylist);
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("PlayListTableau::supprimerNomLigne(ChansonNomPos)"));
    #endif
    wxString extrait;
    int i = 0;
    while (i < GetItemCount())
    {
        extrait = GetItemText(i);
        if (titre.GetNom().EndsWith(extrait) && (i == titre.GetPos() || titre.GetPos() == -1))
        {
            DeleteItem(i);
            for (size_t k = 0; k < m_ocurrenceLigne.GetCount(); k++)
            {
                if (m_ocurrenceLigne.Item(k) >= i)
                    m_ocurrenceLigne.Item(k)--;
            }
            return;
        }
        ++i;
    }
}

/**
 * Lors du changement de musique, cette méthode modifie les couleurs de chaque ligne du tableau. Le titre en cours est en orange, les doubles en vert.
 * @param titre les nom et position du titre en cours
 */
void PlayListTableau::ChangementChanson()
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("PlayListTableau::ChangementChanson(ChansonNomPos)"));
    #endif
    if (MusicManager::get().getSearchedOrAllMusics().empty())
        return;

    if (m_ocurrenceLigne.GetCount() > 0)
    {
        for (size_t i = 0; i < m_ocurrenceLigne.GetCount(); i++)
        {
            if (m_ocurrenceLigne.Item(i) < GetItemCount())
            {
                SetItemTextColour(m_ocurrenceLigne.Item(i), wxColor(0, 0, 0));
                SetItemBackgroundColour(m_ocurrenceLigne.Item(i), wxColor(255, 255, 255));
            }
        }
        m_ocurrenceLigne.Empty();
    }
    m_positionChanson = -1;

    for (size_t i = 0; i < (size_t) GetItemCount(); ++i)
    {
        if (GetItemText(i).IsSameAs(MusicManager::get().getMusic()->GetName()))
        {
            m_ocurrenceLigne.Add(i);
            if (MusicManager::get().getCurrentMusicPosition() == i && !MusicManager::get().hasEfficientSearchedWord())//La couleur orange perd son sens lorsqu'il y a une recherche locale
            {
                SetItemTextColour(i, wxColor(247, 236, 50));
                SetItemBackgroundColour(i, wxColor(243, 124, 45));
                m_positionChanson = i;
            }
            else
            {
                SetItemTextColour(i, wxColor(24, 14, 154));
                SetItemBackgroundColour(i, wxColor(64, 247, 32));
            }
        }
    }
}

/**
 * Opération de Drag&Drop. Déplace les lignes sélectionnées à un autre endroit de liste
 */
void PlayListTableau::Glisser(wxListEvent &WXUNUSED(event))
{
    wxMutexLocker locker(*s_mutexMAJPlaylist);
    if (MusicManager::get().hasEfficientSearchedWord())
        return;

    long item = -1;
    DnDListeFichier* transfile = new DnDListeFichier();

    item = GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    while (item != -1)
    {
        transfile->AddFile(wxString::Format(_("%d"), item));
        //transfile->AddFile(Musique::Get()->GetFichier()->GetNomPosition(item));
        item = GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    }
    if (transfile->GetCount() == 0)  // Si aucun fichier détruire l'instance et sortir
    {
        delete transfile;
        return;
    }

    MusicPlayListDnDBufferData UploadData(transfile);   // Créer un objet de manipulation de données

    wxDropSource source(UploadData, this);

    source.DoDragDrop(wxDrag_DefaultMove); // Effectuer l'opération de D&D
    delete transfile;
}

/**
 * Affiche le menu obtenu lors d'un clic droit dans la liste
 */
void PlayListTableau::AfficheMenu(wxMouseEvent &WXUNUSED(event))
{
    int flag = wxLIST_HITTEST_ONITEM | wxLIST_HITTEST_ONITEMRIGHT | wxLIST_HITTEST_TOLEFT | wxLIST_HITTEST_TORIGHT;
    long pos = HitTest(ScreenToClient(wxGetMousePosition()), flag);

    if (pos != wxNOT_FOUND)//Sélection et dé-sélection des lignes
    {
        if (GetItemState(pos, wxLIST_STATE_SELECTED) != wxLIST_STATE_SELECTED)
            while (GetSelectedItemCount() > 0)
                SetItemState(GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED), 0, wxLIST_STATE_SELECTED);
        SetItemState(pos, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED);
    }

    if ((pos == m_positionChanson) || (pos == wxNOT_FOUND && GetItemCount() > 0))//Element sélectionné est chargé ou pas d'éléments sélectionnés
    {
       ////////////////////// Musique::Get()->GetNomChanson().IsSameAs(GetItem(pos));/////////////////
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_LECTURE, false);
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_PAUSE, true);
        if (MusicManager::get().getMusicPlayer().isPlaying())//En lecture
            m_menu->SetLabel(ID_PAGE_PLAYLIST_MENU_PAUSE, _("Pause"));
        else
            m_menu->SetLabel(ID_PAGE_PLAYLIST_MENU_PAUSE, _("Reprendre"));
    }
    else if (GetItemCount() > 0)//L'élément sélectionné n'est pas en lecture
    {
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_LECTURE, true);
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_PAUSE, true);
        if (MusicManager::get().getMusicPlayer().isPlaying())//En lecture
            m_menu->SetLabel(ID_PAGE_PLAYLIST_MENU_PAUSE, _("Pause"));
        else
            m_menu->SetLabel(ID_PAGE_PLAYLIST_MENU_PAUSE, _("Reprendre"));
    }
    else//Liste vierge
    {
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_LECTURE, false);
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_PAUSE, false);
    }


    if (m_couper && !MusicManager::get().hasEfficientSearchedWord())
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_COLLER, true);
    else
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_COLLER, false);

    if (pos == wxNOT_FOUND)//Pas d'élément sélectionnés
    {
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_COUPER, false);
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_SUPPRIMER, false);
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_DETAILS, false);
    }
    else
    {
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_COUPER, !MusicManager::get().hasEfficientSearchedWord());// couper accessible si on est pas en recherche
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_SUPPRIMER, !MusicManager::get().hasEfficientSearchedWord());// idem
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_DETAILS, true);
    }

    m_yMenu = pos;

    PopupMenu(m_menu);
}

/**
 * Évènement. Lance la lecture du titre sélectionné
 */
void PlayListTableau::menuLecture(wxCommandEvent &WXUNUSED(event))
{
    long pos = GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_FOCUSED);
    MusicManager::get().playMusicAtInShownCollection(pos);
}

/**
 * Évènement. Met en pause ou reprend la l'écoute
 */
void PlayListTableau::menuPause(wxCommandEvent &WXUNUSED(event))
{
    if (MusicManager::get().getMusicPlayer().isPlaying())
        MusicManager::get().getMusicPlayer().setPause(true);
    else if (MusicManager::get().getMusicPlayer().isPaused())
        MusicManager::get().getMusicPlayer().setPause(false);
    else//Musique stoppée
        MusicManager::get().playSameMusic();
}

/**
 * Évènement. Supprime l'élément sélectionné de la liste
 */
void PlayListTableau::menuSupprimer(wxCommandEvent &WXUNUSED(event))
{
    SuppressionLigne();
}

/**
 * Évènement. Mise en mémoire, Ctrl+X
 */
void PlayListTableau::menuCouper(wxCommandEvent &WXUNUSED(event))
{
    long item = -1;
    item = GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    while (item != -1)
    {
        m_tableauCouper.Add(wxString::Format(_T("%ld"), item));
        item = GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    }
    m_couper = true;
}

/**
 * Évènement. Déplacement, Ctrl+V
 */
void PlayListTableau::menuColler(wxCommandEvent &WXUNUSED(event))
{
    MusicManager::get().moveIntTitlesAt(&m_tableauCouper, m_yMenu, true);
    m_tableauCouper.Clear();
    m_couper = false;
}

/**
 * Évènement. Affiche une fenêtre dans laquelle des détails sur le titre sont présent (durée, taille sur le disque)
 */
void PlayListTableau::menuDetails(wxCommandEvent &WXUNUSED(event))
{
    wxCommandEvent evt(wxEVT_LISTE_DETAILS, GetId());
    GetParent()->GetEventHandler()->AddPendingEvent(evt);
}

/**
 * Supprime les lignes sélectionnées de la liste de lecture
 */
void PlayListTableau::SuppressionLigne()
{
    wxMutexLocker lock(*s_mutexMAJPlaylist);
    if (GetItemCount() == 0)
        return;

    #if DEBUG
    FichierLog::Get()->Ajouter(_T("PlayListTableau::SuppressionLigne - Début"));
    #endif
    long position = GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (position != -1 && GetItemCount() > 0)
    {
        if (GetSelectedItemCount() == 1 && !MusicManager::get().hasEfficientSearchedWord())
        {
            #if DEBUG
            FichierLog::Get()->Ajouter(_T("PlayListTableau::SuppressionLigne - 1 ligne"));
            #endif
            DeleteItem(position);
            for (size_t k = 0; k < m_ocurrenceLigne.GetCount(); k++)
            {
                if (m_ocurrenceLigne.Item(k) >= position)
                    m_ocurrenceLigne.Item(k)--;
            }
            MusicManager::get().deleteTitleAt(position);
        }
        else
        {
            //SetDoubleBuffered(true);
            long i = 0, j = 0, max = GetSelectedItemCount();

            #if DEBUG
            FichierLog::Get()->Ajouter(_T("PlayListTableau::SuppressionLigne - ") + wxString::Format(_T("%ld lignes"), max));
            #endif

            wxProgressDialog barProgre(_("Mise à jour"), _("Suppression en cours"), max);//
            wxString chemin;
            wxArrayString tableau;
            wxListItem item;

            tableau.Alloc(max);
            while (i < max)
            {
                j = GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
                item.SetId(j);
                item.SetColumn(6);
                item.SetMask(wxLIST_MASK_TEXT);
                GetItem(item);

                chemin = item.GetText();
                item.SetColumn(0);
                GetItem(item);
                chemin << wxFileName::GetPathSeparator() << item.GetText();

                tableau.Add(chemin);
                DeleteItem(j);
                i++;
                barProgre.Update(i);

                for (size_t k = 0; k < m_ocurrenceLigne.GetCount(); k++)
                {
                    if (m_ocurrenceLigne.Item(k) >= j)
                        m_ocurrenceLigne.Item(k)--;
                }
            }
            //SetDoubleBuffered(false);
            MusicManager::get().deleteTitles(tableau, false);
            tableau.Clear();
        }

        if (GetItemCount() == 0)
        {
            wxCommandEvent evt(wxEVT_VIDER_PANNEAU, GetId());
            GetParent()->GetEventHandler()->AddPendingEvent(evt);
        }
        else if (GetItemCount() > position)//Toujours avoir une ligne active
            SetItemState(position, wxLIST_STATE_FOCUSED|wxLIST_STATE_SELECTED, wxLIST_STATE_FOCUSED|wxLIST_STATE_SELECTED);
        else if (GetItemCount() >= 1)
            SetItemState(position-1, wxLIST_STATE_FOCUSED|wxLIST_STATE_SELECTED, wxLIST_STATE_FOCUSED|wxLIST_STATE_SELECTED);
        GestPeriph::Get()->MAJPlaylist();
        SetFocus();
    }
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("PlayListTableau::SuppressionLigne - Fin"));
    #endif
}

/** @brief Event - Adds a music line in the list
 *
 * @param event an event
 * @return void
 *
 */
void PlayListTableau::onUpdateLine(wxCommandEvent& event)
{
    const int position = event.GetInt();
    std::vector<Music*>::iterator iter = MusicManager::get().getSearchedOrAllMusics().begin() + position;
    addLineThread(**iter, position);
}

