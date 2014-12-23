/***************************************************************
 * Name:      Fenetre.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2009-07-24
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include "../../../include/gui/widgets/Fenetre.h"

/**
 * @class FuXFenetre
 * @brief Interface principale de l'application : barre de menu. Elle contient plusieurs wxSizer.
 */

BEGIN_EVENT_TABLE(FuXFenetre, wxFrame)
    EVT_MENU(ID_APP_BAR_QUITTER, FuXFenetre::EventQuit)
    EVT_MENU(ID_APP_BAR_LECTURE, FuXFenetre::EventMenuBarPlay)
    EVT_MENU(ID_APP_BAR_SUIVANT, FuXFenetre::EventMusicNext)
    EVT_MENU(ID_APP_BAR_PRECEDENT, FuXFenetre::EventMusicPrevious)
    EVT_MENU(ID_APP_BAR_STOP, FuXFenetre::EventMusicStop)
    EVT_MENU(ID_APP_BAR_REPETE, FuXFenetre::EventMusicRepete)
    EVT_MENU(ID_APP_BAR_ALEATOIRE, FuXFenetre::EventMusicRandomize)
    EVT_MENU(ID_APP_BAR_OUVRIR, FuXFenetre::EventOpenDialogToPlayMusic)
    EVT_MENU(ID_APP_BAR_CHARGER_M3U, FuXFenetre::EventOpenDialogToSelectPlayListFile)
    EVT_MENU(ID_APP_BAR_CREER_PLAYLIST, FuXFenetre::EventSavePlayList)
    EVT_MENU(ID_APP_BAR_SUPPRIMER, FuXFenetre::EventDeleteCurrentPlayingTitle)
    EVT_MENU(ID_APP_BAR_MAJ_PLAYLIST, FuXFenetre::EventUpdatePlayLists)
    EVT_MENU(ID_APP_BAR_A_PROPOS, FuXFenetre::MenuAbout)
    EVT_MENU(ID_APP_BAR_SITE_INTERNET, FuXFenetre::MenuSiteWeb)
    EVT_MENU(ID_APP_BAR_AIDE, FuXFenetre::MenuAide)
    EVT_MENU(ID_APP_BAR_COULEUR_PREFERENCE, FuXFenetre::AfficherPreferenceCouleur)
    EVT_MENU(ID_APP_BAR_SON_PREFERENCE, FuXFenetre::AfficherPreferenceSon)
    EVT_MENU(ID_APP_BAR_DEFAUT_PREFERENCE, FuXFenetre::AfficherPreferenceDefaut)
    EVT_BUTTON(ID_APP_AFF_BOUTON_PRECEDENT, FuXFenetre::EventMusicPrevious)//////////////////////
    EVT_BUTTON(ID_APP_AFF_BOUTON_SUIVANT, FuXFenetre::EventMusicNext)//////////////////////
    EVT_BUTTON(ID_APP_AFF_BOUTON_SUPPRIMER, FuXFenetre::EventDeleteCurrentPlayingTitle)//////////////////////
    EVT_BUTTON(ID_APP_AFF_BOUTON_LECTURE, FuXFenetre::EventMenuBarPlay)//////////////////////
    EVT_BUTTON(ID_APP_AFF_PRINCIPAL, FuXFenetre::AffichePrincipal)
    EVT_BUTTON(ID_APP_AFF_PREFERENCE, FuXFenetre::AffichePreference)
    EVT_BUTTON(ID_APP_AFF_EXTRACTEUR, FuXFenetre::AfficheEncodage)
    EVT_BUTTON(ID_APP_AFF_PLAYIST, FuXFenetre::AfficheListeDeLecture)
    EVT_BUTTON(ID_APP_AFF_MODULE_IPOD, FuXFenetre::AfficheGestPeriph)
    EVT_COMMAND_SCROLL(ID_APP_SLIDER_SON, FuXFenetre::EventUpdateMusicVolume)
    //EVT_MUSIQUE_CHANGE(wxID_ANY, FuXFenetre::EventMusicChanged)
    EVT_FUX_MUSICPLAYER_CHANGE_TITLE(wxID_ANY, FuXFenetre::EventMusicChanged)
    //EVT_MUSIQUE_MAJ(wxID_ANY, FuXFenetre::EventUpdatePlayLists)
    EVT_FUX_MUSICLIST_LIST_UPDATE(wxID_ANY, FuXFenetre::EventUpdatePlayLists)
    //EVT_MUSIQUE_LECTURE(wxID_ANY, FuXFenetre::EventSwitchButtonImage)
    EVT_FUX_MUSICPLAYER_CHANGE_STATUS(wxID_ANY, FuXFenetre::EventSwitchButtonImage)
    EVT_SERVEUR(wxID_ANY, FuXFenetre::EvtServeurAjout)
    //EVT_MUSIQUE_GRAPH(wxID_ANY, FuXFenetre::OnTitreChange)
    EVT_FUX_MUSICPLAYER_UPDATE_GRAPH(wxID_ANY, FuXFenetre::OnTitreChange)
    EVT_FUX_MUSICMANAGER_NO_FILE(wxID_ANY, FuXFenetre::EventNoMusic)

    EVT_MUSIQUE_SUPPRESSION(wxID_ANY, FuXFenetre::EventDeleteCurrentPlayingTitle)
    EVT_CHAR_HOOK(FuXFenetre::OnKeyDownRaccourci)
    EVT_BOUTON_FENETRE_DETACHABLE(wxID_ANY, FuXFenetre::SeparationPanel)
    EVT_FERMER_FENETRE_DETACHABLE(wxID_ANY, FuXFenetre::ReunionPanel)
END_EVENT_TABLE()

static wxMutex *s_mutexProtectionDemarrage = new wxMutex;

/**
 * Constructeur
 * @param argc Entier indiquant la taille du tableau
 * @param argv Tableau de caractères
 */
