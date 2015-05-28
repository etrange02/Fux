#ifndef BOUTONFENETREDETACHABLE_H
#define BOUTONFENETREDETACHABLE_H

#include <wx/wx.h>
#include <wx/button.h>
#include "Define.h"
#include "tools/FichierLog.h"

extern const wxEventType wxEVT_BOUTON_FENETRE_DETACHABLE;

class BoutonFenetreDetachable : public wxButton
{
    public:
        BoutonFenetreDetachable(wxWindow *parent, wxWindowID id, const wxString &label, const wxSize &size, int type);
        virtual ~BoutonFenetreDetachable();
        void SeparationPanel(wxMouseEvent &event);
        void EnvoieMessageDrag();

    protected:
        int m_type;

    DECLARE_EVENT_TABLE()
};

#endif // BOUTONFENETREDETACHABLE_H
