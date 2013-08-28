/***************************************************************
 * Name:      PlayListTableau.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2010-08-22
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../../include/GUI/PlayList.h"

using namespace TagLib;

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
    m_rechercheEnCours = false;
    m_modeRecherche = false;

    InsertColumn(0,_("Nom"),wxLIST_FORMAT_CENTER, 280);
    InsertColumn(1,_("Artiste"),wxLIST_FORMAT_LEFT, 150);
    InsertColumn(2,_("Album"),wxLIST_FORMAT_LEFT, 150);
    InsertColumn(3,_("Titre"),wxLIST_FORMAT_LEFT, 150);
    InsertColumn(4,_("Durée"),wxLIST_FORMAT_LEFT, 50);
    InsertColumn(5,_("Année"),wxLIST_FORMAT_LEFT, 50);
    InsertColumn(6,_("Emplacement"),wxLIST_FORMAT_LEFT, 280);
    InsertColumn(7,_("Genre"),wxLIST_FORMAT_LEFT, 80);
    InsertColumn(8,_("Ext."),wxLIST_FORMAT_LEFT, 50);

    SetDropTarget(new DnDCible(this));
    //DragAcceptFiles(true);

    m_menu = new wxMenu;
    m_menu->Append(ID_PAGE_PLAYLIST_MENU_LECTURE, _("Lire"));
    m_menu->Append(ID_PAGE_PLAYLIST_MENU_PAUSE, _("Pause"));
    m_menu->Append(ID_PAGE_PLAYLIST_MENU_SUPPRIMER, _("Effacer"));
    m_menu->Append(ID_PAGE_PLAYLIST_MENU_COUPER, _("Déplacer"));
    m_menu->Append(ID_PAGE_PLAYLIST_MENU_COLLER, _("Déposer"));
    m_menu->Append(ID_PAGE_PLAYLIST_MENU_DETAILS, _("Détails"));
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

    if(m_modeRecherche)
    {
        s_mutexMAJPlaylist->Unlock();
        RechercheElargie(m_motRecherche);
        return;
    }

    #if DEBUG
    FichierLog::Get()->Ajouter(_T("PlayListTableau::MAJ - Début après les tests"));
    #endif

    wxString chaine, extrait;
    int pos = 1;

    if (GetSelectedItemCount() > 0)
        extrait = GetItemText(GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED));

    long ligneVisible = 0;
    if (GetItemCount() >= GetCountPerPage())
        ligneVisible = GetTopItem() + GetCountPerPage()-1;

    DeleteAllItems();

    wxTextFile fichier(FichierListe::Get()->GetCheminListe());
    if (!fichier.Open())
    {
        return;
    }

    if (fichier.GetLineCount() == 0)
    {
        fichier.Close();
        return;
    }

    #if DEBUG
    FichierLog::Get()->Ajouter(_T("PlayListTableau::MAJ - Début du for"));
    #endif

    size_t j=0;
    for (j=0; j<fichier.GetLineCount(); j++)
    {
        chaine = fichier.GetLine(j);
        //i = chaine.Find(wxFileName::GetPathSeparator(), true);

        pos = GetItemCount();
        //pos = InsertItem(pos, chaine.Right(chaine.Length()-i-1));//Nom du fichier
        pos = InsertItem(pos, chaine.AfterLast(wxFileName::GetPathSeparator()));//Nom du fichier

        SetItem(pos, 6, chaine.BeforeLast(wxFileName::GetPathSeparator()));
        //SetItem(pos, 6, chaine.Left(i));//Emplacement
        SetItem(pos, 8, chaine.AfterLast('.'));//Extension
        if (pos%10 == 5)
            wxApp::GetInstance()->Yield(false);
    }
    fichier.Close();
    //wxYield();

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

    TagLib::FileRef chansonTAG;
    wxListItem item;
    for (int k=0; k<GetItemCount(); k++)
    {
        //chaine = fichier.GetLine(j);

        item.SetId(k);
        item.SetColumn(6);
        item.SetMask(wxLIST_MASK_TEXT);
        GetItem(item);
        chaine = item.GetText();

        item.SetColumn(0);
        GetItem(item);
        chaine << wxFileName::GetPathSeparator() << item.GetText();

        pos = k;//GetItemCount();

        if (wxFileExists(chaine))
        {
            chansonTAG = TagLib::FileRef(TagLib::FileName(chaine.fn_str()));//
            BDDRequete *req = new BDDRequete(this);
            wxString annee;

            if (Parametre::Get()->isID3V2(chaine.AfterLast('.').Lower()) && chansonTAG.file()->isValid())
            {

                SetItem(pos, 3, wxString(chansonTAG.tag()->title().toCString(true), wxConvUTF8));//Titre
                SetItem(pos, 4, GetDuree(chansonTAG.audioProperties()->length()));//Durée

                if (chansonTAG.tag()->year() != 0)
                {
                    annee << chansonTAG.tag()->year();// = an;
                    SetItem(pos, 5, annee);//Année
                }
                else
                    SetItem(pos, 5, _T("?"));

                SetItem(pos, 7, wxString(chansonTAG.tag()->genre().toCString(true), wxConvUTF8));//Genre
                req->AjouterChanson(chaine, annee, wxString(chansonTAG.tag()->genre().toCString(true), wxConvUTF8));

                SetItem(pos, 1, wxString(chansonTAG.tag()->artist().toCString(true), wxConvUTF8));//Artiste
                req->AjouterArtiste(wxString(chansonTAG.tag()->artist().toCString(true), wxConvUTF8));
                /*if (!chansonTAG.tag()->artist().isEmpty())
                    req->AjouterArtiste(chansonTAG.tag()->artist().toCString());*/

                SetItem(pos, 2, wxString(chansonTAG.tag()->album().toCString(true), wxConvUTF8));//Album
                //req->AjouterAlbum(chaine, chansonTAG.tag()->album().toCString(true));
            }
            else
            {
                req->AjouterChanson(chaine, _T(""), _T(""));
                SetItem(pos, 5, _T("?"));
            }

            if (pos%10 == 5)
                wxApp::GetInstance()->Yield(false);
            BDDThread::Get()->AjouterRequete(req);
        }
        else
        {
            SetItem(pos, 1, _("Erreur,"));//Artiste
            SetItem(pos, 2, _("fichier"));//Album
            SetItem(pos, 3, _("introuvable !"));//Titre
            SetItemTextColour(pos, wxColor(255, 255, 255));
            SetItemBackgroundColour(pos, wxColor(255, 0, 0));
        }
    }
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("PlayListTableau::MAJ - Fin du for : ") + wxString::Format(_T("%u / %u"), j, GetItemCount()));
    #endif
    //wxApp::GetInstance()->Yield(false);
    this->ChangementChanson(Musique::Get()->GetNomPos());
    //Musique::Get()->GetNomPos();

    #if DEBUG
    FichierLog::Get()->Ajouter(_T("PlayListTableau::MAJ - Fin"));
    #endif
}

