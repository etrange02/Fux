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

#include "../include/Fenetre.h"

/**
 * @class FuXFenetre
 * @brief Interface principale de l'application : barre de menu. Elle contient plusieurs wxSizer.
 */

BEGIN_EVENT_TABLE(FuXFenetre, wxFrame)
    EVT_MENU(ID_APP_BAR_QUITTER, FuXFenetre::Quitter)
    EVT_MENU(ID_APP_BAR_LECTURE, FuXFenetre::Lecture)
    EVT_MENU(ID_APP_BAR_SUIVANT, FuXFenetre::Suivant)
    EVT_MENU(ID_APP_BAR_PRECEDENT, FuXFenetre::Precedent)
    EVT_MENU(ID_APP_BAR_STOP, FuXFenetre::Stop)
    EVT_MENU(ID_APP_BAR_REPETE, FuXFenetre::Repete)
    EVT_MENU(ID_APP_BAR_ALEATOIRE, FuXFenetre::Aleatoire)
    EVT_MENU(ID_APP_BAR_OUVRIR, FuXFenetre::OuvrirChanson)
    EVT_MENU(ID_APP_BAR_CHARGER_M3U, FuXFenetre::OuvrirM3U)
    EVT_MENU(ID_APP_BAR_CREER_PLAYLIST, FuXFenetre::SauvegardeListeLecture)
    EVT_MENU(ID_APP_BAR_SUPPRIMER, FuXFenetre::SupprimerListe)
    EVT_MENU(ID_APP_BAR_MAJ_PLAYLIST, FuXFenetre::MAJplaylist)
    EVT_MENU(ID_APP_BAR_A_PROPOS, FuXFenetre::MenuAbout)
    EVT_MENU(ID_APP_BAR_SITE_INTERNET, FuXFenetre::MenuSiteWeb)
    EVT_MENU(ID_APP_BAR_AIDE, FuXFenetre::MenuAide)
    EVT_MENU(ID_APP_BAR_COULEUR_NOUVEL_ENSEMBLE, FuXFenetre::AffichCouleurNouv)
    EVT_MENU(ID_APP_BAR_COULEUR_MODIFIER_APPLIQ_JEU, FuXFenetre::AffichCouleurMod)
    EVT_MENU(ID_APP_BAR_SON_NOUVEL_ENSEMBLE, FuXFenetre::AffichSonNouv)
    EVT_MENU(ID_APP_BAR_SON_MODIFIER_APPLIQ_JEU, FuXFenetre::AffichSonMod)
    EVT_MENU(ID_APP_BAR_DEFAUT, FuXFenetre::AfficheDefaut)
    EVT_BUTTON(ID_APP_AFF_BOUTON_PRECEDENT, FuXFenetre::Precedent)//////////////////////
    EVT_BUTTON(ID_APP_AFF_BOUTON_SUIVANT, FuXFenetre::Suivant)//////////////////////
    EVT_BUTTON(ID_APP_AFF_BOUTON_SUPPRIMER, FuXFenetre::SupprimerListe)//////////////////////
    EVT_BUTTON(ID_APP_AFF_BOUTON_LECTURE, FuXFenetre::BoutonLecture)//////////////////////
    EVT_BUTTON(ID_APP_AFF_PRINCIPAL, FuXFenetre::AffichePrincipal)
    EVT_BUTTON(ID_APP_AFF_PREFERENCE, FuXFenetre::AffichePreference)
    EVT_BUTTON(ID_APP_AFF_EXTRACTEUR, FuXFenetre::AfficheEncodage)
    EVT_BUTTON(ID_APP_AFF_PLAYIST, FuXFenetre::AfficheListeDeLecture)
    EVT_BUTTON(ID_APP_AFF_MODULE_IPOD, FuXFenetre::AfficheGestPeriph)
    EVT_COMMAND_SCROLL(ID_APP_SLIDER_SON, FuXFenetre::ModifSon)
    EVT_MUSIQUE_CHANGE(wxID_ANY, FuXFenetre::ChangementChanson)
    EVT_MUSIQUE_MAJ(wxID_ANY, FuXFenetre::MAJplaylist)
    EVT_MUSIQUE_LECTURE(wxID_ANY, FuXFenetre::BoutonChangeImage)
    EVT_SERVEUR(wxID_ANY, FuXFenetre::EvtServeurAjout)
    EVT_MUSIQUE_GRAPH(wxID_ANY, FuXFenetre::OnTitreChange)
    EVT_MUSIQUE_SUPPRESSION(wxID_ANY, FuXFenetre::SupprimerListe)
    EVT_CHAR_HOOK(FuXFenetre::OnKeyDownRaccourci)
    EVT_BOUTON_FENETRE_DETACHABLE(wxID_ANY, FuXFenetre::SeparationPanel)
    EVT_FERMER_FENETRE_DETACHABLE(wxID_ANY, FuXFenetre::ReunionPanel)
