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
        void updateLines();
        void removeLine(const long position);
        void removeSelectedLines();
        wxString getDuration(int);

        void onActiveLineEvent  (wxListEvent&);
        void onKeyboardEvent    (wxKeyEvent&);
        void onMouseEvent       (wxMouseEvent&);
        void onDragEvent        (wxListEvent&    WXUNUSED(event));
        void onDisplayMenu      (wxMouseEvent&   WXUNUSED(event));

        void onMenuEventPlay    (wxCommandEvent& WXUNUSED(event));
        void onMenuEventPause   (wxCommandEvent& WXUNUSED(event));
        void onMenuEventDelete  (wxCommandEvent& WXUNUSED(event));
        void onMenuEventCut     (wxCommandEvent& WXUNUSED(event));
        void onMenuEventPaste   (wxCommandEvent& WXUNUSED(event));
        void onMenuEventDetails (wxCommandEvent& WXUNUSED(event));
        /** Event - Adds a music line in the list */
        void onUpdateLine(wxCommandEvent& event);
        /** Event - Adds a music line in the list */
        void onDeleteLine(wxCommandEvent& event);
        void updateColors();


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

        std::vector<unsigned long> getSelectedLines();

    private:
        wxMutex m_mutexListUpdating;
        wxArrayString m_cutTitles;
        wxArrayInt m_similarLinesOccurences;
        bool m_cut;
        wxMenu *m_menu;
        long m_yMenu;

    DECLARE_EVENT_TABLE()
};

#endif // PLAYLISTTABLEAU_H_INCLUDED
