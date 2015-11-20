/***************************************************************
 * Name:      Fenetre.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2009-07-24
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include "Fenetre.h"
#include "MusicManagerSwitcher.h"
#include "ExplorerDriveManagers.h"
#include "music/MusicFileReaderThread.h"
#include "Mediator.h"
#include "DeletedLines.h"
#include "tools/dir/interface/DirFileDialog.h"
#include "tools/dir/interface/DirFileDialogEvent.h"
#include "tools/dir/interface/RepeatedQuestionDialogEvent.h"
#include "tools/dir/AskForRecursiveOperationData.h"
#include "tools/dir/factory/DirFileDialogFactory.h"

using namespace ::music;

/**
 * @class FuXFenetre
 * @brief Interface principale de l'application : barre de menu. Elle contient plusieurs wxSizer.
 */

BEGIN_EVENT_TABLE(FuXFenetre, wxFrame)
    EVT_MENU(ID_APP_BAR_QUITTER,            FuXFenetre::EventQuit)
    EVT_MENU(ID_APP_BAR_LECTURE,            FuXFenetre::EventMenuBarPlay)
    EVT_MENU(ID_APP_BAR_SUIVANT,            FuXFenetre::EventMusicNext)
    EVT_MENU(ID_APP_BAR_PRECEDENT,          FuXFenetre::EventMusicPrevious)
    EVT_MENU(ID_APP_BAR_STOP,               FuXFenetre::EventMusicStop)
    EVT_MENU(ID_APP_BAR_REPETE,             FuXFenetre::EventMusicRepete)
    EVT_MENU(ID_APP_BAR_ALEATOIRE,          FuXFenetre::EventMusicRandomize)
    EVT_MENU(ID_APP_BAR_OUVRIR,             FuXFenetre::EventOpenDialogToPlayMusic)
    EVT_MENU(ID_APP_BAR_CHARGER_M3U,        FuXFenetre::EventOpenDialogToSelectPlayListFile)
    EVT_MENU(ID_APP_BAR_CREER_PLAYLIST,     FuXFenetre::EventSavePlayList)
    EVT_MENU(ID_APP_BAR_SUPPRIMER,          FuXFenetre::EventDeleteCurrentPlayingTitle)
    EVT_MENU(ID_APP_BAR_MAJ_PLAYLIST,       FuXFenetre::EventUpdatePlayLists)
    EVT_MENU(ID_APP_BAR_A_PROPOS,           FuXFenetre::MenuAbout)
    EVT_MENU(ID_APP_BAR_SITE_INTERNET,      FuXFenetre::MenuSiteWeb)
    EVT_MENU(ID_APP_BAR_AIDE,               FuXFenetre::MenuAide)
    EVT_MENU(ID_APP_BAR_COULEUR_PREFERENCE, FuXFenetre::AfficherPreferenceCouleur)
    EVT_MENU(ID_APP_BAR_SON_PREFERENCE,     FuXFenetre::AfficherPreferenceSon)
    EVT_MENU(ID_APP_BAR_DEFAUT_PREFERENCE,  FuXFenetre::AfficherPreferenceDefaut)
    EVT_BUTTON(ID_APP_AFF_BOUTON_PRECEDENT, FuXFenetre::EventMusicPrevious)//////////////////////
    EVT_BUTTON(ID_APP_AFF_BOUTON_SUIVANT,   FuXFenetre::EventMusicNext)//////////////////////
    EVT_BUTTON(ID_APP_AFF_BOUTON_SUPPRIMER, FuXFenetre::EventDeleteCurrentPlayingTitle)//////////////////////
    EVT_BUTTON(ID_APP_AFF_BOUTON_LECTURE,   FuXFenetre::EventMenuBarPlay)//////////////////////
    EVT_BUTTON(ID_APP_AFF_PRINCIPAL,        FuXFenetre::AffichePrincipal)
    EVT_BUTTON(ID_APP_AFF_PREFERENCE,       FuXFenetre::AffichePreference)
    EVT_BUTTON(ID_APP_AFF_EXTRACTEUR,       FuXFenetre::AfficheEncodage)
    EVT_BUTTON(ID_APP_AFF_PLAYIST,          FuXFenetre::AfficheListeDeLecture)
    EVT_BUTTON(ID_APP_AFF_MODULE_IPOD,      FuXFenetre::AfficheGestPeriph)
    EVT_COMMAND_SCROLL(ID_APP_SLIDER_SON,   FuXFenetre::EventUpdateMusicVolume)

    EVT_FUX_MUSICPLAYER_CHANGE_TITLE    (FuXFenetre::EventMusicChanged)
    EVT_FUX_MUSICPLAYER_CHANGE_STATUS   (FuXFenetre::EventSwitchButtonImage)
    EVT_FUX_MUSICPLAYER_UPDATE_GRAPH    (FuXFenetre::OnTitreChange)
    EVT_FUX_MUSICLIST_LIST_UPDATE       (FuXFenetre::EventUpdatePlayLists)
    EVT_FUX_MUSICMANAGER_NO_FILE        (FuXFenetre::EventNoMusic)
    EVT_FUX_MUSICMANAGER_SEARCH_DONE    (FuXFenetre::onEventUpdatePlaylistSearchDone)
    EVT_FUX_MUSICMANAGER_LINE_DELETED   (FuXFenetre::onDeleteLine)
    EVT_FUX_MUSICFILE_READER_THREAD     (FuXFenetre::onUpdateLine)
    EVT_TOOLS_DIR_FILE_CLOSE            (FuXFenetre::onDirFileDialogClose)
    EVT_TOOLS_DIR_FILE_RANGE            (FuXFenetre::onDirFileDialogRange)
    EVT_TOOLS_DIR_FILE_UPDATE           (FuXFenetre::onDirFileDialogUpdate)
    EVT_TOOLS_DIR_FILE_ASK_REC_QUESTION (FuXFenetre::onDirFileRecurseQuestion)

    EVT_SERVEUR(wxID_ANY, FuXFenetre::EvtServeurAjout)

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
FuXFenetre::FuXFenetre(/*Mediator& mediator, */int argc, wxChar **argv) :
    wxFrame(NULL, wxID_ANY, _T("Fu(X) 2.0")),
    m_FenetreActuel(PRINCIPAL),
    m_nouvelleFenetre(PRINCIPAL)//,
    //m_mediator(mediator)
{
    wxMutexLocker lock(*s_mutexProtectionDemarrage);

    tools::dir::DirFileDialogFactory* factory = new tools::dir::DirFileDialogFactory(*this);
    tools::dir::DirFileManager* manager = new tools::dir::DirFileManager(*factory);
    m_mediator.setDirFileManager(manager);

    m_mediator.getExplorerDriveManagers().setDirFileManager(&m_mediator.getDirFileManager());
    m_mediator.getDirFileManager().start();
    sizerPrincipalH = new wxBoxSizer(wxHORIZONTAL);
    sizerGaucheV = new wxBoxSizer(wxVERTICAL);
    sizerPrincipalH->Add(sizerGaucheV, 0, wxALL | wxEXPAND, 0);

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
                    MusicManagerSwitcher::get().parse(fichierMem.GetFullPath());
                }
                else
                    wxLogMessage(_("Impossible de charger le fichier, celui-ci est vierge !"));
                test.Close();
            }
        }
        else if (Parametre::Get()->islisable(fichierMem.GetExt().Lower()))
        {
            MusicManagerSwitcher::get().playMusicThenParse(fichierMem.GetFullPath());
        }
    }

    SetIcon(wxIcon(Parametre::Get()->getRepertoireExecutableLib(_T("play.ico")), wxBITMAP_TYPE_ICO));

    SwitchWindow();
    m_serveur = new TCPServeur(this);
    if (!m_serveur->Create(IPC_SERVICE))
    {
        wxLogMessage(_T("Impossible d'initialiser le serveur"));
    }

    m_fenetresDetachables = new ArrayFenetreDetachable();
    LogFileAppend(_T("Fin de FuXFenetre::FuXFenetre(int argc, wxChar **argv)"));
}

