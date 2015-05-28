#ifndef EXPLORERPANEL_H
#define EXPLORERPANEL_H

#include "Define.h"
#include <vector>
#include <wx/wx.h>
#include <wx/statline.h>
#include "explorer/ExplorerListCtrl.h"

extern const wxEventType wxEVT_FUX_EXPLORERLISTCTRL_FOCUS;

namespace explorer {
    class ExplorerManager;
}

namespace gui
{
    namespace explorer
    {
        class DriveManagersPanel;

        class ExplorerPanel : public wxPanel
        {
            public:
                /** Default constructor */
                ExplorerPanel(DriveManagersPanel& managerPanel, const wxString& managerName, const wxString& managerDescription);
                /** Default destructor */
                virtual ~ExplorerPanel();

                bool operator==(const ExplorerPanel& other);

                void setExplorerManager(::explorer::ExplorerManager* explorerManager);

                ExplorerListCtrl& getExplorerListCtrl();

                void onFilterKnownFormatCheckBox(wxCommandEvent&    event);
                void onHiddenFilesCheckBox      (wxCommandEvent&    event);
                void onPreviousButton           (wxCommandEvent&    event);
                void onRefreshButton            (wxCommandEvent&    event);
                void onItemActivatedInListCtrl  (wxCommandEvent&    event);
                void onDragBeginInListCtrl      (wxCommandEvent&    event);
                void onListFocused              (wxChildFocusEvent& event);
                void onRightButtonMouseClicked  (wxMouseEvent&      event);
                void onMenuCreateDir            (wxCommandEvent&    event);
                void onMenuCreateContainerFile  (wxCommandEvent&    event);
                void onMenuCut                  (wxCommandEvent&    event);
                void onMenuCopy                 (wxCommandEvent&    event);
                void onMenuPaste                (wxCommandEvent&    event);
                void onMenuDelete               (wxCommandEvent&    event);
                void onMenuRenameDir            (wxCommandEvent&    event);
                void onMenuCreateShortcut       (wxCommandEvent&    event);
                void onMenuSelectAll            (wxCommandEvent&    event);
                void onMenuPlay                 (wxCommandEvent&    event);

                bool isHiddenFilesChecked() const;
                bool isFilterActivated() const;

                void setTexts(const wxString& name, const wxString& description);
                void setTexts();


            protected:
                void create();

            private:
                void sendExplorerListCtrlFocusEvent();
                void createMenu();
                void enableMenuElements();

            private:
                wxString m_managerName;
                wxString m_managerDescription;
                ExplorerListCtrl* m_explorerList;
                ::explorer::ExplorerManager* m_explorerManager;
                DriveManagersPanel& m_driveManagersPanel;

                wxStaticBoxSizer* m_sizer1V;
                wxSizer* m_sizer1H;
                wxSizer* m_sizer2H;
                wxTextCtrl* m_pathTextCtrl;
                wxButton* m_refreshButton;
                wxButton* m_previousButton;
                wxCheckBox* m_hiddenFilesCheckBox;
                wxCheckBox* m_filterCheckBox;
                wxMenu* m_listMenu;

                wxMenuItem* m_createDirMenuItem;
                wxMenuItem* m_createContainerFileMenuItem;
                wxMenuItem* m_cutMenuItem;
                wxMenuItem* m_copyMenuItem;
                wxMenuItem* m_pasteMenuItem;
                wxMenuItem* m_deleteMenuItem;
                wxMenuItem* m_renameDirMenuItem;
                wxMenuItem* m_createShortcutDirMenuItem;
                wxMenuItem* m_selectAllDirMenuItem;
                wxMenuItem* m_playDirMenuItem;
        };
    }
}

#endif // EXPLORERPANEL_H
