/***************************************************************
 * Name:      PreferenceDefaut.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2010-02-09
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/

#include "../../include/GUI/PreferenceDefaut.h"

/**
 * @class PreferenceDefaut
 * @brief Gère l'application des filtres (couleur et sonore), et le comportement par défaut de l'application
 */

BEGIN_EVENT_TABLE(PreferenceDefaut, wxScrolledWindow)
    EVT_RADIOBOX(ID_APP_PREF_DEFAUT_CHOIX, PreferenceDefaut::Defaut_RadioMP3_M3U)
    EVT_CHECKBOX(ID_APP_PREF_DEFAUT_BOX_COULEUR, PreferenceDefaut::Defaut_CheckBoxCouleur)
    EVT_CHECKBOX(ID_APP_PREF_DEFAUT_BOX_SON, PreferenceDefaut::Defaut_CheckBoxSon)
    EVT_CHECKBOX(ID_APP_PREF_DEFAUT_BOX_REPRISE, PreferenceDefaut::Defaut_CheckBoxReprise)
    EVT_CHECKBOX(ID_APP_PREF_DEFAUT_BOX_TAG, PreferenceDefaut::Defaut_CheckBoxTAG)// TAG
    EVT_CHECKBOX(ID_APP_PREF_DEFAUT_BOX_DEFAUT_BDR, PreferenceDefaut::Defaut_CheckBoxDefautBDR)// application par défaut
    EVT_CHECKBOX(ID_APP_PREF_DEFAUT_BOX_RECHERCHE, PreferenceDefaut::AutoSave)// application par défaut
    EVT_BUTTON(ID_APP_PREF_DEFAUT_RECHERCHE, PreferenceDefaut::Defaut_Bouton_Recherche)
    EVT_BUTTON(ID_APP_PREF_DEFAUT_PORTABLE, PreferenceDefaut::Defaut_Bouton_Portable)
    EVT_BUTTON(ID_APP_PREF_DEFAUT_CHEMIN_RECHERCHE_DEFAUT, PreferenceDefaut::Defaut_Bouton_CheminDefaut)//Répertoire à afficher lors du début d'une recherche
    EVT_CHOICE(ID_APP_PREF_DEFAUT_LISTE_COULEUR, PreferenceDefaut::AutoSave)
    EVT_CHOICE(ID_APP_PREF_DEFAUT_LISTE_SON, PreferenceDefaut::AutoSave)
    EVT_CHOICE(ID_APP_PREF_DEFAUT_LISTE_M3U, PreferenceDefaut::AutoSave)
    EVT_PREFERENCE_MAJ_LISTE(-1, PreferenceDefaut::Evt_MAJListe)
    EVT_PREFERENCE_MAJ_M3U(-1, PreferenceDefaut::Evt_MAJListe)
END_EVENT_TABLE()

/**
 * Constructeur
 * @param Parent un pointeur vers la fenêtre parente
 * @param Id l'identifiant de la fenêtre
 */
PreferenceDefaut::PreferenceDefaut(wxWindow *Parent, wxWindowID Id)
{
    PreferenceDefaut::Creer(Parent, Id);
    OuvertureFichier();
}

/**
 * Constructeur
 * @param Parent un pointeur vers la fenêtre parente
 * @param Id l'identifiant de la fenêtre
 * @param pageCouleur
 * @param pageSon
 */
PreferenceDefaut::PreferenceDefaut(wxWindow *Parent, wxWindowID Id, PreferenceCouleur *pageCouleur, PreferenceSon *pageSon)
{
    PreferenceDefaut::Creer(Parent, Id);
    SetPreferencePage(pageCouleur, pageSon);
    OuvertureFichier();
}

/**
 * Destructeur
 */
PreferenceDefaut::~PreferenceDefaut()
{
    delete[] m_checkBox;
}