/**
 * Transforme un temps en seconde en chaine de caractère
 * @param temps le temps en secondes
 * @return la chaine nouvellement formée
 */
wxString PlayListTableau::GetDuree(int temps)
{
    wxString chaine;
    chaine << temps/60 << _T(":");
    if (temps%60 < 10)
        chaine << _T("0") << temps%60;
    else
        chaine << temps%60;
    return chaine;
}

/**
 * Évènement. Informe l'application que le titre en cours de lecture doit changer
 */
void PlayListTableau::ChansonActive(wxListEvent &event)
{
    if (m_modeRecherche)
    {
        //GetItemText(event.GetIndex());
        wxListItem item;
        item.SetId(event.GetIndex());
        item.SetColumn(6);
        item.SetMask(wxLIST_MASK_TEXT);
        GetItem(item);

        wxString chemin = item.GetText();
        item.SetColumn(0);
        GetItem(item);
        chemin << wxFileName::GetPathSeparator() << item.GetText();
        Musique::Get()->ChangementChanson(-1, chemin);
    }
    else
    {
        if (!Musique::Get()->ChangementChanson(event.GetIndex(), _T("")))
            MAJ();
    }
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
            Musique::Get()->ChangementChanson(SUIVANT);
        else
            Musique::Get()->ChangementChanson(PRECEDENT);
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

            wxLogMessage(wxString::Format(_T("sur année %d, %d %d"), GetColumnWidth(5), pt.x, pt.y));
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
        if (titre.GetNom().EndsWith(extrait) && (i == titre.GetPos() || titre.GetPos() == -1 || m_modeRecherche))
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
void PlayListTableau::ChangementChanson(ChansonNomPos titre)
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("PlayListTableau::ChangementChanson(ChansonNomPos)"));
    #endif
    if (titre.GetPos() == -1 && (GetItemCount() == 0 || titre.GetNom().IsEmpty()))
        return;
    if (m_ocurrenceLigne.GetCount())
    {
        for (size_t i = 0; i < m_ocurrenceLigne.GetCount(); i++)
        {
            SetItemTextColour(m_ocurrenceLigne.Item(i), wxColor(0, 0, 0));
            SetItemBackgroundColour(m_ocurrenceLigne.Item(i), wxColor(255, 255, 255));
        }
        m_ocurrenceLigne.Empty();
    }
    int max = GetItemCount();
    m_positionChanson = -1;

    for (int i = 0; i < max; i++)
    {
        if (titre.GetNom() == GetItemText(i))
        {
            m_ocurrenceLigne.Add(i);
            if (titre.GetPos() == i && !m_modeRecherche)//La couleur orange perd son sens lorsqu'il y a une recherche locale
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
    wxMutexLocker lock(*s_mutexMAJPlaylist);
    if (m_modeRecherche)
        return;

    long item = -1;
    DnDListeFichier* transfile = new DnDListeFichier();

    item = GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    while (item != -1)
    {
        transfile->AddFile(wxString::Format(_T("%ld"), item));
        //transfile->AddFile(Musique::Get()->GetFichier()->GetNomPosition(item));
        item = GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    }
    if (transfile->GetCount() == 0)  // Si aucun fichier détruire l'instance et sortir
    {
        delete transfile;
        return;
    }

    DnDBufferData UploadData(transfile);   // Créer un objet de manipulation de données

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
        if (Musique::Get()->GetLecture())//En lecture
            m_menu->SetLabel(ID_PAGE_PLAYLIST_MENU_PAUSE, _("Pause"));
        else
            m_menu->SetLabel(ID_PAGE_PLAYLIST_MENU_PAUSE, _("Reprendre"));
    }
    else if (GetItemCount() > 0)//L'élément sélectionné n'est pas en lecture
    {
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_LECTURE, true);
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_PAUSE, true);
        if (Musique::Get()->GetLecture())//En lecture
            m_menu->SetLabel(ID_PAGE_PLAYLIST_MENU_PAUSE, _("Pause"));
        else
            m_menu->SetLabel(ID_PAGE_PLAYLIST_MENU_PAUSE, _("Reprendre"));
    }
    else//Liste vierge
    {
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_LECTURE, false);
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_PAUSE, false);
    }


    if (m_couper && !m_modeRecherche)
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
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_COUPER, !m_modeRecherche);// couper accessible si on est pas en recherche
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_SUPPRIMER, !m_modeRecherche);// idem
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
    if (m_modeRecherche)
    {
        wxListItem item;
        item.SetId(pos);
        item.SetColumn(6);
        item.SetMask(wxLIST_MASK_TEXT);
        GetItem(item);

        wxString chemin = item.GetText();
        item.SetColumn(0);
        GetItem(item);
        chemin << wxFileName::GetPathSeparator() << item.GetText();
        Musique::Get()->ChangementChanson(-1, chemin);
    }
    else
    {
        if (!Musique::Get()->ChangementChanson(pos, _T("")))
            MAJ();
    }
}

