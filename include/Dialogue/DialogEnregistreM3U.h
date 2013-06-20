#ifndef DIALOGENREGISTREM3U_H
#define DIALOGENREGISTREM3U_H

#include <wx/wx.h>
#include <wx/statline.h>
#include <wx/filename.h>
#include <wx/dir.h>
#include "../Define.h"
#include "../Parametre.h"

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

    private:
        wxString m_chemin, m_raccourci, m_rep;
        wxChoice *m_liste;
        wxTextCtrl *m_boiteNouveau, *m_boiteRaccourci;
        wxButton *m_bouton;//wxDirPickerCtrl
        wxArrayString m_chaineM3U;
        wxStaticText* m_text;

    DECLARE_EVENT_TABLE()
};

#endif // DIALOGENREGISTREM3U_H