/**
 * Crée les différents composants graphiques du panel
 * @param Parent un pointeur vers la fenêtre parente
 * @param Id l'identifiant de la fenêtre
 */
void PreferenceDefaut::Creer(wxWindow *Parent, wxWindowID Id)
{
    Create(Parent, Id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxVSCROLL | wxHSCROLL);
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

    //ListerContenuFichier(m_listeCouleur, COULEUR);
    m_pageCouleur = NULL;
    //ListerContenuFichier(m_listeSon, SON);
    m_pageSon = NULL;
    //m_listeM3u_mp3 = MP3;
    CreerListe(m_listeReprise);
    m_listeCouleur->Enable(false);
    m_listeReprise->Enable(false);
    m_listeSon->Enable(false);
    m_choix->Enable(false);
    m_boiteCheminChansonRep->Enable(false);
    m_boutonRecherche->Enable(false);
    m_sizer1V->Layout();

    DialogEnregistreM3U::SetPanelToBeCall(this);
}

/**
 * Construit une liste de fichier .m3u à partir des fichiers présents dans l'arborescence de Fu(X)
 * @param liste une liste à remplir
 * @return le nombre d'éléments dans la liste
 */
int PreferenceDefaut::CreerListe(wxChoice *liste)
{
    int nombre = 0;

    if (wxDir::Exists(Parametre::Get()->getRepertoireParametre(_T("Play_list_M3U"))))
    {
        wxString copie;
        wxDir Repertoire(Parametre::Get()->getRepertoireParametre(_T("Play_list_M3U")));
        bool continuer = Repertoire.GetFirst(&copie, _T("*.m3u"));//, wxDIR_FILES);

        while (continuer)
        {
            nombre++;
            liste->Append(copie);
            continuer = Repertoire.GetNext(&copie);
        }
    }
    return nombre;
}

/**
 * Évènement - Ouvre une fenêtre de navigation pour sélectionner un .mp3 (Il sera lu au lancement de Fu(X))
 */
