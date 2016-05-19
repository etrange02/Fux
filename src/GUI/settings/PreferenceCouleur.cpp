/***************************************************************
 * Name:      PreferenceCouleur.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2009-09-25
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "../../../include/gui/settings/PreferenceCouleur.h"

/**
 * @class PreferenceCouleur
 * @brief Interface représentant différentes compositions graphiques
 * Les fichiers sont synchronisés en même temps que chaque modification. Chaque fichier est associé à un nœud dans l'arbre d'exploration
 */

 BEGIN_EVENT_TABLE(PreferenceCouleur, wxScrolledWindow)
    EVT_TREE_BEGIN_LABEL_EDIT(ID_APP_PREF_COULEUR_TREE, PreferenceCouleur::EvtTreeModifNomDebut)
    EVT_TREE_END_LABEL_EDIT(ID_APP_PREF_COULEUR_TREE, PreferenceCouleur::EvtTreeModifNomFin)
    EVT_TREE_SEL_CHANGED(ID_APP_PREF_COULEUR_TREE, PreferenceCouleur::EvtTreeVoirNoeud)// one clc
    EVT_TREE_ITEM_ACTIVATED(ID_APP_PREF_COULEUR_TREE, PreferenceCouleur::EvtTreeAppliquerNoeud)// dbl clc
    EVT_TREE_ITEM_RIGHT_CLICK(ID_APP_PREF_COULEUR_TREE, PreferenceCouleur::EvtTreeMenu)// menu
    EVT_MENU(ID_APP_PREF_COULEUR_MENU_RENOMMER, PreferenceCouleur::EvtMenuRenommer)
    EVT_MENU(ID_APP_PREF_COULEUR_MENU_SUPPRIMER, PreferenceCouleur::EvtMenuSupprimer)
    EVT_TEXT(ID_APP_PREF_COULEUR_TEXT_NOM, PreferenceCouleur::EvtTextNom)
    EVT_COMMAND_SCROLL(ID_APP_PREF_COULEUR_SLIDER_FOND, PreferenceCouleur::Couleur_MAJ_Fond)
    EVT_COMMAND_SCROLL(ID_APP_PREF_COULEUR_SLIDER_BARRE, PreferenceCouleur::Couleur_MAJ_Barre)
    EVT_CHECKBOX(ID_APP_PREF_COULEUR_BOX_HAUT, PreferenceCouleur::Couleur_MAJ_GraphSup)
    EVT_CHECKBOX(ID_APP_PREF_COULEUR_BOX_BAS, PreferenceCouleur::Couleur_MAJ_GraphInf)
    EVT_CHECKBOX(ID_APP_PREF_COULEUR_BOX_DOUBLE, PreferenceCouleur::Couleur_MAJ_Symetrie)
 END_EVENT_TABLE()

/**
 * Constructeur
 * @param Parent la fenêtre parente
 * @param Id l'identifiant de la fenêtre
 */
PreferenceCouleur::PreferenceCouleur(wxWindow* Parent, wxWindowID Id): GenericTreePanel(Parent, Id, ID_APP_PREF_COULEUR_TREE)
{
    PreferenceCouleur::Creer();
}

/**
 * Destructeur
 */
PreferenceCouleur::~PreferenceCouleur()
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
 * Complète la page en ajoutant des sizers et des box
 */
