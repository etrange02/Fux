#ifndef ARRAYFENETREDETACHABLE_H
#define ARRAYFENETREDETACHABLE_H

#include <wx/wx.h>
#include "../widgets/FenetreDetachable.h"

WX_DEFINE_ARRAY(FenetreDetachable*, ArrayOfFenetreDetachable);

class ArrayFenetreDetachable : public ArrayOfFenetreDetachable
{
    public:
        ArrayFenetreDetachable();
        virtual ~ArrayFenetreDetachable();
        void Vider();
        void Add(wxWindow*, wxWindow*, wxSizer*, int, int, wxString);
        bool IsInsideBouton(int);
        bool IsInsideType(int);
        FenetreDetachable* GetFenetreByIdBouton(int);
        FenetreDetachable* GetFenetreByType(int);

    protected:
};

#endif // ARRAYFENETREDETACHABLE_H
