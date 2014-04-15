/***************************************************************
 * Name:      GestionPeriph.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2010-03-04
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../../include/GUI/GestionPeriph.h"
#include <wx/volume.h>

/**
 * @class GestPeriph
 * @brief Page contenant le double explorateur de fichier
 */

static GestPeriph* s_instanceGestPeriph = NULL;

BEGIN_EVENT_TABLE(GestPeriph, wxPanel)
    EVT_BUTTON(ID_PAGE_PERIHERIQUE_BOUTON_MESDOC, GestPeriph::AfficheMenu_MesDoc)
    EVT_MENU(ID_PAGE_PERIHERIQUE_MENU_MESDOC_GAUCHE, GestPeriph::AffListeMesDoc)
    EVT_MENU(ID_PAGE_PERIHERIQUE_MENU_MESDOC_DROITE, GestPeriph::AffListeMesDoc)
    EVT_BUTTON(ID_PAGE_PERIHERIQUE_BOUTON_PERIPH, GestPeriph::AfficheMenu_Periph)
    EVT_BUTTON(ID_PAGE_PERIHERIQUE_BOUTON_AUTRE, GestPeriph::AfficheMenu_Autre)
    EVT_MENU(ID_PAGE_PERIHERIQUE_MENU_PLAYLIST_GAUCHE, GestPeriph::AffListePlaylist)
    EVT_MENU(ID_PAGE_PERIHERIQUE_MENU_PLAYLIST_DROITE, GestPeriph::AffListePlaylist)
    EVT_BUTTON(ID_PAGE_PERIHERIQUE_BOUTON_COPIE, GestPeriph::Copier)
    EVT_BUTTON(ID_PAGE_PERIHERIQUE_BOUTON_SUPPRIMER, GestPeriph::Supprimer)
    EVT_BUTTON(ID_PAGE_PERIHERIQUE_BOUTON_DEPLACE_POURD, GestPeriph::DeplaceD)
    EVT_BUTTON(ID_PAGE_PERIHERIQUE_BOUTON_DEPLACE_POURG, GestPeriph::DeplaceG)
    EVT_LISTE_RENEW(wxID_ANY, GestPeriph::ComparaisonStatutEvt)
END_EVENT_TABLE()

/**
 * Constructeur protégé
 */
GestPeriph::GestPeriph()
{}

/**
 * Destructeur
 */
GestPeriph::~GestPeriph()
{
    //DetruireListes();
    //ThreadFichierFichier::Get()->SetStop();
    //ThreadFichierFichier::Get()->ViderListe();
    //delete ThreadFichierFichier::Get();
    FichierLog::Get()->Ajouter(_T("GestPeriph::~GestPeriph"));
}

/**
 * Retourne l'unique instance de la classe
 * @return l'instance
 */
GestPeriph* GestPeriph::Get()
{
    if (s_instanceGestPeriph == NULL)
        s_instanceGestPeriph = new GestPeriph();
    return s_instanceGestPeriph;
}

void GestPeriph::Delete()
{
    delete s_instanceGestPeriph;
    s_instanceGestPeriph = NULL;
}

/**
 * Crée les composants graphiques de la fenêtre. Elle n'est pas appelé par les constructeur pour ne par surcharger le démarrage de l'application
 * @param Parent la fenêtre parente
 */
