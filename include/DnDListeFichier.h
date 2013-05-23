#ifndef DNDLISTEFICHIER_H
#define DNDLISTEFICHIER_H

#include <wx/wx.h>
#include <wx/dnd.h>

class DnDListeFichier//Type de donnée glissé
{
    public:
        DnDListeFichier();
        ~DnDListeFichier();

        void AddFile(const wxString&);
        void AddStringArray(const wxArrayString*);
        wxString& Item(size_t);
        size_t GetCount();
        void Clear();
        wxArrayString* arrayString();

    private :
        wxArrayString m_Nom;
};

#endif // DNDLISTEFICHIER_H
