#ifndef PREFERENCECOULEUR_H_INCLUDED
#define PREFERENCECOULEUR_H_INCLUDED

#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <wx/radiobox.h>
#include <wx/statbmp.h>
#include <wx/dcmemory.h>
#include <wx/textfile.h>
#include <wx/scrolwin.h>
#include <wx/dir.h>
#include "Define.h"
#include "Parametre.h"

class PrefCouleur : public wxScrolledWindow
{
    public:
        PrefCouleur();
        PrefCouleur(wxWindow *Parent);
        virtual ~PrefCouleur();
        void Creer();
        int CreerListe(wxChoice*);
        void Couleur_RadioModif_Nouveau(wxCommandEvent &event);
        void Couleur_Modif_Nouveau(int);
        void MAJ_Fond();
        void MAJ_Barre();
        void MAJ_GraphSup();
        void MAJ_GraphInf();
        void MAJ_Annuler();
        void Couleur_MAJ_Fond(wxScrollEvent &event);
        void Couleur_MAJ_Barre(wxScrollEvent &WXUNUSED(event));
        void Couleur_MAJ_GraphSup(wxCommandEvent &WXUNUSED(event));
        void Couleur_MAJ_GraphInf(wxCommandEvent &WXUNUSED(event));
        void OuvrirFichier(wxCommandEvent &WXUNUSED(event));
        void Couleur_OuvrirFichier(wxString, bool);
        void Couleur_Bouton_Enregistrer(wxCommandEvent &WXUNUSED(event));
        void Couleur_Bouton_Annuler(wxCommandEvent &WXUNUSED(event));//Remise � 0 des valeurs
        void Couleur_Bouton_Appliquer(wxCommandEvent &event);
        void Couleur_Bouton_Supprimer(wxCommandEvent &WXUNUSED(event));
        void BoiteNouveauModifiee(wxCommandEvent &WXUNUSED(event));
        Couleur Couleur_ExtraitString(wxString) const;
        bool TFSup_ExtraitString(wxString, wxString);
        bool TFInf_ExtraitString(wxString, wxString, wxString);
        wxRadioBox* GetRadioBox();

    protected:

        wxSizer *m_sizer1V, *m_sizer2H, *m_sizerFond, *m_sizerBarrePolice, *m_sizerGraphHaut, *m_sizerGraphBas, *m_sizerBouton;
        wxRadioBox *m_choix;
        wxChoice *m_listeModif;
        wxTextCtrl *m_boiteNom;
        wxBitmap *m_bitmap;
        wxStaticBitmap *m_apercuFond, *m_apercuBarre, *m_apercuGraphHaut, *m_apercuGraphBas;
        wxSlider *m_sliderFond, *m_sliderBarre, *m_sliderPolice;
        wxStaticText *m_TextFond, *m_TextBarre, *m_TextPolice;
        wxCheckBox *m_checkBoxHaut, *m_checkBoxMiSup, *m_checkBoxMiInf, *m_checkBoxBas, *m_doubleBarre;
        wxButton *m_Bouton_Supprimer, *m_Bouton_Appliquer;

        int m_listeModif_Nouveau;

    DECLARE_EVENT_TABLE()
};

#endif // PREFERENCECOULEUR_H_INCLUDED