/**
 * Destructeur
 */
FuXFenetre::~FuXFenetre()
{
    //m_mediator.getDirFileManager().kill();
    m_mediator.setDirFileManager(NULL);

    LogFileAppend("FuXFenetre::~FuXFenetre - début");
    m_fenetresDetachables->Vider();
    delete m_fenetresDetachables;
    delete m_serveur;
    BDDThread::Get()->Stop();
    m_TimerGraph.Stop();
    delete[] m_imageBouton;
//    Musique::Get()->Delete();
//    GestPeriph::Get()->Delete();
    delete m_musiqueGraph;
    delete m_playList;
    delete m_panelsAssocies;
    delete m_pageCouleur;
    delete m_pageDefaut;
    delete m_pageSon;

//    LogFileAppend(_T("FuXFenetre::~FuXFenetre - fin"));
}

/// Initialization methods ///


/**
 * Initialise les instances des classes nécessaire au lancement de Fu(X)
 */
void FuXFenetre::panelCreation()
{
    LogFileAppend("Début de FuXFenetre::Initialisation");

    int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};
    MusicManagerSwitcher::get().setParent(this);
    m_musiqueGraph = new gui::music::MusiqueGraph(this, args);
    m_playList = new PlayList;
    BDDThread::Get();

    LogFileAppend(_T("Fin de FuXFenetre::Initialisation"));
}

