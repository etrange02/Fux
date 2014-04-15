#ifndef GENERICTREEPANEL_H
#define GENERICTREEPANEL_H

#include <wx/wx.h>
#include <wx/treectrl.h>
#include "../../Define.h"

WX_DEFINE_ARRAY(wxPanel*, ArrayOfwxPanel);
extern const wxEventType wxEVT_PREFERENCE_MAJ_LISTE;

class GenericTreePanel : public wxScrolledWindow
{
    public:
        GenericTreePanel(wxWindow *Parent, wxWindowID Id, wxWindowID IdTreeCtrl);
        virtual ~GenericTreePanel();
        virtual void Create(wxWindow *Parent, wxWindowID Id, wxWindowID IdTreeCtrl);
        virtual void MajListe(wxChoice *liste) = 0;
        virtual void AddListener(wxPanel *panel);
        virtual void CallListeners();
        virtual void EvtTreeMenu(wxTreeEvent &event) = 0;
        virtual void EvtTreeModifNomDebut(wxTreeEvent &event) = 0;
        virtual void EvtTreeModifNomFin(wxTreeEvent &event) = 0;
        virtual void EvtTreeVoirNoeud(wxTreeEvent &event) = 0;
        virtual void EvtTreeAppliquerNoeud(wxTreeEvent &event) = 0;
        virtual void EvtMenuSupprimer(wxCommandEvent &WXUNUSED(event)) = 0;
        virtual void EvtMenuRenommer(wxCommandEvent &WXUNUSED(event)) = 0;

    protected:
        wxTreeCtrl *m_treeFiles;
        wxTreeItemId m_nodeExistant, m_nodeNouveau;
        wxSizer *m_sizer2Preferences;
        wxString m_nomAvantModif;
        ArrayOfwxPanel *m_arrayPanel;

    private:
        wxSizer *m_sizer1H, *m_sizer2V;
};

#endif // GENERICTREEPANEL_H