END_EVENT_TABLE()

static wxMutex s_mutexProtectionDemarrage;

/**
 * Constructeur
 * @param argc Entier indiquant la taille du tableau
 * @param argv Tableau de caractères
 */
FuXFenetre::FuXFenetre(int argc, wxChar **argv) : wxFrame(NULL, wxID_ANY, _T("Fu(X) 2.0"))
{
    wxMutexLocker lock(s_mutexProtectionDemarrage);
    m_FenetreActuel = PRINCIPAL;
    m_nouvelleFenetre = PRINCIPAL;
    sizerPrincipalH = new wxBoxSizer(wxHORIZONTAL);
    sizerGaucheV = new wxBoxSizer(wxVERTICAL);
    sizerPrincipalH->Add(sizerGaucheV, 0, wxALL | wxEXPAND, 0);
    m_MAJliste = false;

    ConstructionBarre();
    ConstructionSizerGauche();

    Initialisation();
    CreerPages();

    SetSizer(sizerPrincipalH);
    sizerPrincipalH->SetSizeHints(this);

    LecturePreference(argc <= 1);

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
                    m_chanson->CopieFichier(fichierMem.GetFullPath());
                    m_chanson->ChangementChanson();
                    m_MAJliste = true;
                }
                else wxLogMessage(_("Impossible de charger le fichier, celui-ci est vierge !"));
                test.Close();
            }
        }
        else if (Parametre::Get()->islisable(fichierMem.GetExt().Lower()))
        {
            m_chanson->Lecture(fichierMem.GetFullPath());
            m_chanson->Listage();
            m_MAJliste = true;
        }
    }

    SetIcon(wxIcon(Parametre::Get()->getRepertoireExecutableLib(_T("play.ico")), wxBITMAP_TYPE_ICO));

    m_TimerGraph.setMusique();
    if (m_MAJliste)
        m_playList->GetListeLecture()->MAJ();

    ChangeFenetre();
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
//    s_mutexProtectionDemarrage.Lock();
//    s_mutexProtectionDemarrage.Unlock();
    //m_fenetresDetachables->Vider();
    delete m_fenetresDetachables;
    delete m_serveur;
    BDDThread::Get()->Stop();
    m_TimerGraph.Stop();
    delete[] m_imageBouton;
    delete m_chanson;
    delete m_musiqueGraph;
    delete m_playList;
    delete m_panelsAssocies;
    delete m_periph;
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::~FuXFenetre - fin"));
    #endif
}

/**
 * Initialise les instances des classes nécessaire au lancement de Fu(X)
 */
void FuXFenetre::Initialisation()
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("Début de FuXFenetre::Initialisation"));
    #endif

    int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};
    m_chanson = new Musique(this);
    m_musiqueGraph = new MusiqueGraph(this, args);
    m_playList = new PlayList;
    m_periph = new GestPeriph;

    BDDThread::Get();

    #if DEBUG
    FichierLog::Get()->Ajouter(_T("Fin de FuXFenetre::Initialisation"));
    #endif
}

/**
 * Attache les panels à la fenêtre principal
 */
