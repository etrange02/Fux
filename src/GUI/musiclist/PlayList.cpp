/***************************************************************
 * Name:      PlayList.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2009-12-17
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "../../../include/gui/musiclist/PlayList.h"
#include "MusicManagerSwitcher.h"

/**
 * @class PlayList
 * @brief Page contenant la liste de lecture et une description détaillée des titres
 */

BEGIN_EVENT_TABLE(PlayList, wxPanel)
    EVT_BUTTON(ID_PAGE_PLAYLIST_BOUTON_ENREGISTRE_M3U, PlayList::EnregistrerM3U)
    EVT_COLLAPSIBLEPANE_CHANGED(ID_PAGE_PLAYLIST_PANNEAUREPLIABLE, PlayList::OnPanneau)
    EVT_LIST_ITEM_FOCUSED(ID_PAGE_PLAYLIST_LISTE,   PlayList::OnAfficheDetails)
    EVT_BUTTON(ID_PAGE_PLAYLIST_BOUTON_APPLIQUER,   PlayList::OnAppliquerTAG)
    EVT_BUTTON(ID_PAGE_PLAYLIST_BOUTON_ANNULER,     PlayList::OnAnnulerTAG)
    EVT_VIDER_PANNEAU(ID_PAGE_PLAYLIST_LISTE,       PlayList::EvtViderPanneauTAG)
    EVT_IMAGE_SELECTION(ID_PAGE_PLAYLIST_POCHETTE,  PlayList::EvtImage)
    EVT_LISTE_DETAILS(ID_PAGE_PLAYLIST_LISTE,       PlayList::FenetreDetails)
    EVT_MOUSE_EVENTS(PlayList::MouseEvents)
    //EVT_SEARCHCTRL_SEARCH_BTN(ID_PAGE_PLAYLIST_CHAMPS_RECHERCHE_LOCALE, PlayList::RechercheListeLecture)
    //EVT_SEARCHCTRL_CANCEL_BTN(ID_PAGE_PLAYLIST_CHAMPS_RECHERCHE_LOCALE, PlayList::)
    EVT_TEXT(ID_PAGE_PLAYLIST_CHAMPS_RECHERCHE_LOCALE, PlayList::RechercheListeLecture)
    EVT_TEXT_ENTER(ID_PAGE_PLAYLIST_CHAMPS_RECHERCHE_LOCALE, PlayList::RechercheListeLecture)
END_EVENT_TABLE()

/**
 * Constructeur
 * @see Creer
 */
PlayList::PlayList()
{
}

/**
 * Destructeur
 */
PlayList::~PlayList()
{
    delete m_liste;
    #if DEBUG
        FichierLog::Get()->Ajouter(_T("PlayList::~PlayList"));
    #endif
}

/**
 * Retourne l'instance de la liste que gère la page
 * @return le liste gérée par la page
 */
PlayListTableau* PlayList::GetPlayListTableau()
{    return m_liste;}

/**
 * Crée les composants graphiques de la page
 * @param Parent un pointeur sur la fenêtre parente
 */