/**
 * Attache les panels à la fenêtre principal
 */
void FuXFenetre::panelAssociation()
{
    LogFileAppend("FuXFenetre::CreerPages() - Création des onglets et des pages manquantes");

    sizerDroitPrincipal = new wxBoxSizer(wxVERTICAL);
    m_TimerGraph.Start(40, false);

    sizerDroitPrincipal->Add(m_musiqueGraph, 1, wxEXPAND, 0);
    sizerDroitPrincipal->Show(m_musiqueGraph);
    sizerDroitPrincipal->Layout();
    LogFileAppend(_T("FuXFenetre::CreerPages() - Graphe"));
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
    LogFileAppend("FuXFenetre::CreerPages() - Préférences");
    //////////////////////////////////////////////////////////////
    sizerDroitExtracteur = new wxBoxSizer(wxVERTICAL);
    wxButton *bouton2 = new wxButton(this, wxID_ANY, _("Extraction indisponible pour le moment"));

    sizerDroitExtracteur->Add(bouton2, 1, wxALL | wxEXPAND, 0);
    sizerDroitExtracteur->Show(bouton2);
    sizerDroitExtracteur->Layout();
    LogFileAppend(_T("FuXFenetre::CreerPages() - Extraction"));
    /////////////////////////////////////////////////////////////
    m_sizerDroitPlaylist = new wxBoxSizer(wxVERTICAL);
    m_playList->Initialize(this);

    //m_grille = new PlayListGrille(this);
    m_sizerDroitPlaylist->Add(m_playList, 1, wxALL | wxEXPAND, 0);
    m_sizerDroitPlaylist->Show(m_playList);

    m_sizerDroitPlaylist->Layout();
    LogFileAppend(_T("FuXFenetre::CreerPages() - Playlist"));
    ////////////////////////////////////////////////////////////////////
    m_sizerRightExplorer = new wxBoxSizer(wxVERTICAL);
    m_driveManagersPanel = new gui::explorer::DriveManagersPanel(this, m_mediator.getExplorerDriveManagers());

    m_sizerRightExplorer->Add(m_driveManagersPanel, 1, wxALL | wxEXPAND, 0);
    m_sizerRightExplorer->Show(m_driveManagersPanel);
    m_sizerRightExplorer->Layout();
    //////////////////////////////////////////////////////////////////////

    sizerDroit = new wxBoxSizer(wxVERTICAL);
    sizerDroit->SetMinSize(512, 256);
    sizerPrincipalH->Add(sizerDroit, 1, wxALL | wxEXPAND, 0);

    sizerDroit->Add(sizerDroitPrincipal, 1, wxALL | wxEXPAND, 0);
    sizerDroit->Add(m_sizerDroitPlaylist, 1, wxALL | wxEXPAND, 0);
    sizerDroit->Add(m_sizerRightExplorer, 1, wxALL | wxEXPAND, 0);
    sizerDroit->Add(sizerDroitPreference, 1, wxALL | wxEXPAND, 0);//2
    sizerDroit->Add(sizerDroitExtracteur, 1, wxALL | wxEXPAND, 0);

    m_panelsAssocies = new bool[5];// {true, true, true, true, true};
    for (int i = 0; i < 5 ; i++){m_panelsAssocies[i] = true;}


    sizerDroitPrincipal->SetMinSize(512, 292);
    m_sizerDroitPlaylist->SetMinSize(512, 292);
    m_sizerRightExplorer->SetMinSize(512, 292);
    sizerDroitPreference->SetMinSize(512, 292);
    sizerDroitExtracteur->SetMinSize(512, 292);

    sizerDroit->Hide(m_sizerDroitPlaylist);
    sizerDroit->Hide(m_sizerRightExplorer);
    sizerDroit->Hide(sizerDroitPreference);
    sizerDroit->Hide(sizerDroitExtracteur);
    LogFileAppend(_T("FuXFenetre::CreerPages() - Fin"));
}