void FuXFenetre::CreerPages()
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::CreerPages() - Création des onglets et des pages manquantes"));
    #endif

    sizerDroitPrincipal = new wxBoxSizer(wxVERTICAL);
    m_TimerGraph.Start(70, false);

    sizerDroitPrincipal->Add(m_musiqueGraph, 1, wxEXPAND, 0);
    sizerDroitPrincipal->Show(m_musiqueGraph);
    sizerDroitPrincipal->Layout();
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::CreerPages() - Graphe"));
    #endif
    ///////////////////////////////////////////////////////
    sizerDroitPreference = new wxBoxSizer(wxVERTICAL);
    NotebookPreference = new wxNotebook(this, -1);

    m_pageCouleur.Create(NotebookPreference, -1);
    m_pageCouleur.Creer();

    m_pageSon.Create(NotebookPreference, -1);
    m_pageSon.Creer();

    m_pageDefaut.Create(NotebookPreference, -1);
    m_pageDefaut.Creer();

    NotebookPreference->AddPage(&m_pageCouleur, _("Couleur"));
    NotebookPreference->AddPage(&m_pageSon, _("Son"));
    NotebookPreference->AddPage(&m_pageDefaut, _("Défaut"));

    sizerDroitPreference->Add(NotebookPreference, 1, wxEXPAND, 0);
    sizerDroitPreference->Show(NotebookPreference);
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
    m_playList->Creer(this, m_MAJliste);

    //m_grille = new PlayListGrille(this);
    sizerDroitPlayist->Add(m_playList, 1, wxALL | wxEXPAND, 0);
    sizerDroitPlayist->Show(m_playList);

    sizerDroitPlayist->Layout();
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::CreerPages() - Playlist"));
    #endif
    ////////////////////////////////////////////////////////////////////
    sizerDroitIPod = new wxBoxSizer(wxVERTICAL);
    m_periph->Creer(this);

    sizerDroitIPod->Add(m_periph, 1, wxALL | wxEXPAND, 0);
    sizerDroitIPod->Show(m_periph);
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

    m_panelsAssocies = new bool[5];//{true, true, true, true, true};
    for (int i = 0; i < 5 ; i++)
        m_panelsAssocies[i] = true;

    sizerDroitPrincipal->SetMinSize(512, 292);
    sizerDroitPreference->SetMinSize(512, 256);
    sizerDroitExtracteur->SetMinSize(512, 256);
    sizerDroitPlayist->SetMinSize(512, 256);
    sizerDroitIPod->SetMinSize(512, 256);

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
void FuXFenetre::ConstructionBarre()
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::ConstructionBarre"));
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
    menuCouleur = new wxMenu;
    menuCouleur->Append(ID_APP_BAR_COULEUR_NOUVEL_ENSEMBLE, _("Nouveau jeu de couleur"));
    menuCouleur->Append(ID_APP_BAR_COULEUR_MODIFIER_APPLIQ_JEU, _("Modifier/Appliquer un jeu de couleur existant"));
    menuSon = new wxMenu;
    menuSon->Append(ID_APP_BAR_SON_NOUVEL_ENSEMBLE, _("Nouvel ensemble audio"));
    menuSon->Append(ID_APP_BAR_SON_MODIFIER_APPLIQ_JEU, _("Modifier/Appliquer une présélection audio"));
    menuPreferences->AppendSubMenu(menuCouleur, _("Couleur"));
    menuPreferences->AppendSubMenu(menuSon, _("Son"));
    menuPreferences->Append(ID_APP_BAR_DEFAUT, _("Défaut"));

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
void FuXFenetre::ConstructionSizerGauche()
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::ConstructionSizerGauche"));
    #endif

    //sizerGaucheV = new wxBoxSizer(wxVERTICAL);
    SliderSon *slide = new SliderSon(this);
    sizerGaucheV->Add(slide, 0, wxUP | wxBOTTOM | wxEXPAND, 5);

    wxGridSizer *sizerBoutonImg = new wxGridSizer(1, 4, 0, 0);
    sizerGaucheV->Add(sizerBoutonImg, 0, wxBOTTOM | wxRIGHT | wxLEFT, 5);
    wxImage::AddHandler(new wxPNGHandler);
    wxImage::AddHandler(new wxJPEGHandler);

    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::ConstructionSizerGauche - chargement des images"));
    #endif
    m_imageBouton = new wxBitmap[6];
    m_imageBouton[PREC].LoadFile(Parametre::Get()->getRepertoireExecutableLib(_T("prec.png")), wxBITMAP_TYPE_PNG);
    m_imageBouton[LECT].LoadFile(Parametre::Get()->getRepertoireExecutableLib(_T("lect.png")), wxBITMAP_TYPE_PNG);
    m_imageBouton[PAUS].LoadFile(Parametre::Get()->getRepertoireExecutableLib(_T("paus.png")), wxBITMAP_TYPE_PNG);
    m_imageBouton[SUIV].LoadFile(Parametre::Get()->getRepertoireExecutableLib(_T("suiv.png")), wxBITMAP_TYPE_PNG);
    m_imageBouton[SUPPR].LoadFile(Parametre::Get()->getRepertoireExecutableLib(_T("suppr.png")), wxBITMAP_TYPE_PNG);
    m_imageBouton[5].LoadFile(Parametre::Get()->getRepertoireExecutableLib(_T("suppr2.png")), wxBITMAP_TYPE_PNG);

    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::ConstructionSizerGauche - Application des images aux boutons"));
    #endif
    wxBitmapButton *boutonImage0 = new wxBitmapButton(this, ID_APP_AFF_BOUTON_PRECEDENT, m_imageBouton[PREC], wxDefaultPosition, wxSize(35, 35));
    m_boutonImageLP = new wxBitmapButton(this, ID_APP_AFF_BOUTON_LECTURE, m_imageBouton[LECT], wxDefaultPosition, wxSize(35, 35));
    wxBitmapButton *boutonImage2 = new wxBitmapButton(this, ID_APP_AFF_BOUTON_SUIVANT, m_imageBouton[SUIV], wxDefaultPosition, wxSize(35, 35));
    wxBitmapButton *boutonImage3 = new wxBitmapButton(this, ID_APP_AFF_BOUTON_SUPPRIMER, m_imageBouton[SUPPR], wxDefaultPosition, wxSize(35, 35));
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::ConstructionSizerGauche - Fin application des images"));
    #endif

    sizerBoutonImg->Add(boutonImage0, 0, wxALL, 0);
    sizerBoutonImg->Add(m_boutonImageLP, 0, wxALL, 0);
    sizerBoutonImg->Add(boutonImage2, 0, wxALL, 0);
    sizerBoutonImg->Add(boutonImage3, 0, wxALL, 0);


    //wxButton *BoutonG_EcranPrincipal = new wxButton(this, ID_APP_AFF_PRINCIPAL, _("Ecran principal"), wxDefaultPosition, wxSize(140, 38));
    wxButton *BoutonG_EcranPrincipal = new BoutonFenetreDetachable(this, ID_APP_AFF_PRINCIPAL, _("Ecran principal"), wxSize(140, 38), PRINCIPAL);
    sizerGaucheV->Add(BoutonG_EcranPrincipal, 0, wxALL, 5);

    //wxButton *BoutonG_Playist = new wxButton(this, ID_APP_AFF_PLAYIST, _("Liste de lecture"), wxDefaultPosition, wxSize(140, 38));
    wxButton *BoutonG_Playist = new BoutonFenetreDetachable(this, ID_APP_AFF_PLAYIST, _("Liste de lecture"), wxSize(140, 38), LISTELECTURE);
    sizerGaucheV->Add(BoutonG_Playist, 0, wxBOTTOM | wxRIGHT | wxLEFT, 5);

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

