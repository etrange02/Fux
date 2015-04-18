#ifndef DRIVEMANAGERSPANEL_H
#define DRIVEMANAGERSPANEL_H

#include <vector>
#include <wx/wx.h>
#include <wx/menu.h>
#include "explorer/MenuElement.h"

namespace explorer
{
    class ExplorerDriveManagers;
}

namespace gui
{
    namespace explorer
    {
        class ExplorerPanel;

        class DriveManagersPanel : public wxPanel
        {
            public:
                /** Default constructor */
                DriveManagersPanel(wxWindow *parent, ::explorer::ExplorerDriveManagers& explorerDriveManagers);
                /** Default destructor */
                virtual ~DriveManagersPanel();

                void onFocusChanged     (wxCommandEvent& event);
                void onButtonMyDocuments(wxCommandEvent& event);
                void onButtonDrivers    (wxCommandEvent& event);
                void onButtonOthers     (wxCommandEvent& event);

                void onMenuItemMyDocumentsLeftSelected    (wxCommandEvent& event);
                void onMenuItemMyDocumentsRightSelected   (wxCommandEvent& event);
                void onMenuItemPlayListLeftSelected       (wxCommandEvent& event);
                void onMenuItemPlayListRightSelected      (wxCommandEvent& event);
                void onMenuItemDriversLeftSelected        (wxCommandEvent& event);
                void onMenuItemDriversRightSelected       (wxCommandEvent& event);
                void onMenuItemContainerFilesLeftSelected (wxCommandEvent& event);
                void onMenuItemContainerFilesRightSelected(wxCommandEvent& event);

                void onButtonDelete   (wxCommandEvent& event);
                void onButtonCopy     (wxCommandEvent& event);
                void onButtonMoveLeft (wxCommandEvent& event);
                void onButtonMoveRight(wxCommandEvent& event);

                void enableButtonDelete   (const bool enable);
                void enableButtonCopy     (const bool enable);
                void enableButtonMoveLeft (const bool enable);
                void enableButtonMoveRight(const bool enable);

            protected:
            private:
                void Initialize(wxWindow *parent);
                ExplorerPanel* createNewExplorerPanel(const wxString& managerName, const wxString& managerDescription);
                void createMenus();
                void fillDriversMenu();
                void fillContainerFilesMenu();
                void emptyMenu(wxMenu& menu, std::vector<::explorer::MenuElement>& menuElements);
                void fillMenu (wxMenu& menu, std::vector<::explorer::MenuElement>& menuElements);
                void mergeAndMarkPresentMenuElements(std::vector<::explorer::MenuElement>& menuElements,
                                                     std::vector<::explorer::MenuElementData> menuElementData,
                                                     void (DriveManagersPanel::*funcMappingLeft)(wxCommandEvent&),
                                                     void (DriveManagersPanel::*funcMappingRight)(wxCommandEvent&) );

                ::explorer::MenuElement& getMenuElementById(std::vector<::explorer::MenuElement>& menuElements, const int id);

            private:
                std::vector<::explorer::MenuElement> m_driversMenuElement;
                std::vector<::explorer::MenuElement> m_containerFilesMenuElement;

                ::explorer::ExplorerDriveManagers& m_explorerDriveManagers;
                ExplorerPanel* m_leftExplorerPanels;
                ExplorerPanel* m_rightExplorerPanels;
                ExplorerPanel* m_focusedExplorerPanel;

                wxButton* m_streamButton;
                wxMenu*   m_myDocumentsMenu;
                wxMenu*   m_driversMenu;
                wxMenu*   m_otherMenu;
                wxMenu*   m_containerFilesMenu;

                enum STREAM_BUTTON_KIND {
                    STREAM_MOVE_LEFT,
                    STREAM_COPY,
                    STREAM_MOVE_RIGHT,
                    STREAM_DELETE
                    };

            DECLARE_EVENT_TABLE();
        };
    }
}

#endif // DRIVERMANAGERSPANEL_H
