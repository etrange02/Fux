#ifndef PLAY_LISTE_H_INCLUDED
#define PLAY_LISTE_H_INCLUDED

#include "Define.h"
#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include <wx/collpane.h>
#include <wx/gbsizer.h>
#include <wx/spinctrl.h>
#include <wx/textdlg.h>
#include <wx/tarstrm.h>
#include <wx/progdlg.h>
#include <wx/mstream.h>
#include <wx/srchctrl.h>
#include <tag.h>
#include <fileref.h>
#include <taglib.h>
#include <mpegfile.h>
#include <id3v2tag.h>
#include <attachedpictureframe.h>
/*#include <TAGLIBDLL/tag.h>
#include <TAGLIBDLL/fileref.h>
#include <TAGLIBDLL/taglib.h>
#include <TAGLIBDLL/mpegfile.h>
#include <TAGLIBDLL/id3v2tag.h>
#include <TAGLIBDLL/attachedpictureframe.h>*/
//#include <TAGLIBDLL/tlist.tcc>
#include "Musique.h"
#include "PlayListTableau.h"
#include "DialogueFenetreExt.h"
#include "ImageFichierMusique.h"
#include "OS_Win.h"
#include "SliderSon.h"


class PlayList : public wxPanel
{
    public:
        PlayList();
        virtual ~PlayList();

        ListeLecture* GetListeLecture();

        void Creer(wxWindow *Parent, bool MAJListe = false);
        void EnregistrerM3U(wxCommandEvent &WXUNUSED(event));
        void OnPanneau(wxCollapsiblePaneEvent &WXUNUSED(event));
        void OnAfficheDetails(wxListEvent&);
        void OnAppliquerTAG(wxCommandEvent &WXUNUSED(event));
        void OnAnnulerTAG(wxCommandEvent &WXUNUSED(event));
        void FenetreDetails(wxCommandEvent &WXUNUSED(event));

        void ViderPanneauTAG();
        void RemplirPanneauTAG(wxString chaine);
        void EvtViderPanneauTAG(wxCommandEvent &WXUNUSED(event));
        void EvtImage(wxCommandEvent&);
        void MouseEvents(wxMouseEvent&);

        void RechercheListeLecture(wxCommandEvent&);

    protected:
        wxString fichierTAG;
        wxSizer *sizer, *m_sizerBouton, *m_sizerRep;
        wxFlexGridSizer *m_sizerPann;
        wxButton *m_BoutonSauver, *m_BoutonAnnuler, *m_BoutonEnregistrerM3U;
        wxCollapsiblePane *m_panneauRepliable;
        wxTextCtrl *m_BoiteNom, *m_BoiteArtiste, *m_BoiteAlbum, *m_BoiteTitre, *m_BoiteGenre;
        wxSpinCtrl *m_BoiteAnnee;
        wxSearchCtrl *m_champsRecherche;

        int ligneSel;
        ImagePochetteMusique *m_pochette;
        ListeLecture *m_liste;
        Musique *m_musique;
        TagLib::FileRef m_ObjetTAG;

        int m_rechercheTailleMot;

    DECLARE_EVENT_TABLE()
};

#endif // PLAY_LISTE_H_INCLUDED