FuXFenetre::FuXFenetre(int argc, wxChar **argv) : wxFrame(NULL, wxID_ANY, _T("Fu(X) 2.0"))
{
    wxMutexLocker lock(*s_mutexProtectionDemarrage);
    m_FenetreActuel = PRINCIPAL;
    m_nouvelleFenetre = PRINCIPAL;
    sizerPrincipalH = new wxBoxSizer(wxHORIZONTAL);
    sizerGaucheV = new wxBoxSizer(wxVERTICAL);
    sizerPrincipalH->Add(sizerGaucheV, 0, wxALL | wxEXPAND, 0);
    m_MAJliste = false;

    MenuBarCreation();
    LeftSizerCreation();

    panelCreation();
    panelAssociation();

    SetSizer(sizerPrincipalH);
    sizerPrincipalH->SetSizeHints(this);

    readPreferences(argc <= 1);

    if (argc > 1)
    {
        wxFileName fichierMem(argv[1]);
        fichierMem.Normalize(wxPATH_NORM_SHORTCUT);
        if (fichierMem.GetExt().Lower() == _T("m3u"))
        {
            wxTextFile test(fichierMem.GetFullPath()); test.Open();
            if (test.IsOpened())
            {
                if (test.GetLineCount() > 1)
                {
                    //Musique::Get()->Lecture(test.GetLine(1));
                    MusicManager::get().parse(fichierMem.GetFullPath());
                    m_MAJliste = true;
                }
                else wxLogMessage(_("Impossible de charger le fichier, celui-ci est vierge !"));
                test.Close();
            }
        }
        else if (Parametre::Get()->islisable(fichierMem.GetExt().Lower()))
        {
            /*Musique::Get()->Lecture(fichierMem.GetFullPath());
            Musique::Get()->Listage();*/
            MusicManager::get().playMusicThenParse(fichierMem.GetFullPath());
            m_MAJliste = true;
        }
    }

    SetIcon(wxIcon(Parametre::Get()->getRepertoireExecutableLib(_T("play.ico")), wxBITMAP_TYPE_ICO));

    if (m_MAJliste)
        m_playList->GetPlayListTableau()->MAJ();

    SwitchWindow();
    m_serveur = new TCPServeur(this);
    if (!m_serveur->Create(IPC_SERVICE))
    {
        wxLogMessage(_T("Impossible d'initialiser le serveur"));
    }

    m_fenetresDetachables = new ArrayFenetreDetachable();
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("Fin de FuXFenetre::FuXFenetre(int argc, wxChar **argv)"));
    #endif
}

/**
 * Destructeur
 */
FuXFenetre::~FuXFenetre()
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::~FuXFenetre - début"));
    #endif
    m_fenetresDetachables->Vider();
    delete m_fenetresDetachables;
    delete m_serveur;
    BDDThread::Get()->Stop();
    m_TimerGraph.Stop();
    delete[] m_imageBouton;
//    Musique::Get()->Delete();
    GestPeriph::Get()->Delete();
    delete m_musiqueGraph;
    delete m_playList;
    delete m_panelsAssocies;
    delete m_pageCouleur;
    delete m_pageDefaut;
    delete m_pageSon;
    #if DEBUG
//    FichierLog::Get()->Ajouter(_T("FuXFenetre::~FuXFenetre - fin"));
    #endif
}

/// Initialization methods ///


/**
 * Initialise les instances des classes nécessaire au lancement de Fu(X)
 */
void FuXFenetre::panelCreation()
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("Début de FuXFenetre::Initialisation"));
    #endif

    int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};
    MusicManager::get().setParent(this);
    m_musiqueGraph = new MusiqueGraph(this, args);
    m_playList = new PlayList;
    //FichierListe::Get();
    BDDThread::Get();



    #if DEBUG
    FichierLog::Get()->Ajouter(_T("Fin de FuXFenetre::Initialisation"));
    #endif
}

/**
 * Attache les panels à la fenêtre principal
 */
void FuXFenetre::panelAssociation()
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::CreerPages() - Création des onglets et des pages manquantes"));
    #endif

    sizerDroitPrincipal = new wxBoxSizer(wxVERTICAL);
    m_TimerGraph.Start(40, false);

    sizerDroitPrincipal->Add(m_musiqueGraph, 1, wxEXPAND, 0);
    sizerDroitPrincipal->Show(m_musiqueGraph);
    sizerDroitPrincipal->Layout();
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::CreerPages() - Graphe"));
    #endif
    ///////////////////////////////////////////////////////
    sizerDroitPreference = new wxBoxSizer(wxVERTICAL);

    m_notebookPreference = new wxNotebook(this, -1);
    m_pageCouleur = new PreferenceCouleur(m_notebookPreference, -1);
    m_pageSon = new PreferenceSon(m_notebookPreference, -1);
    m_pageDefaut = new PreferenceDefaut(m_notebookPreference, -1, m_pageCouleur, m_pageSon);

    m_notebookPreference->AddPage(m_pageCouleur, _("Couleur"));
    m_notebookPreference->AddPage(m_pageSon, _("Son"));
    m_notebookPreference->AddPage(m_pageDefaut, _("Défaut"));

    sizerDroitPreference->Add(m_notebookPreference, 1, wxEXPAND, 0);
    sizerDroitPreference->Show(m_notebookPreference);
    sizerDroitPreference->Layout();
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::CreerPages() - Préférences"));
    #endif
    //////////////////////////////////////////////////////////////
    sizerDroitExtracteur = new wxBoxSizer(wxVERTICAL);
    wxButton *bouton2 = new wxButton(this, wxID_ANY, _("Extraction indisponible pour le moment"));

    sizerDroitExtracteur->Add(bouton2, 1, wxALL | wxEXPAND, 0);
    sizerDroitExtracteur->Show(bouton2);
    sizerDroitExtracteur->Layout();
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::CreerPages() - Extraction"));
    #endif
    /////////////////////////////////////////////////////////////
    sizerDroitPlayist = new wxBoxSizer(wxVERTICAL);
    m_playList->Initialize(this, m_MAJliste);

    //m_grille = new PlayListGrille(this);
    sizerDroitPlayist->Add(m_playList, 1, wxALL | wxEXPAND, 0);
    sizerDroitPlayist->Show(m_playList);

    sizerDroitPlayist->Layout();
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::CreerPages() - Playlist"));
    #endif
    ////////////////////////////////////////////////////////////////////
    sizerDroitIPod = new wxBoxSizer(wxVERTICAL);
    GestPeriph::Get()->Creer(this);

    sizerDroitIPod->Add(GestPeriph::Get(), 1, wxALL | wxEXPAND, 0);
    sizerDroitIPod->Show(GestPeriph::Get());
    sizerDroitIPod->Layout();
    //////////////////////////////////////////////////////////////////////

    sizerDroit = new wxBoxSizer(wxVERTICAL);
    sizerDroit->SetMinSize(512, 256);
    sizerPrincipalH->Add(sizerDroit, 1, wxALL | wxEXPAND, 0);

    sizerDroit->Add(sizerDroitPrincipal, 1, wxALL | wxEXPAND, 0);
    sizerDroit->Add(sizerDroitPreference, 1, wxALL | wxEXPAND, 0);//2
    sizerDroit->Add(sizerDroitExtracteur, 1, wxALL | wxEXPAND, 0);
    sizerDroit->Add(sizerDroitPlayist, 1, wxALL | wxEXPAND, 0);
    sizerDroit->Add(sizerDroitIPod, 1, wxALL | wxEXPAND, 0);

    m_panelsAssocies = new bool[5];// {true, true, true, true, true};
    for (int i = 0; i < 5 ; i++){m_panelsAssocies[i] = true;}


    sizerDroitPrincipal->SetMinSize(512, 292);
    sizerDroitPreference->SetMinSize(512, 292);
    sizerDroitExtracteur->SetMinSize(512, 292);
    sizerDroitPlayist->SetMinSize(512, 292);
    sizerDroitIPod->SetMinSize(512, 292);

    sizerDroit->Hide(sizerDroitPreference);
    sizerDroit->Hide(sizerDroitExtracteur);
    sizerDroit->Hide(sizerDroitPlayist);
    sizerDroit->Hide(sizerDroitIPod);
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::CreerPages() - Fin"));
    #endif
}