/**
 * Barre de menu : Page des préférences, onglet Défaut
 */
void FuXFenetre::AfficheDefaut(wxCommandEvent &WXUNUSED(event))
{
    m_nouvelleFenetre = PREFERENCE;
    ChangeFenetre();
    NotebookPreference->ChangeSelection(2);
}

/**
 * Opère un basculement sur la page contenant le graphe (page principal)
 */
void FuXFenetre::AffichePrincipal(wxCommandEvent &WXUNUSED(event))
{
    m_nouvelleFenetre = PRINCIPAL;
    ChangeFenetre();
}

/**
 * Opère un basculement sur la page contenant les préférences
 */
void FuXFenetre::AffichePreference(wxCommandEvent &WXUNUSED(event))
{
    m_nouvelleFenetre = PREFERENCE;
    ChangeFenetre();
}

/**
 * Opère un basculement sur la page contenant la gestion de CDs
 */
void FuXFenetre::AfficheEncodage(wxCommandEvent &WXUNUSED(event))
{
    m_nouvelleFenetre = ENCODAGE;
    ChangeFenetre();
}

/**
 * Opère un basculement sur la page affichant la liste complète des titres mis en mémoire
 */
void FuXFenetre::AfficheListeDeLecture(wxCommandEvent &WXUNUSED(event))
{
    m_nouvelleFenetre = LISTELECTURE;
    ChangeFenetre();
}

/**
 * Opère un basculement sur la page permettant une exploration de l'ordinateur
 */
void FuXFenetre::AfficheGestPeriph(wxCommandEvent &WXUNUSED(event))
{
    m_nouvelleFenetre = GESTIONPERIPH;
    ChangeFenetre();
}

/**
 * Provoque la fermeture du programme
 */
void FuXFenetre::Quitter(wxCommandEvent &WXUNUSED(event))
{    Close(true);}