void PreferenceCouleur::Creer()
{
    m_textNomSet = new wxTextCtrl(this, ID_APP_PREF_COULEUR_TEXT_NOM);
    m_sizer2Preferences->Add(m_textNomSet, 0, wxALL|wxEXPAND, 5);

    m_bitmap = new wxBitmap[4];
    for (int i = 0; i < 4; i++)
        m_bitmap[i].Create(POCHETTE_COTE, POCHETTE_COTE);

    //// Background ////
    m_sizerFond = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Arrière plan"));
    m_sizer2Preferences->Add(m_sizerFond, 0, wxALL|wxSHAPED, 5);
    m_apercuFond = new wxStaticBitmap(this, ID_APP_PREF_COULEUR_IMG_FOND, m_bitmap[FOND]);
    m_sizerFond->Add(m_apercuFond, 0, wxALL | wxSHAPED, 5);

    wxSizer *sizerFlexGridFond = new wxFlexGridSizer(3, 2, 5, 5);
    m_sizerFond->Add(sizerFlexGridFond, 0, wxALL|wxEXPAND, 5);

    m_sliderFond = new wxSlider[3];
    m_sliderFond[ROUGE].Create(this, ID_APP_PREF_COULEUR_SLIDER_FOND, 0, 0, 255, wxDefaultPosition, wxSize(255, 30));
    m_sliderFond[VERT].Create(this, ID_APP_PREF_COULEUR_SLIDER_FOND, 0, 0, 255, wxDefaultPosition, wxSize(255, 30));
    m_sliderFond[BLEU].Create(this, ID_APP_PREF_COULEUR_SLIDER_FOND, 0, 0, 255, wxDefaultPosition, wxSize(255, 30));

    m_TextFond = new wxStaticText[3];
    m_TextFond[ROUGE].Create(this, wxID_ANY, _("R : 0"));
    m_TextFond[VERT].Create(this, wxID_ANY, _("V : 0"));
    m_TextFond[BLEU].Create(this, wxID_ANY, _("B : 0"));

    sizerFlexGridFond->Add(&m_sliderFond[ROUGE], 0, wxALL, 0);
    sizerFlexGridFond->Add(&m_TextFond[ROUGE], 0, wxALL, 0);
    sizerFlexGridFond->Add(&m_sliderFond[VERT], 0, wxALL, 0);
    sizerFlexGridFond->Add(&m_TextFond[VERT], 0, wxALL, 0);
    sizerFlexGridFond->Add(&m_sliderFond[BLEU], 0, wxALL, 0);
    sizerFlexGridFond->Add(&m_TextFond[BLEU], 0, wxALL, 0);

    //// Barre de progression et texte ////
    m_sizerBarrePolice = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Barre de progression et texte"));
	m_sizer2Preferences->Add(m_sizerBarrePolice, 0, wxALL | wxSHAPED, 5);

    wxSizer *sizerFlexGridBarre = new wxFlexGridSizer(3, 2, 5, 5);//Contient nom et cases non modifiables (droite); dispo en colonne
    m_sizerBarrePolice->Add(sizerFlexGridBarre, 0, wxALL | wxEXPAND, 5);

    m_sliderBarre = new wxSlider[3];
    m_sliderBarre[ROUGE].Create(this, ID_APP_PREF_COULEUR_SLIDER_BARRE, 0, 0, 255, wxDefaultPosition, wxSize(255, 30));
    m_sliderBarre[VERT].Create(this, ID_APP_PREF_COULEUR_SLIDER_BARRE, 0, 0, 255, wxDefaultPosition, wxSize(255, 30));
    m_sliderBarre[BLEU].Create(this, ID_APP_PREF_COULEUR_SLIDER_BARRE, 255, 0, 255, wxDefaultPosition, wxSize(255, 30));

    m_TextBarre = new wxStaticText[3];
    m_TextBarre[ROUGE].Create(this, wxID_ANY, _("R : 0"));
    m_TextBarre[VERT].Create(this, wxID_ANY, _("V : 0"));
    m_TextBarre[BLEU].Create(this, wxID_ANY, _("B : 255"));

    sizerFlexGridBarre->Add(&m_sliderBarre[ROUGE], 0, wxALL, 0);
    sizerFlexGridBarre->Add(&m_TextBarre[ROUGE], 0, wxALL|wxFIXED_MINSIZE, 0);
    sizerFlexGridBarre->Add(&m_sliderBarre[VERT], 0, wxALL, 0);
    sizerFlexGridBarre->Add(&m_TextBarre[VERT], 0, wxALL|wxFIXED_MINSIZE, 0);
    sizerFlexGridBarre->Add(&m_sliderBarre[BLEU], 0, wxALL, 0);
    sizerFlexGridBarre->Add(&m_TextBarre[BLEU], 0, wxALL|wxFIXED_MINSIZE, 0);


    wxMemoryDC tempBarre;
    tempBarre.SelectObject(m_bitmap[BARRE]);
    tempBarre.SetBrush(wxColour(0, 0, 255));
    tempBarre.DrawRectangle(0, 0, POCHETTE_COTE, POCHETTE_COTE);
    tempBarre.SetTextForeground(wxColour(255, 0, 255));
    int x, y;
    tempBarre.GetTextExtent(_("Musique"), &x, &y);
    tempBarre.DrawText(_("Musique"), (POCHETTE_COTE-x)/2, (POCHETTE_COTE-y)/2);
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


    //// Graph ////
    m_sizerGraph = new wxBoxSizer(wxHORIZONTAL);
    m_sizer2Preferences->Add(m_sizerGraph, 0, wxALL|wxEXPAND, 0);

        //// Partie supérieure du graphe ////
        m_sizerGraphHaut = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Partie supérieure du graph"));
        m_sizerGraph->Add(m_sizerGraphHaut, 1, wxALL | wxSHAPED, 5);

        wxSizer *sizerFlexGridHaut = new wxFlexGridSizer(4, 1, 5, 5);//Contient nom et cases non modifiables (droite); dispo en colonne
        m_sizerGraphHaut->Add(sizerFlexGridHaut, 0, wxALL | wxEXPAND, 5);

        wxStaticText* TextHaut = new wxStaticText(this, wxID_ANY, _("Haut de l'écran"));

        m_checkBoxHaut = new wxCheckBox[3];
        m_checkBoxHaut[ROUGE].Create(this, ID_APP_PREF_COULEUR_BOX_HAUT, _("Rouge"));
        m_checkBoxHaut[ROUGE].SetValue(true);
        m_checkBoxHaut[VERT].Create(this, ID_APP_PREF_COULEUR_BOX_HAUT, _("Vert"));
        m_checkBoxHaut[BLEU].Create(this, ID_APP_PREF_COULEUR_BOX_HAUT, _("Bleu"));

        sizerFlexGridHaut->Add(TextHaut, 0, wxALL, 0);
        sizerFlexGridHaut->Add(&m_checkBoxHaut[ROUGE], 0, wxALL, 0);
        sizerFlexGridHaut->Add(&m_checkBoxHaut[VERT], 0, wxALL, 0);
        sizerFlexGridHaut->Add(&m_checkBoxHaut[BLEU], 0, wxALL, 0);


        wxMemoryDC tempHaut;
        tempHaut.SelectObject(m_bitmap[HAUT_SUP]);
        tempHaut.GradientFillLinear(wxRect(0, 0, POCHETTE_COTE, POCHETTE_COTE), wxColour(0, 255, 0), wxColour(255, 0, 0), wxNORTH);
        m_apercuGraphHaut = new wxStaticBitmap(this, ID_APP_PREF_COULEUR_IMG_GRAPH_HAUT, m_bitmap[HAUT_SUP]);
        m_sizerGraphHaut->Add(m_apercuGraphHaut, 0, wxALL | wxSHAPED, 5);

        wxSizer *sizerFlexGraphSup = new wxFlexGridSizer(4, 1, 5, 5);//Contient nom et cases non modifiables (droite); dispo en colonne
        m_sizerGraphHaut->Add(sizerFlexGraphSup, 0, wxALL | wxEXPAND, 5);

        wxStaticText* TextSup = new wxStaticText(this, wxID_ANY, _("Moitié supérieure"));
        m_checkBoxMiSup = new wxCheckBox[3];
        m_checkBoxMiSup[ROUGE].Create(this, ID_APP_PREF_COULEUR_BOX_HAUT, _("Rouge"));
        m_checkBoxMiSup[VERT].Create(this, ID_APP_PREF_COULEUR_BOX_HAUT, _("Vert"));
        m_checkBoxMiSup[VERT].SetValue(true);
        m_checkBoxMiSup[BLEU].Create(this, ID_APP_PREF_COULEUR_BOX_HAUT, _("Bleu"));

        sizerFlexGraphSup->Add(TextSup, 0, wxALL, 0);
        sizerFlexGraphSup->Add(&m_checkBoxMiSup[ROUGE], 0, wxALL, 0);
        sizerFlexGraphSup->Add(&m_checkBoxMiSup[VERT], 0, wxALL, 0);
        sizerFlexGraphSup->Add(&m_checkBoxMiSup[BLEU], 0, wxALL, 0);

        //// Symétrie ////
        wxSizer *sizerMilieu = new wxBoxSizer(wxVERTICAL);
        m_sizerGraph->Add(sizerMilieu, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0);
        m_doubleBarre = new wxCheckBox(this, ID_APP_PREF_COULEUR_BOX_DOUBLE, _("Symétrie horizontale"));
        sizerMilieu->Add(m_doubleBarre, 1, wxALL|wxALIGN_CENTER_HORIZONTAL, 0);

        //// Partie inférieure du graphe ////
        m_sizerGraphBas = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Partie inférieure du graph"));
        m_sizerGraph->Add(m_sizerGraphBas, 1, wxALL | wxSHAPED, 5);

        wxSizer *sizerFlexGraphInf = new wxFlexGridSizer(4, 1, 5, 5);//Contient nom et cases non modifiables (droite); dispo en colonne
        m_sizerGraphBas->Add(sizerFlexGraphInf, 0, wxALL | wxEXPAND, 5);

        wxStaticText* TextInf = new wxStaticText(this, wxID_ANY, _("Moitié inférieure"));

        m_checkBoxMiInf = new wxCheckBox[3];
        m_checkBoxMiInf[ROUGE].Create(this, ID_APP_PREF_COULEUR_BOX_BAS, _("Rouge"));
        m_checkBoxMiInf[VERT].Create(this, ID_APP_PREF_COULEUR_BOX_BAS, _("Vert"));
        m_checkBoxMiInf[BLEU].Create(this, ID_APP_PREF_COULEUR_BOX_BAS, _("Bleu"));
        m_checkBoxMiInf[BLEU].SetValue(true);

        sizerFlexGraphInf->Add(TextInf, 0, wxALL, 0);
        sizerFlexGraphInf->Add(&m_checkBoxMiInf[ROUGE], 0, wxALL, 0);
        sizerFlexGraphInf->Add(&m_checkBoxMiInf[VERT], 0, wxALL, 0);
        sizerFlexGraphInf->Add(&m_checkBoxMiInf[BLEU], 0, wxALL, 0);


        wxMemoryDC tempBas;
        tempBas.SelectObject(m_bitmap[BAS_INF]);
        tempBas.GradientFillLinear(wxRect(0, 0, POCHETTE_COTE, POCHETTE_COTE), wxColour(0, 0, 255), wxColour(0, 0, 0), wxSOUTH);
        m_apercuGraphBas = new wxStaticBitmap(this, ID_APP_PREF_COULEUR_IMG_GRAPH_BAS, m_bitmap[BAS_INF]);
        m_sizerGraphBas->Add(m_apercuGraphBas, 0, wxALL | wxSHAPED, 5);

        wxSizer *sizerFlexGridBas = new wxFlexGridSizer(4, 1, 5, 5);//Contient nom et cases non modifiables (droite); dispo en colonne
        m_sizerGraphBas->Add(sizerFlexGridBas, 0, wxALL | wxEXPAND, 5);

        wxStaticText* TextBas = new wxStaticText(this, wxID_ANY, _("Bas de l'écran"));
        m_checkBoxBas = new wxCheckBox[3];
        m_checkBoxBas[ROUGE].Create(this, ID_APP_PREF_COULEUR_BOX_BAS, _("Rouge"));
        m_checkBoxBas[VERT].Create(this, ID_APP_PREF_COULEUR_BOX_BAS, _("Vert"));
        m_checkBoxBas[BLEU].Create(this, ID_APP_PREF_COULEUR_BOX_BAS, _("Bleu"));

        sizerFlexGridBas->Add(TextBas, 0, wxALL, 0);
        sizerFlexGridBas->Add(&m_checkBoxBas[ROUGE], 0, wxALL, 0);
        sizerFlexGridBas->Add(&m_checkBoxBas[VERT], 0, wxALL, 0);
        sizerFlexGridBas->Add(&m_checkBoxBas[BLEU], 0, wxALL, 0);

    //// Affectation des valeurs ////
    for (int i=0; i<3; i++)
    {
        m_sliderBarre[i].SetBackgroundColour(wxColour(255, 255, 255));//SetTransparent(0);//
        m_sliderPolice[i].SetBackgroundColour(wxColour(255, 255, 255));//SetTransparent(0);//
    }

    RemplirTree();
    m_menu = new wxMenu;
    m_menu->Append(ID_APP_PREF_COULEUR_MENU_RENOMMER, _("Renommer"));
    m_menu->Append(ID_APP_PREF_COULEUR_MENU_SUPPRIMER, _("Supprimer"));
}

