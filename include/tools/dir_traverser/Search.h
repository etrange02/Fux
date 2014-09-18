#ifndef RECHERCHE_H
#define RECHERCHE_H

#include "../../Define.h"
#include <wx/wx.h>
#include <wx/dir.h>
//#include <wx/filename.h>
#include "../../settings/Parametre.h"
#include "ISearchTraversable.h"

class Search : public wxDirTraverser
{
    public:
        Search(ISearchTraversable *searchTraversable);
        virtual wxDirTraverseResult OnFile(const wxString &filename);
        virtual wxDirTraverseResult OnDir(const wxString &dirname);

    private:
        ISearchTraversable *m_searchTraversable;
};

#endif // RECHERCHE_H
