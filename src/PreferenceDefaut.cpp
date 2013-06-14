/***************************************************************
 * Name:      PreferenceDefaut.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2010-02-09
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/

#include "../include/PreferenceDefaut.h"

/**
 * @class PrefDefaut
 * @brief Gère l'application des filtres (couleur et sonore), et le comportement par défaut de l'application
 */

BEGIN_EVENT_TABLE(PrefDefaut, wxScrolledWindow)
    EVT_RADIOBOX(ID_APP_PREF_DEFAUT_CHOIX, PrefDefaut::Defaut_RadioMP3_M3U)
    EVT_CHECKBOX(ID_APP_PREF_DEFAUT_BOX_COULEUR, PrefDefaut::Defaut_CheckBoxCouleur)
    EVT_CHECKBOX(ID_APP_PREF_DEFAUT_BOX_SON, PrefDefaut::Defaut_CheckBoxSon)
    EVT_CHECKBOX(ID_APP_PREF_DEFAUT_BOX_REPRISE, PrefDefaut::Defaut_CheckBoxReprise)
    EVT_CHECKBOX(ID_APP_PREF_DEFAUT_BOX_TAG, PrefDefaut::Defaut_CheckBoxTAG)// TAG
    EVT_CHECKBOX(ID_APP_PREF_DEFAUT_BOX_DEFAUT_BDR, PrefDefaut::Defaut_CheckBoxDefautBDR)// application par défaut
    EVT_BUTTON(ID_APP_PREF_DEFAUT_ENREGISTRER, PrefDefaut::Defaut_Bouton_Enregistrer)
    EVT_BUTTON(ID_APP_PREF_DEFAUT_ANNULER, PrefDefaut::Defaut_Bouton_Annuler)
    EVT_BUTTON(ID_APP_PREF_DEFAUT_RECHERCHE, PrefDefaut::Defaut_Bouton_Recherche)
    EVT_BUTTON(ID_APP_PREF_DEFAUT_MAJLISTE, PrefDefaut::Defaut_Bouton_MAJListe)
    EVT_BUTTON(ID_APP_PREF_DEFAUT_PORTABLE, PrefDefaut::Defaut_Bouton_Portable)
    EVT_BUTTON(ID_APP_PREF_DEFAUT_CHEMIN_RECHERCHE_DEFAUT, PrefDefaut::Defaut_Bouton_CheminDefaut)//Répertoire à afficher lors du début d'une recherche
END_EVENT_TABLE()

/**
 * Constructeur
 */
PrefDefaut::PrefDefaut()
{}

/**
 * Constructeur
 * @param Parent un pointeur vers la fenêtre parente
 */
PrefDefaut::PrefDefaut(wxWindow *Parent) : wxScrolledWindow(Parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxVSCROLL | wxHSCROLL)
{}

/**
 * Destructeur
 */
PrefDefaut::~PrefDefaut()
{}

/**
 * Crée les différents composants graphiques du panel
 */