void PlayList::Initialize(wxWindow *Parent)
{
    Create(Parent);
    sizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(sizer);

    wxSizer *sizerHorizRecherche = new wxBoxSizer(wxHORIZONTAL);
    m_champsRecherche = new wxSearchCtrl(this, ID_PAGE_PLAYLIST_CHAMPS_RECHERCHE_LOCALE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    m_champsRecherche->SetDescriptiveText(_T("Faire une recherche dans la liste courante..."));
    m_BoutonEnregistrerM3U = new wxButton(this, ID_PAGE_PLAYLIST_BOUTON_ENREGISTRE_M3U, _("Enregistrer la liste de lecture"));
    m_BoutonEnregistrerM3U->SetToolTip(_("Enregistre la liste de lecture au format m3u"));
    sizerHorizRecherche->Add(m_champsRecherche, 1, wxRIGHT|wxEXPAND, 5);
    sizerHorizRecherche->Add(m_BoutonEnregistrerM3U, 0, 0, 0);

    m_liste = new PlayListTableau(this);

    m_panneauRepliable = new wxCollapsiblePane(this, ID_PAGE_PLAYLIST_PANNEAUREPLIABLE, _("Détails"), wxDefaultPosition, wxDefaultSize, wxCP_NO_TLW_RESIZE | wxALWAYS_SHOW_SB);
    m_sizerRep = new wxBoxSizer(wxHORIZONTAL);
    m_sizerPann = new wxFlexGridSizer(3, 4, 1, 1);
    m_sizerBouton = new wxBoxSizer(wxVERTICAL);

    wxWindow *win = m_panneauRepliable->GetPane();
    m_pochette = new ImagePochetteMusique(win, ID_PAGE_PLAYLIST_POCHETTE, POCHETTE_COTE, POCHETTE_COTE, true);
    m_pochette->SetSize(wxSize(POCHETTE_COTE, POCHETTE_COTE));
    m_pochette->AfficheImage(true);
    m_sizerRep->Add(m_pochette, 0, wxALL, 5);

    m_sizerRep->Add(m_sizerPann, 1, wxALL|wxEXPAND, 0);
    m_sizerRep->Add(m_sizerBouton, 0, wxALL|wxEXPAND, 0);//

    m_sizerPann->AddGrowableCol(1, 1);
    m_sizerPann->AddGrowableCol(3, 1);

    m_sizerPann->Add(new wxStaticText(win, wxID_ANY, _("Nom")), 1, wxGROW | wxALL, 5);
    m_BoiteNom = new wxTextCtrl(win, wxID_ANY, _T(""));
    //m_BoiteNom->SetMinSize(wxSize(200, 21));
    m_sizerPann->Add(m_BoiteNom, 1, wxGROW | wxALL | wxEXPAND, 5);

    m_sizerPann->Add(new wxStaticText(win, wxID_ANY, _("Titre")), 1, wxGROW | wxALL, 5);
    m_BoiteTitre = new wxTextCtrl(win, wxID_ANY, _T(""));
    //m_BoiteTitre->SetMinSize(wxSize(200, 21));
    m_sizerPann->Add(m_BoiteTitre, 1, wxGROW | wxALL | wxEXPAND, 5);

    m_sizerPann->Add(new wxStaticText(win, wxID_ANY, _("Artiste")), 1, wxGROW | wxALL, 5);
    m_BoiteArtiste = new wxTextCtrl(win, wxID_ANY, _T(""));
    m_sizerPann->Add(m_BoiteArtiste, 1, wxGROW | wxALL | wxEXPAND, 5);

    m_sizerPann->Add(new wxStaticText(win, wxID_ANY, _("Genre")), 1, wxGROW | wxALL, 5);
    m_BoiteGenre = new wxTextCtrl(win, wxID_ANY, _T(""));
    m_sizerPann->Add(m_BoiteGenre, 1, wxGROW | wxALL | wxEXPAND, 5);

    m_sizerPann->Add(new wxStaticText(win, wxID_ANY, _("Album")), 1, wxGROW | wxALL, 5);
    m_BoiteAlbum = new wxTextCtrl(win, wxID_ANY, _T(""));
    m_sizerPann->Add(m_BoiteAlbum, 1, wxGROW | wxALL | wxEXPAND, 5);

    m_sizerPann->Add(new wxStaticText(win, wxID_ANY, _("Année")), 1, wxGROW | wxALL, 5);
    m_BoiteAnnee = new wxSpinCtrl(win, wxID_ANY, _T(""));
    m_BoiteAnnee->SetRange(0, 3000);
    m_sizerPann->Add(m_BoiteAnnee, 1, wxGROW | wxALL | wxEXPAND, 5);

    m_BoutonSauver = new wxButton(win, ID_PAGE_PLAYLIST_BOUTON_APPLIQUER, _("Enregistrer"));
    m_BoutonAnnuler = new wxButton(win, ID_PAGE_PLAYLIST_BOUTON_ANNULER, _("Annuler"));
    m_sizerBouton->Add(m_BoutonSauver, 1, wxALL, 5);
    m_sizerBouton->Add(m_BoutonAnnuler, 1, wxBOTTOM | wxLEFT | wxRIGHT, 5);

    win->SetSizer(m_sizerRep);

    sizer->Add(sizerHorizRecherche, 0, wxUP | wxRIGHT | wxLEFT | wxEXPAND, 5);
    sizer->Add(m_liste, 1, wxUP | wxDOWN | wxLEFT | wxEXPAND, 5);
    sizer->Add(m_panneauRepliable, 0, wxGROW | wxDOWN | wxLEFT | wxRIGHT, 1);
    sizer->Layout();
}

/**
 * Évènement - Affiche une boîte de dialogue pour enregistrer la liste de lecture dans un fichier .m3u
 */
void PlayList::EnregistrerM3U(wxCommandEvent &WXUNUSED(event))
{
    DialogEnregistreM3U *fen = new DialogEnregistreM3U(this, wxID_ANY, wxEmptyString);
    fen->Creer();
    bool modif = true;

    if (fen->ShowModal() == wxID_OK)
    {
        if (fen->GetName().IsEmpty())
            return;

        if (wxFileExists(fen->GetChemin()))
        {
            wxMessageDialog assertDialog(NULL, _("Fichier déjà existant. Souhaitez-vous le remplacer ?"), _("Fichier déjà existant"), wxYES_NO|wxICON_QUESTION|wxCENTRE|wxYES_DEFAULT);
            if (assertDialog.ShowModal() != wxID_YES)
                modif = false;
        }
        else if (!wxDir::Exists(Parametre::Get()->getRepertoireParametre(_T("Play_list_M3U"))))
            return;
        if (modif)
        {
            if (!MusicManagerSwitcher::getSearch().saveMusicListIntoFile(fen->GetChemin()))
            {
                wxLogError(_("Erreur dans le nom.\nVérifiez que vous utilisez des caractères autorisés."), _("Erreur"));
                return;
            }
            else
            {
                if (!fen->GetCheminRaccourci().IsEmpty() && !wxFileExists(fen->GetCheminRaccourci()))
                {
                    if (!CreationRaccourci(fen->GetCheminRaccourci(), fen->GetChemin()))
                    {
                        wxLogMessage(_("Echec de la création du raccourci."));
                    }
                }
            }
        }
    }
    fen->CallPanel();
    delete fen;
}

/**
 * Évènement - Lors de l'ouverture/fermeture du panneau, redimensionne le sizer de la page
 */
void PlayList::OnPanneau(wxCollapsiblePaneEvent &WXUNUSED(event))
{    sizer->Layout();}

/**
 * Event - Called when a line is selected in the play list
 */
void PlayList::OnAfficheDetails(wxListEvent &event)
{
    RemplirPanneauTAG(event.GetIndex());
}

/**
 * Évènement - Applique les les modifications des TAGs au fichier sélectionné
 */
void PlayList::OnAppliquerTAG(wxCommandEvent &WXUNUSED(event))
{
    int position = m_liste->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (position < 0)
        return;

    if (MusicManagerSwitcher::getSearch().getMusics().size() <= position)
        return;

    Music* music = fux::music::Factory::createMusic(*MusicManagerSwitcher::getSearch().getMusics().at(position));

    music->SetAlbum(m_BoiteAlbum->GetValue());
    music->SetName(m_BoiteNom->GetValue());
    music->SetArtists(m_BoiteArtiste->GetValue());
    music->SetTitle(m_BoiteTitre->GetValue());
    music->SetGenres(m_BoiteGenre->GetValue());
    music->SetYear(m_BoiteAnnee->GetValue());

    MusicManagerSwitcher::getSearch().updateMusicContent(position, music);
}

/**
 * Évènement - Remet les TAGs à leur valeur d'origine ie ceux dans le fichier
 */
void PlayList::OnAnnulerTAG(wxCommandEvent &WXUNUSED(event))
{
    long itemPosition = m_liste->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (0 > itemPosition) // ==> -1
    {
        ViderPanneauTAG();
    }
    else
    {
        RemplirPanneauTAG(itemPosition);
    }
}

/**
 * Efface tous les champs
 */
void PlayList::ViderPanneauTAG()
{
    m_BoiteNom->ChangeValue(wxEmptyString);//Nom du fichier
    m_BoiteArtiste->ChangeValue(wxEmptyString);//Artiste
    m_BoiteAlbum->ChangeValue(wxEmptyString);//Album
    m_BoiteTitre->ChangeValue(wxEmptyString);//Titre
    m_BoiteAnnee->SetValue(0);//Année
    m_BoiteGenre->ChangeValue(wxEmptyString);//Genre
    m_pochette->AfficheImage(false);
}

/**
 * Fill fields with music data
 * @param musicPosition a music position
 */
void PlayList::RemplirPanneauTAG(int musicPosition)
{
    std::vector<Music*>::iterator iter = MusicManagerSwitcher::getSearch().getMusics().begin() + musicPosition;
    RemplirPanneauTAG(**iter);
    m_sizerRep->Layout();
}

/**
 * Fill fields with music data
 * @param music a music
 */
void PlayList::RemplirPanneauTAG(IMusic& music)
{
    m_BoiteNom->ChangeValue(music.GetName());//Nom du fichier
    m_BoiteArtiste->ChangeValue(music.GetArtists());//Artiste
    m_BoiteAlbum->ChangeValue(music.GetAlbum());//Album
    m_BoiteTitre->ChangeValue(music.GetTitle());//Titre
    m_BoiteAnnee->SetValue(music.GetStringYear());
    m_BoiteGenre->ChangeValue(music.GetGenres());//Genre

    if (music.HasRecordSleeve())
    {
        m_pochette->SetImage(*music.GetRecordSleeve());
        m_pochette->AfficheImage(true);
    }
    else
    {
        m_pochette->AfficheImage(false);
    }
}

/**
 * Évènement - Efface tous les champs
 */
void PlayList::EvtViderPanneauTAG(wxCommandEvent &WXUNUSED(event))
{
    ViderPanneauTAG();
}

/**
 * Évènement - Appelé lors du changement de la pochette du titre. L'enregistrement dans le fichier se fait automatiquement
 */
void PlayList::EvtImage(wxCommandEvent &event)
{
    long position = m_liste->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (0 > position) // ==> -1
        return;

    if (MusicManagerSwitcher::getSearch().getMusics().size() <= position)
        return;

    Music* music = fux::music::Factory::createMusic(*MusicManagerSwitcher::getSearch().getMusics().at(position));

    music->SetRecordSleeve(&m_pochette->GetImage());
    MusicManagerSwitcher::getSearch().updateMusicContent(position, music);
}

/**
 * Évènement - Affiche une fenêtre détaillant les propriétés du titre
 */
void PlayList::FenetreDetails(wxCommandEvent &WXUNUSED(event))
{
    int position = m_liste->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (position < 0)
        return;

    if (MusicManagerSwitcher::getSearch().getMusics().size() <= position)
        return;

    Music* music = MusicManagerSwitcher::getSearch().getMusics().at(position);

    if (NULL == music)
        return;
    DialogTagMP3 dialog(this, -1, *music);
    dialog.Layout();

    bool mustChange = (wxID_OK == dialog.ShowModal());
    mustChange &= dialog.isModified();

    if (mustChange)
        MusicManagerSwitcher::getSearch().updateMusicContent(position, dialog.getResult());
}

/**
 * Évènement Souris -
 */
void PlayList::MouseEvents(wxMouseEvent &event)
{
    if (event.ControlDown() && event.GetWheelRotation() != 0)
    {
        if (event.GetWheelRotation() < 0)
            MusicManagerSwitcher::getSearch().playNextMusic();
        else
            MusicManagerSwitcher::getSearch().playPreviousMusic();
    }
    else if (event.AltDown() && event.GetWheelRotation() != 0)
    {
        if (event.GetWheelRotation() < 0)
            SliderSon::Get()->SonUp();
        else
            SliderSon::Get()->SonDown();
    }
    else
        event.Skip();
}

void PlayList::RechercheListeLecture(wxCommandEvent &WXUNUSED(event))
{
    MusicManagerSwitcher::getSearch().setSearchWord(m_champsRecherche->GetValue());
    m_liste->MAJ();
}