/**
 * Rempli l'arbre avec les éléments du dossier. Les éléments inexistants sont supprimés
 */
void PreferenceCouleur::RemplirTree()
{
    if (wxDir::Exists(Parametre::Get()->getCheminCouleur()))
    {
        wxString copie;
        wxDir Repertoire(Parametre::Get()->getCheminCouleur());
        bool continuer = Repertoire.GetFirst(&copie, _T("*.sauve"), wxDIR_FILES);

        while (continuer)
        {
            m_treeFiles->AppendItem(m_nodeExistant, copie);
            continuer = Repertoire.GetNext(&copie);
        }
    }
    m_treeFiles->ExpandAll();
}

/**
 * Rempli une liste avec les éléments du dossier
 * @param liste une liste à remplir
 */
void PreferenceCouleur::MajListe(wxChoice *liste)
{
    if (wxDir::Exists(Parametre::Get()->getCheminCouleur()) && liste != NULL)
    {
        wxString copie;
        wxDir Repertoire(Parametre::Get()->getCheminCouleur());
        bool continuer = Repertoire.GetFirst(&copie, _T("*.sauve"), wxDIR_FILES);

        while (continuer)
        {
            liste->Append(copie);
            continuer = Repertoire.GetNext(&copie);
        }
    }
}

/**
 * Affiche le menu sur un élément de l'arbre
 * @param event un évènement
 */
