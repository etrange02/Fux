#ifndef PREFERENCECOULEUR_H_INCLUDED
#define PREFERENCECOULEUR_H_INCLUDED

#include <wx/wx.h>
//#include <wx/stdpaths.h>
//#include <wx/radiobox.h>
#include <wx/statbmp.h>
#include <wx/dcmemory.h>
//#include <wx/textfile.h>
//#include <wx/scrolwin.h>
#include <wx/xml/xml.h>
#include <wx/dir.h>
#include "../Define.h"
#include "GenericTreePanel.h"
#include "../Parametre.h"

class PreferenceCouleur : public GenericTreePanel
{
    public:
        PreferenceCouleur(wxWindow *Parent, wxWindowID id);
        virtual ~PreferenceCouleur();
        void MajListe(wxChoice *liste);

        void EvtTreeMenu(wxTreeEvent &event);
        void EvtTreeModifNomDebut(wxTreeEvent &event);
        void EvtTreeModifNomFin(wxTreeEvent &event);
        void EvtTreeVoirNoeud(wxTreeEvent &event);
        void EvtTreeAppliquerNoeud(wxTreeEvent &event);
        void EvtMenuSupprimer(wxCommandEvent &WXUNUSED(event));
        void EvtMenuRenommer(wxCommandEvent &WXUNUSED(event));
        void EvtTextNom(wxCommandEvent &WXUNUSED(event));
        void Couleur_MAJ_Fond(wxScrollEvent &event);
        void Couleur_MAJ_Barre(wxScrollEvent &WXUNUSED(event));
        void Couleur_MAJ_GraphSup(wxCommandEvent &WXUNUSED(event));
        void Couleur_MAJ_GraphInf(wxCommandEvent &WXUNUSED(event));
        void Couleur_MAJ_Symetrie(wxCommandEvent &WXUNUSED(event));
        bool ModifierFiltre(wxString nom, Couleur fond, Couleur barre, Couleur police, Couleur haut, Couleur miSup, bool symetrie, Couleur miInf, Couleur bas, wxString oldNom = wxEmptyString);
        bool ModifierFiltre(wxString nom = wxEmptyString, wxString oldNom = wxEmptyString);
        bool OuvrirFiltre(wxString filtre, bool evenement);

    private:
        void Creer();
        void RemplirTree();
        void MAJ_Fond();
        void MAJ_Barre();
        void MAJ_GraphSup();
        void MAJ_GraphInf();
        void MAJ_Symetrie();
        void ValeursDefaut();
        void AppliquerFiltreSelectionne();

    protected:
        wxSizer *m_sizerFond, *m_sizerBarrePolice, *m_sizerGraph, *m_sizerGraphHaut, *m_sizerGraphBas;
        wxTextCtrl *m_textNomSet;
        wxBitmap *m_bitmap;
        wxMenu *m_menu;
        wxStaticBitmap *m_apercuFond, *m_apercuBarre, *m_apercuGraphHaut, *m_apercuGraphBas;
        wxSlider *m_sliderFond, *m_sliderBarre, *m_sliderPolice;
        wxStaticText *m_TextFond, *m_TextBarre, *m_TextPolice;
        wxCheckBox *m_checkBoxHaut, *m_checkBoxMiSup, *m_checkBoxMiInf, *m_checkBoxBas, *m_doubleBarre;

    DECLARE_EVENT_TABLE()
};

#endif // PREFERENCECOULEUR_H_INCLUDED
