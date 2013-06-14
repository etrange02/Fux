#ifndef TRAVERSERCOPIEDOSSIER_H
#define TRAVERSERCOPIEDOSSIER_H

#include "../Define.h"
#include <wx/wx.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/textfile.h>
#include "../ThreadGestion.h"

class TraverserCopieDossier : public wxDirTraverser
{
    public:
        TraverserCopieDossier(wxString destination, wxString origine);
        virtual wxDirTraverseResult OnFile(const wxString &filename);
        virtual wxDirTraverseResult OnDir(const wxString &dirname);

    private:
        wxString m_destination, m_origine;
};

#endif // TRAVERSERCOPIEDOSSIER_H