void PreferenceCouleur::EvtTreeMenu(wxTreeEvent &event)
{
    if (m_treeFiles->GetItemParent(event.GetItem()) == m_nodeExistant)
        PopupMenu(m_menu);
}

/**
 * Autorise ou non la modification d'un nœud
 * @param event un évènement
 */
void PreferenceCouleur::EvtTreeModifNomDebut(wxTreeEvent &event)
{
    if (m_treeFiles->GetItemParent(event.GetItem()) == m_nodeExistant)
        m_nomAvantModif = event.GetLabel();
    else
    {
        m_treeFiles->EndEditLabel(event.GetItem(), true);
        m_treeFiles->SetFocus();
        m_treeFiles->SelectItem(event.GetItem());
        m_nomAvantModif.Clear();
    }
}

/**
 * Applique les modifications dans le fichier correspondant au nœud sélectionné
 * @param event un évènement
 */
void PreferenceCouleur::EvtTreeModifNomFin(wxTreeEvent &event)
{
    if (!event.IsEditCancelled())
    {
        //renommer le fichier - event.GetLabel();
        if (wxFileExists(Parametre::Get()->getCheminCouleur(event.GetLabel())))
        {
            wxLogMessage(_T("Fichier Existant !"));
            m_treeFiles->EndEditLabel(event.GetItem(), true);
            m_treeFiles->SetFocus();
        }
        else
        {
            if (wxFileExists(Parametre::Get()->getCheminCouleur(m_treeFiles->GetItemText(event.GetItem()))))
            {
                ModifierFiltre(event.GetLabel().BeforeLast('.'), m_treeFiles->GetItemText(event.GetItem()));
                wxRemoveFile(Parametre::Get()->getCheminCouleur(m_treeFiles->GetItemText(event.GetItem())));
                m_textNomSet->ChangeValue(event.GetLabel().BeforeLast('.'));
                m_treeFiles->SortChildren(m_nodeExistant);
                CallListeners();
            }
        }
    }
    m_nomAvantModif.Clear();
}