/**
 * Évènement. Met en pause ou reprend la l'écoute
 */
void PlayListTableau::menuPause(wxCommandEvent &WXUNUSED(event))
{
    if (Musique::Get()->GetLecture())
        Musique::Get()->SetPause(true);
    else if (Musique::Get()->GetPause())
        Musique::Get()->SetPause(false);
    else//Musique stoppée
        Musique::Get()->ChangementChanson(IDENTIQUE);
}

/**
 * Évènement. Supprime l'élément sélectionné de la liste
 */
void PlayListTableau::menuSupprimer(wxCommandEvent &WXUNUSED(event))
{    SuppressionLigne();}

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
    Musique::Get()->PlacerLigneInt(&m_tableauCouper, m_yMenu, true);
    m_tableauCouper.Clear();
    GestPeriph::Get()->MAJPlaylist();
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
 * Retourne la position du titre en cours dans le tableau
 * @return la position du titre
 */
int PlayListTableau::GetPositionChansonLecture()
{    return m_positionChanson;}

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
        if (GetSelectedItemCount() == 1 && !m_modeRecherche)
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
            Musique::Get()->SupprimerNom(position);
        }
        else
        {
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

                tableau.Add(chemin);//
                DeleteItem(j);
                i++;
                barProgre.Update(i);//Pulse();//

                for (size_t k = 0; k < m_ocurrenceLigne.GetCount(); k++)
                {
                    if (m_ocurrenceLigne.Item(k) >= j)
                        m_ocurrenceLigne.Item(k)--;
                }
            }
            Musique::Get()->SupprimerNom(&tableau);
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