/**
 * Construit la barre de menu
 */
void FuXFenetre::MenuBarCreation()
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::MenuBarCreation"));
    #endif
    menuFichier = new wxMenu;
    menuFichier->Append(ID_APP_BAR_OUVRIR, _("Ouvrir"));
    menuFichier->Append(ID_APP_BAR_CHARGER_M3U, _("Charger une playlist"));
    menuFichier->Append(ID_APP_BAR_CHARGER_MATIN, _("Charger un .matin"));
    menuFichier->Enable(ID_APP_BAR_CHARGER_MATIN, false);
    menuFichier->AppendSeparator();
    menuFichier->Append(ID_APP_BAR_CREER_PLAYLIST, _("Enregistrer la liste de lecture\tCtrl-S"));//"));//
    menuFichier->Append(ID_APP_BAR_CREER_MATIN, _("Créer un fichier matin"));
    menuFichier->Enable(ID_APP_BAR_CREER_MATIN, false);
    menuFichier->AppendSeparator();
    menuFichier->Append(ID_APP_BAR_QUITTER, _("Quitter Fu(X)\tCtrl-Q"));//"));//

    menuPreferences = new wxMenu;
    menuPreferences->Append(ID_APP_BAR_COULEUR_PREFERENCE, _("Couleur"));
    menuPreferences->Append(ID_APP_BAR_SON_PREFERENCE, _("Son"));
    menuPreferences->Append(ID_APP_BAR_DEFAUT_PREFERENCE, _("Défaut"));

    menuExtraction = new wxMenu;
    menuExtraction->Append(ID_APP_BAR_EXTRACTION, _("Extration de CD"));
    menuExtraction->Enable(ID_APP_BAR_EXTRACTION, false);
    menuExtraction->Append(ID_APP_BAR_MAJ_PLAYLIST, _("MAJ Liste de lecture"));
    //menuExtraction->AppendCheckItem(ID_APP_BAR_FENETRE_GRAPH, _("Fenetre graph"));
    //menuExtraction->Enable(ID_APP_BAR_FENETRE_GRAPH, false);

    menuAide = new wxMenu;
    menuAide->Append(ID_APP_BAR_AIDE, _("Aide\tF1"));//"));//
    menuAide->Append(ID_APP_BAR_SITE_INTERNET, _("Site internet"));
    menuAide->Append(ID_APP_BAR_A_PROPOS, _("A propos"));
    //menuAide->Append(ID_APP_BAR_OBTENIR_EXTENSIONS, _("Obtenir des extensions"));

    menuControle = new wxMenu;
    menuControle->Append(ID_APP_BAR_LECTURE, _("Lecture\tCtrl-P"));//"));//
    menuControle->Append(ID_APP_BAR_STOP, _("Stop"));
    menuControle->AppendSeparator();
    menuControle->Append(ID_APP_BAR_SUIVANT, _("Suivant\tCtrl-RIGHT"));//"));//
    menuControle->Append(ID_APP_BAR_PRECEDENT, _("Précédent\tCtrl-LEFT"));//"));//
    menuControle->AppendCheckItem(ID_APP_BAR_REPETE, _("Répétition"));
    menuControle->AppendCheckItem(ID_APP_BAR_ALEATOIRE, _("Aléatoire"));//\tCtrl-A
    menuControle->AppendSeparator();
    menuControle->Append(ID_APP_BAR_SUPPRIMER, _("Retirer de la liste de lecture\tCtrl-DELETE"));

    menuBarre = new wxMenuBar();
    menuBarre->Append(menuFichier, _("Fichier"));
    menuBarre->Append(menuPreferences, _("Préférences"));
    menuBarre->Append(menuExtraction, _("Outils"));
    menuBarre->Append(menuAide, _("?"));
    menuBarre->Append(menuControle, _("Contrôles"));

    SetMenuBar(menuBarre);
}

/**
 * Construit la partie gauche de la fenêtre : les 4 raccourcis et les 5 boutons donnant accès aux pages
 */
