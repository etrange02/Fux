#ifndef PREFERENCE_H_INCLUDED
#define PREFERENCE_H_INCLUDED

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include "../Define.h"
#include "GenericTreePanel.h"
#include "../Musique.h"
#include "SliderSon.h"

class PreferenceSon : public GenericTreePanel
{
    public:
        PreferenceSon(wxWindow *Parent, wxWindowID id);
        virtual ~PreferenceSon();
        void MajListe(wxChoice *liste);

        void EvtTreeMenu(wxTreeEvent &event);
        void EvtTreeModifNomDebut(wxTreeEvent &event);
        void EvtTreeModifNomFin(wxTreeEvent &event);
        void EvtTreeVoirNoeud(wxTreeEvent &event);
        void EvtTreeAppliquerNoeud(wxTreeEvent &event);
        void EvtMenuSupprimer(wxCommandEvent &WXUNUSED(event));
        void EvtMenuRenommer(wxCommandEvent &WXUNUSED(event));
        void EvtTextNom(wxCommandEvent &WXUNUSED(event));
        void EvtSpinVolume(wxSpinEvent &WXUNUSED(event));
        void EvtSpinVolumePC(wxSpinEvent &WXUNUSED(event));
        void SetValeurMusique(long valeur);
        bool ModifierFiltre(wxString nom, wxString vol, wxString volPC, wxString oldNom = wxEmptyString);
        bool ModifierFiltre(wxString nom, int vol, int volPC, wxString oldNom = wxEmptyString);

    private:
        void Creer();
        void RemplirTree();

    protected:
        wxSizer *m_sizerNewSet, *m_sizerCurrentSet, *m_gridSizerNew, *m_gridSizerCurr;
        wxSpinCtrl *m_spinVolume, *m_spinVolumePC;
        wxTextCtrl *m_textNomSet, *m_textVolumeCurr, *m_textVolumePCCurr;
        wxMenu *m_menu;
        /*wxChoice *m_listeModif;
        wxRadioBox *m_choix;
        int m_listeModif_Nouveau;*/

    DECLARE_EVENT_TABLE()
};

/*class PrefSon : public wxScrolledWindow
{
    public:
        PrefSon();
        PrefSon(wxWindow *Parent);
        virtual ~PrefSon();
        void Creer(wxWindow *parent, wxWindowID id);
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
        wxTreeCtrl *m_treeFiles;
        wxTreeItemId m_nodeExistant;
        wxChoice *m_listeModif;
        wxRadioBox *m_choix;
        wxSizer *m_sizer0H, *m_sizer1V, *m_sizer2H, *m_sizerActuel, *m_sizerBouton, *m_sizerNewModif, *m_sizerNewModifTAB;
        wxTextCtrl *m_boiteNomMod, *m_boiteNomActuel, *m_boiteVolActuel, *m_boiteVolPCActuel;
        wxSpinCtrl *m_boiteVolMod, *m_boiteVolPCMod;
        wxButton *m_Bouton_Supprimer, *m_Bouton_Appliquer;
        wxStaticText* m_textNom, *m_textVolume, *m_textVolumePC;

        int m_listeModif_Nouveau;

    DECLARE_EVENT_TABLE()
};*/

#endif // PREFERENCE_H_INCLUDED
