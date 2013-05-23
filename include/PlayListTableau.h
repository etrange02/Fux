#ifndef PLAYLISTTABLEAU_H_INCLUDED
#define PLAYLISTTABLEAU_H_INCLUDED

#include "Define.h"
#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include <wx/listctrl.h>
//#include <wx/collpane.h>
//#include <wx/gbsizer.h>
//#include <wx/spinctrl.h>
//#include <wx/textdlg.h>
#include <wx/tarstrm.h>
#include <wx/progdlg.h>
#include <wx/dnd.h>
#include <wx/mstream.h>
/////////////
#include <wx/renderer.h>
/*#include <TAGLIBDLL/tag.h>
#include <TAGLIBDLL/fileref.h>
#include <TAGLIBDLL/taglib.h>
#include <TAGLIBDLL/mpegfile.h>
#include <TAGLIBDLL/id3v2tag.h>*/
#include <TAGLIB/tag.h>
#include <TAGLIB/fileref.h>
#include "Musique.h"
#include "DnDCible.h"
//#include "DialogueFenetreExt.h"
#include "GestionPeriph.h"
#include "SliderSon.h"
#include "FichierLog.h"
#include "BDDRequete.h"
#include "BDDThread.h"

extern const wxEventType wxEVT_VIDER_PANNEAU;
extern const wxEventType wxEVT_LISTE_DETAILS;


class ListeLecture : public wxListCtrl
{
    public:
        ListeLecture(wxWindow *Parent);
        virtual ~ListeLecture();
        void MAJ();
        void supprimerNomLigne(ChansonNomPos);
        wxString GetDuree(int);
        int GetPositionChansonLecture();

        void ChansonActive(wxListEvent&);
        void OnKey(wxKeyEvent&);
        void MouseEvents(wxMouseEvent&);
        void Glisser(wxListEvent &WXUNUSED(event));
        void ChangementChanson(ChansonNomPos);
        void AfficheMenu(wxMouseEvent &WXUNUSED(event));

        void menuLecture(wxCommandEvent &WXUNUSED(event));
        void menuPause(wxCommandEvent &WXUNUSED(event));
        void menuSupprimer(wxCommandEvent &WXUNUSED(event));
        void menuCouper(wxCommandEvent &WXUNUSED(event));
        void menuColler(wxCommandEvent &WXUNUSED(event));
        void menuDetails(wxCommandEvent &WXUNUSED(event));

        void SuppressionLigne();

    protected:
        bool m_couper, m_majEnCours, m_supprEnCours;
        wxMenu *m_menu;
        wxArrayString m_tableauCouper;
        wxArrayInt m_ocurrenceLigne;
        long m_yMenu;

        int m_positionChanson;
        Musique *m_musique;

    DECLARE_EVENT_TABLE()
};

#endif // PLAYLISTTABLEAU_H_INCLUDED