/**
 * Construit la barre de menu
 */
void FuXFenetre::MenuBarCreation()
{
    LogFileAppend(_T("FuXFenetre::MenuBarCreation"));
    menuFichier = new wxMenu;
    menuFichier->Append(ID_APP_BAR_OUVRIR, _("Ouvrir"));
    menuFichier->Append(ID_APP_BAR_CHARGER_M3U, _("Charger une playlist"));
    menuFichier->Append(ID_APP_BAR_CHARGER_MATIN, _("Charger un .matin"));
    menuFichier->Enable(ID_APP_BAR_CHARGER_MATIN, false);
    menuFichier->AppendSeparator();
    menuFichier->Append(ID_APP_BAR_CREER_PLAYLIST, _("Enregistrer la liste de lecture\tCtrl-S"));//"));//
    menuFichier->Append(ID_APP_BAR_CREER_MATIN, "Créer un fichier matin");
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
    LogFileAppend(_T("FuXFenetre::LeftSizerCreation"));

    //sizerGaucheV = new wxBoxSizer(wxVERTICAL);
    SliderSon::Get()->Create(this, ID_APP_SLIDER_SON, 100, 0, 100);
    sizerGaucheV->Add(SliderSon::Get(), 0, wxUP | wxBOTTOM | wxEXPAND, 5);

    wxGridSizer *sizerBoutonImg = new wxGridSizer(1, 4, 0, 0);
    sizerGaucheV->Add(sizerBoutonImg, 0, wxBOTTOM | wxRIGHT | wxLEFT, 5);
    wxImage::AddHandler(new wxPNGHandler);
    wxImage::AddHandler(new wxJPEGHandler);

    LogFileAppend(_T("FuXFenetre::LeftSizerCreation - chargement des images"));
    m_imageBouton = new wxBitmap[5];
    m_imageBouton[PREC].LoadFile(Parametre::Get()->getRepertoireExecutableLib(_T("prec.png")), wxBITMAP_TYPE_PNG);
    m_imageBouton[LECT].LoadFile(Parametre::Get()->getRepertoireExecutableLib(_T("lect.png")), wxBITMAP_TYPE_PNG);
    m_imageBouton[PAUS].LoadFile(Parametre::Get()->getRepertoireExecutableLib(_T("paus.png")), wxBITMAP_TYPE_PNG);
    m_imageBouton[SUIV].LoadFile(Parametre::Get()->getRepertoireExecutableLib(_T("suiv.png")), wxBITMAP_TYPE_PNG);
    m_imageBouton[SUPPR].LoadFile(Parametre::Get()->getRepertoireExecutableLib(_T("suppr.png")), wxBITMAP_TYPE_PNG);

    LogFileAppend(_T("FuXFenetre::LeftSizerCreation - Application des images aux boutons"));
    wxBitmapButton *boutonImage0 = new wxBitmapButton(this, ID_APP_AFF_BOUTON_PRECEDENT, m_imageBouton[PREC], wxDefaultPosition, wxSize(35, 35));
    m_boutonImageLP = new wxBitmapButton(this, ID_APP_AFF_BOUTON_LECTURE, m_imageBouton[LECT], wxDefaultPosition, wxSize(35, 35));
    wxBitmapButton *boutonImage2 = new wxBitmapButton(this, ID_APP_AFF_BOUTON_SUIVANT, m_imageBouton[SUIV], wxDefaultPosition, wxSize(35, 35));
    wxBitmapButton *boutonImage3 = new wxBitmapButton(this, ID_APP_AFF_BOUTON_SUPPRIMER, m_imageBouton[SUPPR], wxDefaultPosition, wxSize(35, 35));
    LogFileAppend(_T("FuXFenetre::LeftSizerCreation - Fin application des images"));

    sizerBoutonImg->Add(boutonImage0,    0, wxALL, 0);
    sizerBoutonImg->Add(m_boutonImageLP, 0, wxALL, 0);
    sizerBoutonImg->Add(boutonImage2,    0, wxALL, 0);
    sizerBoutonImg->Add(boutonImage3,    0, wxALL, 0);


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
            LogFileAppend(_T("FuXFenetre::SeparationPanel - PRINCIPAL"));
            break;
        case LISTELECTURE:
            sizerDroit->Detach(m_sizerDroitPlaylist);
            m_fenetresDetachables->Add(this, (wxWindow*) m_playList, m_sizerDroitPlaylist, LISTELECTURE, event.GetId(), _("Liste de lecture - Fu(X) 2.0"));
            m_sizerDroitPlaylist = NULL;
            LogFileAppend(_T("FuXFenetre::SeparationPanel - LISTELECTURE"));
            break;
        case GESTIONPERIPH:
            sizerDroit->Detach(m_sizerRightExplorer);
            m_fenetresDetachables->Add(this, (wxWindow*) m_driveManagersPanel, m_sizerRightExplorer, GESTIONPERIPH, event.GetId(), _("Exploration - Fu(X) 2.0"));
            m_sizerRightExplorer = NULL;
            LogFileAppend(_T("FuXFenetre::SeparationPanel - GESTIONPERIPH"));
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
            LogFileAppend(_T("FuXFenetre::ReunionPanel - PRINCIPAL"));
            break;
        case LISTELECTURE:
            m_sizerDroitPlaylist = (wxBoxSizer*)f->RetourNormale();
            s = m_sizerDroitPlaylist;
            LogFileAppend(_T("FuXFenetre::ReunionPanel - LISTELECTURE"));
            break;
        case GESTIONPERIPH:
            m_sizerRightExplorer = (wxBoxSizer*)f->RetourNormale();
            s = m_sizerRightExplorer;
            LogFileAppend(_T("FuXFenetre::ReunionPanel - GESTIONPERIPH"));
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
    MusicManagerSwitcher::get().getMusicPlayer().setVolume(SliderSon::Get()->GetValue());
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
    LogFileAppend(_T("FuXFenetre::EventMenuBarPlay - Barre de menu"));

    playButtonPressed();
}