void FuXFenetre::LeftSizerCreation()
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::LeftSizerCreation"));
    #endif

    //sizerGaucheV = new wxBoxSizer(wxVERTICAL);
    SliderSon::Get()->Create(this, ID_APP_SLIDER_SON, 100, 0, 100);
    sizerGaucheV->Add(SliderSon::Get(), 0, wxUP | wxBOTTOM | wxEXPAND, 5);

    wxGridSizer *sizerBoutonImg = new wxGridSizer(1, 4, 0, 0);
    sizerGaucheV->Add(sizerBoutonImg, 0, wxBOTTOM | wxRIGHT | wxLEFT, 5);
    wxImage::AddHandler(new wxPNGHandler);
    wxImage::AddHandler(new wxJPEGHandler);

    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::LeftSizerCreation - chargement des images"));
    #endif
    m_imageBouton = new wxBitmap[5];
    m_imageBouton[PREC].LoadFile(Parametre::Get()->getRepertoireExecutableLib(_T("prec.png")), wxBITMAP_TYPE_PNG);
    m_imageBouton[LECT].LoadFile(Parametre::Get()->getRepertoireExecutableLib(_T("lect.png")), wxBITMAP_TYPE_PNG);
    m_imageBouton[PAUS].LoadFile(Parametre::Get()->getRepertoireExecutableLib(_T("paus.png")), wxBITMAP_TYPE_PNG);
    m_imageBouton[SUIV].LoadFile(Parametre::Get()->getRepertoireExecutableLib(_T("suiv.png")), wxBITMAP_TYPE_PNG);
    m_imageBouton[SUPPR].LoadFile(Parametre::Get()->getRepertoireExecutableLib(_T("suppr.png")), wxBITMAP_TYPE_PNG);

    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::LeftSizerCreation - Application des images aux boutons"));
    #endif
    wxBitmapButton *boutonImage0 = new wxBitmapButton(this, ID_APP_AFF_BOUTON_PRECEDENT, m_imageBouton[PREC], wxDefaultPosition, wxSize(35, 35));
    m_boutonImageLP = new wxBitmapButton(this, ID_APP_AFF_BOUTON_LECTURE, m_imageBouton[LECT], wxDefaultPosition, wxSize(35, 35));
    wxBitmapButton *boutonImage2 = new wxBitmapButton(this, ID_APP_AFF_BOUTON_SUIVANT, m_imageBouton[SUIV], wxDefaultPosition, wxSize(35, 35));
    wxBitmapButton *boutonImage3 = new wxBitmapButton(this, ID_APP_AFF_BOUTON_SUPPRIMER, m_imageBouton[SUPPR], wxDefaultPosition, wxSize(35, 35));
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::LeftSizerCreation - Fin application des images"));
    #endif

    sizerBoutonImg->Add(boutonImage0, 0, wxALL, 0);
    sizerBoutonImg->Add(m_boutonImageLP, 0, wxALL, 0);
    sizerBoutonImg->Add(boutonImage2, 0, wxALL, 0);
    sizerBoutonImg->Add(boutonImage3, 0, wxALL, 0);


    //wxButton *BoutonG_EcranPrincipal = new wxButton(this, ID_APP_AFF_PRINCIPAL, _("Ecran principal"), wxDefaultPosition, wxSize(140, 38));
    wxButton *BoutonG_EcranPrincipal = new BoutonFenetreDetachable(this, ID_APP_AFF_PRINCIPAL, _("Ecran principal"), wxSize(140, 38), PRINCIPAL);
    sizerGaucheV->Add(BoutonG_EcranPrincipal, 0, wxALL, 5);

    //wxButton *BoutonG_Playist = new wxButton(this, ID_APP_AFF_PLAYIST, _("Liste de lecture"), wxDefaultPosition, wxSize(140, 38));
    wxButton *BoutonG_PlayList = new BoutonFenetreDetachable(this, ID_APP_AFF_PLAYIST, _("Liste de lecture"), wxSize(140, 38), LISTELECTURE);
    sizerGaucheV->Add(BoutonG_PlayList, 0, wxBOTTOM | wxRIGHT | wxLEFT, 5);

    //wxButton *BoutonG_ModuleIPod = new wxButton(this, ID_APP_AFF_MODULE_IPOD, _("Exploration"), wxDefaultPosition, wxSize(140, 38));
    wxButton *BoutonG_ModuleIPod = new BoutonFenetreDetachable(this, ID_APP_AFF_MODULE_IPOD, _("Exploration"), wxSize(140, 38), GESTIONPERIPH);
    sizerGaucheV->Add(BoutonG_ModuleIPod, 0, wxBOTTOM | wxRIGHT | wxLEFT, 5);

    wxButton *BoutonG_Preferences = new wxButton(this, ID_APP_AFF_PREFERENCE, _("Préférences"), wxDefaultPosition, wxSize(140, 38));
    sizerGaucheV->Add(BoutonG_Preferences, 0, wxBOTTOM | wxRIGHT | wxLEFT, 5);

    wxButton *BoutonG_ExtracteurMP3 = new wxButton(this, ID_APP_AFF_EXTRACTEUR, _("Encodage"), wxDefaultPosition, wxSize(140, 38));
    sizerGaucheV->Add(BoutonG_ExtracteurMP3, 0, wxBOTTOM | wxRIGHT | wxLEFT, 5);
    BoutonG_ExtracteurMP3->Enable(false);

    sizerGaucheV->SetMinSize(150, 256);
    //sizerPrincipalH->Add(sizerGaucheV, 0, wxALL | wxEXPAND, 0);
}


/// Event methods ///
// button left panel event //
/**
 * Opère un basculement sur la page contenant le graphe (page principal)
 */
void FuXFenetre::AffichePrincipal(wxCommandEvent &WXUNUSED(event))
{
    m_nouvelleFenetre = PRINCIPAL;
    SwitchWindow();
}

/**
 * Opère un basculement sur la page contenant les préférences
 */
void FuXFenetre::AffichePreference(wxCommandEvent &WXUNUSED(event))
{
    m_nouvelleFenetre = PREFERENCE;
    SwitchWindow();
}

/**
 * Opère un basculement sur la page contenant la gestion de CDs
 */
void FuXFenetre::AfficheEncodage(wxCommandEvent &WXUNUSED(event))
{
    m_nouvelleFenetre = ENCODAGE;
    SwitchWindow();
}

/**
 * Opère un basculement sur la page affichant la liste complète des titres mis en mémoire
 */
void FuXFenetre::AfficheListeDeLecture(wxCommandEvent &WXUNUSED(event))
{
    m_nouvelleFenetre = LISTELECTURE;
    SwitchWindow();
}

