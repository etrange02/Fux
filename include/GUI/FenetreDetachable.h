#ifndef FENETREDETACHABLE_H
#define FENETREDETACHABLE_H

#include <wx/wx.h>
#include <wx/frame.h>
#include "../Define.h"
#include "../Parametre.h"

extern const wxEventType wxEVT_FERMER_FENETRE_DETACHABLE;

class FenetreDetachable : public wxFrame
{
    public:
        FenetreDetachable(wxWindow*, wxWindow*, wxSizer*, int, int, wxString);
        ~FenetreDetachable();
        wxSizer* GetSizer();
        void SetSizer(wxSizer* val);
        int GetType();
        int GetIdBouton();
        void Fermer(wxCloseEvent &event);
        void RenvoieEvent(wxCommandEvent &event);
        wxSizer* RetourNormale();

    protected:
        wxWindow *m_parent, *m_page;
        wxSizer *m_sizer;
        int m_type, m_idBouton;

    DECLARE_EVENT_TABLE()
};

#endif // FENETREDETACHABLE_H