void PlayListTableau::RechercheElargie(wxString chaine)
{
    wxMutexLocker lock(*s_mutexMAJPlaylist);
    m_rechercheEnCours = true;
    wxListItem item;
    size_t j = 0;
    int i = 0, pos = 1;

    wxTextFile fichier(FichierListe::Get()->GetCheminListe());
    if (!fichier.Open())
    {
        return;
    }
    if (fichier.GetLineCount() == 0)
    {
        fichier.Close();
        return;
    }

    m_motRecherche = chaine;

    m_motRecherche.MakeLower();
    wxString ligneFic, ligneTab, titre, duree, annee, genre, artiste, album;
    chaine.MakeLower();
    TagLib::FileRef chansonTAG;

    if (i<GetItemCount())
    {
        item.SetId(i);
        item.SetColumn(6);
        item.SetMask(wxLIST_MASK_TEXT);
        GetItem(item);
        ligneTab = item.GetText();
        item.SetColumn(0);
        GetItem(item);
        ligneTab << wxFileName::GetPathSeparator() << item.GetText();
    }

    while (m_rechercheEnCours && j<fichier.GetLineCount())
    {
        ligneFic = fichier.GetLine(j++);

        if (ligneFic.IsSameAs(ligneTab))//si la comparaison est positive entre fichier et ListCtrl, on charge la ligne suivante
        {
            item.SetId(i);
            item.SetColumn(1);
            item.SetMask(wxLIST_MASK_TEXT);
            GetItem(item);
            artiste = item.GetText();
            item.SetColumn(2);
            item.SetMask(wxLIST_MASK_TEXT);
            GetItem(item);
            album = item.GetText();
            item.SetColumn(3);
            item.SetMask(wxLIST_MASK_TEXT);
            GetItem(item);
            titre = item.GetText();
            item.SetColumn(4);
            item.SetMask(wxLIST_MASK_TEXT);
            GetItem(item);
            duree = item.GetText();
            item.SetColumn(5);
            item.SetMask(wxLIST_MASK_TEXT);
            GetItem(item);
            annee = item.GetText();
            item.SetColumn(7);
            item.SetMask(wxLIST_MASK_TEXT);
            GetItem(item);
            genre = item.GetText();


            if (ligneFic.Lower().Find(chaine) != wxNOT_FOUND
             || titre.Lower().Find(chaine) != wxNOT_FOUND
             || duree.Lower().Find(chaine) != wxNOT_FOUND
             || annee.Lower().Find(chaine) != wxNOT_FOUND
             || genre.Lower().Find(chaine) != wxNOT_FOUND
             || album.Lower().Find(chaine) != wxNOT_FOUND
             || artiste.Lower().Find(chaine) != wxNOT_FOUND
             || duree.Lower().Find(chaine) != wxNOT_FOUND)
                i++;
            else
            {
                DeleteItem(i);
                for (size_t k = 0; k < m_ocurrenceLigne.GetCount(); ++k)
                {
                    if (m_ocurrenceLigne.Item(k) == i)
                        m_ocurrenceLigne.RemoveAt(k);
                    else if (m_ocurrenceLigne.Item(k) > i)
                        m_ocurrenceLigne.Item(k)--;
                }
            }

            if (i<GetItemCount())
            {
                item.SetId(i);
                item.SetColumn(6);
                item.SetMask(wxLIST_MASK_TEXT);
                GetItem(item);
                ligneTab = item.GetText();
                item.SetColumn(0);
                GetItem(item);
                ligneTab << wxFileName::GetPathSeparator() << item.GetText();
            }
            else
                ligneTab.Clear();
        }
        else
        {
            //ajouter la ligne si tag oks
            chansonTAG = TagLib::FileRef(TagLib::FileName(ligneFic.fn_str()));
            if (chansonTAG.file()->isValid())
            {
                titre = wxString(chansonTAG.tag()->title().toCString(true), wxConvUTF8);
                duree = wxString(GetDuree(chansonTAG.audioProperties()->length()));
                if (chansonTAG.tag()->year() != 0)
                    annee << chansonTAG.tag()->year();
                else
                    annee << _T("?");
                genre = wxString(chansonTAG.tag()->genre().toCString(true), wxConvUTF8);
                artiste = wxString(chansonTAG.tag()->artist().toCString(true), wxConvUTF8);
                album = wxString(chansonTAG.tag()->album().toCString(true), wxConvUTF8);

                if (ligneFic.Lower().Find(m_motRecherche) != wxNOT_FOUND
                 || titre.Lower().Find(m_motRecherche) != wxNOT_FOUND
                 || duree.Lower().Find(m_motRecherche) != wxNOT_FOUND
                 || annee.Lower().Find(m_motRecherche) != wxNOT_FOUND
                 || genre.Lower().Find(m_motRecherche) != wxNOT_FOUND
                 || album.Lower().Find(m_motRecherche) != wxNOT_FOUND
                 || artiste.Lower().Find(m_motRecherche) != wxNOT_FOUND
                 || duree.Lower().Find(m_motRecherche) != wxNOT_FOUND)
                {
                    pos = InsertItem(i, ligneFic.AfterLast(wxFileName::GetPathSeparator()));
                    SetItem(pos, 1, artiste);
                    SetItem(pos, 2, album);
                    SetItem(pos, 3, titre);
                    SetItem(pos, 4, duree);
                    SetItem(pos, 5, annee);
                    SetItem(pos, 6, ligneFic.BeforeLast(wxFileName::GetPathSeparator()));
                    SetItem(pos, 7, genre);
                    SetItem(pos, 8, ligneFic.AfterLast('.'));

                    if (Musique::Get()->GetNomComplet().IsSameAs(ligneFic))
                    {
                        bool present = false;
                        size_t k = 0;
                        while (!present && k < m_ocurrenceLigne.GetCount())
                        {
                            if (m_ocurrenceLigne.Item(k))
                                present = true;
                            ++k;
                        }
                        if (!present)
                            m_ocurrenceLigne.Add(i);
                    }

                    for (size_t k = 0; k < m_ocurrenceLigne.GetCount(); ++k)
                    {
                        if (m_ocurrenceLigne.Item(k) > i)
                            m_ocurrenceLigne.Item(k)++;
                    }

                    ++i;
                    /*if (ligneFic.IsSameAs(ligneTab))
                    {
                        ++i;
                        if (i<GetItemCount())
                        {
                            item.SetId(i);
                            item.SetColumn(6);
                            item.SetMask(wxLIST_MASK_TEXT);
                            GetItem(item);
                            ligneTab = item.GetText();
                            item.SetColumn(0);
                            GetItem(item);
                            ligneTab << wxFileName::GetPathSeparator() << item.GetText();
                        }
                        else
                            ligneTab.Clear();
                    }*/
                }
            }
            //sinon, passer à la ligne suivante dans le fichier
        }
        if (j%2)
            wxApp::GetInstance()->Yield(false);
    }
    while (i<GetItemCount())
        DeleteItem(i++);
    fichier.Close();
    m_modeRecherche = !m_motRecherche.IsEmpty();
    ChangementChanson(Musique::Get()->GetNomPos());
}