/**
 * Barre de menu : relance la lecture
 */
void FuXFenetre::Lecture(wxCommandEvent &WXUNUSED(event))
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::Lecture - Barre de menu"));
    #endif
    if (m_chanson->GetLecture())
        m_chanson->SetPause(true);
    else if (m_chanson->GetPause())
        m_chanson->SetPause(false);
    else
        m_chanson->ChangementChanson(IDENTIQUE);

    if (m_chanson->GetLecture())
    {
        m_boutonImageLP->SetBitmapLabel(m_imageBouton[PAUS]);
        menuControle->FindItem(ID_APP_BAR_LECTURE)->SetItemLabel(_("Pause\tCtrl-P"));
    }
    else
    {
        m_boutonImageLP->SetBitmapLabel(m_imageBouton[LECT]);
        menuControle->FindItem(ID_APP_BAR_LECTURE)->SetItemLabel(_("Lecture\tCtrl-P"));
    }
}

/**
 * Relance la lecture si un titre est chargé, ouvre une fenêtre de sélection sinon
 */
void FuXFenetre::BoutonLecture(wxCommandEvent &event)
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::BoutonLecture"));
    #endif
    if (m_chanson->GetLecture())//En lecture
    {
        m_chanson->SetPause(true);
        m_boutonImageLP->SetBitmapLabel(m_imageBouton[LECT]);
        menuControle->FindItem(ID_APP_BAR_LECTURE)->SetItemLabel(_("Pause\tCtrl-P"));//"));//
    }
    else if (m_chanson->GetFichier()->GetNombreFichier() == 0)//Pas de fichier chargé
        OuvrirChanson(event);
    else if (m_chanson->GetPause())//En pause
    {
        m_chanson->SetPause(false);
        m_boutonImageLP->SetBitmapLabel(m_imageBouton[PAUS]);
        menuControle->FindItem(ID_APP_BAR_LECTURE)->SetItemLabel(_("Lecture\tCtrl-P"));//"));//
    }
    else//Musique stoppée
    {
        m_chanson->ChangementChanson(IDENTIQUE);
        if (m_chanson->GetLecture())
        {
            m_boutonImageLP->SetBitmapLabel(m_imageBouton[PAUS]);
            menuControle->FindItem(ID_APP_BAR_LECTURE)->SetItemLabel(_("Pause\tCtrl-P"));//"));//
        }
        else
        {
            m_boutonImageLP->SetBitmapLabel(m_imageBouton[LECT]);
            menuControle->FindItem(ID_APP_BAR_LECTURE)->SetItemLabel(_("Lecture\tCtrl-P"));//"));//
        }
    }
    ChangeFenetre();
}

/**
 * Modifie l'image du bouton lecture/pause en fonction de l'état du système
 */
void FuXFenetre::BoutonChangeImage(wxCommandEvent &event)
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::BoutonChangeImage - bascule image Lecture/Pause"));
    #endif
    if (event.GetInt() == 1)
    {
        m_boutonImageLP->SetBitmapLabel(m_imageBouton[LECT]);
        menuControle->FindItem(ID_APP_BAR_LECTURE)->SetItemLabel(_("Lecture\tCtrl-P"));
    }
    else
    {
        m_boutonImageLP->SetBitmapLabel(m_imageBouton[PAUS]);
        menuControle->FindItem(ID_APP_BAR_LECTURE)->SetItemLabel(_("Pause\tCtrl-P"));
    }
    ChangeFenetre();
}

/**
 * Arrête la chanson
 */
void FuXFenetre::Stop(wxCommandEvent &WXUNUSED(event))
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::Stop"));
    #endif
    m_chanson->SetStop();
    menuControle->FindItem(ID_APP_BAR_LECTURE)->SetItemLabel(_("Lecture\tCtrl-P"));
    m_boutonImageLP->SetBitmapLabel(m_imageBouton[LECT]);
}

/**
 * Passe au titre suivant
 */
void FuXFenetre::Suivant(wxCommandEvent &WXUNUSED(event))
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::suivant"));
    #endif
    m_chanson->ChangementChanson(SUIVANT);
    ChangeFenetre();
}

/**
 * Passe au titre précédent
 */
void FuXFenetre::Precedent(wxCommandEvent &WXUNUSED(event))
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::Precedent"));
    #endif
    m_chanson->ChangementChanson(PRECEDENT);
    ChangeFenetre();
}

/**
 * Active/Désactive la répétition
 */
