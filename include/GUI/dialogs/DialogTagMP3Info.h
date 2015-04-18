#ifndef DIALOGUEFENETREEXT_H_INCLUDED
#define DIALOGUEFENETREEXT_H_INCLUDED

#include <wx/wx.h>
#include <wx/filename.h>
#include <wx/spinctrl.h>
#include "../../Define.h"
#include "Music.h"

class DialogTagMP3Info : public wxPanel
{
    public:
        DialogTagMP3Info(wxWindow *parent, wxWindowID id, music::Music* music);
        ~DialogTagMP3Info();
        bool isModified();

        void toMusic();

    private:
        void fillFields();
        void fillDuration(wxString duree);
        void fillDebit(const int debit);
        void fillSize(const int taille);

    private:
        wxTextCtrl *m_boiteNom, *m_boiteArtiste, *m_boiteTitre, *m_boiteAlbum, *m_boiteGenre;
        wxSpinCtrl *m_boiteAnnee;
        wxStaticText *m_echantillonage, *m_taille, *m_duree;
        wxStaticText *m_texte;
        music::Music* m_music;
};

#endif // DIALOGUEFENETREEXT_H_INCLUDED