/**
 * Relance la lecture si un titre est chargé, ouvre une fenêtre de sélection sinon
 */
void FuXFenetre::EventPlayButtonPressed(wxCommandEvent &WXUNUSED(event))
{
    LogFileAppend(_T("FuXFenetre::BoutonLecture"));

    playButtonPressed();
    //SwitchWindow();
}

/**
 * Arrête la chanson
 */
void FuXFenetre::EventMusicStop(wxCommandEvent &WXUNUSED(event))
{
    LogFileAppend(_T("FuXFenetre::Stop"));

    MusicManagerSwitcher::get().getMusicPlayer().stop();
    drawPlayImageStatus();
}

/**
 * Palys the next title or a random title.
 */
void FuXFenetre::EventMusicNext(wxCommandEvent &WXUNUSED(event))
{
    LogFileAppend(_T("FuXFenetre::EventMusicNext"));

    MusicManagerSwitcher::get().playNextOrRandomMusic();
    SwitchWindow();
}

/**
 * Passe au titre précédent
 */
void FuXFenetre::EventMusicPrevious(wxCommandEvent &WXUNUSED(event))
{
    LogFileAppend(_T("FuXFenetre::Precedent"));

    MusicManagerSwitcher::get().playPreviousOrRandomMusic();
    SwitchWindow();
}

