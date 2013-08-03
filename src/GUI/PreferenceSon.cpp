/***************************************************************
 * Name:      PreferenceSon.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2009-12-14
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../../include/GUI/PreferenceSon.h"

/**
 * @class PreferenceSon
 * @brief Interface représentant différents volumes sonores - Passer les fichiers au format XML
 * Les fichiers sont synchronisés en même temps que chaque modification. Chaque fichier est associé à un nœud dans l'arbre d'exploration
 */

BEGIN_EVENT_TABLE(PreferenceSon, wxScrolledWindow)
    EVT_TREE_BEGIN_LABEL_EDIT(ID_APP_PREF_SON_TREE, PreferenceSon::EvtTreeModifNomDebut)
    EVT_TREE_END_LABEL_EDIT(ID_APP_PREF_SON_TREE, PreferenceSon::EvtTreeModifNomFin)
    EVT_TREE_SEL_CHANGED(ID_APP_PREF_SON_TREE, PreferenceSon::EvtTreeVoirNoeud)// one clc
    EVT_TREE_ITEM_ACTIVATED(ID_APP_PREF_SON_TREE, PreferenceSon::EvtTreeAppliquerNoeud)// dbl clc
    EVT_TREE_ITEM_RIGHT_CLICK(ID_APP_PREF_SON_TREE, PreferenceSon::EvtTreeMenu)// menu
    EVT_MENU(ID_APP_PREF_SON_MENU_RENOMMER, PreferenceSon::EvtMenuRenommer)
    EVT_MENU(ID_APP_PREF_SON_MENU_SUPPRIMER, PreferenceSon::EvtMenuSupprimer)
    EVT_TEXT(ID_APP_PREF_SON_TEXT_NOM, PreferenceSon::EvtTextNom)
    EVT_SPINCTRL(ID_APP_PREF_SON_TEXT_VOLUME, PreferenceSon::EvtSpinVolume)
    EVT_SPINCTRL(ID_APP_PREF_SON_TEXT_VOLUME_PC, PreferenceSon::EvtSpinVolumePC)
END_EVENT_TABLE()

/**
 * Constructeur
 * @param Parent la fenêtre parente
 * @param Id l'identifiant de la fenêtre
 */
PreferenceSon::PreferenceSon(wxWindow *Parent, wxWindowID Id): GenericTreePanel(Parent, Id, ID_APP_PREF_SON_TREE)
{
    PreferenceSon::Creer();
}

/**
 * Destructeur
 */
PreferenceSon::~PreferenceSon()
{}

/**
 * Complète la page en ajoutant des sizers et des box
 */