void PrefDefaut::Creer()
{
    SetScrollbars(20, 20, 50, 50);

    m_sizer1V = new wxBoxSizer(wxVERTICAL);
    SetSizer(m_sizer1V);

    m_sizerUseQuo = new wxStaticBoxSizer(wxVERTICAL, this, _("Filtres"));
    m_sizer1V->Add(m_sizerUseQuo, 0, wxALL, 5);
    wxFlexGridSizer *m_sizerUseF = new wxFlexGridSizer(2, 2, 5, 5);//Suite des cases contenant des valeurs modifiables
    m_sizerUseQuo->Add(m_sizerUseF, 0, wxALL, 5);

    m_checkBox = new wxCheckBox[6];//TAG = 6
    m_checkBox[COULEUR].Create(this, ID_APP_PREF_DEFAUT_BOX_COULEUR, _("Couleur"));
    m_checkBox[SON].Create(this, ID_APP_PREF_DEFAUT_BOX_SON, _("Son"));
    m_checkBox[REPRISE].Create(this, ID_APP_PREF_DEFAUT_BOX_REPRISE, _("Reprise"));
    m_checkBox[SOUSDOSSIER].Create(this, ID_APP_PREF_DEFAUT_BOX_RECHERCHE, _("Inclure les fichiers des sous-dossiers lors d'une opération"));
    m_checkBox[TAG].Create(this, ID_APP_PREF_DEFAUT_BOX_TAG, _("Afficher les noms en fonction des TAGs"));
    m_checkBox[DEFAUT].Create(this, ID_APP_PREF_DEFAUT_BOX_DEFAUT_BDR, _("Application par défaut"));

    m_checkBox[COULEUR].SetToolTip(_("Appliquer un filtre couleur sur le graphe."));
    m_checkBox[SON].SetToolTip(_("Appliquer un filtre son à l'écoute."));
    m_checkBox[REPRISE].SetToolTip(_("Lancer automatiquement un fichier lors du lancement de Fu(X)."));
    m_checkBox[SOUSDOSSIER].SetToolTip(_("Fu(X) recherchera dans toute l'arborescence du dossier les fichiers lors d'une opération de lecture par exemple."));
    m_checkBox[TAG].SetToolTip(_("Le titre de la chanson se fait à partir des données enregistrées dans le fichier musical et non à partir du nom de celui-ci."));
    m_checkBox[DEFAUT].SetToolTip(_("Faire de Fu(X) le programme par défaut pour les mp3, m3u.\nNe pas utiliser si vous avez fait une installation classique."));

    m_listeCouleur = new wxChoice(this, ID_APP_PREF_DEFAUT_LISTE_COULEUR, wxDefaultPosition, wxSize(200, 21));
    m_listeSon = new wxChoice(this, ID_APP_PREF_DEFAUT_LISTE_SON, wxDefaultPosition, wxSize(200, 21));
    m_listeReprise = new wxChoice(this, ID_APP_PREF_DEFAUT_LISTE_M3U, wxDefaultPosition, wxSize(200, 21));

    m_sizerUseF->Add(&m_checkBox[COULEUR], 0, wxALL, 0);
    m_sizerUseF->Add(m_listeCouleur, 0, wxALL, 0);
    m_sizerUseF->Add(&m_checkBox[SON], 0, wxALL, 0);
    m_sizerUseF->Add(m_listeSon, 0, wxALL, 0);

    m_sizerAvancee = new wxStaticBoxSizer(wxVERTICAL, this, _("Avancée"));
    m_sizer1V->Add(m_sizerAvancee, 0, wxALL, 5);

    m_boutonPortable = new wxButton(this, ID_APP_PREF_DEFAUT_PORTABLE, _("Portable"));//, wxDefaultPosition, wxSize(30, 21));
    m_boutonPortable->SetToolTip(_("Configure Fu(X) pour une utilisation sur clef USB.\nNe pas utiliser si vous avez fait une installation classique."));
    m_sizerAvancee->Add(m_boutonPortable, 0, wxALL, 5);
    m_sizerAvancee->Add(&m_checkBox[DEFAUT], 0, wxALL, 5);
    wxBoxSizer *sizerAvancee2H = new wxBoxSizer(wxHORIZONTAL);
    m_sizerAvancee->Add(sizerAvancee2H, 0, wxBOTTOM | wxEXPAND, 5);
    sizerAvancee2H->Add(&m_checkBox[REPRISE], 0, wxALL, 5);

    wxString proposition[2]; proposition[0] = _("MP3"); proposition[1] = _("M3U");
    m_choix = new wxRadioBox(this, ID_APP_PREF_DEFAUT_CHOIX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 2, proposition, 1, wxRA_SPECIFY_COLS);
    sizerAvancee2H->Add(m_choix, 0, wxALL, 0);

    wxFlexGridSizer *sizerAvancee3F = new wxFlexGridSizer(2, 2, 5, 5);
    sizerAvancee2H->Add(sizerAvancee3F, 0, wxALL, 5);

    m_boiteCheminChansonRep = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, 21), wxTE_READONLY);
    m_boutonRecherche = new wxButton(this, ID_APP_PREF_DEFAUT_RECHERCHE, _T("..."), wxDefaultPosition, wxSize(30, 21));

    wxStaticText *textDossier = new wxStaticText(this, wxID_ANY, _("Dossier par défaut"));//dossier de recherche par défaut, à ouvrir en premier
    m_boiteCheminDefautRech = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(220, 21), wxTE_READONLY);
    m_boutonCheminDefautRecherche = new wxButton(this, ID_APP_PREF_DEFAUT_CHEMIN_RECHERCHE_DEFAUT, _T("..."), wxDefaultPosition, wxSize(30, 21));

    sizerAvancee3F->Add(m_boiteCheminChansonRep, 0, wxALL, 0);
    sizerAvancee3F->Add(m_boutonRecherche, 0, wxALL, 0);
    sizerAvancee3F->Add(m_listeReprise, 0, wxRIGHT | wxLEFT | wxEXPAND, 0);

    wxBoxSizer *sizerAvancee3H = new wxBoxSizer(wxHORIZONTAL);
    m_sizerAvancee->Add(sizerAvancee3H, 0, wxALL | wxEXPAND, 5);
    sizerAvancee3H->Add(textDossier, 0, wxRIGHT | wxEXPAND, 5);
    sizerAvancee3H->Add(m_boiteCheminDefautRech, 0, wxRIGHT | wxEXPAND, 5);
    sizerAvancee3H->Add(m_boutonCheminDefautRecherche, 0, wxRIGHT | wxLEFT | wxEXPAND, 0);

    m_sizerAvancee->Add(&m_checkBox[SOUSDOSSIER], 0, wxALL | wxEXPAND, 5);
    m_sizerAvancee->Add(&m_checkBox[TAG], 0, wxALL | wxEXPAND, 5);

    wxFlexGridSizer *sizerAvancee4F = new wxFlexGridSizer(1, 3, 5, 5);
    m_sizer1V->Add(sizerAvancee4F, 0, wxALL, 5);

    m_boutonEnregistrer = new wxButton(this, ID_APP_PREF_DEFAUT_ENREGISTRER, _("Enregistrer"));//, wxDefaultPosition, wxSize(30, 21));
    m_boutonAnnuler = new wxButton(this, ID_APP_PREF_DEFAUT_ANNULER, _("Annuler"));//, wxDefaultPosition, wxSize(30, 21));
    m_boutonMAJListe = new wxButton(this, ID_APP_PREF_DEFAUT_MAJLISTE, _("Rechargement des listes"));
    sizerAvancee4F->Add(m_boutonEnregistrer, 0, wxALL, 0);
    sizerAvancee4F->Add(m_boutonAnnuler, 0, wxALL, 0);
    sizerAvancee4F->Add(m_boutonMAJListe, 0, wxALL, 0);

    ListerContenuFichier(m_listeCouleur, COULEUR);
    ListerContenuFichier(m_listeSon, SON);
    m_listeM3u_mp3 = MP3;
    CreerListe(m_listeReprise);
    m_listeCouleur->Enable(false);
    m_listeReprise->Enable(false);
    m_listeSon->Enable(false);
    m_choix->Enable(false);
    m_boiteCheminChansonRep->Enable(false);
    m_boutonRecherche->Enable(false);
    OuvertureFichier();
    m_sizer1V->Layout();
}

