#ifndef DIALOGENREGISTREM3U_H
#define DIALOGENREGISTREM3U_H

#include <wx/wx.h>
#include <wx/statline.h>
#include <wx/filename.h>
#include <wx/dir.h>
#include "Define.h"
#include "settings/Parametre.h"

extern const wxEventType wxEVT_PREFERENCE_MAJ_M3U;

class DialogEnregistreM3U : public wxDialog
{
    public:
        DialogEnregistreM3U(wxWindow *parent, wxWindowID id, wxString racc);
        ~DialogEnregistreM3U();
        void Creer();
        wxString GetChemin();
        wxString GetCheminRaccourci();
        void CreerListeM3U();
        void OuvrirDossier(wxCommandEvent &WXUNUSED(event));
        static void SetPanelToBeCall(wxPanel *Panel);
        static void CallPanel();

    private:
        wxArrayString m_chaineM3U;
        wxString      m_chemin;
        wxString      m_raccourci;
        wxString      m_rep;
        wxChoice*     m_liste;
        wxTextCtrl*   m_boiteNouveau;
        wxTextCtrl*   m_boiteRaccourci;
        wxButton*     m_bouton;//wxDirPickerCtrl
        wxStaticText* m_text;

    DECLARE_EVENT_TABLE()
};

#endif // DIALOGENREGISTREM3U_H
