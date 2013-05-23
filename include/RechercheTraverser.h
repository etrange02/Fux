#ifndef RECHERCHETRAVERSER_H_INCLUDED
#define RECHERCHETRAVERSER_H_INCLUDED

#include "Define.h"
#include <wx/wx.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/textfile.h>
#include "Parametre.h"
#include "ThreadGestion.h"


class Recherche : public wxDirTraverser
{
    public:
        Recherche(wxTextFile *fichier);
        virtual wxDirTraverseResult OnFile(const wxString &filename);
        virtual wxDirTraverseResult OnDir(const wxString &dirname);

    private:
        wxTextFile *m_fichier;
};

class TraverserCopieFichier : public wxDirTraverser
{
    public:
        TraverserCopieFichier(wxString destination, wxString origine);
        virtual wxDirTraverseResult OnFile(const wxString &filename);
        virtual wxDirTraverseResult OnDir(const wxString &dirname);

    private:
        wxString m_destination, m_origine;
};

class TraverserCopieDossier : public wxDirTraverser
{
    public:
        TraverserCopieDossier(wxString destination, wxString origine);
        virtual wxDirTraverseResult OnFile(const wxString &filename);
        virtual wxDirTraverseResult OnDir(const wxString &dirname);

    private:
        wxString m_destination, m_origine;
};

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

/*class TraverserSupprimeDossier : public wxDirTraverser
{
    public:
        TraverserSupprimeDossier(wxString origine);
        ~TraverserSupprimeDossier();
        virtual wxDirTraverseResult OnFile(const wxString &filename);
        virtual wxDirTraverseResult OnDir(const wxString &dirname);

    private:
        wxString m_origine;
};*/

#endif // RECHERCHE_H_INCLUDED
