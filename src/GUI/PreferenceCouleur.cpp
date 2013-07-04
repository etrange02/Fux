/***************************************************************
 * Name:      PreferenceCouleur.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2009-09-25
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../../include/GUI/PreferenceCouleur.h"

/**
 * @class PrefCouleur
 * @brief Interface de sélection des couleurs - Passer les fichiers au format XML
 */

BEGIN_EVENT_TABLE(PrefCouleur, wxScrolledWindow)
    EVT_RADIOBOX(ID_APP_PREF_COULEUR_CHOIX, PrefCouleur::Couleur_RadioModif_Nouveau)
    EVT_COMMAND_SCROLL(ID_APP_PREF_COULEUR_SLIDER_FOND, PrefCouleur::Couleur_MAJ_Fond)
    EVT_COMMAND_SCROLL(ID_APP_PREF_COULEUR_SLIDER_BARRE, PrefCouleur::Couleur_MAJ_Barre)
    EVT_CHECKBOX(ID_APP_PREF_COULEUR_BOX_HAUT, PrefCouleur::Couleur_MAJ_GraphSup)
    EVT_CHECKBOX(ID_APP_PREF_COULEUR_BOX_BAS, PrefCouleur::Couleur_MAJ_GraphInf)
    EVT_CHOICE(ID_APP_PREF_COULEUR_LISTE_MODIF, PrefCouleur::OuvrirFichier)
    EVT_BUTTON(ID_APP_PREF_COULEUR_ENREGISTRER, PrefCouleur::Couleur_Bouton_Enregistrer)
    EVT_BUTTON(ID_APP_PREF_COULEUR_ANNULER, PrefCouleur::Couleur_Bouton_Annuler)
    EVT_BUTTON(ID_APP_PREF_COULEUR_SUPPRIMER, PrefCouleur::Couleur_Bouton_Supprimer)
    EVT_BUTTON(ID_APP_PREF_COULEUR_APPLIQUER, PrefCouleur::Couleur_Bouton_Appliquer)
    EVT_TEXT(ID_APP_PREF_COULEUR_BOITE, PrefCouleur::BoiteNouveauModifiee)
END_EVENT_TABLE()

/**
 * Constructeur
 */
PrefCouleur::PrefCouleur()
{}

/**
 * Constructeur
 * @param Parent un pointeur sur la fenêtre parente
 */
PrefCouleur::PrefCouleur(wxWindow *Parent) : wxScrolledWindow(Parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxVSCROLL | wxHSCROLL)
{}

/**
 * Destructeur
 */
PrefCouleur::~PrefCouleur()
{
    delete[] m_bitmap;
    delete[] m_sliderBarre;
    delete[] m_sliderFond;
    delete[] m_sliderPolice;
    delete[] m_TextBarre;
    delete[] m_TextFond;
    delete[] m_TextPolice;
    delete[] m_checkBoxBas;
    delete[] m_checkBoxHaut;
    delete[] m_checkBoxMiInf;
    delete[] m_checkBoxMiSup;
}

/**
 * Crée les différents éléments graphique du panel et les place dessus.
 */
