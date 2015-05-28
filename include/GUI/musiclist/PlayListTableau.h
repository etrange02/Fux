#ifndef PLAYLISTTABLEAU_H_INCLUDED
#define PLAYLISTTABLEAU_H_INCLUDED

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/thread.h>

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
        void addLine(music::IMusic& music);
        /** Adds a line at the specified position */
        void addLine(music::IMusic& music, const int position);
        /** Adds a line at the specified position */
        void addLineThread(music::IMusic& music, const int position);
        /** Modifies a line in the list */
        void modifyLine(music::IMusic& music, const int position);

        void updateColor(const size_t position);
        void updateColorNormalMode(const size_t position);
        void updateColorSearchMode(const size_t position);
        void setDefaultColor(const size_t position);

    private:
        wxMutex m_mutexMAJPlaylist;
        wxArrayString m_tableauCouper;
        wxArrayInt m_ocurrenceLigne;
        bool m_couper;
        wxMenu *m_menu;
        long m_yMenu;

        int m_positionChanson;

    DECLARE_EVENT_TABLE()
};

#endif // PLAYLISTTABLEAU_H_INCLUDED
