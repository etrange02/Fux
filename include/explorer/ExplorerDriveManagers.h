#ifndef EXPLORERDRIVEMANAGERS_H
#define EXPLORERDRIVEMANAGERS_H

#include <vector>
#include "ExplorerDriveManagersData.h"
#include "DriveManagersPanel.h"


/**
 * Explorer name space.
 */
namespace explorer
{
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

            bool canCopySelectedLines(gui::explorer::ExplorerPanel& sourceExplorerPanel);
            bool canMoveSelectedLines(gui::explorer::ExplorerPanel& sourceExplorerPanel);
            void deleteSelectedLines(gui::explorer::ExplorerPanel& explorerPanel);
            void copySelectedLines  (gui::explorer::ExplorerPanel& sourceExplorerPanel, gui::explorer::ExplorerPanel& destinationExplorerPanel);
            void moveSelectedLines  (gui::explorer::ExplorerPanel& sourceExplorerPanel, gui::explorer::ExplorerPanel& destinationExplorerPanel);

            void updateStreamButtonStates(gui::explorer::ExplorerPanel& explorerPanel);

        protected:
            ExplorerManager& getControllerOf(gui::explorer::ExplorerPanel& explorerPanel);
            ExplorerManager& getOppositeExplorerManager(gui::explorer::ExplorerPanel& explorerPanel);
            ExplorerManager& getOppositeExplorerManager(explorer::ExplorerManager& explorerManager);

        private:
            /** Default constructor */
            ExplorerDriveManagers();
            /** Default destructor */
            virtual ~ExplorerDriveManagers();

        private:
            static ExplorerDriveManagers s_explorerDriveManagersInstance;
            ExplorerDriveManagersData m_data;
    };
}

#endif // EXPLORERDRIVEMANAGERS_H