void PrefCouleur::Creer(wxWindow *parent, wxWindowID id)
{
    Create(parent, id);
    //m_musiqueGraph = MusiqueGraph::Get();
    SetScrollbars(20, 20, 50, 50);

    m_sizer1V = new wxBoxSizer(wxVERTICAL);
    SetSizer(m_sizer1V);

    //Choix sous forme de bouton radio
    wxString proposition[2]; proposition[0] = _("Nouveau"); proposition[1] = _("Modifier");
    m_choix = new wxRadioBox(this, ID_APP_PREF_COULEUR_CHOIX, _("Mon choix"), wxDefaultPosition, wxDefaultSize, 2, proposition, 1, wxRA_SPECIFY_ROWS);
    m_sizer1V->Add(m_choix, 0, wxALL | wxSHAPED, 5);

    m_sizer2H = new wxBoxSizer(wxHORIZONTAL);//Tableau des données
    m_sizer1V->Add(m_sizer2H, 0, wxALL | wxSHAPED, 0);

    m_listeModif = new wxChoice(this, ID_APP_PREF_COULEUR_LISTE_MODIF, wxDefaultPosition, wxSize(180, 20));//Liste déroulante
    CreerListe(m_listeModif);//Listage
    m_boiteNom = new wxTextCtrl(this, ID_APP_PREF_COULEUR_BOITE, _T(""), wxDefaultPosition, wxSize(120, 21));
    m_sizer2H->Add(m_listeModif, 1, wxALL | wxSHAPED, 5);
    m_sizer2H->Add(m_boiteNom, 0, wxALL | wxEXPAND, 5);

    m_bitmap = new wxBitmap[4];
    for (int i = 0; i < 4; i++)
        m_bitmap[i].Create(POCHETTE_COTE, POCHETTE_COTE);

/////////////////Arrière plan du graph/////////////////////////////////////////////////////////////////////////////////////////////
    m_sizerFond = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Arrière plan"));
    m_sizer1V->Add(m_sizerFond, 0, wxALL | wxSHAPED, 5);
    m_apercuFond = new wxStaticBitmap(this, ID_APP_PREF_COULEUR_IMG_FOND, m_bitmap[FOND]);
    m_sizerFond->Add(m_apercuFond, 0, wxALL | wxSHAPED, 5);

    wxSizer *sizerFondF = new wxFlexGridSizer(3, 2, 5, 5);
    m_sizerFond->Add(sizerFondF, 0, wxALL | wxEXPAND, 5);

    m_sliderFond = new wxSlider[3];
    m_sliderFond[ROUGE].Create(this, ID_APP_PREF_COULEUR_SLIDER_FOND, 0, 0, 255, wxDefaultPosition, wxSize(255, 30));
    m_sliderFond[VERT].Create(this, ID_APP_PREF_COULEUR_SLIDER_FOND, 0, 0, 255, wxDefaultPosition, wxSize(255, 30));
    m_sliderFond[BLEU].Create(this, ID_APP_PREF_COULEUR_SLIDER_FOND, 0, 0, 255, wxDefaultPosition, wxSize(255, 30));

    m_TextFond = new wxStaticText[3];
    m_TextFond[ROUGE].Create(this, wxID_ANY, _("R : 0"));
    m_TextFond[VERT].Create(this, wxID_ANY, _("V : 0"));
    m_TextFond[BLEU].Create(this, wxID_ANY, _("B : 0"));

    sizerFondF->Add(&m_sliderFond[ROUGE], 0, wxALL, 0);
    sizerFondF->Add(&m_TextFond[ROUGE], 0, wxALL, 0);
    sizerFondF->Add(&m_sliderFond[VERT], 0, wxALL, 0);
    sizerFondF->Add(&m_TextFond[VERT], 0, wxALL, 0);
    sizerFondF->Add(&m_sliderFond[BLEU], 0, wxALL, 0);
    sizerFondF->Add(&m_TextFond[BLEU], 0, wxALL, 0);

//////////////////////Barre de progression et Texte////////////////////////////////////////////////////////////////////////////////
	m_sizerBarrePolice = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Barre de progression et texte"));
	m_sizer1V->Add(m_sizerBarrePolice, 0, wxALL | wxSHAPED, 5);

    wxSizer *sizerBarreF = new wxFlexGridSizer(3, 2, 5, 5);//Contient nom et cases non modifiables (droite); dispo en colonne
    m_sizerBarrePolice->Add(sizerBarreF, 0, wxALL | wxEXPAND, 5);

    m_sliderBarre = new wxSlider[3];
    m_sliderBarre[ROUGE].Create(this, ID_APP_PREF_COULEUR_SLIDER_BARRE, 0, 0, 255, wxDefaultPosition, wxSize(255, 30));
    m_sliderBarre[VERT].Create(this, ID_APP_PREF_COULEUR_SLIDER_BARRE, 0, 0, 255, wxDefaultPosition, wxSize(255, 30));
    m_sliderBarre[BLEU].Create(this, ID_APP_PREF_COULEUR_SLIDER_BARRE, 255, 0, 255, wxDefaultPosition, wxSize(255, 30));

    m_TextBarre = new wxStaticText[3];
    m_TextBarre[ROUGE].Create(this, wxID_ANY, _("R : 0"));
    m_TextBarre[VERT].Create(this, wxID_ANY, _("V : 0"));
    m_TextBarre[BLEU].Create(this, wxID_ANY, _("B : 255"));

    sizerBarreF->Add(&m_sliderBarre[ROUGE], 0, wxALL, 0);
    sizerBarreF->Add(&m_TextBarre[ROUGE], 0, wxALL, 0);
    sizerBarreF->Add(&m_sliderBarre[VERT], 0, wxALL, 0);
    sizerBarreF->Add(&m_TextBarre[VERT], 0, wxALL, 0);
    sizerBarreF->Add(&m_sliderBarre[BLEU], 0, wxALL, 0);
    sizerBarreF->Add(&m_TextBarre[BLEU], 0, wxALL, 0);


    wxMemoryDC tempBarre;
    tempBarre.SelectObject(m_bitmap[BARRE]);
    tempBarre.SetBrush(wxColour(0, 0, 255));
    tempBarre.DrawRectangle(0, 0, POCHETTE_COTE, POCHETTE_COTE);
    tempBarre.SetTextForeground(wxColour(255, 0, 255));
    int x, y;
    tempBarre.GetTextExtent(_("Texte"), &x, &y);
    tempBarre.DrawText(_("Texte"), (POCHETTE_COTE-x)/2, (POCHETTE_COTE-y)/2);
    m_apercuBarre = new wxStaticBitmap(this, ID_APP_PREF_COULEUR_IMG_BARRE, m_bitmap[BARRE]);
    m_sizerBarrePolice->Add(m_apercuBarre, 0, wxALL | wxSHAPED, 5);

    wxSizer *sizerPoliceF = new wxFlexGridSizer(3, 2, 5, 5);//Contient nom et cases non modifiables (droite); dispo en colonne
    m_sizerBarrePolice->Add(sizerPoliceF, 0, wxALL | wxEXPAND, 5);

    m_sliderPolice = new wxSlider[3];
    m_sliderPolice[ROUGE].Create(this, ID_APP_PREF_COULEUR_SLIDER_BARRE, 255, 0, 255, wxDefaultPosition, wxSize(255, 30));
    m_sliderPolice[VERT].Create(this, ID_APP_PREF_COULEUR_SLIDER_BARRE, 0, 0, 255, wxDefaultPosition, wxSize(255, 30));
    m_sliderPolice[BLEU].Create(this, ID_APP_PREF_COULEUR_SLIDER_BARRE, 255, 0, 255, wxDefaultPosition, wxSize(255, 30));

    m_TextPolice = new wxStaticText[3];
    m_TextPolice[ROUGE].Create(this, wxID_ANY, _("R : 255"));
    m_TextPolice[VERT].Create(this, wxID_ANY, _("V : 0"));
    m_TextPolice[BLEU].Create(this, wxID_ANY, _("B : 255"));

    sizerPoliceF->Add(&m_TextPolice[ROUGE], 0, wxALL, 0);
    sizerPoliceF->Add(&m_sliderPolice[ROUGE], 0, wxALL, 0);
    sizerPoliceF->Add(&m_TextPolice[VERT], 0, wxALL, 0);
    sizerPoliceF->Add(&m_sliderPolice[VERT], 0, wxALL, 0);
    sizerPoliceF->Add(&m_TextPolice[BLEU], 0, wxALL, 0);
    sizerPoliceF->Add(&m_sliderPolice[BLEU], 0, wxALL, 0);

///////////////Partie supérieure du graph/////////////////////////////////////////////////////////////////////////////////////
	m_sizerGraphHaut = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Partie supérieure du graph"));
	m_sizer1V->Add(m_sizerGraphHaut, 0, wxALL | wxSHAPED, 5);

    wxSizer *sizerGraphHaF = new wxFlexGridSizer(4, 1, 5, 5);//Contient nom et cases non modifiables (droite); dispo en colonne
    m_sizerGraphHaut->Add(sizerGraphHaF, 0, wxALL | wxEXPAND, 5);

    wxStaticText* TextHaut = new wxStaticText(this, wxID_ANY, _("Haut de l'écran"));

    m_checkBoxHaut = new wxCheckBox[3];
    m_checkBoxHaut[ROUGE].Create(this, ID_APP_PREF_COULEUR_BOX_HAUT, _("Rouge"));
    m_checkBoxHaut[ROUGE].SetValue(true);
    m_checkBoxHaut[VERT].Create(this, ID_APP_PREF_COULEUR_BOX_HAUT, _("Vert"));
    m_checkBoxHaut[BLEU].Create(this, ID_APP_PREF_COULEUR_BOX_HAUT, _("Bleu"));

    sizerGraphHaF->Add(TextHaut, 0, wxALL, 0);
    sizerGraphHaF->Add(&m_checkBoxHaut[ROUGE], 0, wxALL, 0);
    sizerGraphHaF->Add(&m_checkBoxHaut[VERT], 0, wxALL, 0);
    sizerGraphHaF->Add(&m_checkBoxHaut[BLEU], 0, wxALL, 0);


    wxMemoryDC tempHaut;
    tempHaut.SelectObject(m_bitmap[HAUT_SUP]);
    tempHaut.GradientFillLinear(wxRect(0, 0, POCHETTE_COTE, POCHETTE_COTE), wxColour(0, 255, 0), wxColour(255, 0, 0), wxNORTH);
    m_apercuGraphHaut = new wxStaticBitmap(this, ID_APP_PREF_COULEUR_IMG_GRAPH_HAUT, m_bitmap[HAUT_SUP]);
    m_sizerGraphHaut->Add(m_apercuGraphHaut, 0, wxALL | wxSHAPED, 5);

    wxSizer *sizerGraphSuF = new wxFlexGridSizer(4, 1, 5, 5);//Contient nom et cases non modifiables (droite); dispo en colonne
    m_sizerGraphHaut->Add(sizerGraphSuF, 0, wxALL | wxEXPAND, 5);

    wxStaticText* TextSup = new wxStaticText(this, wxID_ANY, _("Moitié supérieure"));
    m_checkBoxMiSup = new wxCheckBox[3];
    m_checkBoxMiSup[ROUGE].Create(this, ID_APP_PREF_COULEUR_BOX_HAUT, _("Rouge"));
    m_checkBoxMiSup[VERT].Create(this, ID_APP_PREF_COULEUR_BOX_HAUT, _("Vert"));
    m_checkBoxMiSup[VERT].SetValue(true);
    m_checkBoxMiSup[BLEU].Create(this, ID_APP_PREF_COULEUR_BOX_HAUT, _("Bleu"));

    sizerGraphSuF->Add(TextSup, 0, wxALL, 0);
    sizerGraphSuF->Add(&m_checkBoxMiSup[ROUGE], 0, wxALL, 0);
    sizerGraphSuF->Add(&m_checkBoxMiSup[VERT], 0, wxALL, 0);
    sizerGraphSuF->Add(&m_checkBoxMiSup[BLEU], 0, wxALL, 0);
//////////////////////////////////////////////////////////////////////////////////////
    m_doubleBarre = new wxCheckBox(this, ID_APP_PREF_COULEUR_BOX_DOUBLE, _("Symétrie horizontal"));
    m_sizer1V->Add(m_doubleBarre, 0, wxALL | wxSHAPED, 20);

////////////////////////////Partie inférieure du graph/////////////////////////////////////////////////////////////////////////////////////
	m_sizerGraphBas = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Partie inférieure du graph"));
    m_sizer1V->Add(m_sizerGraphBas, 0, wxALL | wxSHAPED, 5);

    wxSizer *sizerGraphInF = new wxFlexGridSizer(4, 1, 5, 5);//Contient nom et cases non modifiables (droite); dispo en colonne
    m_sizerGraphBas->Add(sizerGraphInF, 0, wxALL | wxEXPAND, 5);

    wxStaticText* TextInf = new wxStaticText(this, wxID_ANY, _("Moitié inférieure"));

    m_checkBoxMiInf = new wxCheckBox[3];
    m_checkBoxMiInf[ROUGE].Create(this, ID_APP_PREF_COULEUR_BOX_BAS, _("Rouge"));
    m_checkBoxMiInf[VERT].Create(this, ID_APP_PREF_COULEUR_BOX_BAS, _("Vert"));
    m_checkBoxMiInf[BLEU].Create(this, ID_APP_PREF_COULEUR_BOX_BAS, _("Bleu"));
    m_checkBoxMiInf[BLEU].SetValue(true);

    sizerGraphInF->Add(TextInf, 0, wxALL, 0);
    sizerGraphInF->Add(&m_checkBoxMiInf[ROUGE], 0, wxALL, 0);
    sizerGraphInF->Add(&m_checkBoxMiInf[VERT], 0, wxALL, 0);
    sizerGraphInF->Add(&m_checkBoxMiInf[BLEU], 0, wxALL, 0);


    wxMemoryDC tempBas;
    tempBas.SelectObject(m_bitmap[BAS_INF]);
    tempBas.GradientFillLinear(wxRect(0, 0, POCHETTE_COTE, POCHETTE_COTE), wxColour(0, 0, 255), wxColour(0, 0, 0), wxSOUTH);
    m_apercuGraphBas = new wxStaticBitmap(this, ID_APP_PREF_COULEUR_IMG_GRAPH_BAS, m_bitmap[BAS_INF]);
    m_sizerGraphBas->Add(m_apercuGraphBas, 0, wxALL | wxSHAPED, 5);

    wxSizer *sizerGraphBasF = new wxFlexGridSizer(4, 1, 5, 5);//Contient nom et cases non modifiables (droite); dispo en colonne
    m_sizerGraphBas->Add(sizerGraphBasF, 0, wxALL | wxEXPAND, 5);

    wxStaticText* TextBas = new wxStaticText(this, wxID_ANY, _("Bas de l'écran"));
    m_checkBoxBas = new wxCheckBox[3];
    m_checkBoxBas[ROUGE].Create(this, ID_APP_PREF_COULEUR_BOX_BAS, _("Rouge"));
    m_checkBoxBas[VERT].Create(this, ID_APP_PREF_COULEUR_BOX_BAS, _("Vert"));
    m_checkBoxBas[BLEU].Create(this, ID_APP_PREF_COULEUR_BOX_BAS, _("Bleu"));

    sizerGraphBasF->Add(TextBas, 0, wxALL, 0);
    sizerGraphBasF->Add(&m_checkBoxBas[ROUGE], 0, wxALL, 0);
    sizerGraphBasF->Add(&m_checkBoxBas[VERT], 0, wxALL, 0);
    sizerGraphBasF->Add(&m_checkBoxBas[BLEU], 0, wxALL, 0);

//////////////Partie Création des boutons//////////////////////
    m_sizerBouton = new wxFlexGridSizer(1, 4, 5, 5);
    m_sizer1V->Add(m_sizerBouton, 0, wxUP | wxALIGN_BOTTOM, 5);

    wxButton *m_Bouton_Enregistrer = new wxButton(this, ID_APP_PREF_COULEUR_ENREGISTRER, _("Enregistrer"));
    wxButton *m_Bouton_Annuler = new wxButton(this, ID_APP_PREF_COULEUR_ANNULER, _("Annuler"));
    m_Bouton_Appliquer = new wxButton(this, ID_APP_PREF_COULEUR_APPLIQUER, _("Appliquer"));
    m_Bouton_Supprimer = new wxButton(this, ID_APP_PREF_COULEUR_SUPPRIMER, _("Supprimer"));

    m_sizerBouton->Add(m_Bouton_Enregistrer, 0, wxALL | wxEXPAND, 5);
    m_sizerBouton->Add(m_Bouton_Annuler, 0, wxALL | wxEXPAND, 5);
    m_sizerBouton->Add(m_Bouton_Appliquer, 0, wxALL | wxEXPAND, 5);
    m_sizerBouton->Add(m_Bouton_Supprimer, 0, wxALL | wxEXPAND, 5);

//////////////Partie Affectation valeurs//////////////////////
    m_listeModif->Enable(false);
    m_Bouton_Appliquer->Enable(false);
    m_Bouton_Supprimer->Enable(false);
    m_listeModif_Nouveau = NOUVEAU;
    //Refresh();
    for (int i=0; i<3; i++)
    {
        m_sliderBarre[i].SetBackgroundColour(wxColour(255, 255, 255));//SetTransparent(0);//
        m_sliderPolice[i].SetBackgroundColour(wxColour(255, 255, 255));//SetTransparent(0);//
    }

    m_sizer1V->Layout();
}