/**
 * Affiche le contenu d'un nœud dans la page
 * @param event un évènement
 */
void PreferenceCouleur::EvtTreeVoirNoeud(wxTreeEvent &event)
{
    wxTextFile fichier();
    bool loaded = false;
    if (wxFileExists(Parametre::Get()->getCheminCouleur(m_treeFiles->GetItemText(event.GetItem()))))
    {
        if (OuvrirFiltre(m_treeFiles->GetItemText(event.GetItem()), true))
        {
            loaded = true;
        }
    }
    if (!loaded)
    {
        if (event.GetItem() == m_nodeExistant)
            ValeursDefaut();
        else if (event.GetItem() == m_nodeNouveau)
            m_textNomSet->Clear();
    }
}

/**
 * Applique les paramètres contenus dans le nœud sélectionné
 * @param event un évènement
 */
void PreferenceCouleur::EvtTreeAppliquerNoeud(wxTreeEvent &event)
{
    if (!m_textNomSet->IsEmpty())
    {
        AppliquerFiltreSelectionne();
    }
    else if (event.GetItem() == m_nodeNouveau)
    {
        wxTextEntryDialog *dlg = new wxTextEntryDialog(this, _("Choisissez un nom"), _("Création de filtre couleur"));

        if (dlg->ShowModal() == wxID_OK)
        {
            if (wxFileExists(Parametre::Get()->getCheminCouleur(dlg->GetValue() + _T(".sauve"))))
            {
                wxLogMessage(_("Fichier Existant !"));
            }
            else
            {
                if (ModifierFiltre(dlg->GetValue()))
                {
                    wxTreeItemId item = m_treeFiles->AppendItem(m_nodeExistant, dlg->GetValue() + _T(".sauve"));
                    m_treeFiles->SelectItem(item);
                    m_treeFiles->SortChildren(m_nodeExistant);
                    CallListeners();
                }
                else
                    wxMessageBox(_("Erreur dans le nom.\nVérifiez que vous utilisez des caractères autorisés."), _("Erreur"));
            }
        }
    }
}

/**
 * Efface le nœud (et le fichier correspondant)
 */
void PreferenceCouleur::EvtMenuSupprimer(wxCommandEvent &WXUNUSED(event))
{
    if (!wxRemoveFile(Parametre::Get()->getCheminCouleur(m_treeFiles->GetItemText(m_treeFiles->GetSelection()))))
        return;

    m_textNomSet->Clear();
    ValeursDefaut();
    m_treeFiles->Delete(m_treeFiles->GetSelection());
    CallListeners();
}

/**
 * Renommage d'un nœud (et de son fichier correspondant)
 */
void PreferenceCouleur::EvtMenuRenommer(wxCommandEvent &WXUNUSED(event))
{
    m_treeFiles->EditLabel(m_treeFiles->GetSelection());
}

/**
 * Renommage du nom du fichier. Le nœud correspondant est modifié
 */
void PreferenceCouleur::EvtTextNom(wxCommandEvent &WXUNUSED(event))
{
    if (m_treeFiles->GetItemParent(m_treeFiles->GetSelection()) == m_nodeExistant)
    {
        ModifierFiltre(m_textNomSet->GetValue(), m_treeFiles->GetItemText(m_treeFiles->GetSelection()));
        m_treeFiles->SetItemText(m_treeFiles->GetSelection(), m_textNomSet->GetValue() + _T(".sauve"));
        m_treeFiles->SortChildren(m_nodeExistant);
        CallListeners();
    }
    else if (!m_textNomSet->IsEmpty())
    {
        ModifierFiltre(m_textNomSet->GetValue());
        wxTreeItemId item = m_treeFiles->AppendItem(m_nodeExistant, m_textNomSet->GetValue() + _T(".sauve"));
        m_treeFiles->SelectItem(item);
        m_treeFiles->SortChildren(m_nodeExistant);
        CallListeners();
    }
}

/**
 * Evènement - Appelé lors de l'utilisation d'un slider
 * @see MAJ_Fond
 */
void PreferenceCouleur::Couleur_MAJ_Fond(wxScrollEvent &WXUNUSED(event))
{
    MAJ_Fond();
    ModifierFiltre(m_textNomSet->GetValue());
}

/**
 * Modifie les informations et la couleur du carré de visualisation "Arrière plan"
 */
void PreferenceCouleur::MAJ_Fond()
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
    AppliquerFiltreSelectionne();
}

/**
 * Evènement - Appelé lors de l'utilisation d'un slider
 * @see MAJ_Barre
 */
void PreferenceCouleur::Couleur_MAJ_Barre(wxScrollEvent &WXUNUSED(event))
{
    MAJ_Barre();
    ModifierFiltre(m_textNomSet->GetValue());
}

/**
 * Modifie les informations et la couleur du carré de visualisation "Barre de progression et texte"
 */