/**
 * Construit une liste de fichier .m3u à partir des fichiers présents dans l'arborescence de Fu(X)
 * @param liste une liste à remplir
 * @return le nombre d'éléments dans la liste
 */
int PrefDefaut::CreerListe(wxChoice *liste)
{
    int nombre = 0;
    wxFile fichier;
    fichier.Create(Parametre::Get()->getRepertoireParametre(_T("Liste_M3U.txt")), true);

    if (wxDir::Exists(Parametre::Get()->getRepertoireParametre(_T("Play_list_M3U"))))
    {
        wxString copie;
        wxDir Repertoire(Parametre::Get()->getRepertoireParametre(_T("Play_list_M3U")));
        bool continuer = Repertoire.GetFirst(&copie, _T("*.m3u"));//, wxDIR_FILES);

        while (continuer)
        {
            fichier.Write(copie);
            fichier.Write(_T("\r\n"));
            nombre++;
            liste->Append(copie);
            continuer = Repertoire.GetNext(&copie);
        }
    }
    fichier.Close();
    return nombre;
}

/**
 * Construit une liste de filtre
 * @param typeListe le type de liste à construire (COULEUR ou SON)
 * @param liste la liste contenant les filtres propres au type
 * @return le nombre d'éléments
 */
int PrefDefaut::ListerContenuFichier(wxChoice *liste, int typeListe)
{
    wxString chemin = _T(""), chaine;
    int nombre = 0;

    if (typeListe == COULEUR)
        chemin = Parametre::Get()->getRepertoireParametre(_T("Liste_Couleur.txt"));
    else if (typeListe == SON)
        chemin = Parametre::Get()->getRepertoireParametre(_T("Liste_Son.txt"));

    wxTextFile fichier;
    fichier.Open(chemin);
    chaine = fichier.GetFirstLine();

    for(chaine = fichier.GetFirstLine(); !fichier.Eof(); chaine = fichier.GetNextLine() )
    {
        liste->Append(chaine);
        nombre++;
    }

    fichier.Close();
    return nombre;
}