/**
 * Opère un basculement sur la page permettant une exploration de l'ordinateur
 */
void FuXFenetre::AfficheGestPeriph(wxCommandEvent &WXUNUSED(event))
{
    m_nouvelleFenetre = GESTIONPERIPH;
    SwitchWindow();
}

/**
 * Bascule sur la page des Préférences, onglet Couleur
 */
void FuXFenetre::AfficherPreferenceCouleur(wxCommandEvent &WXUNUSED(event))
{
    m_nouvelleFenetre = PREFERENCE;
    SwitchWindow();
    m_notebookPreference->ChangeSelection(0);
}

/**
 * Bascule sur la page des Préférences, onglet Défaut
 */
void FuXFenetre::AfficherPreferenceDefaut(wxCommandEvent &WXUNUSED(event))
{
    m_nouvelleFenetre = PREFERENCE;
    SwitchWindow();
    m_notebookPreference->ChangeSelection(2);
}

/**
 * Bascule sur la page des Préférences, onglet Son
 */
void FuXFenetre::AfficherPreferenceSon(wxCommandEvent &WXUNUSED(event))
{
    m_nouvelleFenetre = PREFERENCE;
    SwitchWindow();
    m_notebookPreference->ChangeSelection(1);
}

/**
 * Évènement - Permet la séparation des pages dans différentes fenêtres
 * @param event
 */
void FuXFenetre::SeparationPanel(wxCommandEvent &event)
{
    if (!m_panelsAssocies[event.GetInt()])
        return;
    switch(event.GetInt())
    {
        case PRINCIPAL:
            sizerDroit->Detach(sizerDroitPrincipal);
            m_fenetresDetachables->Add(this, (wxWindow*) m_musiqueGraph, sizerDroitPrincipal, PRINCIPAL, event.GetId(), _("Graphe - Fu(X) 2.0"));
            sizerDroitPrincipal = NULL;
            #if DEBUG
            FichierLog::Get()->Ajouter(_T("FuXFenetre::SeparationPanel - PRINCIPAL"));
            #endif
            break;
        case LISTELECTURE:
            sizerDroit->Detach(sizerDroitPlayist);
            m_fenetresDetachables->Add(this, (wxWindow*) m_playList, sizerDroitPlayist, LISTELECTURE, event.GetId(), _("Liste de lecture - Fu(X) 2.0"));
            sizerDroitPlayist = NULL;
            #if DEBUG
            FichierLog::Get()->Ajouter(_T("FuXFenetre::SeparationPanel - LISTELECTURE"));
            #endif
            break;
        case GESTIONPERIPH:
            sizerDroit->Detach(sizerDroitIPod);
            m_fenetresDetachables->Add(this, (wxWindow*) GestPeriph::Get(), sizerDroitIPod, GESTIONPERIPH, event.GetId(), _("Exploration - Fu(X) 2.0"));
            sizerDroitIPod = NULL;
            #if DEBUG
            FichierLog::Get()->Ajouter(_T("FuXFenetre::SeparationPanel - GESTIONPERIPH"));
            #endif
            break;
        default:
            break;
    }
    m_panelsAssocies[event.GetInt()] = false;

    if (!m_panelsAssocies[m_FenetreActuel])
    {
        if (m_panelsAssocies[PRINCIPAL])
            m_nouvelleFenetre = PRINCIPAL;
        else if (m_panelsAssocies[LISTELECTURE])
            m_nouvelleFenetre = LISTELECTURE;
        else if (m_panelsAssocies[GESTIONPERIPH])
            m_nouvelleFenetre = GESTIONPERIPH;
        else if (m_panelsAssocies[PREFERENCE])
            m_nouvelleFenetre = PREFERENCE;
    }

    SwitchWindow();
    m_nouvelleFenetre = event.GetInt();
    SwitchWindow();
}

/**
 * Évènement - Permet la réintégration des pages dans la fenêtre principale
 * @param event
 */
void FuXFenetre::ReunionPanel(wxCommandEvent &event)
{
    FenetreDetachable *f = m_fenetresDetachables->GetFenetreByType(event.GetInt());
    if (f == NULL)
        return;

    wxBoxSizer *s = NULL;
    switch(event.GetInt())
    {
        case PRINCIPAL:
            sizerDroitPrincipal = (wxBoxSizer*) f->RetourNormale();
            s = sizerDroitPrincipal;
            #if DEBUG
            FichierLog::Get()->Ajouter(_T("FuXFenetre::ReunionPanel - PRINCIPAL"));
            #endif
            break;
        case LISTELECTURE:
            sizerDroitPlayist = (wxBoxSizer*)f->RetourNormale();
            s = sizerDroitPlayist;
            #if DEBUG
            FichierLog::Get()->Ajouter(_T("FuXFenetre::ReunionPanel - LISTELECTURE"));
            #endif
            break;
        case GESTIONPERIPH:
            sizerDroitIPod = (wxBoxSizer*)f->RetourNormale();
            s = sizerDroitIPod;
            #if DEBUG
            FichierLog::Get()->Ajouter(_T("FuXFenetre::ReunionPanel - GESTIONPERIPH"));
            #endif
            break;
        default:
            break;
    }
    if (s)
    {
        m_panelsAssocies[event.GetInt()] = true;
        sizerDroit->Add(s, 1, wxALL | wxEXPAND, 0);
        sizerDroit->Show(s);
        sizerDroit->Layout();
        if (m_FenetreActuel != event.GetInt())
            sizerDroit->Hide(s);
        m_nouvelleFenetre = m_FenetreActuel;
    }
    sizerDroit->Layout();

    if (f)
    {
        f->~FenetreDetachable();
        m_fenetresDetachables->Remove(f);
    }
}

/**
 * Modifie le volume sonore
 */
void FuXFenetre::EventUpdateMusicVolume(wxScrollEvent &WXUNUSED(event))
{
    MusicManager::get().getMusicPlayer().setVolume(SliderSon::Get()->GetValue());
    m_pageSon->SetValeurMusique(SliderSon::Get()->GetValue());
    SwitchWindow();
}


// Bar menu event //

/**
 * Provoque la fermeture du programme
 */
