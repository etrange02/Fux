#ifndef TRAVERSERDEPLACEFICHIER_H
#define TRAVERSERDEPLACEFICHIER_H

#include "../Define.h"
#include <wx/wx.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/textfile.h>
#include "../ThreadGestion.h"

class TraverserDeplaceFichier : public wxDirTraverser
{
    public:
        TraverserDeplaceFichier(wxString destination, wxString origine, wxArrayString&);
        virtual wxDirTraverseResult OnFile(const wxString &filename);
        virtual wxDirTraverseResult OnDir(const wxString &dirname);

    private:
        wxString m_destination, m_origine;
        wxArrayString &m_tableau;
};

#endif // TRAVERSERDEPLACEFICHIER_H