/**
 * Évènement - Enregistre dans un fichier de configuration les paramètres saisies
 */
void PrefDefaut::Defaut_Bouton_Enregistrer(wxCommandEvent &WXUNUSED(event))
{
    wxFile FichierListe;
    wxString chemin = Parametre::Get()->getRepertoireParametre(_T("Fu(X).conf")), chaineCouleur, chaineSon, chaineReprise, chaineRecherche;

    if (m_checkBox[COULEUR].GetValue() && m_listeCouleur->GetCurrentSelection() != wxNOT_FOUND)
        chaineCouleur << _T("Couleur= ") << m_listeCouleur->GetString(m_listeCouleur->GetCurrentSelection());
    else
        chaineCouleur << _T("Couleur= NON");

    if (m_checkBox[SON].GetValue() && m_listeSon->GetCurrentSelection() != wxNOT_FOUND)
        chaineSon << _T("Son= ") << m_listeSon->GetString(m_listeSon->GetCurrentSelection());
    else
        chaineSon << _T("Son= NON");

    if (m_checkBox[REPRISE].GetValue())
    {
        if(m_listeM3u_mp3 == MP3 && !m_boiteCheminChansonRep->IsEmpty())
            chaineReprise << _T("Reprise= MP3\r\nChemin= ") << m_boiteCheminChansonRep->GetValue();
        else if (m_listeM3u_mp3 == M3U && !m_listeReprise->GetCurrentSelection() != wxNOT_FOUND)
            chaineReprise << _T("Reprise= M3U\r\nChemin= ") << m_listeReprise->GetString(m_listeReprise->GetCurrentSelection());
        else
            chaineReprise << _T("Reprise= NON\r\nChemin= NON");
    }
    else
        chaineReprise << _T("Reprise= NON\r\nChemin= NON");

    if (m_checkBox[SOUSDOSSIER].GetValue())
    {
        chaineRecherche << _T("SousDossier= OUI");
        Parametre::Get()->setSousDossier(true);
    }
    else
    {
        chaineRecherche << _T("SousDossier= NON");
        Parametre::Get()->setSousDossier(false);
    }

    FichierListe.Create(chemin, true);
    FichierListe.Write(_T("#EXTCONF_1\r\n"));
    FichierListe.Write(chaineCouleur + _T("\r\n"));
    FichierListe.Write(chaineSon + _T("\r\n"));
    FichierListe.Write(chaineReprise + _T("\r\n"));
    FichierListe.Write(chaineRecherche + _T("\r\n"));
    FichierListe.Close();
}

/**
 * Évènement - Annule toutes les modifications pour remettre les valeurs par défaut
 */
void PrefDefaut::Defaut_Bouton_Annuler(wxCommandEvent &WXUNUSED(event))
{
    for (int i=0; i<5; i++)
        m_checkBox[i].SetValue(false);

    m_listeCouleur->SetSelection(wxNOT_FOUND);
    m_listeReprise->SetSelection(wxNOT_FOUND);
    m_listeSon->SetSelection(wxNOT_FOUND);

    m_choix->SetSelection(wxNOT_FOUND);
    m_listeM3u_mp3 = MP3;
    m_boiteCheminChansonRep->Clear();

    m_listeCouleur->Enable(false);
    m_listeReprise->Enable(false);
    m_listeSon->Enable(false);
    m_choix->Enable(false);
    m_boiteCheminChansonRep->Enable(false);
    m_boutonRecherche->Enable(false);
}

