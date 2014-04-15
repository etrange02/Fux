#ifndef DIALOGTAGMP3_H
#define DIALOGTAGMP3_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include "../../Define.h"
#include "../widgets/ImagePochetteMusique.h"
#include "DialogTagMP3Info.h"

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

#endif // DIALOGTAGMP3_H
