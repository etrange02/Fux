#ifndef ELEMENTTHREADFICHIER_H
#define ELEMENTTHREADFICHIER_H

#include <wx/wx.h>

class ElementThreadFichier
{
    public:
        ElementThreadFichier(wxString, int, wxString);
        virtual ~ElementThreadFichier();
        wxString& GetNom();
        wxString& GetDestination();
        int GetAction();
        bool IsAction(int);

    protected:
        wxString m_nom, m_destination;
        int m_action;
};

#endif // ELEMENTTHREADFICHIER_H