void FuXFenetre::Repete(wxCommandEvent &WXUNUSED(event))
{    m_chanson->SetRepete(!m_chanson->GetRepete());}

/**
 * Active/Désactive la lecture aléatoire
 */
void FuXFenetre::Aleatoire(wxCommandEvent &WXUNUSED(event))
{    m_chanson->SetAleatoire(!m_chanson->GetAleatoire());}

/**
 * Ouvre une fenêtre pour choisir le ou les titres de musique à lire. Ajoute le(s) titre(s) à liste si celle-ci n'est pas vide
 */
void FuXFenetre::OuvrirChanson(wxCommandEvent &WXUNUSED(event))
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::OuvrirChanson"));
    #endif
    //int ouvert = 0;
    wxFileDialog navig(this, _("Choisissez une chanson"), Parametre::Get()->getRepertoireDefaut(), _T(""), Parametre::Get()->getExtensionValideMusique(), wxFD_OPEN | wxFD_MULTIPLE | wxFD_FILE_MUST_EXIST);//";*.wav");

    int result=navig.ShowModal();

    if (result==wxID_CANCEL) return;
    //if (ouvert == wxID_OK)
    {
        //return;
        wxArrayString musNav;
        navig.GetPaths(musNav);
        /*for (int i = 0; i<musNav.GetCount(); i++)
            musNav.Item(i).SetChar(0, musNav.Item(i).Upper()[0]);*/

        if (m_chanson->GetFichier()->GetNombreFichier() == 0)
        {
            m_chanson->Lecture(musNav.Item(0));
            if (musNav.GetCount() == 1)
                m_chanson->Listage();
            else if (musNav.GetCount() >= 2)
                m_chanson->Listage(&musNav);
        }
        else
        {
            if (musNav.GetCount() == 1)
                m_chanson->Listage(musNav.Item(0));
            else if (musNav.GetCount() >= 2)
                m_chanson->Listage(&musNav);
        }
        musNav.Clear();
        m_playList->GetListeLecture()->MAJ();
        GestPeriph::Get()->MAJPlaylist();
    }
}

/**
 * Ouvre une fenêtre afin de choisir une liste de lecture enregistrée
 */
void FuXFenetre::OuvrirM3U(wxCommandEvent &WXUNUSED(event))
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::OuvrirM3U"));
    #endif
    int ouvert = 0;
    //wxFileDialog navig(this, _("Choisissez une playlist (fichier .m3u)"), Parametre::Get()->getRepertoireParametre(_T("Play_list_M3U")), _T(""), _T("Playlist (*.m3u)|*.m3u"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    wxFileDialog navig(this, _("Choisissez une playlist (fichier .m3u)"), wxEmptyString,wxEmptyString, wxEmptyString, wxFD_OPEN);
    ouvert = navig.ShowModal();

    if (ouvert == wxID_OK)
    {
        return;
        wxString chemin;
        chemin = navig.GetPath();
        //chemin = _T("C:\\Users\\Etrange02\\AppData\\Roaming\\Fu(X)\\Play_list_M3U\\musiques_ok.m3u");

        wxTextFile test(chemin); test.Open();
        if (test.IsOpened())
        {
            int nb = test.GetLineCount();
            test.Close();
            if (nb > 1)
            {
                /*if (m_chanson->GetFichier()->GetNombreFichier() == 0)
                {
                    //int ligne = m_chanson->GetFichier()->GetNombreFichier();
                    m_chanson->CopieFichier(chemin);
                    //m_chanson->ChangementChanson(0, _T(""));
                    //m_chanson->Lecture(m_chanson->GetFichier()->GetNomPosition(0));
                }
                else*/
                m_chanson->CopieFichier(chemin);
                m_playList->GetListeLecture()->MAJ();
                GestPeriph::Get()->MAJPlaylist();
            }
            else
            {
                wxLogMessage(_("Impossible d'ouvrir le fichier, celui-ci est vierge !"));
            }
        }
    }
}

/**
 * Supprime le titre en cours de diffusion de la liste de lecture
 */
void FuXFenetre::SupprimerListe(wxCommandEvent &WXUNUSED(event))
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::SupprimerListe"));
    #endif
    m_playList->GetListeLecture()->supprimerNomLigne(m_chanson->SupprimerNom());
    m_periph->MAJPlaylist();
    ChangeFenetre();
}

/**
 * Échange la page actuelle contre une autre page (effectue l'opération)
 */