void GestPeriph::Creer(wxWindow *Parent)
{
    Create(Parent);
    m_sizer1V = new wxBoxSizer(wxVERTICAL);
    SetSizer(m_sizer1V);

    //Boutons supérieurs//////////////////////////////////////////////////////////
    m_sizerBoutonRacc = new wxFlexGridSizer(1, 3, 10, 10);
    m_sizer1V->Add(m_sizerBoutonRacc, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

    m_boutonMesDoc = new wxButton(this, ID_PAGE_PERIHERIQUE_BOUTON_MESDOC, _("Mes Documents"));
    m_boutonPeriph = new wxButton(this, ID_PAGE_PERIHERIQUE_BOUTON_PERIPH, _("Ordinateur"));
    m_boutonAutre = new wxButton(this, ID_PAGE_PERIHERIQUE_BOUTON_AUTRE, _("Autre"));
    m_sizerBoutonRacc->Add(m_boutonMesDoc, 0, wxALL | wxEXPAND, 0);
    m_sizerBoutonRacc->Add(m_boutonPeriph, 0, wxALL | wxEXPAND, 0);
    m_sizerBoutonRacc->Add(m_boutonAutre, 0, wxALL | wxEXPAND, 0);

    m_boutonMesDoc->SetToolTip(_("Accédez au dossier Mes Documents"));
    m_boutonPeriph->SetToolTip(_("Accédez aux différents lecteurs de votre ordinateur"));
    m_boutonAutre->SetToolTip(_("Accédez aux enregistrements et à la liste de lecture de Fu(X)"));

    //Navigation//////////////////////////////////////////////////////////
    m_sizer2G = new wxBoxSizer(wxHORIZONTAL);
    m_sizer1V->Add(m_sizer2G, 1, wxALL | wxEXPAND, 5);

    m_sizerBoutonModif = new wxGridSizer(4, 1, 0, 0);

    m_listeG = new PageGestionPeriph(this, ID_PAGE_PERIHERIQUE_GAUCHE);
    m_listeD = new PageGestionPeriph(this, ID_PAGE_PERIHERIQUE_DROITE);
    m_sizer2G->Add(m_listeG, 1, wxALL | wxEXPAND, 0);
    m_sizer2G->Add(m_sizerBoutonModif, 0, wxALIGN_CENTER_VERTICAL, 0);
    m_sizer2G->Add(m_listeD, 1, wxALL | wxEXPAND, 0);

    m_listeG->SetPageParallele(m_listeD);
    m_listeD->SetPageParallele(m_listeG);

    m_boutonModif = new wxButton[4];
    m_boutonModif[0].Create(this, ID_PAGE_PERIHERIQUE_BOUTON_DEPLACE_POURG, _T("<"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    m_sizerBoutonModif->Add(&m_boutonModif[0], 0, wxALL, 0);
    m_boutonModif[1].Create(this, ID_PAGE_PERIHERIQUE_BOUTON_COPIE, _T("="), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    m_sizerBoutonModif->Add(&m_boutonModif[1], 0, wxALL, 0);
    m_boutonModif[1].Enable(false);
    m_boutonModif[2].Create(this, ID_PAGE_PERIHERIQUE_BOUTON_DEPLACE_POURD, _T(">"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    m_sizerBoutonModif->Add(&m_boutonModif[2], 0, wxALL, 0);
    m_boutonModif[3].Create(this, ID_PAGE_PERIHERIQUE_BOUTON_SUPPRIMER, _T("X"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    m_sizerBoutonModif->Add(&m_boutonModif[3], 0, wxALL, 0);

    m_boutonModif[0].SetToolTip(_("Déplacer l'élément sélectionné de la fenêtre droite vers la fenêtre gauche"));
    m_boutonModif[1].SetToolTip(_("Copier l'élément sélectionné dans l'autre fenêtre de navigation"));
    m_boutonModif[2].SetToolTip(_("Déplacer l'élément sélectionné de la fenêtre gauche vers la fenêtre droite"));
    m_boutonModif[3].SetToolTip(_("Supprimer l'élément sélectionné"));

    m_menuMesDoc = new wxMenu;
    m_menuMesDoc->Append(ID_PAGE_PERIHERIQUE_MENU_MESDOC_GAUCHE, _("Gauche"));
    m_menuMesDoc->Append(ID_PAGE_PERIHERIQUE_MENU_MESDOC_DROITE, _("Droite"));

    m_menuPeriph = new wxMenu;
    //m_liste_lecteur = Initialisation();
    m_listeLecteur = new ArrayOfElementLecteurRacineFichier();

    m_menuAutre = new wxMenu; m_menuM3U = new wxMenu;
    m_menuAutre->AppendSubMenu(m_menuM3U, _("Fichiers m3u"));
    //m_liste_playlist = Initialisation();
    m_listePlaylist = new ArrayOfElementLecteurRacineFichier();
    wxMenu *menuPlaylist = new wxMenu;
    menuPlaylist->Append(ID_PAGE_PERIHERIQUE_MENU_PLAYLIST_GAUCHE, _("Gauche"));
    menuPlaylist->Append(ID_PAGE_PERIHERIQUE_MENU_PLAYLIST_DROITE, _("Droite"));
    m_menuAutre->AppendSubMenu(menuPlaylist, _("Liste de lecture"));

    m_listeG->Connect(wxEVT_CHILD_FOCUS, wxChildFocusEventHandler(GestPeriph::FocusG), NULL, this);
    m_listeD->Connect(wxEVT_CHILD_FOCUS, wxChildFocusEventHandler(GestPeriph::FocusD), NULL, this);

    ComparaisonStatut();
}

/**
 * Affiche un menu lors du clic sur le bouton "Mes Documents"
 */
void GestPeriph::AfficheMenu_MesDoc(wxCommandEvent &WXUNUSED(event))
{    PopupMenu(m_menuMesDoc);}

/**
 * Affiche un menu lors du clic sur le bouton "Ordinateur"
 */
void GestPeriph::AfficheMenu_Periph(wxCommandEvent &WXUNUSED(event))
{
    ListePeripherique();
    PopupMenu(m_menuPeriph);
}

/**
 * Affiche un menu lors du clic sur le bouton "Autre"
 */
void GestPeriph::AfficheMenu_Autre(wxCommandEvent &WXUNUSED(event))
{
    ListeM3U();
    PopupMenu(m_menuAutre);
}

/**
 * Crée et prépare le menu présentant les lecteurs de l'ordinateur
 */
void GestPeriph::ListePeripherique()
{
    bool inclu;
    ElementLecteurRacineFichier *t = NULL;
    for (unsigned int i = 0; i<m_listeLecteur->GetCount(); i++)
    {
        t = m_listeLecteur->Item(i);
        if (t->GetUtilise())
        {
            m_menuPeriph->Remove(t->GetMenuItem());
            t->PasUtilise();
        }
    }

    wxArrayString chemin = wxFSVolume().GetVolumes();
    unsigned int j = 0;

    for (size_t i = 0; i < chemin.Count(); i++)
    {
        if (wxDirExists(chemin[i]))
        {
            inclu = false;
            j = 0;
            while (j < m_listeLecteur->GetCount() && !inclu)
            {
                if (m_listeLecteur->Item(j)->GetChemin() == chemin[i])
                {
                    t = m_listeLecteur->Item(j);
                    inclu = true;
                }
                j++;
            }

            if (!inclu)
            {
                wxFSVolume volume(chemin[i]);
                t = Insertion(m_listeLecteur, chemin[i], volume.GetDisplayName());
            }

            t->SetMenuItem(m_menuPeriph->AppendSubMenu(t->GetMenu(), t->GetNomAffiche()));
            t->SetUtilise(true);
        }
    }
}

/**
 * Crée et prépare le menu présentant les .m3u enregistrés dans les dossiers de Fu(X)
 */
void GestPeriph::ListeM3U()
{
    bool inclu;
    //Vidage du menu
    ElementLecteurRacineFichier *t = NULL;
    for (unsigned int i = 0; i<m_listePlaylist->GetCount(); i++)
    {
        t = m_listePlaylist->Item(i);
        if (t->GetUtilise())
        {
            m_menuM3U->Remove(t->GetMenuItem());
            t->PasUtilise();
        }
    }

    wxArrayString chaine;
    wxString cheminM3U = Parametre::Get()->getRepertoireParametre(_T("Play_list_M3U"));

    //wxDir Repertoire(cheminM3U);
    wxDir::GetAllFiles(cheminM3U, &chaine, _T("*.m3u"));//, wxDIR_FILES);

    unsigned int j = 0;

    for (unsigned int i=0; i<chaine.GetCount(); i++)
    {
        inclu = false;
        j = 0;
        while (j < m_listePlaylist->GetCount() && !inclu)
        {
            if (m_listePlaylist->Item(j)->GetChemin() == chaine.Item(i))
            {
                t = m_listePlaylist->Item(j);
                inclu = true;
            }
            j++;
        }

        if (!inclu)
            t = Insertion(m_listePlaylist, chaine.Item(i), cheminM3U.Length()+1);

        t->SetMenuItem(m_menuM3U->AppendSubMenu(t->GetMenu(), t->GetNomAffiche()));
        t->SetUtilise(true);
    }
}

/**
 * Insère dans liste un élément
 * @param liste la liste
 * @param chemin l'emplacement d'un élément
 * @param type le type de l'élément
 * @return l'objet créé
 */
ElementLecteurRacineFichier *GestPeriph::Insertion(ArrayOfElementLecteurRacineFichier *liste, wxString chemin, wxString type)
{
    ElementLecteurRacineFichier *nouveau = new ElementLecteurRacineFichier();

    if (liste == NULL || nouveau == NULL)
        return NULL;

    nouveau->SetChemin(chemin);
    #ifdef __WINDOWS__
        nouveau->SetNomAffiche(type);
    #else
        nouveau->SetNomAffiche(type + " (" + chemin.BeforeLast(wxFileName::GetPathSeparator()) + ")");
    #endif

    nouveau->SetIdGauche(wxNewId());
    Connect(nouveau->GetIdGauche(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GestPeriph::AffListeRepertoireLect));
    nouveau->SetIdDroite(wxNewId());
    Connect(nouveau->GetIdDroite(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GestPeriph::AffListeRepertoireLect));

    nouveau->CreerMenu();
    nouveau->SetUtilise(false);
    liste->Add(nouveau);
    return nouveau;
}

/**
 * Insère dans liste un élément
 * @param liste la liste
 * @param chemin l'emplacement d'un élément
 * @param nbr sert à la création de l'affichage, retire les nbr premiers caractères de chemin
 * @return l'objet créé
 */
ElementLecteurRacineFichier *GestPeriph::Insertion(ArrayOfElementLecteurRacineFichier *liste, wxString chemin, int nbr)
{
    ElementLecteurRacineFichier *nouveau = new ElementLecteurRacineFichier();

    if (liste == NULL || nouveau == NULL)
        return NULL;

    nouveau->SetChemin(chemin);
    nouveau->SetNomAffiche(chemin.Remove(0, nbr));

    nouveau->SetIdGauche(wxNewId());
    Connect(nouveau->GetIdGauche(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GestPeriph::AffListeM3U));

    nouveau->SetIdDroite(wxNewId());
    Connect(nouveau->GetIdDroite(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GestPeriph::AffListeM3U));

    nouveau->CreerMenu();
    nouveau->SetUtilise(false);
    liste->Add(nouveau);
    return nouveau;
}

/**
 * Efface les deux listes servant à construire les menus contenant les lecteurs et les .m3u
 */
void GestPeriph::DetruireListes()
{
    m_listeLecteur->Clear();
    m_listePlaylist->Clear();
}

/**
 * Évènement - Affiche le dossier Mes Documents dans la liste appropriée
 */
void GestPeriph::AffListeMesDoc(wxCommandEvent &event)
{
    if (event.GetId() == ID_PAGE_PERIHERIQUE_MENU_MESDOC_GAUCHE)
        m_listeG->SetFichierDossier(wxStandardPaths::Get().GetDocumentsDir(), DOSSIER, true);
    else if (event.GetId() == ID_PAGE_PERIHERIQUE_MENU_MESDOC_DROITE)
        m_listeD->SetFichierDossier(wxStandardPaths::Get().GetDocumentsDir(), DOSSIER, true);
}

/**
 * Évènement - Affiche le contenu du lecteur sélectionné dans la liste appropriée
 */
void GestPeriph::AffListeRepertoireLect(wxCommandEvent &event)
{
    int id = event.GetId();

    unsigned int i = 0;
    while (i < m_listeLecteur->GetCount())
    {
        if (id == m_listeLecteur->Item(i)->GetIdGauche())
        {
            m_listeG->SetFichierDossier(m_listeLecteur->Item(i)->GetChemin().BeforeLast(wxFileName::GetPathSeparator()), DOSSIER, true);
            i = m_listeLecteur->GetCount();
        }
        else if (id == m_listeLecteur->Item(i)->GetIdDroite())
        {
            m_listeD->SetFichierDossier(m_listeLecteur->Item(i)->GetChemin().BeforeLast(wxFileName::GetPathSeparator()), DOSSIER, true);
            i = m_listeLecteur->GetCount();
        }
        else
            i++;
    }
}

/**
 * Évènement - Affiche la liste de lecture dans la liste appropriée
 */
void GestPeriph::AffListePlaylist(wxCommandEvent &event)
{
    if (event.GetId() == ID_PAGE_PERIHERIQUE_MENU_PLAYLIST_GAUCHE)
        m_listeG->SetFichierDossier(Parametre::Get()->getRepertoireParametre(_T("musique.liste")), PLAYLIST, true);
    else if (event.GetId() == ID_PAGE_PERIHERIQUE_MENU_PLAYLIST_DROITE)
        m_listeD->SetFichierDossier(Parametre::Get()->getRepertoireParametre(_T("musique.liste")), PLAYLIST, true);
}

/**
 * Évènement - Affiche le contenu du fichier .m3u sélectionné dans la liste appropriée
 */
void GestPeriph::AffListeM3U(wxCommandEvent &event)
{
    int id = event.GetId();

    unsigned int i = 0;
    while (i < m_listePlaylist->GetCount())
    {
        if (id == m_listePlaylist->Item(i)->GetIdGauche())
        {
            m_listeG->SetFichierDossier(m_listePlaylist->Item(i)->GetChemin(), M3U, true);
            i = m_listePlaylist->GetCount();
        }
        else if (id == m_listePlaylist->Item(i)->GetIdDroite())
        {
            m_listeD->SetFichierDossier(m_listePlaylist->Item(i)->GetChemin(), M3U, true);
            i = m_listePlaylist->GetCount();
        }
        else
            i++;
    }
}
//////////////////////////////////////////////////////

/**
 * Évènement - Appelé lorsque le tableau de gauche a le focus
 */
void GestPeriph::FocusG(wxChildFocusEvent &WXUNUSED(event))
{    m_tableauFocus = GAUCHE;}

/**
 * Évènement - Appelé lorsque le tableau de droite a le focus
 */
void GestPeriph::FocusD(wxChildFocusEvent &WXUNUSED(event))
{    m_tableauFocus = DROITE;}

/**
 * Active/Désactive les boutons centraux en fonction du type de données affichées dans chaque liste
 */
void GestPeriph::ComparaisonStatut()
{
    if (m_listeG->GetEtat() == VIDE && m_listeD->GetEtat() == VIDE)
    {
        for (int i=0; i<4; i++)
            m_boutonModif[i].Enable(false);
    }
    else if (m_listeG->GetEtat() == VIDE || m_listeD->GetEtat() == VIDE)
    {
        for (int i=0; i<3; i++)
            m_boutonModif[i].Enable(false);
        m_boutonModif[3].Enable(true);
    }
    else if (m_listeG->GetEtat() == DOSSIER && m_listeD->GetEtat() == DOSSIER)
    {
        for (int i=0; i<4; i++)
            m_boutonModif[i].Enable(true);
    }
    else if ((m_listeG->GetEtat() == M3U || m_listeG->GetEtat() == PLAYLIST) && (m_listeD->GetEtat() == M3U || m_listeD->GetEtat() == PLAYLIST))
    {
        for (int i=0; i<4; i++)
            m_boutonModif[i].Enable(true);
    }
    else if (m_listeG->GetEtat() == DOSSIER && (m_listeD->GetEtat() == M3U || m_listeD->GetEtat() == PLAYLIST))
    {
        m_boutonModif[0].Enable(false);
        m_boutonModif[1].Enable(false);
        m_boutonModif[2].Enable(true);
        m_boutonModif[3].Enable(true);
    }
    else if (m_listeD->GetEtat() == DOSSIER && (m_listeG->GetEtat() == M3U || m_listeG->GetEtat() == PLAYLIST))
    {
        m_boutonModif[0].Enable(true);
        m_boutonModif[1].Enable(false);
        m_boutonModif[2].Enable(false);
        m_boutonModif[3].Enable(true);
    }
}

/**
 * Évènement - Active/Désactive les boutons centraux en fonction du type de données affichées dans chaque liste
 * @see ComparaisonStatut
 */
void GestPeriph::ComparaisonStatutEvt(wxCommandEvent &WXUNUSED(event))
{    ComparaisonStatut();}

/**
 * Évènement - Bouton central '=' lance une copie
 */
void GestPeriph::Copier(wxCommandEvent &WXUNUSED(event))
{
    if (m_tableauFocus == GAUCHE)
        m_listeG->Copie();
    else if (m_tableauFocus == DROITE)
        m_listeD->Copie();
}

/**
 * Évènement - Bouton central '>' lance un déplacement de la gauche vers la droite
 */
void GestPeriph::DeplaceD(wxCommandEvent &WXUNUSED(event))
{    m_listeG->Deplace();}

/**
 * Évènement - Bouton central '<' lance un déplacement de la droite vers la gauche
 */
void GestPeriph::DeplaceG(wxCommandEvent &WXUNUSED(event))
{    m_listeD->Deplace();}

/**
 * Évènement - Bouton central 'X' lance une suppression
 */
void GestPeriph::Supprimer(wxCommandEvent &WXUNUSED(event))
{
    if (m_tableauFocus == GAUCHE)
        m_listeG->Suppression();
    else if (m_tableauFocus == DROITE)
        m_listeD->Suppression();
}

/**
 * Met à jour les listes si elles affichent la liste de lecture
 */
void GestPeriph::MAJPlaylist()
{
    if (m_listeG->GetEtat() == PLAYLIST)
        m_listeG->Recharger();
    if (m_listeD->GetEtat() == PLAYLIST)
        m_listeD->Recharger();
}


