#ifndef DIALOGUEFENETREEXT_H_INCLUDED
#define DIALOGUEFENETREEXT_H_INCLUDED

#include <wx/wx.h>
#include <wx/statline.h>
#include <wx/filename.h>
#include <wx/dir.h>
#include <wx/notebook.h>
#include <wx/spinctrl.h>
#include "Define.h"
#include "ImageFichierMusique.h"
#include "Parametre.h"
#include "Musique.h"

class DialogEnregistreM3U : public wxDialog
{
    public:
        DialogEnregistreM3U(wxWindow *parent, wxWindowID id, wxString racc);
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

    DECLARE_EVENT_TABLE()
};

class DialogTagMP3Info : public wxPanel
{
    public:
        DialogTagMP3Info(wxWindow *parent, wxWindowID id, wxString chanson);
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
        void SetDuree(wxString duree);
        void SetDebit(int debit);
        void SetTaille(int taille);
        bool IsModified();

    private:
        int m_annee;
        wxTextCtrl *m_boiteNom, *m_boiteArtiste, *m_boiteTitre, *m_boiteAlbum, *m_boiteGenre;
        wxSpinCtrl *m_boiteAnnee;
        wxStaticText *m_echantillonage, *m_taille, *m_duree;
};

class DialogTagMP3 : public wxDialog
{
    public:
        DialogTagMP3(wxWindow *parent, wxWindowID id, wxString chanson);
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
        void SetCommentaire(wxString commentaire);
        void SetAnnee(int annee);
        void SetDuree(wxString duree);
        void SetDebit(int debit);
        void SetTaille(int taille);
        bool IsModified();
        wxString GetCommentaire();
        ImagePochetteMusique *GetImage();

    protected:
        DialogTagMP3Info *m_pageInfo;
        ImagePochetteMusique *m_image;
        wxNotebook *m_notebook;
        wxTextCtrl *m_commentaires;
};

#endif // DIALOGUEFENETREEXT_H_INCLUDED