void PreferenceCouleur::MAJ_Barre()
{
    wxMemoryDC tempBarre;
    tempBarre.SelectObject(m_bitmap[BARRE]);
    tempBarre.SetBrush(wxColour(m_sliderBarre[ROUGE].GetValue(), m_sliderBarre[VERT].GetValue(), m_sliderBarre[BLEU].GetValue()));
    tempBarre.DrawRectangle(0, 0, POCHETTE_COTE, POCHETTE_COTE);
    tempBarre.SetTextForeground(wxColour(m_sliderPolice[ROUGE].GetValue(), m_sliderPolice[VERT].GetValue(), m_sliderPolice[BLEU].GetValue()));
    int x, y;
    tempBarre.GetTextExtent(_("Musique"), &x, &y);
    tempBarre.DrawText(_("Musique"), (POCHETTE_COTE-x)/2, (POCHETTE_COTE-y)/2);
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

    AppliquerFiltreSelectionne();
}

/**
 * Evènement - Appelé lors de la modification d'une checkbox
 * @see MAJ_GraphSup
 */
void PreferenceCouleur::Couleur_MAJ_GraphSup(wxCommandEvent &WXUNUSED(event))
{
    MAJ_GraphSup();
    ModifierFiltre(m_textNomSet->GetValue());
}

/**
 * Modifie la couleur du carré de visualisation "Partie supérieure du graphe"
 */
void PreferenceCouleur::MAJ_GraphSup()
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

    AppliquerFiltreSelectionne();
}

/**
 * Evènement - Appelé lors de la modification d'une checkbox
 * @see MAJ_GraphInf
 */
void PreferenceCouleur::Couleur_MAJ_GraphInf(wxCommandEvent &WXUNUSED(event))
{
    MAJ_GraphInf();
    ModifierFiltre(m_textNomSet->GetValue());
}

/**
 * Modifie la couleur du carré de visualisation "Partie inférieure du graphe"
 */
void PreferenceCouleur::MAJ_GraphInf()
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

    AppliquerFiltreSelectionne();
}

/**
 * Evènement - Appelé lors de la modification d'une checkbox
 * @see MAJ_Symetrie
 */
void PreferenceCouleur::Couleur_MAJ_Symetrie(wxCommandEvent &WXUNUSED(event))
{
    MAJ_Symetrie();
    ModifierFiltre(m_textNomSet->GetValue());
}

/**
 * Modifie l'accès au bloc sur la partie inférieure du graphe
 */
void PreferenceCouleur::MAJ_Symetrie()
{
    if (m_doubleBarre->IsChecked())
    {
        for (int i = 0; i < 3; i++)
        {
            m_checkBoxBas[i].Enable(true);
            m_checkBoxMiInf[i].Enable(true);
        }
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            m_checkBoxBas[i].Enable(false);
            m_checkBoxMiInf[i].Enable(false);
        }
    }

    AppliquerFiltreSelectionne();
}

/**
 * Met toutes les valeurs par défaut
 */
void PreferenceCouleur::ValeursDefaut()
{
    m_textNomSet->Clear();
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
    MAJ_Symetrie();
}

/**
 * Modifie un filtre existant
 * @param nom le nom du filtre
 * @param fond la couleur du fond
 * @param barre la couleur de la barre de progression
 * @param police la couleur du texte
 * @param haut la couleur de la partie supérieure du graphe
 * @param miSup la couleur de la moitié supérieure du graphe
 * @param symetrie symétrie du graphe
 * @param miInf la couleur de la moitié inférieure du graphe
 * @param bas la couleur de la partie inférieure du graphe
 * @param oldNom l'ancien nom du filtre
 * @return vrai si réussite
 */
