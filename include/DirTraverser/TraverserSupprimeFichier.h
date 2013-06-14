#ifndef TRAVERSERSUPPRIMEFICHIER_H
#define TRAVERSERSUPPRIMEFICHIER_H

#include "../Define.h"
#include <wx/wx.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/textfile.h>
#include "../ThreadGestion.h"

class TraverserSupprimeFichier : public wxDirTraverser
{
    public:
        TraverserSupprimeFichier(wxString origine, wxArrayString&);
        virtual wxDirTraverseResult OnFile(const wxString &filename);
        virtual wxDirTraverseResult OnDir(const wxString &dirname);

    private:
        wxString m_origine;
        wxArrayString &m_tableau;
};

#endif // TRAVERSERSUPPRIMEFICHIER_H
