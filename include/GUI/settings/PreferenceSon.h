#ifndef PREFERENCE_H_INCLUDED
#define PREFERENCE_H_INCLUDED

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/xml/xml.h>
#include "../../Define.h"
#include "../widgets/GenericTreePanel.h"
#include "../../music/Musique.h"
#include "../widgets/SliderSon.h"

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
        bool OuvrirFiltre(wxString filtre, bool evenement = true);

    private:
        void Creer();
        void RemplirTree();
        void AppliquerFiltreSelectionne();

    protected:
        wxSizer *m_sizerNewSet, *m_sizerCurrentSet, *m_gridSizerNew, *m_gridSizerCurr;
        wxSpinCtrl *m_spinVolume, *m_spinVolumePC;
        wxTextCtrl *m_textNomSet, *m_textVolumeCurr, *m_textVolumePCCurr;
        wxMenu *m_menu;

    DECLARE_EVENT_TABLE()
};

#endif // PREFERENCE_H_INCLUDED