/**
 * Active/Désactive la répétition
 */
void FuXFenetre::EventMusicRepete(wxCommandEvent &WXUNUSED(event))
{
    MusicManagerSwitcher::get().setRepete(!MusicManagerSwitcher::get().isRepete());
}

/**
 * Active/Désactive la lecture aléatoire
 */
void FuXFenetre::EventMusicRandomize(wxCommandEvent &WXUNUSED(event))
{
    MusicManagerSwitcher::get().setRandom(!MusicManagerSwitcher::get().isRandom());
}

/**
 * Ouvre une fenêtre pour choisir le ou les titres de musique à lire. Ajoute le(s) titre(s) à liste si celle-ci n'est pas vide
 */
void FuXFenetre::EventOpenDialogToPlayMusic(wxCommandEvent &WXUNUSED(event))
{
    LogFileAppend(_T("FuXFenetre::EventOpenDialogToPlayMusic"));

    openDialogToPlayMusic();
}

/**
 * Ouvre une fenêtre afin de choisir une liste de lecture enregistrée
 */
void FuXFenetre::EventOpenDialogToSelectPlayListFile(wxCommandEvent &WXUNUSED(event))
{
    LogFileAppend(_T("FuXFenetre::EventOpenDialogToSelectPlayListFile"));

    openDialogToSelectPlayListFile();
}

/**
 * Supprime le titre en cours de diffusion de la liste de lecture
 */
void FuXFenetre::EventDeleteCurrentPlayingTitle(wxCommandEvent &WXUNUSED(event))
{
    LogFileAppend(_T("FuXFenetre::EventDeleteCurrentPlayingTitle"));

    deleteCurrentPlayingTitle();
    SwitchWindow();
}

/**
 * Provoque les changements nécessaires afin de s'adapter à la nouvelle situation : changement de titre ou suppression de tous les titres
 */
void FuXFenetre::EventMusicChanged(wxCommandEvent &WXUNUSED(event))
{
    LogFileAppend(_T("FuXFenetre::ChangementChanson"));

    m_playList->GetPlayListTableau()->updateColors();
    changePlayPauseImageStatus();
}

/**
 * Provoque une mise à jour de la liste de lecture affichée à l'utilisateur
 */
void FuXFenetre::EventUpdatePlayLists(wxCommandEvent &WXUNUSED(event))
{
    m_playList->GetPlayListTableau()->updateLines();
//    GestPeriph::Get()->MAJPlaylist();
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
    wxString message("Nom : Fu(X) 2.0\tVersion : a5\tDate : ");
    message.Append(__DATE__);
    message.Append("\n\n");
    message.Append("Auteur : David Lecoconnier (david.lecoconnier@free.fr)");
    message.Append("\n\n");
    message.Append("Interface réalisée avec wxWidgets 3.0.2");
    message.Append("\n\n\n");
    message.Append("Copyright © 2009-2015 David Lecoconnier, tous droits réservés");
    message.Append("\n\n");
    message.Append("FMOD Sound System, copyright © Firelight Technologies Pty, Ltd., 1994-2007");
    message.Append("\n");
    wxMessageBox(message, _("A propos"), wxOK | wxICON_INFORMATION, this);
}

