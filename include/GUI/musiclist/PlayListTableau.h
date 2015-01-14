#ifndef PLAYLISTTABLEAU_H_INCLUDED
#define PLAYLISTTABLEAU_H_INCLUDED

#include "../../Define.h"
#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include <wx/listctrl.h>
#include <wx/tarstrm.h>
#include <wx/progdlg.h>
#include <wx/dnd.h>
#include <wx/mstream.h>
#include <wx/renderer.h>
#include "../../music/MusicManager.h"
#include "../../tools/dnd/DnDCible.h"
#include "../explorer/GestionPeriph.h"
#include "../widgets/SliderSon.h"
#include "../../tools/FichierLog.h"
#include "../../db/BDDRequete.h"
#include "../../db/BDDThread.h"

extern const wxEventType wxEVT_VIDER_PANNEAU;
extern const wxEventType wxEVT_LISTE_DETAILS;


class PlayListTableau : public wxListCtrl
{
    public:
        PlayListTableau(wxWindow *Parent);
        virtual ~PlayListTableau();
        void MAJ();
        void removeLine(const int position);
        wxString GetDuration(int);

        void ChansonActive(wxListEvent&);
        void OnKey(wxKeyEvent&);
        void MouseEvents(wxMouseEvent&);
        void Glisser(wxListEvent &WXUNUSED(event));
        void AfficheMenu(wxMouseEvent &WXUNUSED(event));

        void menuLecture(wxCommandEvent &WXUNUSED(event));
        void menuPause(wxCommandEvent &WXUNUSED(event));
        void menuSupprimer(wxCommandEvent &WXUNUSED(event));
        void menuCouper(wxCommandEvent &WXUNUSED(event));
        void menuColler(wxCommandEvent &WXUNUSED(event));
        void menuDetails(wxCommandEvent &WXUNUSED(event));
        /** Event - Adds a music line in the list */
        void onUpdateLine(wxCommandEvent& event);
        void updateColors();

        void SuppressionLigne();

    protected:
        /** Adds a line at the end of the list */
        void addLine(Music& music);
        /** Adds a line at the specified position */
        void addLine(Music& music, const int position);
        /** Adds a line at the specified position */
        void addLineThread(Music& music, const int position);
        /** Modifies a line in the list */
        void modifyLine(Music& music, const int position);

        void updateColor(const size_t position);
        void updateColorNormalMode(const size_t position);
        void updateColorSearchMode(const size_t position);
        void setDefaultColor(const size_t position);

    private:
        bool m_couper;
        wxMenu *m_menu;
        wxArrayString m_tableauCouper;
        wxArrayInt m_ocurrenceLigne;
        long m_yMenu;

        int m_positionChanson;

    DECLARE_EVENT_TABLE()
};

#endif // PLAYLISTTABLEAU_H_INCLUDED