void FuXFenetre::EventQuit(wxCommandEvent &WXUNUSED(event))
{    Close(true);}

/**
 * Barre de menu : relance la lecture
 */
void FuXFenetre::EventMenuBarPlay(wxCommandEvent &WXUNUSED(event))
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::EventMenuBarPlay - Barre de menu"));
    #endif
    playButtonPressed();
}

/**
 * Relance la lecture si un titre est chargé, ouvre une fenêtre de sélection sinon
 */
void FuXFenetre::EventPlayButtonPressed(wxCommandEvent &WXUNUSED(event))
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::BoutonLecture"));
    #endif
    playButtonPressed();
    //SwitchWindow();
}

/**
 * Arrête la chanson
 */
void FuXFenetre::EventMusicStop(wxCommandEvent &WXUNUSED(event))
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::Stop"));
    #endif
    MusicManager::get().getMusicPlayer().stop();
    drawPlayImageStatus();
}

/**
 * Passe au titre suivant
 */
void FuXFenetre::EventMusicNext(wxCommandEvent &WXUNUSED(event))
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::suivant"));
    #endif
    MusicManager::get().playNextOrRandomMusic();
    SwitchWindow();
}

/**
 * Passe au titre précédent
 */
void FuXFenetre::EventMusicPrevious(wxCommandEvent &WXUNUSED(event))
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::Precedent"));
    #endif
    MusicManager::get().playPreviousOrRandomMusic();
    SwitchWindow();
}

/**
 * Active/Désactive la répétition
 */
void FuXFenetre::EventMusicRepete(wxCommandEvent &WXUNUSED(event))
{
    MusicManager::get().setRepete(!MusicManager::get().isRepete());
}

/**
 * Active/Désactive la lecture aléatoire
 */
void FuXFenetre::EventMusicRandomize(wxCommandEvent &WXUNUSED(event))
{
    MusicManager::get().setRandom(!MusicManager::get().isRandom());
}

/**
 * Ouvre une fenêtre pour choisir le ou les titres de musique à lire. Ajoute le(s) titre(s) à liste si celle-ci n'est pas vide
 */
void FuXFenetre::EventOpenDialogToPlayMusic(wxCommandEvent &WXUNUSED(event))
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::EventOpenDialogToPlayMusic"));
    #endif
    openDialogToPlayMusic();
}

/**
 * Ouvre une fenêtre afin de choisir une liste de lecture enregistrée
 */
void FuXFenetre::EventOpenDialogToSelectPlayListFile(wxCommandEvent &WXUNUSED(event))
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::EventOpenDialogToSelectPlayListFile"));
    #endif
    openDialogToSelectPlayListFile();
}

/**
 * Supprime le titre en cours de diffusion de la liste de lecture
 */
void FuXFenetre::EventDeleteCurrentPlayingTitle(wxCommandEvent &WXUNUSED(event))
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::EventDeleteCurrentPlayingTitle"));
    #endif
    deleteCurrentPlayingTitle();
    SwitchWindow();
}

/**
 * Provoque les changements nécessaires afin de s'adapter à la nouvelle situation : changement de titre ou suppression de tous les titres
 */
void FuXFenetre::EventMusicChanged(wxCommandEvent &WXUNUSED(event))
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::ChangementChanson"));
    #endif
    m_playList->GetPlayListTableau()->ChangementChanson();
    changePlayPauseImageStatus();
}

/**
 * Provoque une mise à jour de la liste de lecture affichée à l'utilisateur
 */
void FuXFenetre::EventUpdatePlayLists(wxCommandEvent &WXUNUSED(event))
{
    m_playList->GetPlayListTableau()->MAJ();
    GestPeriph::Get()->MAJPlaylist();
}

/**
 * Affiche une fenêtre permettant l'enregistrement de la liste de lecture
 */
void FuXFenetre::EventSavePlayList(wxCommandEvent &event)
{
    m_playList->EnregistrerM3U(event);
}

/**
 * Affiche le menu About de l'application
 */
void FuXFenetre::MenuAbout(wxCommandEvent &WXUNUSED(event))
{
    wxString message(_T("Nom : Fu(X) 2.0\tVersion : a5\tDate : ") + wxString(_T(__DATE__)) + _T("\n\nAuteur : David Lecoconnier (etrange02@aol.com)\n\nInterface réalisée avec wxWidgets 2.8.12\n\n\n") +
                        _T("Copyright © 2009-2014 David Lecoconnier, tous droits réservés\n\nFMOD Sound System, copyright © Firelight Technologies Pty, Ltd., 1994-2007\n"));
    wxMessageBox(message, _("A propos"), wxOK | wxICON_INFORMATION, this);
}

/**
 * Affiche le site de l'application à travers le navigateur internet
 */
void FuXFenetre::MenuSiteWeb(wxCommandEvent &WXUNUSED(event))
{    wxLaunchDefaultBrowser(_T("http://fuxplay.com/"));}

/**
 * Affiche la page d'aide à travers le navigateur internet
 */
void FuXFenetre::MenuAide(wxCommandEvent &WXUNUSED(event))
{    wxLaunchDefaultBrowser(_T("http://fuxplay.com/aide.php"));}


// Internal management event //

/**
 * Modifie l'image du bouton lecture/pause en fonction de l'état du système
 */
void FuXFenetre::EventSwitchButtonImage(wxCommandEvent &event)
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::BoutonChangeImage - bascule image Lecture/Pause"));
    #endif
//    if (event.GetInt() == 1)
//    {
//        drawPlayImageStatus();
//    }
//    else
//    {
//        drawPauseImageStatus();
//    }
    changePlayPauseImageStatus();
    SwitchWindow();
}

/**
 * Évènement provenant du serveur de l'application : un titre ajouté
 */
void FuXFenetre::EvtServeurAjout(wxCommandEvent &event)
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::EvtServeurAjout"));
    #endif
    wxArrayString *a = m_serveur->GetConnexionTableau(event.GetInt());

    //bool lire = Musique::Get()->IsContainingMus();
    MusicManager::get().parse(a, true);
    /*if (lire && !a->Item(i).Lower().EndsWith(_T(".m3u")))
        Musique::Get()->ChangementChanson(-1, a->Item(0));*/
    m_serveur->Deconnecter(event.GetInt());
}