void PreferenceDefaut::Defaut_Bouton_Recherche(wxCommandEvent &WXUNUSED(event))
{
    int ouvert;
    wxFileDialog navig(this, _("Choisissez une chanson"), wxStandardPaths::Get().GetDocumentsDir(), m_boiteCheminChansonRep->GetValue(), Parametre::Get()->getExtensionValideMusique(), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    ouvert = navig.ShowModal();

    m_boiteCheminChansonRep->SetValue( (ouvert == wxID_OK) ? navig.GetPath() : _T("") );
    AutoSave();
}

/**
 * Évènement - Ouvre une fenêtre de navigation pour sélectionner le dossier à ouvrir par défaut
 */
void PreferenceDefaut::Defaut_Bouton_DossierDefaut(wxCommandEvent &WXUNUSED(event))
{
    int ouvert;
    wxDirDialog navig(this, _("Choisissez le répertoire par défaut"), m_boiteCheminDefautRech->GetValue(), wxDD_DEFAULT_STYLE|wxDD_DIR_MUST_EXIST);

    ouvert = navig.ShowModal();

    m_boiteCheminDefautRech->SetValue((ouvert == wxID_OK) ? navig.GetPath() : _T(""));
    AutoSave();
}

/**
 * Évènement - Met à jour toutes les listes de la page
 */
void PreferenceDefaut::Evt_MAJListe(wxCommandEvent &WXUNUSED(event))
{
    MAJListe();
}

/**
 * Met à jour toutes les listes de la page
 */
void PreferenceDefaut::MAJListe(bool save)
{
    wxString coul = m_listeCouleur->GetStringSelection(), son = m_listeSon->GetStringSelection(), rep = m_listeReprise->GetStringSelection();

    if (m_pageCouleur)
    {
        m_listeCouleur->Clear();
        m_pageCouleur->MajListe(m_listeCouleur);
        m_listeCouleur->SetStringSelection(coul);
    }
    if (m_pageSon)
    {
        m_listeSon->Clear();
        m_pageSon->MajListe(m_listeSon);
        m_listeSon->SetStringSelection(son);
    }

    m_listeReprise->Clear();
    CreerListe(m_listeReprise);
    m_listeReprise->SetStringSelection(rep);
    if (save)
        AutoSave();
}

/**
 * Évènement - Active/Désactive les listes en fonction du type (MP3 ou M3U) choisi.
 */
void PreferenceDefaut::Defaut_RadioMP3_M3U(wxCommandEvent &event)
{
    //m_listeM3u_mp3 = event.GetSelection();
    if (/*m_listeM3u_mp3 */event.GetSelection() == MP3)
    {
        m_listeReprise->Enable(false);
        m_boiteCheminChansonRep->Enable(true);
        m_boutonRecherche->Enable(true);
    }
    else if (/*m_listeM3u_mp3 */event.GetSelection() == M3U)
    {
        m_listeReprise->Enable(true);
        m_boiteCheminChansonRep->Enable(false);
        m_boutonRecherche->Enable(false);
    }
    AutoSave();
}

/**
 * Évènement - Active/Désactive la liste des filtres couleurs
 */
void PreferenceDefaut::Defaut_CheckBoxCouleur(wxCommandEvent &event)
{
    m_listeCouleur->Enable(event.IsChecked());
    AutoSave();
}

/**
 * Évènement - Active/Désactive la liste des filtres sons
 */
void PreferenceDefaut::Defaut_CheckBoxSon(wxCommandEvent &event)
{
    m_listeSon->Enable(event.IsChecked());
    AutoSave();
}

/**
 * Évènement - Active/Désactive les listes permettant une lecture de musique sans donner de paramètre à l'application
 */
void PreferenceDefaut::Defaut_CheckBoxReprise(wxCommandEvent &event)
{
    if (event.IsChecked())
    {
        m_choix->Enable(true);
        if (m_choix->GetSelection() == MP3)//m_listeM3u_mp3 == MP3)
        {
            m_listeReprise->Enable(false);
            m_boiteCheminChansonRep->Enable(true);
            m_boutonRecherche->Enable(true);
        }
        else if (/*m_listeM3u_mp3 */m_choix->GetSelection() == M3U)
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
    AutoSave();
}

/**
 * Évènement/Non implémenté - Modifie le mode d'affichage des titres : titre du fichier ou données incorporées (TAG)
 */
void PreferenceDefaut::Defaut_CheckBoxTAG(wxCommandEvent &WXUNUSED(event))
{
    wxLogMessage(_("Non implémenté - Tag"));
    //AutoSave();
}

/**
 * Évènement - Lance la création de l'arborescence contenant les fichiers de configuration dans le répertoire d'installation de Fu(X)
 */
void PreferenceDefaut::Defaut_Bouton_Portable(wxCommandEvent &WXUNUSED(event))
{
    Parametre::Get()->creerRepertoireParametre(wxStandardPaths::Get().GetDataDir());
}

/**
 * Évènement/Non implémenté - Modifie la Base de Registre (BDR de Windows) pour mettre Fu(X) en application par défaut
 */
void PreferenceDefaut::Defaut_CheckBoxDefautBDR(wxCommandEvent &WXUNUSED(event))
{
    wxLogMessage(_("Non implémenté - Application par défaut"));
    //AutoSave();
}

/**
 * Évènement/Non implémenté - Lance l'ouverture d'une fenêtre pour sélectionner le répertoire devant être ouvert lors d'une recherche
 */
void PreferenceDefaut::Defaut_Bouton_CheminDefaut(wxCommandEvent &WXUNUSED(event))
{
    wxLogMessage(_("Non implémenté - Répertoire par défaut"));
    //AutoSave();
}

/**
 * Applique à la fenêtre les paramètres contenus dans le fichier de configuration enregistré
 */
void PreferenceDefaut::OuvertureFichier()
{
    wxTextFile fichierPref(Parametre::Get()->getRepertoireParametre(_T("Fu(X).conf")));

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
        fichierPref.Close();
    }
    else
    {
        fichierPref.Close();
        wxXmlDocument doc;
        if (!doc.Load(Parametre::Get()->getRepertoireParametre(_T("Fu(X).conf"))))
            return;
        if (doc.GetRoot()->GetName() != _T("default"))
            return;
        wxXmlNode *child = doc.GetRoot()->GetChildren();
        while (child)
        {
            if (child->GetName() == _T("filter_colour"))
            {
                m_checkBox[COULEUR].SetValue(true);
                m_listeCouleur->Enable(true);
                m_listeCouleur->SetStringSelection(child->GetAttribute(_T("file"), wxEmptyString));
            }
            else if (child->GetName() == _T("filter_sound"))
            {
                m_checkBox[SON].SetValue(true);
                m_listeSon->Enable(true);
                m_listeSon->SetStringSelection(child->GetAttribute(_T("file"), wxEmptyString));
            }
            else if (child->GetName() == _T("reprise"))
            {
                m_checkBox[REPRISE].SetValue(true);
                m_choix->Enable(true);
                if (child->GetAttribute(_T("type"), wxEmptyString) == _T("M3U"))
                {
                    m_listeReprise->Enable(true);
                    m_listeReprise->SetStringSelection(child->GetNodeContent());
                    m_choix->SetSelection(M3U);
                }
                else if (child->GetAttribute(_T("type"), wxEmptyString) == _T("MP3"))
                {
                    m_boiteCheminChansonRep->Enable(true);
                    m_boutonRecherche->Enable(true);
                    m_boiteCheminChansonRep->ChangeValue(child->GetNodeContent());
                    m_choix->SetSelection(MP3);
                }
            }
            else if (child->GetName() == _T("subfile"))
            {
                m_checkBox[SOUSDOSSIER].SetValue(true);
            }
            child = child->GetNext();
        }
    }
}

/**
 * Enregistre les préférences dans un fichier
 * @return vrai si réussite
 */
bool PreferenceDefaut::AutoSave()
{
    wxXmlNode *rootNode = new wxXmlNode(wxXML_ELEMENT_NODE, _T("default"));
    wxXmlNode *childNode = NULL;

    if (m_checkBox[COULEUR].GetValue() && m_listeCouleur->GetCurrentSelection() != wxNOT_FOUND)
    {
        childNode = new wxXmlNode(rootNode, wxXML_ELEMENT_NODE, _T("filter_colour"));
        childNode->AddAttribute(_T("file"), m_listeCouleur->GetString(m_listeCouleur->GetCurrentSelection()));
    }
    if (m_checkBox[SON].GetValue() && m_listeSon->GetCurrentSelection() != wxNOT_FOUND)
    {
        childNode = new wxXmlNode(rootNode, wxXML_ELEMENT_NODE, _T("filter_sound"));
        childNode->AddAttribute(_T("file"), m_listeSon->GetString(m_listeSon->GetCurrentSelection()));
    }
    if (m_checkBox[REPRISE].GetValue())
    {
        childNode = new wxXmlNode(rootNode, wxXML_ELEMENT_NODE, _T("reprise"));
        wxXmlNode *sub = new wxXmlNode(childNode, wxXML_TEXT_NODE, _(""));
        if(/*m_listeM3u_mp3*/m_choix->GetSelection() == MP3 && !m_boiteCheminChansonRep->IsEmpty())
        {
            childNode->AddAttribute(_T("type"), _T("MP3"));
            sub->SetContent(m_boiteCheminChansonRep->GetValue());
        }
        else if (/*m_listeM3u_mp3 */m_choix->GetSelection() == M3U && !m_listeReprise->GetCurrentSelection() != wxNOT_FOUND)
        {
            childNode->AddAttribute(_T("type"), _T("M3U"));
            sub->SetContent(m_listeReprise->GetString(m_listeReprise->GetCurrentSelection()));
        }
    }
    if (m_checkBox[SOUSDOSSIER].GetValue())
    {
        childNode = new wxXmlNode(rootNode, wxXML_ELEMENT_NODE, _T("subfile"));
        Parametre::Get()->setSousDossier(true);
    }
    else
    {
        Parametre::Get()->setSousDossier(false);
    }
    wxXmlDocument doc;
    doc.SetRoot(rootNode);
    //wxRemoveFile(Parametre::Get()->getRepertoireParametre(_T("Fu(X).conf")));
    return doc.Save(Parametre::Get()->getRepertoireParametre(_T("Fu(X).conf")));

    /*wxTextFile fichier(Parametre::Get()->getRepertoireParametre(_T("Fu(X).conf")));
    if (fichier.Create() || fichier.Open())
    {
        wxString chaineCouleur(_("Couleur= ")), chaineSon(_T("Son= ")), chaineReprise(_T("Reprise= ")), chaineChemin(_("Chemin= ")), chaineRecherche(_T("SousDossier= "));

        if (m_checkBox[COULEUR].GetValue() && m_listeCouleur->GetCurrentSelection() != wxNOT_FOUND)
            chaineCouleur << m_listeCouleur->GetString(m_listeCouleur->GetCurrentSelection());
        else
            chaineCouleur << _T("NON");

        if (m_checkBox[SON].GetValue() && m_listeSon->GetCurrentSelection() != wxNOT_FOUND)
            chaineSon << m_listeSon->GetString(m_listeSon->GetCurrentSelection());
        else
            chaineSon << _T("NON");

        if (m_checkBox[REPRISE].GetValue())
        {
            if(m_listeM3u_mp3 == MP3 && !m_boiteCheminChansonRep->IsEmpty())
            {
                chaineReprise << _T("MP3");
                chaineChemin << m_boiteCheminChansonRep->GetValue();
            }
            else if (m_listeM3u_mp3 == M3U && !m_listeReprise->GetCurrentSelection() != wxNOT_FOUND)
            {
                chaineReprise << _T("M3U");
                chaineChemin << m_listeReprise->GetString(m_listeReprise->GetCurrentSelection());
            }
            else
            {
                chaineReprise << _T("NON");
                chaineChemin << _T("NON");
            }
        }
        else
        {
            chaineReprise << _T("NON");
            chaineChemin << _T("NON");
        }

        if (m_checkBox[SOUSDOSSIER].GetValue())
        {
            chaineRecherche << _T("OUI");
            Parametre::Get()->setSousDossier(true);
        }
        else
        {
            chaineRecherche << _T("NON");
            Parametre::Get()->setSousDossier(false);
        }

        fichier.Clear();
        fichier.AddLine(_T("#EXTCONF_1"));
        fichier.AddLine(chaineCouleur);
        fichier.AddLine(chaineSon);
        fichier.AddLine(chaineReprise);
        fichier.AddLine(chaineChemin);
        fichier.AddLine(chaineRecherche);
        fichier.Write();
        fichier.Close();
        return true;
    }
    return false;*/
}

void PreferenceDefaut::AutoSave(wxCommandEvent &WXUNUSED(event))
{
    AutoSave();
}

/**
 * Associe des pages de préférences à celle-ci
 * @param pageCouleur
 * @param pageSon
 */
void PreferenceDefaut::SetPreferencePage(PreferenceCouleur *pageCouleur, PreferenceSon *pageSon)
{
    m_pageCouleur = pageCouleur;
    m_pageSon = pageSon;
    if (m_pageCouleur)
        m_pageCouleur->AddListener(this);
    if (m_pageSon)
        m_pageSon->AddListener(this);

    MAJListe(false);
}