void PlayListTableau::RecherchePrecise(wxString chaine)
{
    wxMutexLocker lock(*s_mutexMAJPlaylist);
    m_rechercheEnCours = true;
    m_modeRecherche = true;
    wxListItem item;
    int i = 0, k = 0;
    bool cont = true;
    m_motRecherche = chaine;

    m_motRecherche.MakeLower();
    SetDoubleBuffered(true);

    while (m_rechercheEnCours && i < GetItemCount())
    {
        k = 0;
        item.SetId(i);
        cont = true;
        while (k < GetColumnCount() && cont)
        {
            item.SetColumn(k++);
            item.SetMask(wxLIST_MASK_TEXT);
            GetItem(item);
            if (item.GetText().Lower().Find(m_motRecherche) != wxNOT_FOUND)
                cont = false;
        }
        if (cont)// l'élément doit être supprimé, il ne correspond pas à la recherche
        {
            DeleteItem(i);
            for (size_t k = 0; k < m_ocurrenceLigne.GetCount(); ++k)
            {
                if (m_ocurrenceLigne.Item(k) == i)
                    m_ocurrenceLigne.RemoveAt(k);
                else if (m_ocurrenceLigne.Item(k) > i)
                    m_ocurrenceLigne.Item(k)--;
            }
        }
        else
            i++;
        if ((i >= GetTopItem()) && i <= (GetTopItem()+GetCountPerPage()))// (++j)%5 == 2)
            wxApp::GetInstance()->Yield(false);
    }
    SetDoubleBuffered(false);
    wxApp::GetInstance()->Yield(false);
    m_modeRecherche = !m_motRecherche.IsEmpty();
    ChangementChanson(Musique::Get()->GetNomPos());
}

void PlayListTableau::StopRecherche()
{
    m_rechercheEnCours = false;
}

bool PlayListTableau::RechercheRunning()
{
    if (s_mutexMAJPlaylist->TryLock() != wxMUTEX_NO_ERROR)
        return true;
    s_mutexMAJPlaylist->Unlock();
    return false;
}

