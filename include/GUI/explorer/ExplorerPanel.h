#ifndef EXPLORERPANEL_H
#define EXPLORERPANEL_H

#include "Define.h"
#include <vector>
#include <wx/wx.h>
#include <wx/statline.h>
#include "explorer/ExplorerListCtrl.h"

extern const wxEventType wxEVT_FUX_EXPLORERLISTCTRL_FOCUS;

class ExplorerManager;

namespace gui
{
    namespace explorer
    {
        class ExplorerPanel : public wxPanel
        {
            public:
                /** Default constructor */
                ExplorerPanel(wxWindow* parent, const wxString& managerName, const wxString& managerDescription);
                /** Default destructor */
                virtual ~ExplorerPanel();

                bool operator==(const ExplorerPanel& other);

                void setExplorerManager(ExplorerManager* explorerManager);

                ExplorerListCtrl& getExplorerListCtrl();

                void onFilterKnownFormatCheckBox(wxCommandEvent&    event);
                void onHiddenFilesCheckBox      (wxCommandEvent&    event);
                void onPreviousButton           (wxCommandEvent&    event);
                void onRefreshButton            (wxCommandEvent&    event);
                void onItemActivatedInListCtrl  (wxCommandEvent&    event);
                void onDragBeginInListCtrl      (wxCommandEvent&    event);
                void onListFocused              (wxChildFocusEvent& event);

                bool isHiddenFilesChecked() const;
                bool isFilterActivated() const;

                void setTexts(const wxString& name, const wxString& description);
                void setTexts();


            protected:
                void create();
                std::vector<unsigned long> getSelectedItems();

            private:
                void sendExplorerListCtrlFocusEvent();

            private:
                wxString m_managerName;
                wxString m_managerDescription;
                ExplorerListCtrl *m_explorerList;
                ExplorerManager *m_explorerManager;

                wxStaticBoxSizer *m_sizer1V;
                wxSizer *m_sizer1H, *m_sizer2H;
                wxTextCtrl *m_pathTextCtrl;
                wxButton *m_refreshButton, *m_previousButton;
                wxCheckBox *m_hiddenFilesCheckBox, *m_filterCheckBox;
        };
    }
}

#endif // EXPLORERPANEL_H