/**
 * Affiche le site de l'application à travers le navigateur internet
 */
void FuXFenetre::MenuSiteWeb(wxCommandEvent &WXUNUSED(event))
{
    wxLaunchDefaultBrowser(_T("http://getfux.fr/"));
}

/**
 * Affiche la page d'aide à travers le navigateur internet
 */
void FuXFenetre::MenuAide(wxCommandEvent &WXUNUSED(event))
{
    wxLaunchDefaultBrowser(_T("http://getfux.fr/aide.php"));
}


// Internal management event //

/**
 * Modifie l'image du bouton lecture/pause en fonction de l'état du système
 */
void FuXFenetre::EventSwitchButtonImage(wxCommandEvent &WXUNUSED(event))
{
    LogFileAppend(_T("FuXFenetre::BoutonChangeImage - bascule image Lecture/Pause"));

    changePlayPauseImageStatus();
    SwitchWindow();
}

/**
 * Évènement provenant du serveur de l'application : un titre ajouté
 */
void FuXFenetre::EvtServeurAjout(wxCommandEvent &event)
{
    LogFileAppend(_T("FuXFenetre::EvtServeurAjout"));

    wxArrayString *a = m_serveur->GetConnexionTableau(event.GetInt());

    //bool lire = Musique::Get()->IsContainingMus();
    MusicManagerSwitcher::get().parse(*a, true);
    /*if (lire && !a->Item(i).Lower().EndsWith(_T(".m3u")))
        Musique::Get()->ChangementChanson(-1, a->Item(0));*/
    m_serveur->Deconnecter(event.GetInt());
}

/**
 * Informe le panel du graphe que le titre de la chanson a été modifié.
 */
void FuXFenetre::OnTitreChange(wxCommandEvent &WXUNUSED(event))
{
    LogFileAppend(_T("FuXFenetre::OnTitreChange"));
    m_musiqueGraph->TitreChange();
}

/**
 * Évènements clavier - Utilisation des raccourcis généraux (titre suivant, volume, ...)
 * @param event l'événement à analyser
 */
void FuXFenetre::OnKeyDownRaccourci(wxKeyEvent &event)
{
    LogFileAppend(_T("FuXFenetre::OnKeyDownRaccourci"));

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
    m_playList->ViderPanneauTAG();
    m_playList->GetPlayListTableau()->DeleteAllItems();
}

/// Internal management methods ///

void FuXFenetre::changePlayPauseImageStatus()
{
    if (MusicManagerSwitcher::get().getMusicPlayer().isPlaying())
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
    if (MusicManagerSwitcher::get().getMusicPlayer().isPlaying())//En lecture
    {
        MusicManagerSwitcher::get().getMusicPlayer().setPause(true);
    }
    else if (MusicManagerSwitcher::get().empty())//Pas de fichier chargé
        openDialogToPlayMusic();
    else if (MusicManagerSwitcher::get().getMusicPlayer().isPaused())//En pause
    {
        MusicManagerSwitcher::get().getMusicPlayer().setPause(false);
    }
    else//Musique stoppée
    {
        MusicManagerSwitcher::get().playSameMusic();
    }
}