bool PreferenceCouleur::ModifierFiltre(wxString nom, Couleur fond, Couleur barre, Couleur police, Couleur haut, Couleur miSup, bool symetrie, Couleur miInf, Couleur bas, wxString oldNom)
{
    if (nom.IsEmpty())
        return false;
    /*if (oldNom.IsEmpty())
    {
        wxTextFile fichier(Parametre::Get()->getCheminCouleur(nom + _T(".sauve")));
        if (fichier.Create() || fichier.Open())
        {
            wxString sym;
            sym << _T("Double= ") << (symetrie?_T("t"):_T("f"));
            fichier.Clear();
            fichier.AddLine(_T("#EXTSAUVE_C1"));
            fichier.AddLine(nom);
            fichier.AddLine(fond.ToString(_T("Fond=")));
            fichier.AddLine(barre.ToString(_T("Barre=")));
            fichier.AddLine(police.ToString(_T("Police=")));
            fichier.AddLine(haut.ToBoolString(_T("Haut=")));
            fichier.AddLine(miSup.ToBoolString(_T("MiSup=")));
            fichier.AddLine(sym);//symetrie Double
            fichier.AddLine(miInf.ToBoolString(_T("MiInf=")));
            fichier.AddLine(bas.ToBoolString(_T("Bas=")));
            fichier.Write();
            fichier.Close();
            return true;
        }
    }
    else
    {
        wxTextFile fichier(Parametre::Get()->getCheminCouleur(nom + _T(".sauve")));
        if (fichier.Create()/ * || fichier.Open()* /)
        {
            wxString sym;
            sym << _T("Double= ") << (symetrie?_T("t"):_T("f"));
            fichier.AddLine(_T("#EXTSAUVE_C1"));
            fichier.AddLine(nom);
            fichier.AddLine(fond.ToString(_T("Fond=")));
            fichier.AddLine(barre.ToString(_T("Barre=")));
            fichier.AddLine(police.ToString(_T("Police=")));
            fichier.AddLine(haut.ToBoolString(_T("Haut=")));
            fichier.AddLine(miSup.ToBoolString(_T("MiSup=")));
            fichier.AddLine(sym);//symetrie Double
            fichier.AddLine(miInf.ToBoolString(_T("MiInf=")));
            fichier.AddLine(bas.ToBoolString(_T("Bas=")));
            fichier.Write();
            fichier.Close();

            return wxRemoveFile(Parametre::Get()->getCheminCouleur(oldNom));
        }
    }
    return false;*/

    if (!oldNom.IsEmpty())
        wxRemoveFile(Parametre::Get()->getCheminCouleur(oldNom));
    wxXmlNode *rootNode = new wxXmlNode(wxXML_ELEMENT_NODE, _T("colour"));
    wxXmlNode *childNode = NULL;

    childNode = new wxXmlNode(rootNode, wxXML_ELEMENT_NODE, _T("name"));
    new wxXmlNode(childNode, wxXML_TEXT_NODE, _T(""), nom);
    fond.ToXMLNode(rootNode, _T("fond"));
    barre.ToXMLNode(rootNode, _T("barre"));
    police.ToXMLNode(rootNode, _T("police"));
    haut.ToXMLNode(rootNode, _T("haut"));
    miSup.ToXMLNode(rootNode, _T("mi_sup"));
    miInf.ToXMLNode(rootNode, _T("mi_inf"));
    bas.ToXMLNode(rootNode, _T("bas"));
    if (symetrie)
        /*childNode = */new wxXmlNode(rootNode, wxXML_ELEMENT_NODE, _T("symetrie"));

    wxXmlDocument doc;
    doc.SetRoot(rootNode);
    return doc.Save(Parametre::Get()->getCheminCouleur(nom + _T(".sauve")));
}

/**
 * Modifie un filtre existant, version simplifiée de l'autre version
 * @param nom le nom du filtre
 * @param oldNom l'ancien nom du filtre
 * @return vrai si réussite
 */
bool PreferenceCouleur::ModifierFiltre(wxString nom, wxString oldNom)
{
    return ModifierFiltre(nom,
        Couleur(m_sliderFond[ROUGE].GetValue(), m_sliderFond[VERT].GetValue(), m_sliderFond[BLEU].GetValue()),
        Couleur(m_sliderBarre[ROUGE].GetValue(), m_sliderBarre[VERT].GetValue(), m_sliderBarre[BLEU].GetValue()),
        Couleur(m_sliderPolice[ROUGE].GetValue(), m_sliderPolice[VERT].GetValue(), m_sliderPolice[BLEU].GetValue()),
        Couleur(m_checkBoxHaut[ROUGE].GetValue(), m_checkBoxHaut[VERT].GetValue(), m_checkBoxHaut[BLEU].GetValue(), true),
        Couleur(m_checkBoxMiSup[ROUGE].GetValue(), m_checkBoxMiSup[VERT].GetValue(), m_checkBoxMiSup[BLEU].GetValue(), true),
        m_doubleBarre->GetValue(),
        Couleur(m_checkBoxMiInf[ROUGE].GetValue(), m_checkBoxMiInf[VERT].GetValue(), m_checkBoxMiInf[BLEU].GetValue(), true),
        Couleur(m_checkBoxBas[ROUGE].GetValue(), m_checkBoxBas[VERT].GetValue(), m_checkBoxBas[BLEU].GetValue(), true),
        oldNom);
}

/**
 * Lit le contenu d'un fichier(filtre) et modifie le graphe ou la fenêtre de visualisation
 * @param filtre le nom du filtre à lire
 * @param evenement si vrai, les paramètres sont juste visualisés, si faux les paramètres sont appliqués au graphe
 * @return vrai si réussite
 */
