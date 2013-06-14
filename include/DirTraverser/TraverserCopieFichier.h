#ifndef TRAVERSERCOPIEFICHIER_H
#define TRAVERSERCOPIEFICHIER_H

#include "../Define.h"
#include <wx/wx.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/textfile.h>
#include "../ThreadGestion.h"

class TraverserCopieFichier : public wxDirTraverser
{
    public:
        TraverserCopieFichier(wxString destination, wxString origine);
        virtual wxDirTraverseResult OnFile(const wxString &filename);
        virtual wxDirTraverseResult OnDir(const wxString &dirname);

    private:
        wxString m_destination, m_origine;
};

#endif // TRAVERSERCOPIEFICHIER_H