/**
 * Liste tous les éléments présent dans le dossier Couleur
 * @param liste élément graphique devant être mis à jour
 * @return le nombre d'éléments présent dans liste
 */
int PrefCouleur::CreerListe(wxChoice *liste)
{
    int nombre = 0;
    wxFile fichier;
    fichier.Create(Parametre::Get()->getRepertoireParametre(_T("Liste_Couleur.txt")), true);

    if (wxDir::Exists(Parametre::Get()->getRepertoireParametre(_T("Preference"), _T("Couleur"))))
    {
        wxString copie;
        wxDir Repertoire(Parametre::Get()->getRepertoireParametre(_T("Preference"), _T("Couleur")));
        bool continuer = Repertoire.GetFirst(&copie, _T("*.sauve"), wxDIR_FILES);

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
 * Évènement - Modifie l'accessibilité des élément graphique en fonction du mode création/modification
 */
void PrefCouleur::Couleur_RadioModif_Nouveau(wxCommandEvent &event)
{
    m_listeModif_Nouveau = event.GetInt();

    if (m_listeModif_Nouveau == MODIFIER)
    {
        m_listeModif->Enable(true);
        m_Bouton_Appliquer->Enable(true);
        m_Bouton_Supprimer->Enable(true);
        m_listeModif->SetSelection(wxNOT_FOUND);
        //m_sizerNewModif->GetStaticBox().SetLabel(_("Modifier"));
    }
    else if (m_listeModif_Nouveau == NOUVEAU)
    {
        m_listeModif->Enable(false);
        m_Bouton_Appliquer->Enable(false);
        m_Bouton_Supprimer->Enable(false);
        m_listeModif->SetSelection(wxNOT_FOUND);
        //m_sizerNewModif->GetStaticBox().SetLabel(_("Nouveau"));
    }
    MAJ_Annuler();
    m_sizer1V->Layout();
}

/**
 * Méthode pour un changement manuel
 * @param changement le mode utilisé
 * @see Couleur_RadioModif_Nouveau
 */
void PrefCouleur::Couleur_Modif_Nouveau(int changement)
{
    m_listeModif_Nouveau = changement;

    if (m_listeModif_Nouveau == MODIFIER)
    {
        m_listeModif->Enable(true);
        m_Bouton_Appliquer->Enable(true);
        m_Bouton_Supprimer->Enable(true);
        m_listeModif->SetSelection(wxNOT_FOUND);
        //m_sizerNewModif->GetStaticBox().SetLabel(_("Modifier"));
    }
    else if (m_listeModif_Nouveau == NOUVEAU)
    {
        m_listeModif->Enable(false);
        m_Bouton_Appliquer->Enable(false);
        m_Bouton_Supprimer->Enable(false);
        m_listeModif->SetSelection(wxNOT_FOUND);
        //m_sizerNewModif->GetStaticBox().SetLabel(_("Nouveau"));
    }
    MAJ_Annuler();
    m_sizer1V->Layout();
}

/**
 * Modifie les informations et la couleur du carré de visualisation "Arrière plan"
 */
void PrefCouleur::MAJ_Fond()
{
    wxMemoryDC tempFond;
    tempFond.SelectObject(m_bitmap[FOND]);
    tempFond.SetBrush(wxColour(m_sliderFond[ROUGE].GetValue(), m_sliderFond[VERT].GetValue(), m_sliderFond[BLEU].GetValue()));
    tempFond.DrawRectangle(0, 0, POCHETTE_COTE, POCHETTE_COTE);
    tempFond.SelectObject(wxNullBitmap);
    m_apercuFond->SetBitmap(m_bitmap[FOND]);

    wxString es[3];
    es[0] << _("R : ") << m_sliderFond[ROUGE].GetValue();
    es[1] << _("V : ") << m_sliderFond[VERT].GetValue();
    es[2] << _("B : ") << m_sliderFond[BLEU].GetValue();
    m_TextFond[ROUGE].SetLabel(es[0]);
    m_TextFond[VERT].SetLabel(es[1]);
    m_TextFond[BLEU].SetLabel(es[2]);
}

/**
 * Evènement - Appelé lors de l'utilisation d'un slider
 * @see MAJ_Fond
 */
void PrefCouleur::Couleur_MAJ_Fond(wxScrollEvent &WXUNUSED(event))
{    MAJ_Fond();}

/**
 * Modifie les informations et la couleur du carré de visualisation "Barre de progression et texte"
 */
void PrefCouleur::MAJ_Barre()
{
    wxMemoryDC tempBarre;
    tempBarre.SelectObject(m_bitmap[BARRE]);
    tempBarre.SetBrush(wxColour(m_sliderBarre[ROUGE].GetValue(), m_sliderBarre[VERT].GetValue(), m_sliderBarre[BLEU].GetValue()));
    tempBarre.DrawRectangle(0, 0, POCHETTE_COTE, POCHETTE_COTE);
    tempBarre.SetTextForeground(wxColour(m_sliderPolice[ROUGE].GetValue(), m_sliderPolice[VERT].GetValue(), m_sliderPolice[BLEU].GetValue()));
    int x, y;
    tempBarre.GetTextExtent(_("Texte"), &x, &y);
    tempBarre.DrawText(_("Texte"), (POCHETTE_COTE-x)/2, (POCHETTE_COTE-y)/2);
    tempBarre.SelectObject(wxNullBitmap);
    m_apercuBarre->SetBitmap(m_bitmap[BARRE]);

    wxString es[6];
    es[0] << _("R : ") << m_sliderBarre[ROUGE].GetValue();
    es[1] << _("V : ") << m_sliderBarre[VERT].GetValue();
    es[2] << _("B : ") << m_sliderBarre[BLEU].GetValue();
    es[3] << _("R : ") << m_sliderPolice[ROUGE].GetValue();
    es[4] << _("V : ") << m_sliderPolice[VERT].GetValue();
    es[5] << _("B : ") << m_sliderPolice[BLEU].GetValue();
    m_TextBarre[ROUGE].SetLabel(es[0]);
    m_TextBarre[VERT].SetLabel(es[1]);
    m_TextBarre[BLEU].SetLabel(es[2]);
    m_TextPolice[ROUGE].SetLabel(es[3]);
    m_TextPolice[VERT].SetLabel(es[4]);
    m_TextPolice[BLEU].SetLabel(es[5]);
}

/**
 * Evènement - Appelé lors de l'utilisation d'un slider
 * @see MAJ_Barre
 */
void PrefCouleur::Couleur_MAJ_Barre(wxScrollEvent &WXUNUSED(event))
{    MAJ_Barre();}

/**
 * Modifie la couleur du carré de visualisation "Partie supérieure du graphe"
 */
void PrefCouleur::MAJ_GraphSup()
{
    int couleurHaut[3] = {0, 0, 0}, couleurSup[3] = {0, 0, 0};
    wxMemoryDC tempGraph;

    for (int i = 0; i < 3; i++)
    {
        if (m_checkBoxHaut[i].GetValue())
            couleurHaut[i] = 255;
        if (m_checkBoxMiSup[i].GetValue())
            couleurSup[i] = 255;
    }
    tempGraph.SelectObject(m_bitmap[HAUT_SUP]);
    tempGraph.GradientFillLinear(wxRect(0, 0, POCHETTE_COTE, POCHETTE_COTE), wxColour(couleurSup[0], couleurSup[1], couleurSup[2]), wxColour(couleurHaut[0], couleurHaut[1], couleurHaut[2]), wxNORTH);
    tempGraph.SelectObject(wxNullBitmap);
    m_apercuGraphHaut->SetBitmap(m_bitmap[HAUT_SUP]);
}

/**
 * Evènement - Appelé lors de la modification d'une checkbox
 * @see MAJ_GraphInf
 */
void PrefCouleur::Couleur_MAJ_GraphInf(wxCommandEvent &WXUNUSED(event))
{    MAJ_GraphInf();}

/**
 * Modifie la couleur du carré de visualisation "Partie inférieure du graphe"
 */
void PrefCouleur::MAJ_GraphInf()
{
    int couleurBas[3] = {0, 0, 0}, couleurInf[3] = {0, 0, 0};
    wxMemoryDC tempGraph;

    for (int i = 0; i < 3; i++)
    {
        if (m_checkBoxBas[i].GetValue())
            couleurBas[i] = 255;
        if (m_checkBoxMiInf[i].GetValue())
            couleurInf[i] = 255;
    }
    tempGraph.SelectObject(m_bitmap[BAS_INF]);
    tempGraph.GradientFillLinear(wxRect(0, 0, POCHETTE_COTE, POCHETTE_COTE), wxColour(couleurBas[0], couleurBas[1], couleurBas[2]), wxColour(couleurInf[0], couleurInf[1], couleurInf[2]), wxNORTH);
    tempGraph.SelectObject(wxNullBitmap);
    m_apercuGraphBas->SetBitmap(m_bitmap[BAS_INF]);
}

/**
 * Evènement - Appelé lors de la modification d'une checkbox
 * @see MAJ_GraphSup
 */
void PrefCouleur::Couleur_MAJ_GraphSup(wxCommandEvent &WXUNUSED(event))
{    MAJ_GraphSup();}


/**
 * Evènement - Appelé lors de la demande de lecture d'un fichier contenant des préférences
 * @see Couleur_OuvrirFichier
 */
void PrefCouleur::OuvrirFichier(wxCommandEvent &WXUNUSED(event))
{    Couleur_OuvrirFichier(m_listeModif->GetString(m_listeModif->GetCurrentSelection()), true);}

/**
 * Lit le contenu d'un fichier et modifie le graphe ou la fenêtre de visualisation
 * @param chemin le chamin du fichier à lire
 * @param evenement si vrai, les paramètres sont juste visualisés, si faux les paramètres sont appliqués au graphe
 */
void PrefCouleur::Couleur_OuvrirFichier(wxString chemin, bool evenement)
{
    wxString cheminFichier = Parametre::Get()->getRepertoireParametre(_T("Preference"), _T("Couleur"), chemin);

    wxTextFile fichier(cheminFichier);
    //////////////////////////////////
    fichier.Open();
    if (fichier.GetLine(0).IsSameAs(_T("#EXTSAUVE_C1")))
    {
        Couleur colFond = Couleur_ExtraitString(fichier.GetLine(2));
        Couleur colBarre = Couleur_ExtraitString(fichier.GetLine(3));
        Couleur colPolice = Couleur_ExtraitString(fichier.GetLine(4));

        if (evenement)
        {
            wxString nom = fichier.GetLine(1);
            m_boiteNom->ChangeValue(nom);
            m_sliderFond[ROUGE].SetValue(colFond.GetRed());
            m_sliderFond[VERT].SetValue(colFond.GetGreen());
            m_sliderFond[BLEU].SetValue(colFond.GetBlue());
            m_sliderBarre[ROUGE].SetValue(colBarre.GetRed());
            m_sliderBarre[VERT].SetValue(colBarre.GetGreen());
            m_sliderBarre[BLEU].SetValue(colBarre.GetBlue());
            m_sliderPolice[ROUGE].SetValue(colPolice.GetRed());
            m_sliderPolice[VERT].SetValue(colPolice.GetGreen());
            m_sliderPolice[BLEU].SetValue(colPolice.GetBlue());
            TFSup_ExtraitString(fichier.GetLine(5), fichier.GetLine(6));
            TFInf_ExtraitString(fichier.GetLine(8), fichier.GetLine(9), fichier.GetLine(7));
            MAJ_Fond();
            MAJ_Barre();
            MAJ_GraphSup();
            MAJ_GraphInf();
        }
        else
        {
            Couleur haut, miSup, miInf, bas;

            wxString temp, chaineCol1[3], chaineCol2[3];
            temp = fichier.GetLine(5).AfterFirst(' ');
            for (int i=0; i<3; i++)
            {
                chaineCol1[i] = temp.BeforeFirst(' ');
                temp = temp.AfterFirst(' ');
            }
            temp = fichier.GetLine(6).AfterFirst(' ');
            for (int i=0; i<3; i++)
            {
                chaineCol2[i] = temp.BeforeFirst(' ');
                temp = temp.AfterFirst(' ');
            }

            if (chaineCol1[0] == _T("t"))
                haut.SetRed(255);
            if (chaineCol1[1] == _T("t"))
                haut.SetGreen(255);
            if (chaineCol1[2] == _T("t"))
                haut.SetBlue(255);
            if (chaineCol2[0] == _T("t"))
                miSup.SetRed(255);
            if (chaineCol2[1] == _T("t"))
                miSup.SetGreen(255);
            if (chaineCol2[2] == _T("t"))
                miSup.SetBlue(255);

            wxString chaineCol3;
            temp = fichier.GetLine(8).AfterFirst(' ');
            for (int i=0; i<3; i++)
            {
                chaineCol1[i] = temp.BeforeFirst(' ');
                temp = temp.AfterFirst(' ');
            }
            temp = fichier.GetLine(9).AfterFirst(' ');
            for (int i=0; i<3; i++)
            {
                chaineCol2[i] = temp.BeforeFirst(' ');
                temp = temp.AfterFirst(' ');
            }
            temp = fichier.GetLine(7).AfterFirst(' ');
            chaineCol3 = temp.BeforeFirst(' ');

            if (chaineCol1[0] == _T("t"))
                miInf.SetRed(255);
            if (chaineCol1[1] == _T("t"))
                miInf.SetGreen(255);
            if (chaineCol1[2] == _T("t"))
                miInf.SetBlue(255);
            if (chaineCol2[0] == _T("t"))
                bas.SetRed(255);
            if (chaineCol2[1] == _T("t"))
                bas.SetGreen(255);
            if (chaineCol2[2] == _T("t"))
                bas.SetBlue(255);

            bool doubleBarre = false;
            if (chaineCol3 == _T("t"))
                doubleBarre = true;

            Parametre::Get()->setCouleurs(colFond, colBarre, colPolice, haut, miSup, miInf, bas, doubleBarre);
        }
    }
    fichier.Close();
}

/**
 * Convertit une chaîne de caractères en structure Couleur (Couleur.R, Couleur.V, Couleur.B)
 * @param chaine une chaine contenant des entiers 0-255 séparé par des espaces ' '
 * @return la structure Couleur correspondante
 */
Couleur PrefCouleur::Couleur_ExtraitString(wxString chaine) const
{
    Couleur ObjetCouleur;
    wxString temp, chaineCol[3];
    long val = 0;
    temp = chaine.AfterFirst(' ');

    for (int i=0; i<3; i++)
    {
        chaineCol[i] = temp.BeforeFirst(' ');
        temp = temp.AfterFirst(' ');
    }

    chaineCol[ROUGE].ToLong(&val);
    ObjetCouleur.SetRed(val);
    chaineCol[VERT].ToLong(&val);
    ObjetCouleur.SetGreen(val);
    chaineCol[BLEU].ToLong(&val);
    ObjetCouleur.SetBlue(val);

    return ObjetCouleur;
}

/**
 * Transforme et applique le contenu des éléments donnés en paramètre au carré de visualisation "Partie supérieure du graphe"
 * @param chaine1
 * @param chaine2
 * @return vrai
 */
bool PrefCouleur::TFSup_ExtraitString(wxString chaine1, wxString chaine2)
{
    wxString temp, chaineCol1[3], chaineCol2[3];

    temp = chaine1.AfterFirst(' ');
    for (int i=0; i<3; i++)
    {
        chaineCol1[i] = temp.BeforeFirst(' ');
        temp = temp.AfterFirst(' ');
    }
    temp = chaine2.AfterFirst(' ');
    for (int i=0; i<3; i++)
    {
        chaineCol2[i] = temp.BeforeFirst(' ');
        temp = temp.AfterFirst(' ');
    }

    for (int i=0; i<3; i++)
    {
        /*if (chaineCol1[i] == "t")
            m_checkBoxHaut[i].SetValue(true);
        else
            m_checkBoxHaut[i].SetValue(false);
        if (chaineCol2[i] == "t")
            m_checkBoxMiSup[i].SetValue(true);
        else
            m_checkBoxMiSup[i].SetValue(false);*/
        m_checkBoxHaut[i].SetValue((chaineCol1[i] == _T("t")));
        m_checkBoxMiSup[i].SetValue((chaineCol2[i] == _T("t")));
    }
    return true;
}

/**
 * Transforme et applique le contenu des éléments donnés en paramètre au carré de visualisation "Partie inférieure du graphe"
 * @param chaine1
 * @param chaine2
 * @param chaine3
 * @return vrai
 */
bool PrefCouleur::TFInf_ExtraitString(wxString chaine1, wxString chaine2, wxString chaine3)
{
    wxString temp, chaineCol1[3], chaineCol2[3], chaineCol3;

    temp = chaine1.AfterFirst(' ');
    for (int i=0; i<3; i++)
    {
        chaineCol1[i] = temp.BeforeFirst(' ');
        temp = temp.AfterFirst(' ');
    }
    temp = chaine2.AfterFirst(' ');
    for (int i=0; i<3; i++)
    {
        chaineCol2[i] = temp.BeforeFirst(' ');
        temp = temp.AfterFirst(' ');
    }
    temp = chaine3.AfterFirst(' ');
    chaineCol3 = temp.BeforeFirst(' ');

    for (int i=0; i<3; i++)
    {
        /*if (chaineCol1[i] == "t")
            m_checkBoxMiInf[i].SetValue(true);
        else
            m_checkBoxMiInf[i].SetValue(false);
        if (chaineCol2[i] == "t")
            m_checkBoxBas[i].SetValue(true);
        else
            m_checkBoxBas[i].SetValue(false);*/
        m_checkBoxMiInf[i].SetValue((chaineCol1[i] == _T("t")));
        m_checkBoxBas[i].SetValue((chaineCol2[i] == _T("t")));
    }
    /*if (chaineCol3 == "t")
        m_doubleBarre->SetValue(true);
    else
        m_doubleBarre->SetValue(false);*/
        m_doubleBarre->SetValue((chaineCol3 == _T("t")));
    return true;
}

/**
 * Évènement - Enregistre dans un fichier les paramètres sélectionnés
 */
void PrefCouleur::Couleur_Bouton_Enregistrer(wxCommandEvent &WXUNUSED(event))
{
    if (!m_boiteNom->IsEmpty() && (m_listeModif_Nouveau == NOUVEAU || m_listeModif->GetCurrentSelection() != wxNOT_FOUND))
    {
        wxFile FichierListe;
        wxString chemin = Parametre::Get()->getRepertoireParametre(_T("Preference"), _T("Couleur"), wxFileName::GetPathSeparator()), cheminFichier, nom = m_boiteNom->GetValue();

        cheminFichier = chemin;
        chemin << nom << _T(".sauve");

        if (wxFileName::FileExists(chemin) && m_listeModif_Nouveau == NOUVEAU && !m_Bouton_Appliquer->IsEnabled())
        {
            wxMessageBox(_("Un fichier portant ce nom existe déjà !"), _("Erreur !"));
        }
        else
        {
            if (m_listeModif_Nouveau == MODIFIER)// && m_boiteNom->IsModified())// || (m_listeModif_Nouveau == NOUVEAU && m_Bouton_Appliquer->IsEnabled())
            {
                cheminFichier << m_listeModif->GetString(m_listeModif->GetCurrentSelection());
                wxRemoveFile(cheminFichier);
            }
            wxString chaineFond, chaineBarre, chainePolice, chaineHaut, chaineSup, chaineDouble, chaineInf, chaineBas;
            chaineFond << _T("Fond= ") << m_sliderFond[0].GetValue() << _T(" ") << m_sliderFond[1].GetValue() << _T(" ") << m_sliderFond[2].GetValue();
            chaineBarre << _T("Barre= ") << m_sliderBarre[0].GetValue() << _T(" ") << m_sliderBarre[1].GetValue() << _T(" ") << m_sliderBarre[2].GetValue();
            chainePolice << _T("Police= ") << m_sliderPolice[0].GetValue() << _T(" ") << m_sliderPolice[1].GetValue() << _T(" ") << m_sliderPolice[2].GetValue();

            chaineHaut << _T("Haut=");
            for (int i=0; i<3; i++)
            {
                if (m_checkBoxHaut[i].GetValue())
                    chaineHaut << _T(" t");
                else
                    chaineHaut << _T(" f");
            }
            chaineSup << _T("MiSup=");
            for (int i=0; i<3; i++)
            {
                if (m_checkBoxMiSup[i].GetValue())
                    chaineSup << _T(" t");
                else
                    chaineSup << _T(" f");
            }
            chaineInf << _T("MiInf=");
            for (int i=0; i<3; i++)
            {
                if (m_checkBoxMiInf[i].GetValue())
                    chaineInf << _T(" t");
                else
                    chaineInf << _T(" f");
            }
            chaineBas << _T("Bas=");
            for (int i=0; i<3; i++)
            {
                if (m_checkBoxBas[i].GetValue())
                    chaineBas << _T(" t");
                else
                    chaineBas << _T(" f");
            }
            chaineDouble << _T("Double=");
            if (m_doubleBarre->GetValue())
                chaineDouble << _T(" t");
            else
                chaineDouble << _T(" f");

            if (!FichierListe.Create(chemin, true))
            {
                wxMessageBox(_("Erreur dans le nom.\nVérifiez que vous utilisez des caractères autorisés."), _("Erreur"));
                return;
            }

            FichierListe.Write(_T("#EXTSAUVE_C1\r\n"));
            FichierListe.Write(nom);
            FichierListe.Write(_T("\r\n"));
            FichierListe.Write(chaineFond);
            FichierListe.Write(_T("\r\n"));
            FichierListe.Write(chaineBarre);
            FichierListe.Write(_T("\r\n"));
            FichierListe.Write(chainePolice);
            FichierListe.Write(_T("\r\n"));
            FichierListe.Write(chaineHaut);
            FichierListe.Write(_T("\r\n"));
            FichierListe.Write(chaineSup);
            FichierListe.Write(_T("\r\n"));
            FichierListe.Write(chaineDouble);
            FichierListe.Write(_T("\r\n"));
            FichierListe.Write(chaineInf);
            FichierListe.Write(_T("\r\n"));
            FichierListe.Write(chaineBas);
            FichierListe.Close();

            m_listeModif->Clear();
            CreerListe(m_listeModif);
            if (m_listeModif_Nouveau == MODIFIER)
                m_listeModif->SetStringSelection(nom + _T(".sauve"));
            else
                m_Bouton_Appliquer->Enable(true);
        }
    }
    else
        wxMessageBox(_("Vous devez renseigner tous les champs"), _("Erreur !"));
}

/**
 * Évènement - Remet toutes les valeurs avec leur valeur par défaut
 * @see MAJ_Annuler
 */
void PrefCouleur::Couleur_Bouton_Annuler(wxCommandEvent &WXUNUSED(event))
{    MAJ_Annuler();}

/**
 * Met toutes les valeurs par défaut
 */
void PrefCouleur::MAJ_Annuler()
{
    m_listeModif->SetSelection(wxNOT_FOUND);
    m_boiteNom->Clear();
    for (int i=0; i<3; i++)
        m_sliderFond[i].SetValue(0);

    m_sliderBarre[0].SetValue(0); m_sliderBarre[1].SetValue(0); m_sliderBarre[2].SetValue(255);
    m_sliderPolice[0].SetValue(255); m_sliderPolice[1].SetValue(0); m_sliderPolice[2].SetValue(255);
    m_checkBoxHaut[0].SetValue(true); m_checkBoxHaut[1].SetValue(false); m_checkBoxHaut[2].SetValue(false);
    m_checkBoxMiSup[0].SetValue(false); m_checkBoxMiSup[1].SetValue(true); m_checkBoxMiSup[2].SetValue(false);
    m_checkBoxMiInf[0].SetValue(false); m_checkBoxMiInf[1].SetValue(false); m_checkBoxMiInf[2].SetValue(true);
    m_checkBoxBas[0].SetValue(false); m_checkBoxBas[1].SetValue(false); m_checkBoxBas[2].SetValue(false);
    m_doubleBarre->SetValue(false);

    MAJ_Barre();
    MAJ_Fond();
    MAJ_GraphSup();
    MAJ_GraphInf();
}

/**
 * Évènement - Désactive le bouton "Appliquer" si mode création
 */
void PrefCouleur::BoiteNouveauModifiee(wxCommandEvent &WXUNUSED(event))
{
    //Désactive le bouton appliquer si le texte est modifié dans les condition suivantes
    if (m_listeModif_Nouveau == NOUVEAU && m_Bouton_Appliquer->IsEnabled())
        m_Bouton_Appliquer->Enable(false);
}

/**
 * Évènement - Supprime le fichier sélectionné
 */
void PrefCouleur::Couleur_Bouton_Supprimer(wxCommandEvent &WXUNUSED(event))
{
    wxString chemin = Parametre::Get()->getRepertoireParametre(_T("Preference"), _T("Couleur"), m_listeModif->GetString(m_listeModif->GetCurrentSelection()));
    if (!wxRemoveFile(chemin))
        return;

    m_listeModif->Clear();
    CreerListe(m_listeModif);

    MAJ_Annuler();
}

/**
 * Évènement - Applique les paramètres au graphe et enregistre les données dans le fichier correspondant
 */
void PrefCouleur::Couleur_Bouton_Appliquer(wxCommandEvent &event)
{
    Couleur_Bouton_Enregistrer(event);

    if (!m_boiteNom->IsEmpty())
    {
        Couleur haut, miSup, miInf, bas;
        int colHaut[3], colMiSup[3], colMiInf[3], colBas[3];

        Couleur fond(m_sliderFond[0].GetValue(), m_sliderFond[1].GetValue(), m_sliderFond[2].GetValue());
        Couleur barre(m_sliderBarre[0].GetValue(), m_sliderBarre[1].GetValue(), m_sliderBarre[2].GetValue());
        Couleur police(m_sliderPolice[0].GetValue(), m_sliderPolice[1].GetValue(), m_sliderPolice[2].GetValue());

        for (int i=0; i<3; i++)
        {
            if (m_checkBoxHaut[i].GetValue())
                colHaut[i] = 255;
            else
                colHaut[i] = 0;
            if (m_checkBoxMiSup[i].GetValue())
                colMiSup[i] = 255;
            else
                colMiSup[i] = 0;
            if (m_checkBoxMiInf[i].GetValue())
                colMiInf[i] = 255;
            else
                colMiInf[i] = 0;
            if (m_checkBoxBas[i].GetValue())
                colBas[i] = 255;
            else
                colBas[i] = 0;
        }
        haut.SetRGB(colHaut[0], colHaut[1], colHaut[2]);
        miSup.SetRGB(colMiSup[0], colMiSup[1], colMiSup[2]);
        miInf.SetRGB(colMiInf[0], colMiInf[1], colMiInf[2]);
        bas.SetRGB(colBas[0], colBas[1], colBas[2]);
        //m_musiqueGraph->AffecteCouleurs(fond, barre, police, haut, miSup, m_doubleBarre->GetValue(), miInf, bas);
        Parametre::Get()->setCouleurs(fond, barre, police, haut, miSup, miInf, bas, m_doubleBarre->GetValue());
    }
}

/**
 * Renvoie l'instance des radioBox "Mon choix". Ceci permet une sélection extérieure du mode d'utilisation
 * @return l'instance
 */
wxRadioBox* PrefCouleur::GetRadioBox()
{    return m_choix;}