void FuXFenetre::ChangeFenetre()/////////////////
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
        }
    }
    switch(m_nouvelleFenetre)
    {
        case PRINCIPAL:
            m_musiqueGraph->SetFocus();
            break;
        case PREFERENCE:
            NotebookPreference->SetFocus();
            break;
        case ENCODAGE:
            break;
        case LISTELECTURE:
            m_playList->GetListeLecture()->SetFocus();
            break;
        case GESTIONPERIPH:
            m_periph->SetFocus();
            break;
    }
    sizerDroit->Layout();
}

/**
 * Modifie le volume sonore
 */
void FuXFenetre::ModifSon(wxScrollEvent &WXUNUSED(event))
{
    m_chanson->SetVolume(SliderSon::Get()->GetValue());
    m_pageSon.SetValeurMusique(SliderSon::Get()->GetValue());
    ChangeFenetre();
}

/**
 * Provoque les changements nécessaires afin de s'adapter à la nouvelle situation : changement de titre ou suppression de tous les titres
 */
void FuXFenetre::ChangementChanson(wxCommandEvent &event)
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::ChangementChanson"));
    #endif
    if (event.GetInt())
    {
        m_playList->GetListeLecture()->ChangementChanson(m_chanson->GetNomPos());
        m_boutonImageLP->SetBitmapLabel(m_imageBouton[PAUS]);
        menuControle->FindItem(ID_APP_BAR_LECTURE)->SetItemLabel(_("Pause\tCtrl-P"));//"));//
    }
    else
    {
        m_boutonImageLP->SetBitmapLabel(m_imageBouton[LECT]);
        menuControle->FindItem(ID_APP_BAR_LECTURE)->SetItemLabel(_("Lecture\tCtrl-P"));//"));//
    }
}

/**
 * Provoque une mise à jour de la liste de lecture affichée à l'utilisateur
 */
void FuXFenetre::MAJplaylist(wxCommandEvent &WXUNUSED(event))
{
    m_playList->GetListeLecture()->MAJ();
    GestPeriph::Get()->MAJPlaylist();
}

/**
 * Affiche une fenêtre permettant l'enregistrement de la liste de lecture
 */
void FuXFenetre::SauvegardeListeLecture(wxCommandEvent &event)
{    m_playList->EnregistrerM3U(event);}

/**
 * Affiche le menu About de l'application
 */
void FuXFenetre::MenuAbout(wxCommandEvent &WXUNUSED(event))
{
    wxString message(_T("Nom : Fu(X) 2.0\tVersion : a5\tDate : ") + wxString(_T(__DATE__)) + _T("\n\nAuteur : David Lecoconnier (etrange02@aol.com)\n\nInterface réalisée avec wxWidgets 2.8.10\n\n\n") +
                        _T("Copyright © 2009-2013 David Lecoconnier, tous droits réservés\n\nFMOD Sound System, copyright © Firelight Technologies Pty, Ltd., 1994-2007\n"));
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

/**
 * Lit les préférences se trouvant dans le fichier de configuration si celui-ci existe
 * @param lecture Si vrai, l'application cherche à lancer le fichier enregistré comme devant être lancé à l'ouverture de l'application
 */
void FuXFenetre::LecturePreference(bool lecture)
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("FuXFenetre::LecturePreference"));
    #endif

    wxString cheminFichier = Parametre::Get()->getRepertoireParametre(_T("Fu(X).conf")) , nomFichierCouleur, nomFichierSon;
    wxTextFile fichierPref(cheminFichier);

    if (!(fichierPref.Exists() && fichierPref.Open()))
        return;

    if (fichierPref.GetLine(0).IsSameAs(_T("#EXTCONF_1")))
    {
        ///////Couleur
        if (!fichierPref.GetLine(1).IsSameAs(_T("Couleur= NON")))
            m_pageCouleur.Couleur_OuvrirFichier(fichierPref.GetLine(1).AfterFirst(' '), false);

        ///////Son
        if (!fichierPref.GetLine(2).IsSameAs(_T("Son= NON")))
        {
            long volume;
            nomFichierSon = Parametre::Get()->getRepertoireParametre(_T("Preference"), _T("Son"), fichierPref.GetLine(2).AfterFirst(' '));
            wxTextFile fichierS(nomFichierSon);
            fichierS.Open();
            if (fichierS.GetLine(0).IsSameAs(_T("#EXTSAUVE_S1")))
            {
                fichierS.GetLine(2).ToLong(&volume);
                m_chanson->SetVolume(volume);
                SliderSon::Get()->SetValue(volume);
                m_pageSon.SetValeurMusique(volume);
                fichierS.Close();
            }
        }
        ///////Sous-dossier
        if (fichierPref.GetLine(5) != _T("SousDossier= NON"))
            Parametre::Get()->setSousDossier(true);
        /////////Reprise
        if (lecture && !(fichierPref.GetLine(3).IsSameAs(_T("Reprise= NON"))))
        {
            if (fichierPref.GetLine(3).IsSameAs(_T("Reprise= M3U")))
            {
                wxString cheminM3U = Parametre::Get()->getRepertoireParametre(_T("Play_list_M3U"), fichierPref.GetLine(4).AfterFirst(' '));

                wxTextFile test(cheminM3U);
                if (test.Open())
                {
                    if (test.GetLineCount() > 1)
                    {
                        m_chanson->CopieFichier(cheminM3U);
                        m_chanson->Lecture(m_chanson->GetFichier()->GetNomPosition(0));
                        m_MAJliste = true;
                    }
                    else wxLogMessage(_("Impossible d'ouvrir le fichier, celui-ci est vierge !"));
                    test.Close();
                }
            }
            else if (fichierPref.GetLine(3).IsSameAs(_T("Reprise= MP3")))
            {
                m_chanson->Lecture(fichierPref.GetLine(4).AfterFirst(' '));
                m_chanson->Listage();
                m_MAJliste = true;
            }
        }
    }
    else
        wxLogMessage(_("Vous devez mettre les paramètres par défaut de Fu(X) à jour.\nMerci de votre compréhension"));

    fichierPref.Close();
}

