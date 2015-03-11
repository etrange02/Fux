#ifndef EXPLORERDRIVEMANAGERS_H
#define EXPLORERDRIVEMANAGERS_H

#include <vector>
#include "ExplorerDriveManagersData.h"
#include "DriveManagersPanel.h"

class MenuElementData;

class ExplorerDriveManagers
{
    public:
        static ExplorerDriveManagers& get();

        gui::explorer::DriveManagersPanel *getDriveManagersPanel();
        void setDriveManagersPanel(gui::explorer::DriveManagersPanel* driveManagersPanel);
        void addExplorerManager(gui::explorer::ExplorerPanel& explorerPanel);

        std::vector<MenuElementData> getContainersFiles();
        std::vector<MenuElementData> getDrivers();

        void setDirState     (gui::explorer::ExplorerPanel& explorerPanel, const wxString& path);
        void setPlayListState(gui::explorer::ExplorerPanel& explorerPanel);
        void setFileState    (gui::explorer::ExplorerPanel& explorerPanel, const wxString& path);

        void updateStreamButtonStates();

    protected:
        ExplorerManager& getControllerOf(gui::explorer::ExplorerPanel& explorerPanel);

    private:
        /** Default constructor */
        ExplorerDriveManagers();
        /** Default destructor */
        virtual ~ExplorerDriveManagers();

    private:
        static ExplorerDriveManagers s_explorerDriveManagersInstance;
        ExplorerDriveManagersData m_data;
};

#endif // EXPLORERDRIVEMANAGERS_H
