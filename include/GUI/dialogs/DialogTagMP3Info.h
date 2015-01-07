#ifndef DIALOGUEFENETREEXT_H_INCLUDED
#define DIALOGUEFENETREEXT_H_INCLUDED

#include <wx/wx.h>
#include <wx/filename.h>
#include <wx/spinctrl.h>
#include "../../Define.h"

class DialogTagMP3Info : public wxPanel
{
    public:
        DialogTagMP3Info(wxWindow *parent, wxWindowID id, wxString chanson);
        ~DialogTagMP3Info();
        void SetChanson(wxString chanson);
        wxString GetNom();
        wxString GetTitre();
        wxString GetAlbum();
        wxString GetArtiste();
        wxString GetGenre();
        int GetAnnee();
        void SetTitre(wxString titre);
        void SetAlbum(wxString album);
        void SetArtiste(wxString artiste);
        void SetGenre(wxString genre);
        void SetAnnee(int annee);
        void SetDuration(wxString duree);
        void SetDebit(int debit);
        void SetTaille(int taille);
        bool IsModified();

    private:
        int m_annee;
        wxTextCtrl *m_boiteNom, *m_boiteArtiste, *m_boiteTitre, *m_boiteAlbum, *m_boiteGenre;
        wxSpinCtrl *m_boiteAnnee;
        wxStaticText *m_echantillonage, *m_taille, *m_duree;
        wxStaticText *m_texte;
};

#endif // DIALOGUEFENETREEXT_H_INCLUDED
