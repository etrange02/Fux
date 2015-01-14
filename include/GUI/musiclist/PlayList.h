#ifndef PLAY_LISTE_H_INCLUDED
#define PLAY_LISTE_H_INCLUDED

#include "../../Define.h"
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
//#include "../../music/Musique.h"
#include "../../music/MusicManager.h"
#include "PlayListTableau.h"
#include "../dialogs/DialogEnregistreM3U.h"
#include "../dialogs/DialogTagMP3.h"
#include "../tools/jaquetteClasses.h"
#include "../../tools/OS_Win.h"
#include "../widgets/SliderSon.h"


class PlayList : public wxPanel
{
    public:
        PlayList();
        virtual ~PlayList();

        PlayListTableau* GetPlayListTableau();

        void Initialize(wxWindow *Parent);
        void EnregistrerM3U(wxCommandEvent &WXUNUSED(event));
        void OnPanneau(wxCollapsiblePaneEvent &WXUNUSED(event));
        void OnAfficheDetails(wxListEvent&);
        void OnAppliquerTAG(wxCommandEvent &WXUNUSED(event));
        void OnAnnulerTAG(wxCommandEvent &WXUNUSED(event));
        void FenetreDetails(wxCommandEvent &WXUNUSED(event));

        void ViderPanneauTAG();
        void RemplirPanneauTAG(int musicPosition);
        void EvtViderPanneauTAG(wxCommandEvent &WXUNUSED(event));
        void EvtImage(wxCommandEvent&);
        void MouseEvents(wxMouseEvent&);

        void RechercheListeLecture(wxCommandEvent&);

    private:
        void RemplirPanneauTAG(Music& music);

    protected:
        wxSizer *sizer, *m_sizerBouton, *m_sizerRep;
        wxFlexGridSizer *m_sizerPann;
        wxButton *m_BoutonSauver, *m_BoutonAnnuler, *m_BoutonEnregistrerM3U;
        wxCollapsiblePane *m_panneauRepliable;
        wxTextCtrl *m_BoiteNom, *m_BoiteArtiste, *m_BoiteAlbum, *m_BoiteTitre, *m_BoiteGenre;
        wxSpinCtrl *m_BoiteAnnee;
        wxSearchCtrl *m_champsRecherche;

        ImagePochetteMusique *m_pochette;
        wxImage m_defaultRecordSleeve;
        PlayListTableau *m_liste;

    DECLARE_EVENT_TABLE()
};

#endif // PLAY_LISTE_H_INCLUDED