void PreferenceSon::Creer()
{
    m_sizerNewSet = new wxStaticBoxSizer(wxVERTICAL, this, _("Nouveau"));
    m_sizerCurrentSet = new wxStaticBoxSizer(wxVERTICAL, this, _("Valeurs actuelles"));
    m_sizer2Preferences->Add(m_sizerNewSet, 0, wxALL|wxEXPAND, 5);
    m_sizer2Preferences->Add(m_sizerCurrentSet, 0, wxALL | wxEXPAND | wxALIGN_RIGHT, 5);

    m_gridSizerNew = new wxFlexGridSizer(3, 2, 5, 5);//Suite des cases contenant des valeurs modifiables
    m_gridSizerCurr = new wxFlexGridSizer(2, 2, 5, 5);
    m_sizerNewSet->Add(m_gridSizerNew, 0, wxALL | wxEXPAND, 5);
    m_sizerCurrentSet->Add(m_gridSizerCurr, 0, wxALL | wxEXPAND, 5);

    //// Modification d'un jeu ////
    m_textNomSet = new wxTextCtrl(this, ID_APP_PREF_SON_TEXT_NOM, _T(""));
    m_spinVolume = new wxSpinCtrl(this, ID_APP_PREF_SON_TEXT_VOLUME, _T(""));
    m_spinVolumePC = new wxSpinCtrl(this, ID_APP_PREF_SON_TEXT_VOLUME_PC, _T(""));
    m_spinVolumePC->SetRange(-1, 100);
    m_gridSizerNew->Add(new wxStaticText(this, wxID_ANY, _("Nom")), 0, wxALL, 0);
    m_gridSizerNew->Add(m_textNomSet, 0, wxALL|wxEXPAND, 0);
    m_gridSizerNew->Add(new wxStaticText(this, wxID_ANY, _("Volume")), 0, wxALL, 0);
    m_gridSizerNew->Add(m_spinVolume, 0, wxALL|wxEXPAND, 0);
    m_gridSizerNew->Add(new wxStaticText(this, wxID_ANY, _("Volume PC")), 0, wxALL, 0);
    m_gridSizerNew->Add(m_spinVolumePC, 0, wxALL|wxEXPAND, 0);

    //// Valeurs actuelles ////
    m_textVolumeCurr = new wxTextCtrl(this, wxID_ANY, _T("100"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    m_textVolumePCCurr = new wxTextCtrl(this, wxID_ANY, _T("-1"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    m_gridSizerCurr->Add(new wxStaticText(this, wxID_ANY, _("Volume")), 0, wxALL, 0);
    m_gridSizerCurr->Add(m_textVolumeCurr, 0, wxALL|wxEXPAND, 0);
    m_gridSizerCurr->Add(new wxStaticText(this, wxID_ANY, _("Volume PC")), 0, wxALL, 0);
    m_gridSizerCurr->Add(m_textVolumePCCurr, 0, wxALL|wxEXPAND, 0);

    RemplirTree();
    m_menu = new wxMenu;
    m_menu->Append(ID_APP_PREF_SON_MENU_RENOMMER, _("Renommer"));
    m_menu->Append(ID_APP_PREF_SON_MENU_SUPPRIMER, _("Supprimer"));
}

/**
 * Rempli l'arbre avec les éléments du dossier. Les éléments inexistants sont supprimés
 */
void PreferenceSon::RemplirTree()
{
    if (wxDir::Exists(Parametre::Get()->getCheminSon()))
    {
        wxString copie;
        wxDir Repertoire(Parametre::Get()->getCheminSon());
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
void PreferenceSon::MajListe(wxChoice *liste)
{
    if (wxDir::Exists(Parametre::Get()->getCheminSon()) && liste != NULL)
    {
        wxString copie;
        wxDir Repertoire(Parametre::Get()->getCheminSon());
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
void PreferenceSon::EvtTreeMenu(wxTreeEvent &event)
{
    if (m_treeFiles->GetItemParent(event.GetItem()) == m_nodeExistant)
        PopupMenu(m_menu);
}

/**
 * Autorise ou non la modification d'un nœud
 * @param event un évènement
 */
void PreferenceSon::EvtTreeModifNomDebut(wxTreeEvent &event)
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
void PreferenceSon::EvtTreeModifNomFin(wxTreeEvent &event)
{
    if (!event.IsEditCancelled())
    {
        //renommer le fichier - event.GetLabel();
        if (wxFileExists(Parametre::Get()->getCheminSon(event.GetLabel())))
        {
            wxLogMessage(_T("Fichier Existant !"));
            m_treeFiles->EndEditLabel(event.GetItem(), true);
            m_treeFiles->SetFocus();
        }
        else
        {
            if (wxFileExists(Parametre::Get()->getCheminSon(m_treeFiles->GetItemText(event.GetItem()))))
            {
                ModifierFiltre(event.GetLabel().BeforeLast('.'), m_spinVolume->GetValue(), m_spinVolumePC->GetValue(), m_treeFiles->GetItemText(event.GetItem()));
                wxRemoveFile(Parametre::Get()->getCheminSon(m_treeFiles->GetItemText(event.GetItem())));
                m_textNomSet->ChangeValue(event.GetLabel().BeforeLast('.'));
            }
        }
    }
}

/**
 * Affiche le contenu d'un nœud dans la page
 * @param event un évènement
 */
void PreferenceSon::EvtTreeVoirNoeud(wxTreeEvent &event)
{
    bool loaded = false;
    if (wxFileExists(Parametre::Get()->getCheminSon(m_treeFiles->GetItemText(event.GetItem()))))
    {
        if (OuvrirFiltre(m_treeFiles->GetItemText(event.GetItem())))
        {
            loaded = true;
        }
    }
    if (!loaded)
    {
        m_textNomSet->Clear();
        m_spinVolume->SetValue(0);
        m_spinVolumePC->SetValue(0);
    }
}

/**
 * Applique les paramètres contenus dans le nœud sélectionné
 * @param event un évènement
 */
void PreferenceSon::EvtTreeAppliquerNoeud(wxTreeEvent &event)
{
    if (!m_textNomSet->IsEmpty())
    {
        AppliquerFiltreSelectionne();
    }
    else if (event.GetItem() == m_nodeNouveau)
    {
        wxTextEntryDialog *dlg = new wxTextEntryDialog(this, _("Choisissez un nom"), _("Création de filtre audio"));

        if (dlg->ShowModal() == wxID_OK)
        {
            if (wxFileExists(Parametre::Get()->getCheminSon(dlg->GetValue() + _T(".sauve"))))
            {
                wxLogMessage(_("Fichier Existant !"));
            }
            else
            {
                if (ModifierFiltre(dlg->GetValue(), m_textVolumeCurr->GetValue(), m_textVolumePCCurr->GetValue()))
                {
                    wxTreeItemId item = m_treeFiles->AppendItem(m_nodeExistant, dlg->GetValue() + _T(".sauve"));
                    m_treeFiles->SelectItem(item);
                    m_treeFiles->SortChildren(m_nodeExistant);
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
void PreferenceSon::EvtMenuSupprimer(wxCommandEvent &WXUNUSED(event))
{
    if (!wxRemoveFile(Parametre::Get()->getCheminSon(m_treeFiles->GetItemText(m_treeFiles->GetSelection()))))
        return;

    m_textNomSet->Clear();
    m_spinVolume->SetValue(0);
    m_spinVolumePC->SetValue(0);

    m_treeFiles->Delete(m_treeFiles->GetSelection());
}

/**
 * Renommage d'un nœud (et de son fichier correspondant)
 */
void PreferenceSon::EvtMenuRenommer(wxCommandEvent &WXUNUSED(event))
{
    m_treeFiles->EditLabel(m_treeFiles->GetSelection());
}

/**
 * Renommage du nom du fichier. Le nœud correspondant est modifié
 */
void PreferenceSon::EvtTextNom(wxCommandEvent &WXUNUSED(event))
{
    if (m_treeFiles->GetItemParent(m_treeFiles->GetSelection()) == m_nodeExistant)
    {
        ModifierFiltre(m_textNomSet->GetValue(), m_spinVolume->GetValue(), m_spinVolumePC->GetValue(), m_treeFiles->GetItemText(m_treeFiles->GetSelection()));
        m_treeFiles->SetItemText(m_treeFiles->GetSelection(), m_textNomSet->GetValue() + _T(".sauve"));
    }
}

/**
 * Modification du volume de l'application
 */
void PreferenceSon::EvtSpinVolume(wxSpinEvent &WXUNUSED(event))
{
    ModifierFiltre(m_textNomSet->GetValue(), m_spinVolume->GetValue(), m_spinVolumePC->GetValue());
}

/**
 * Modification du volume de l'ordinateur
 */
void PreferenceSon::EvtSpinVolumePC(wxSpinEvent &WXUNUSED(event))
{
    ModifierFiltre(m_textNomSet->GetValue(), m_spinVolumePC->GetValue(), m_spinVolumePC->GetValue());
}

/**
 * Met le volume sonore actuel à jour
 * @param valeur la nouvelle valeur du volume sonore
 */
void PreferenceSon::SetValeurMusique(long valeur)
{
    wxString volume;
    volume << valeur;
    m_textVolumeCurr->SetValue(volume);
}

/**
 * Modifie un filtre existant
 * @param nom le nom du filtre
 * @param vol le volume sonore dde l'application
 * @param volPC le volume sonore de l'ordinateur
 * @param oldNom l'ancien nom du filtre
 * @return vrai si réussite
 */
bool PreferenceSon::ModifierFiltre(wxString nom, wxString vol, wxString volPC, wxString oldNom)
{
    if (nom.IsEmpty())
        return false;
    if (oldNom.IsEmpty())
    {
        wxTextFile fichier(Parametre::Get()->getCheminSon(nom + _T(".sauve")));
        if (fichier.Create() || fichier.Open())
        {
            fichier.Clear();
            fichier.AddLine(_T("#EXTSAUVE_S1"));
            fichier.AddLine(nom);
            fichier.AddLine(vol);
            fichier.AddLine(volPC);
            fichier.AddLine(_T("0.5"));
            fichier.AddLine(_T("0.5"));
            fichier.Write();
            fichier.Close();
            return true;
        }
    }
    else
    {
        wxTextFile fichier(Parametre::Get()->getCheminSon(nom + _T(".sauve")));
        if (fichier.Create()/* || fichier.Open()*/)
        {
            fichier.AddLine(_T("#EXTSAUVE_S1"));
            fichier.AddLine(nom);
            fichier.AddLine(vol);
            fichier.AddLine(volPC);
            fichier.AddLine(_T("0.5"));
            fichier.AddLine(_T("0.5"));
            fichier.Write();
            fichier.Close();

            return wxRemoveFile(Parametre::Get()->getCheminSon(oldNom));
        }
    }
    return false;
}

/**
 * Modifie un filtre existant
 * @param nom le nom du filtre
 * @param vol le volume sonore dde l'application
 * @param volPC le volume sonore de l'ordinateur
 * @param oldNom l'ancien nom du filtre
 * @return vrai si réussite
 */
bool PreferenceSon::ModifierFiltre(wxString nom, int vol, int volPC, wxString oldNom)
{
    wxString volume, volumePC;
    volume << vol;
    volumePC << volPC;
    return ModifierFiltre(nom, volume, volumePC, oldNom);
}

/**
 * Lit le contenu d'un fichier(filtre) et modifie le volume sonore
 * @param nom le nom du filtre à lire
 * @param evenement si vrai, les paramètres sont juste visualisés, si faux les paramètres sont appliqués au graphe
 * @return vrai si réussite
 */
bool PreferenceSon::OuvrirFiltre(wxString filtre)
{
    wxTextFile fichier(Parametre::Get()->getCheminCouleur(filtre));
    if (fichier.Open())
    {
        if (fichier.GetLine(0).IsSameAs(_T("#EXTSAUVE_S1")))
        {
            /*wxString nom = fichier.GetLine(1);
            wxString volume = fichier.GetLine(1);
            wxString volumePC = fichier.GetLine(2);
            fichier.Close();

            m_textNomSet->ChangeValue(nom);
            m_spinVolume->SetValue(volume);
            m_spinVolumePC->SetValue(volumePC);*/
            m_textNomSet->ChangeValue(fichier.GetLine(1));
            m_spinVolume->SetValue(fichier.GetLine(2));
            m_spinVolumePC->SetValue(fichier.GetLine(3));
            fichier.Close();
            return true;
        }
        else
            fichier.Close();
    }
    return false;
}

/**
 * Applique les valeurs du filtre audio sélectionné
 */
void PreferenceSon::AppliquerFiltreSelectionne()
{
    wxString volume, volumePC;
    volume << m_spinVolume->GetValue();
    volumePC << m_spinVolumePC->GetValue();

    m_textVolumeCurr->ChangeValue(volume);
    m_textVolumePCCurr->ChangeValue(volumePC);

    Musique::Get()->SetVolume(m_spinVolume->GetValue());
    SliderSon::Get()->SetValue(m_spinVolume->GetValue());
}







