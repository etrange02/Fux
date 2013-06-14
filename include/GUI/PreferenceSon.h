#ifndef PREFERENCE_H_INCLUDED
#define PREFERENCE_H_INCLUDED

#include <wx/wx.h>
#include <wx/filedlg.h>
#include <wx/spinctrl.h>
#include <wx/stdpaths.h>
#include <wx/textfile.h>
#include <wx/dir.h>
#include <wx/radiobox.h>
#include "../Define.h"
#include "../Musique.h"
#include "SliderSon.h"

class PrefSon : public wxScrolledWindow
{
    public:
        PrefSon();
        PrefSon(wxWindow *Parent);
        virtual ~PrefSon();
        void Creer();
        int CreerListe(wxChoice*);
        void Son_RadioModif_Nouveau(wxCommandEvent &event);
        void Son_Modif_Nouveau(int);
        void Son_ModifOuvrirFichier(wxCommandEvent &WXUNUSED(event));
        void Son_Bouton_Enregistrer(wxCommandEvent &WXUNUSED(event));
        void Son_Bouton_Annuler(wxCommandEvent &WXUNUSED(event));//Remise à 0 des valeurs
        void Son_Bouton_Appliquer(wxCommandEvent &event);
        void Son_Bouton_Supprimer(wxCommandEvent &WXUNUSED(event));
        void Son_Bouton_Actuel(wxCommandEvent &WXUNUSED(event));
        void BoiteNouveauModifiee(wxCommandEvent &WXUNUSED(event));
        wxRadioBox* GetRadioBox();

        void SetValeurMusique(long);

    protected:
        wxChoice *m_listeModif;
        wxRadioBox *m_choix;
        wxSizer *m_sizer1V, *m_sizer2H, *m_sizerActuel, *m_sizerBouton, *m_sizerNewModif, *m_sizerNewModifTAB;
        wxTextCtrl *m_boiteNomMod, *m_boiteNomActuel, *m_boiteVolActuel, *m_boiteVolPCActuel;
        wxSpinCtrl *m_boiteVolMod, *m_boiteVolPCMod;
        wxButton *m_Bouton_Supprimer, *m_Bouton_Appliquer;

        int m_listeModif_Nouveau;

    DECLARE_EVENT_TABLE()
};

#endif // PREFERENCE_H_INCLUDED