bool PreferenceCouleur::OuvrirFiltre(wxString filtre, bool evenement)
{
    wxTextFile fichier(Parametre::Get()->getCheminCouleur(filtre));

    if (!(fichier.Exists() && fichier.Open()))
        return false;

    wxString nom;
    Couleur colFond, colBarre, colPolice, colHaut, colMiSup, colMiInf, colBas;
    bool symetrie = false;

    if (fichier.GetLine(0).IsSameAs(_T("#EXTSAUVE_C1")))
    {
        nom = fichier.GetLine(1);
        colFond.FromString(fichier.GetLine(2), false);
        colBarre.FromString(fichier.GetLine(3), false);
        colPolice.FromString(fichier.GetLine(4), false);
        colHaut.FromString(fichier.GetLine(5), true);
        colMiSup.FromString(fichier.GetLine(6), true);
        symetrie = fichier.GetLine(7).AfterFirst(' ').BeforeFirst(' ').IsSameAs(_T("t"));
        colMiInf.FromString(fichier.GetLine(8), true);
        colBas.FromString(fichier.GetLine(9), true);
        fichier.Close();
    }
    else
    {
        fichier.Close();
        wxXmlDocument doc;
        if (!doc.Load(Parametre::Get()->getCheminCouleur(filtre)))
            return false;
        if (doc.GetRoot()->GetName() != _T("colour"))
            return false;
        wxXmlNode *child = doc.GetRoot()->GetChildren();
        while (child)
        {
            if (child->GetName() == _T("name"))
            {
                nom = child->GetNodeContent();
            }
            else if (child->GetName() == _T("fond"))
            {
                colFond.FromXMLNode(child);
            }
            else if (child->GetName() == _T("barre"))
            {
                colBarre.FromXMLNode(child);
            }
            else if (child->GetName() == _T("police"))
            {
                colPolice.FromXMLNode(child);
            }
            else if (child->GetName() == _T("haut"))
            {
                colHaut.FromXMLNode(child);
            }
            else if (child->GetName() == _T("mi_sup"))
            {
                colMiSup.FromXMLNode(child);
            }
            else if (child->GetName() == _T("mi_inf"))
            {
                colMiInf.FromXMLNode(child);
            }
            else if (child->GetName() == _T("bas"))
            {
                colBas.FromXMLNode(child);
            }
            else if (child->GetName() == _T("symetrie"))
            {
                symetrie = true;
            }
            child = child->GetNext();
        }
    }

    if (evenement)
    {
        m_textNomSet->ChangeValue(nom);
        m_sliderFond[ROUGE].SetValue(colFond.GetRed());
        m_sliderFond[VERT].SetValue(colFond.GetGreen());
        m_sliderFond[BLEU].SetValue(colFond.GetBlue());
        m_sliderBarre[ROUGE].SetValue(colBarre.GetRed());
        m_sliderBarre[VERT].SetValue(colBarre.GetGreen());
        m_sliderBarre[BLEU].SetValue(colBarre.GetBlue());
        m_sliderPolice[ROUGE].SetValue(colPolice.GetRed());
        m_sliderPolice[VERT].SetValue(colPolice.GetGreen());
        m_sliderPolice[BLEU].SetValue(colPolice.GetBlue());

        m_checkBoxHaut[ROUGE].SetValue(colHaut.GetBoolRed());
        m_checkBoxHaut[VERT].SetValue(colHaut.GetBoolGreen());
        m_checkBoxHaut[BLEU].SetValue(colHaut.GetBoolBlue());
        m_checkBoxMiSup[ROUGE].SetValue(colMiSup.GetBoolRed());
        m_checkBoxMiSup[VERT].SetValue(colMiSup.GetBoolGreen());
        m_checkBoxMiSup[BLEU].SetValue(colMiSup.GetBoolBlue());
        m_checkBoxMiInf[ROUGE].SetValue(colMiInf.GetBoolRed());
        m_checkBoxMiInf[VERT].SetValue(colMiInf.GetBoolGreen());
        m_checkBoxMiInf[BLEU].SetValue(colMiInf.GetBoolBlue());
        m_checkBoxBas[ROUGE].SetValue(colBas.GetBoolRed());
        m_checkBoxBas[VERT].SetValue(colBas.GetBoolGreen());
        m_checkBoxBas[BLEU].SetValue(colBas.GetBoolBlue());

        m_doubleBarre->SetValue(symetrie);

        MAJ_Fond();
        MAJ_Barre();
        MAJ_GraphSup();
        MAJ_GraphInf();
        MAJ_Symetrie();
    }
    else
    {
        Parametre::Get()->setCouleurs(colFond, colBarre, colPolice, colHaut, colMiSup, colMiInf, colBas, symetrie);
    }
    return true;
}

/**
 * Applique les valeurs du filtre audio sélectionné
 */
void PreferenceCouleur::AppliquerFiltreSelectionne()
{
    /*if (m_textNomSet->IsEmpty())
        return;*/
    Parametre::Get()->setCouleurs(
        Couleur(m_sliderFond[ROUGE].GetValue(), m_sliderFond[VERT].GetValue(), m_sliderFond[BLEU].GetValue()),
        Couleur(m_sliderBarre[ROUGE].GetValue(), m_sliderBarre[VERT].GetValue(), m_sliderBarre[BLEU].GetValue()),
        Couleur(m_sliderPolice[ROUGE].GetValue(), m_sliderPolice[VERT].GetValue(), m_sliderPolice[BLEU].GetValue()),
        Couleur(m_checkBoxHaut[ROUGE].GetValue(), m_checkBoxHaut[VERT].GetValue(), m_checkBoxHaut[BLEU].GetValue(), true),
        Couleur(m_checkBoxMiSup[ROUGE].GetValue(), m_checkBoxMiSup[VERT].GetValue(), m_checkBoxMiSup[BLEU].GetValue(), true),
        Couleur(m_checkBoxMiInf[ROUGE].GetValue(), m_checkBoxMiInf[VERT].GetValue(), m_checkBoxMiInf[BLEU].GetValue(), true),
        Couleur(m_checkBoxBas[ROUGE].GetValue(), m_checkBoxBas[VERT].GetValue(), m_checkBoxBas[BLEU].GetValue(), true),
        m_doubleBarre->GetValue()
        );
}