/**
 * Informe le panel du graphe que le titre de la chanson a été modifié.
 */
void FuXFenetre::OnTitreChange(wxCommandEvent &WXUNUSED(event))
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::OnTitreChange"));
    #endif
    m_musiqueGraph->TitreChange();
}

/**
 * Évènements clavier - Utilisation des raccourcis généraux (titre suivant, volume, ...)
 * @param event l'événement à analyser
 */
void FuXFenetre::OnKeyDownRaccourci(wxKeyEvent &event)
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::OnKeyDownRaccourci"));
    #endif
    if (event.ControlDown())
    {
        switch (event.GetKeyCode())
        {
            case '+':
            case WXK_ADD:
            case WXK_NUMPAD_ADD:
                SliderSon::Get()->SonUp();
                break;
            case '-':
            case '6':
            case WXK_SUBTRACT:
            case WXK_NUMPAD_SUBTRACT:
                SliderSon::Get()->SonDown();
                break;
            default :
                event.Skip();
        }
    }
    else
        event.Skip();
}

void FuXFenetre::EventNoMusic(wxCommandEvent& WXUNUSED(event))
{
    drawPlayImageStatus();
}

/// Internal management methods ///

void FuXFenetre::changePlayPauseImageStatus()
{
    if (MusicManager::get().getMusicPlayer().isPlaying())
        drawPauseImageStatus();
    else
        drawPlayImageStatus();
}

void FuXFenetre::drawPauseImageStatus()
{
    m_boutonImageLP->SetBitmapLabel(m_imageBouton[PAUS]);
    menuControle->FindItem(ID_APP_BAR_LECTURE)->SetItemLabel(_("Pause\tCtrl-P"));
}

void FuXFenetre::drawPlayImageStatus()
{
    menuControle->FindItem(ID_APP_BAR_LECTURE)->SetItemLabel(_("Lecture\tCtrl-P"));
    m_boutonImageLP->SetBitmapLabel(m_imageBouton[LECT]);
}

void FuXFenetre::playButtonPressed()
{
    if (MusicManager::get().getMusicPlayer().isPlaying())//En lecture
    {
        MusicManager::get().getMusicPlayer().setPause(true);
    }
    else if (MusicManager::get().empty())//Pas de fichier chargé
        openDialogToPlayMusic();
    else if (MusicManager::get().getMusicPlayer().isPaused())//En pause
    {
        MusicManager::get().getMusicPlayer().setPause(false);
    }
    else//Musique stoppée
    {
        MusicManager::get().playSameMusic();
    }
}

void FuXFenetre::openDialogToPlayMusic()
{
    wxFileDialog navig(this, _("Choisissez une chanson"), Parametre::Get()->getRepertoireDefaut(), _T(""), Parametre::Get()->getExtensionValideMusique(), wxFD_OPEN | wxFD_MULTIPLE | wxFD_FILE_MUST_EXIST);//";*.wav");

    if (navig.ShowModal() == wxID_OK)
    {
        wxArrayString musNav;
        navig.GetPaths(musNav);

        if (musNav.GetCount() == 1)
        {
            if (MusicManager::get().empty())
                MusicManager::get().playMusicThenParse(musNav.Item(0));
            else
                MusicManager::get().parse(musNav.Item(0));
        }
        else if (musNav.GetCount() >= 2)
            MusicManager::get().parse(&musNav, false);

        musNav.Clear();
        m_playList->GetPlayListTableau()->MAJ();
        GestPeriph::Get()->MAJPlaylist();
    }
}