/**
 * Bascule sur la page des Préférences, onglet Couleur, choix sur nouveau
 */
void FuXFenetre::AffichCouleurNouv(wxCommandEvent &WXUNUSED(event))
{
    m_nouvelleFenetre = PREFERENCE;
    ChangeFenetre();
    NotebookPreference->ChangeSelection(0);
    m_pageCouleur.GetRadioBox()->SetSelection(0);
    m_pageCouleur.Couleur_Modif_Nouveau(0);
}


/**
 * Bascule sur la page des Préférences, onglet Couleur, choix sur modifier
 */
void FuXFenetre::AffichCouleurMod(wxCommandEvent &WXUNUSED(event))
{
    m_nouvelleFenetre = PREFERENCE;
    ChangeFenetre();
    NotebookPreference->ChangeSelection(0);
    m_pageCouleur.GetRadioBox()->SetSelection(1);
    m_pageCouleur.Couleur_Modif_Nouveau(1);
}


/**
 * Bascule sur la page des Préférences, onglet Son, choix sur nouveau
 */
void FuXFenetre::AffichSonNouv(wxCommandEvent &WXUNUSED(event))
{
    m_nouvelleFenetre = PREFERENCE;
    ChangeFenetre();
    NotebookPreference->ChangeSelection(1);
    m_pageSon.GetRadioBox()->SetSelection(0);
    m_pageSon.Son_Modif_Nouveau(0);
}


/**
 * Bascule sur la page des Préférences, onglet Son, choix sur modifier
 */
void FuXFenetre::AffichSonMod(wxCommandEvent &WXUNUSED(event))
{
    m_nouvelleFenetre = PREFERENCE;
    ChangeFenetre();
    NotebookPreference->ChangeSelection(1);
    m_pageSon.GetRadioBox()->SetSelection(1);
    m_pageSon.Son_Modif_Nouveau(1);
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

    bool lire = m_chanson->IsContainingMus();
    m_chanson->Listage(a, false);
    if (lire)
        m_chanson->ChangementChanson(-1, a->Item(0));
    m_serveur->Deconnecter(event.GetInt());
    m_playList->GetListeLecture()->MAJ();
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
            m_fenetresDetachables->Add(this, (wxWindow*) m_periph, sizerDroitIPod, GESTIONPERIPH, event.GetId(), _("Exploration - Fu(X) 2.0"));
            sizerDroitIPod = NULL;
            #if DEBUG
            FichierLog::Get()->Ajouter(_T("FuXFenetre::SeparationPanel - GESTIONPERIPH"));
            #endif
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

    ChangeFenetre();
    m_nouvelleFenetre = event.GetInt();
    ChangeFenetre();
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