/**
 * Évènement - Ouvre une fenêtre de navigation pour sélectionner un .mp3 (Il sera lu au lancement de Fu(X))
 */
void PrefDefaut::Defaut_Bouton_Recherche(wxCommandEvent &WXUNUSED(event))
{
    int ouvert;
    wxFileDialog navig(this, _("Choisissez une chanson"), wxStandardPaths::Get().GetDocumentsDir(), m_boiteCheminChansonRep->GetValue(), Parametre::Get()->getExtensionValideMusique(), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    ouvert = navig.ShowModal();

    m_boiteCheminChansonRep->SetValue( (ouvert == wxID_OK) ? navig.GetPath() : _T("") );
}

/**
 * Évènement - Ouvre une fenêtre de navigation pour sélectionner le dossier à ouvrir par défaut
 */
void PrefDefaut::Defaut_Bouton_DossierDefaut(wxCommandEvent &WXUNUSED(event))
{
    int ouvert;
    wxDirDialog navig(this, _("Choisissez le répertoire par défaut"), m_boiteCheminDefautRech->GetValue(), wxDD_DEFAULT_STYLE|wxDD_DIR_MUST_EXIST);

    ouvert = navig.ShowModal();

    m_boiteCheminDefautRech->SetValue((ouvert == wxID_OK) ? navig.GetPath() : _T(""));
}

/**
 * Évènement - Met à jour toutes les listes de la page
 */
void PrefDefaut::Defaut_Bouton_MAJListe(wxCommandEvent &WXUNUSED(event))
{
    wxString coul = m_listeCouleur->GetStringSelection(), son = m_listeSon->GetStringSelection(), rep = m_listeReprise->GetStringSelection();
    m_listeCouleur->Clear();
    ListerContenuFichier(m_listeCouleur, COULEUR);
    m_listeCouleur->SetStringSelection(coul);

    m_listeSon->Clear();
    ListerContenuFichier(m_listeSon, SON);
    m_listeSon->SetStringSelection(son);

    m_listeReprise->Clear();
    CreerListe(m_listeReprise);
    m_listeReprise->SetStringSelection(rep);
}

/**
 * Évènement - Active/Désactive les listes en fonction du type (MP3 ou M3U) choisi.
 */
void PrefDefaut::Defaut_RadioMP3_M3U(wxCommandEvent &event)
{
    m_listeM3u_mp3 = event.GetSelection();
    if (m_listeM3u_mp3 == MP3)
    {
        m_listeReprise->Enable(false);
        m_boiteCheminChansonRep->Enable(true);
        m_boutonRecherche->Enable(true);
    }
    else if (m_listeM3u_mp3 == M3U)
    {
        m_listeReprise->Enable(true);
        m_boiteCheminChansonRep->Enable(false);
        m_boutonRecherche->Enable(false);
    }
}

/**
 * Évènement - Active/Désactive la liste des filtres couleurs
 */
void PrefDefaut::Defaut_CheckBoxCouleur(wxCommandEvent &event)
{
    m_listeCouleur->Enable(event.IsChecked());
}

/**
 * Évènement - Active/Désactive la liste des filtres sons
 */
void PrefDefaut::Defaut_CheckBoxSon(wxCommandEvent &event)
{
    m_listeSon->Enable(event.IsChecked());
}

/**
 * Évènement - Active/Désactive les listes permettant une lecture de musique sans donner de paramètre à l'application
 */
void PrefDefaut::Defaut_CheckBoxReprise(wxCommandEvent &event)
{
    if (event.IsChecked())
    {
        m_choix->Enable(true);
        if (m_listeM3u_mp3 == MP3)
        {
            m_listeReprise->Enable(false);
            m_boiteCheminChansonRep->Enable(true);
            m_boutonRecherche->Enable(true);
        }
        else if (m_listeM3u_mp3 == M3U)
        {
            m_listeReprise->Enable(true);
            m_boiteCheminChansonRep->Enable(false);
            m_boutonRecherche->Enable(false);
        }
    }
    else
    {
        m_choix->Enable(false);
        m_listeReprise->Enable(false);
        m_boiteCheminChansonRep->Enable(false);
        m_boutonRecherche->Enable(false);
    }
}

/**
 * Évènement/Non implémenté - Modifie le mode d'affichage des titres : titre du fichier ou données incorporées (TAG)
 */
void PrefDefaut::Defaut_CheckBoxTAG(wxCommandEvent &WXUNUSED(event))
{
    wxLogMessage(_("Non implémenté - Tag"));
}

/**
 * Évènement - Lance la création de l'arborescence contenant les fichiers de configuration dans le répertoire d'installation de Fu(X)
 */
void PrefDefaut::Defaut_Bouton_Portable(wxCommandEvent &WXUNUSED(event))
{
    Parametre::Get()->creerRepertoireParametre(wxStandardPaths::Get().GetDataDir());
}

/**
 * Évènement/Non implémenté - Modifie la Base de Registre (BDR de Windows) pour mettre Fu(X) en application par défaut
 */
void PrefDefaut::Defaut_CheckBoxDefautBDR(wxCommandEvent &WXUNUSED(event))
{
    wxLogMessage(_("Non implémenté - Application par défaut"));
}

/**
 * Évènement/Non implémenté - Lance l'ouverture d'une fenêtre pour sélectionner le répertoire devant être ouvert lors d'une recherche
 */
void PrefDefaut::Defaut_Bouton_CheminDefaut(wxCommandEvent &WXUNUSED(event))
{
    wxLogMessage(_("Non implémenté - Répertoire par défaut"));
}

/**
 * Applique à la fenêtre les paramètres contenus dans le fichier de configuration enregistré
 */
void PrefDefaut::OuvertureFichier()
{
    wxString cheminFichier = Parametre::Get()->getRepertoireParametre(_T("Fu(X).conf")), nomFichierCouleur, nomFichierSon;
    wxTextFile fichierPref(cheminFichier);

    if (!(fichierPref.Exists() && fichierPref.Open()))
        return;

    if (fichierPref.GetLine(0).IsSameAs(_T("#EXTCONF_1")))
    {
        ///////Couleur
        if (!fichierPref.GetLine(1).IsSameAs(_T("Couleur= NON")))
        {
            m_checkBox[COULEUR].SetValue(true);
            m_listeCouleur->Enable(true);
            m_listeCouleur->SetStringSelection(fichierPref.GetLine(1).AfterFirst(' '));
        }
        ///////Son
        if (!fichierPref.GetLine(2).IsSameAs(_T("Son= NON")))
        {
            m_checkBox[SON].SetValue(true);
            m_listeSon->Enable(true);
            m_listeSon->SetStringSelection(fichierPref.GetLine(2).AfterFirst(' '));
        }
        ///////Reprise
        if (!fichierPref.GetLine(3).IsSameAs(_T("Reprise= NON")))
        {
            m_checkBox[REPRISE].SetValue(true);
            m_choix->Enable(true);
            if (fichierPref.GetLine(3).IsSameAs(_T("Reprise= M3U")))
            {
                m_listeReprise->Enable(true);
                m_listeReprise->SetStringSelection(fichierPref.GetLine(4).AfterFirst(' '));
                m_choix->SetSelection(M3U);
            }
            else if (fichierPref.GetLine(3).IsSameAs(_T("Reprise= MP3")))
            {
                m_boiteCheminChansonRep->Enable(true);
                m_boutonRecherche->Enable(true);
                m_boiteCheminChansonRep->ChangeValue(fichierPref.GetLine(4).AfterFirst(' '));
                m_choix->SetSelection(MP3);
            }
        }
        //////////Sous-dossier
        if (!fichierPref.GetLine(5).IsSameAs(_T("SousDossier= NON")))
            m_checkBox[SOUSDOSSIER].SetValue(true);
    }

    fichierPref.Close();
}