void FuXFenetre::openDialogToSelectPlayListFile()
{
    wxFileDialog navig(this, _("Choisissez une playlist (fichier .m3u)"), Parametre::Get()->getRepertoireParametre(_T("Play_list_M3U")), _T(""), _T("Playlist (*.m3u)|*.m3u"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (navig.ShowModal() == wxID_OK)
    {
        wxString chemin = navig.GetPath();

        wxTextFile test(chemin);
        if (test.Open())
        {
            int nb = test.GetLineCount();
            test.Close();
            if (nb > 1)
            {
                /*if (Musique::Get()->GetFichier()->GetNombreFichier() == 0)
                {
                    //int ligne = Musique::Get()->GetFichier()->GetNombreFichier();
                    //Musique::Get()->CopieFichier(chemin);
                    //Musique::Get()->ChangementChanson(0, _T(""));
                    //Musique::Get()->Lecture(Musique::Get()->GetFichier()->GetNomPosition(0));
                }
                else*/
                    MusicManager::get().parse(chemin);
                m_playList->GetPlayListTableau()->MAJ();
                GestPeriph::Get()->MAJPlaylist();
            }
            else
            {
                wxLogMessage(_("Impossible d'ouvrir le fichier, celui-ci est vierge !"));
            }
        }
    }
}

void FuXFenetre::deleteCurrentPlayingTitle()
{
    MusicManager::get().deleteCurrentTitle();
    GestPeriph::Get()->MAJPlaylist();
}

/**
 * Échange la page actuelle contre une autre page (effectue l'opération)
 */
void FuXFenetre::SwitchWindow()/////////////////
{
    if (m_FenetreActuel != m_nouvelleFenetre && m_panelsAssocies[m_nouvelleFenetre])
    {
        //if ()
            switch(m_FenetreActuel)
            {
                case PRINCIPAL:
                    if (sizerDroitPrincipal)
                        sizerDroit->Hide(sizerDroitPrincipal);
                    break;
                case PREFERENCE:
                    if (sizerDroitPreference)
                        sizerDroit->Hide(sizerDroitPreference);
                    break;
                case ENCODAGE:
                    if (sizerDroitExtracteur)
                        sizerDroit->Hide(sizerDroitExtracteur);
                    break;
                case LISTELECTURE:
                    if (sizerDroitPlayist)
                        sizerDroit->Hide(sizerDroitPlayist);
                    break;
                case GESTIONPERIPH:
                    if (sizerDroitIPod)
                        sizerDroit->Hide(sizerDroitIPod);
                    break;
                default:
            break;
            }
        switch(m_nouvelleFenetre)
        {
            case PRINCIPAL:
                m_FenetreActuel = PRINCIPAL;
                sizerDroit->Show(sizerDroitPrincipal);
                break;
            case PREFERENCE:
                m_FenetreActuel = PREFERENCE;
                sizerDroit->Show(sizerDroitPreference);
                break;
            case ENCODAGE:
                m_FenetreActuel = ENCODAGE;
                sizerDroit->Show(sizerDroitExtracteur);
                break;
            case LISTELECTURE:
                m_FenetreActuel = LISTELECTURE;
                sizerDroit->Show(sizerDroitPlayist);
                break;
            case GESTIONPERIPH:
                m_FenetreActuel = GESTIONPERIPH;
                sizerDroit->Show(sizerDroitIPod);
                break;
            default:
                break;
        }
    }
    switch(m_nouvelleFenetre)
    {
        case PRINCIPAL:
            m_musiqueGraph->SetFocus();
            break;
        case PREFERENCE:
            m_notebookPreference->SetFocus();
            break;
        case ENCODAGE:
            break;
        case LISTELECTURE:
            m_playList->GetPlayListTableau()->SetFocus();
            break;
        case GESTIONPERIPH:
            GestPeriph::Get()->SetFocus();
            break;
        default:
            break;
    }
    sizerDroit->Layout();
}

void FuXFenetre::readPreferencesNewWay(bool loadDefaultMusic, const wxString& fileName)
{
    wxXmlDocument doc;
    if (!doc.Load(fileName))
        return;
    if (doc.GetRoot()->GetName() != _("default"))
        return;

    wxXmlNode *child = doc.GetRoot()->GetChildren();
    wxXmlNode *nodeReprise = NULL;

    while (child)
    {
        if (child->GetName() == _("filter_colour"))
        {
            m_pageCouleur->OuvrirFiltre(child->GetAttribute(_("file"), wxEmptyString), false);
        }
        else if (child->GetName() == _("filter_sound"))
        {
            m_pageSon->OuvrirFiltre(child->GetAttribute(_("file"), wxEmptyString), false);
        }
        else if (child->GetName() == _("reprise"))
        {
            nodeReprise = child;
        }
        else if (child->GetName() == _("subfile"))
        {
            Parametre::Get()->setSousDossier(true);
        }
        child = child->GetNext();
    }

    if (loadDefaultMusic && nodeReprise)
    {
        if (nodeReprise->GetAttribute(_("type"), wxEmptyString) == _T("M3U"))
        {
            wxString cheminM3U = Parametre::Get()->getRepertoireParametre(_T("Play_list_M3U"), nodeReprise->GetNodeContent());

            wxTextFile test(cheminM3U);
            if (test.Open())
            {
                if (test.GetLineCount() > 1)
                {
                    //Musique::Get()->Lecture(test.GetLine(1));
                    MusicManager::get().parse(cheminM3U);
                    //Musique::Get()->Lecture(FichierListe::Get()->GetNomPosition(0));
                    m_MAJliste = true;
                }
                else wxLogMessage(_("Impossible d'ouvrir le fichier, celui-ci est vierge !"));
                test.Close();
            }
        }
        else if (nodeReprise->GetAttribute(_("type"), wxEmptyString) == _T("MP3"))
        {
            MusicManager::get().playMusicThenParse(nodeReprise->GetNodeContent());
            m_MAJliste = MusicManager::get().getMusicPlayer().isPlaying();
        }
    }
}

void FuXFenetre::readPreferencesOldWay(bool loadDefaultMusic, wxTextFile& prefFile)
{
    ///////Couleur
    if (!prefFile.GetLine(1).IsSameAs(_T("Couleur= NON")))
        m_pageCouleur->OuvrirFiltre(prefFile.GetLine(1).AfterFirst(' '), false);

    ///////Son
    if (!prefFile.GetLine(2).IsSameAs(_T("Son= NON")))
    {
        m_pageSon->OuvrirFiltre(prefFile.GetLine(2).AfterFirst(' '), false);
    }
    ///////Sous-dossier
    if (prefFile.GetLine(5) != _T("SousDossier= NON"))
        Parametre::Get()->setSousDossier(true);
    /////////Reprise
    if (loadDefaultMusic && !(prefFile.GetLine(3).IsSameAs(_T("Reprise= NON"))))
    {
        if (prefFile.GetLine(3).IsSameAs(_T("Reprise= M3U")))
        {
            wxString cheminM3U = Parametre::Get()->getRepertoireParametre(_T("Play_list_M3U"), prefFile.GetLine(4).AfterFirst(' '));

            wxTextFile test(cheminM3U);
            if (test.Open())
            {
                if (test.GetLineCount() > 1)
                {
                    MusicManager::get().parse(cheminM3U);
                    //MusicManager::get().playMusic(MusicManager::get().getMusicList()->getNameAtPosition(0));
                    m_MAJliste = true;
                }
                else wxLogMessage(_("Impossible d'ouvrir le fichier, celui-ci est vierge !"));
                test.Close();
            }
        }
        else if (prefFile.GetLine(3).IsSameAs(_T("Reprise= MP3")))
        {
            MusicManager::get().playMusicThenParse(prefFile.GetLine(4).AfterFirst(' '));
            m_MAJliste = true;
        }
    }
}

/**
 * Lit les préférences se trouvant dans le fichier de configuration si celui-ci existe
 * @param loadDefaultMusic Si vrai, l'application cherche à lancer le fichier enregistré comme devant être lancé à l'ouverture de l'application
 */
void FuXFenetre::readPreferences(bool loadDefaultMusic)
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::readPreferences"));
    #endif

    wxString cheminFichier = Parametre::Get()->getRepertoireParametre(_T("Fu(X).conf")) , nomFichierCouleur, nomFichierSon;
    wxTextFile fichierPref(cheminFichier);

    if (!(fichierPref.Exists() && fichierPref.Open()))
        return;

    if (fichierPref.GetLine(0).IsSameAs(_T("#EXTCONF_1")))
    {
        readPreferencesOldWay(loadDefaultMusic, fichierPref);
        fichierPref.Close();
    }
    else
    {
        fichierPref.Close();
        readPreferencesNewWay(loadDefaultMusic, cheminFichier);
    }
}

