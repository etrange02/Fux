#ifndef GESTIONPERIPHTABLEAU_H_INCLUDED
#define GESTIONPERIPHTABLEAU_H_INCLUDED

#include "Define.h"
#include <wx/wx.h>
#include <wx/dir.h>
#include <wx/listctrl.h>
#include <wx/filename.h>
#include <wx/imaglist.h>
#include "GestionPeriphCouperCopier.h"
#include "tools/dnd/DnDCible.h"

extern const wxEventType wxEVT_LISTE_PERIPH_CLAVIER;
extern const wxEventType wxEVT_LISTE_PERIPH_SOURIS;
extern const wxEventType wxEVT_LISTE_RENEW;

class ListeGestionPeriph : public wxListCtrl
{
    public :
        ListeGestionPeriph();
        ListeGestionPeriph(wxWindow*, wxWindowID);
        virtual ~ListeGestionPeriph();
        void Creer(wxWindow*, wxWindowID);
        bool AfficheContenuFichier(wxString, int);
        bool AfficheContenuDossier(wxString, bool, bool);
        bool VideListe();
        int GetEtat();
        void SetEtat(int);

        void OnKey(wxKeyEvent&);
        void OnMenu(wxCommandEvent&);
        void AfficheMenu(wxMouseEvent &WXUNUSED(event));

    private :
        wxMenu *m_menu;
        int m_etat;

    DECLARE_EVENT_TABLE()
};

#endif // GESTIONPERIPHTABLEAU_H_INCLUDED