void FuXFenetre::openDialogToPlayMusic()
{
    wxFileDialog navig(this, _("Choisissez une chanson"), Parametre::Get()->getRepertoireDefaut(), _T(""), Parametre::Get()->getExtensionValideMusique(), wxFD_OPEN | wxFD_MULTIPLE | wxFD_FILE_MUST_EXIST);//";*.wav");

    if (navig.ShowModal() == wxID_OK)
    {
        wxArrayString musNav;
        navig.GetPaths(musNav);

        if (musNav.GetCount() == 1 && MusicManagerSwitcher::get().empty())
        {
            MusicManagerSwitcher::get().playMusicThenParse(musNav.Item(0));
        }
        else
            MusicManagerSwitcher::get().parse(musNav, false);
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
                MusicManagerSwitcher::get().parse(chemin);
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
    MusicManagerSwitcher::get().deleteCurrentTitle();
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
                    if (m_sizerDroitPlaylist)
                        sizerDroit->Hide(m_sizerDroitPlaylist);
                    break;
                case GESTIONPERIPH:
                    if (m_sizerRightExplorer)
                        sizerDroit->Hide(m_sizerRightExplorer);
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
                sizerDroit->Show(m_sizerDroitPlaylist);
                break;
            case GESTIONPERIPH:
                m_FenetreActuel = GESTIONPERIPH;
                sizerDroit->Show(m_sizerRightExplorer);
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
            m_driveManagersPanel->SetFocus();
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
                    MusicManagerSwitcher::get().parse(cheminM3U);
                }
                else wxLogMessage(_("Impossible d'ouvrir le fichier, celui-ci est vierge !"));
                    test.Close();
            }
        }
        else if (nodeReprise->GetAttribute(_("type"), wxEmptyString) == _T("MP3"))
        {
            MusicManagerSwitcher::get().playMusicThenParse(nodeReprise->GetNodeContent());
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
                    MusicManagerSwitcher::get().parse(cheminM3U);
                }
                else wxLogMessage(_("Impossible d'ouvrir le fichier, celui-ci est vierge !"));
                test.Close();
            }
        }
        else if (prefFile.GetLine(3).IsSameAs(_T("Reprise= MP3")))
        {
            MusicManagerSwitcher::get().playMusicThenParse(prefFile.GetLine(4).AfterFirst(' '));
        }
    }
}

/**
 * Lit les préférences se trouvant dans le fichier de configuration si celui-ci existe
 * @param loadDefaultMusic Si vrai, l'application cherche à lancer le fichier enregistré comme devant être lancé à l'ouverture de l'application
 */
void FuXFenetre::readPreferences(bool loadDefaultMusic)
{
    LogFileAppend(_T("FuXFenetre::readPreferences"));

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

void FuXFenetre::onUpdateLine(wxCommandEvent& event)
{
    m_playList->GetPlayListTableau()->onUpdateLine(event);
}

void FuXFenetre::onDeleteLine(wxCommandEvent& event)
{
    m_playList->GetPlayListTableau()->onDeleteLine(event);
    DeletedLines* deletedLines = static_cast<DeletedLines*>(event.GetClientData());
    delete deletedLines;
    event.SetClientData(NULL);
}

void FuXFenetre::onEventUpdatePlaylistSearchDone(wxCommandEvent &WXUNUSED(event))
{
    m_playList->GetPlayListTableau()->updateLines();
}

void FuXFenetre::onDirFileDialogClose(wxCommandEvent& event)
{
    m_mediator.getDirFileDialog().close();
    event.StopPropagation();
}

void FuXFenetre::onDirFileDialogRange(wxCommandEvent& event)
{
    m_mediator.getDirFileDialog().setRange(event.GetInt());
    event.StopPropagation();
}

void FuXFenetre::onDirFileDialogUpdate(wxCommandEvent& event)
{
    m_mediator.getDirFileDialog().update(event.GetInt(), event.GetString());
    event.StopPropagation();
}

void FuXFenetre::onDirFileRecurseQuestion(wxCommandEvent& event)
{
    //wxLogMessage(wxString::Format("%p :", event.GetClientData()));
    tools::dir::AskForRecursiveOperationData* data = static_cast<tools::dir::AskForRecursiveOperationData*>(event.GetClientData());

    if (NULL == data)
        return;

    m_mediator.getDirFileDialog().askQuestion(*data);
}

