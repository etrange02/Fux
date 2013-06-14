#ifndef RECHERCHE_H
#define RECHERCHE_H

#include "../Define.h"
#include <wx/wx.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/textfile.h>
#include "../Parametre.h"

class Recherche : public wxDirTraverser
{
    public:
        Recherche(wxTextFile *fichier);
        virtual wxDirTraverseResult OnFile(const wxString &filename);
        virtual wxDirTraverseResult OnDir(const wxString &dirname);

    private:
        wxTextFile *m_fichier;
};

#endif // RECHERCHE_H
