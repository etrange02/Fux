#ifndef EXPLORERDRIVEMANAGERSDATA_H
#define EXPLORERDRIVEMANAGERSDATA_H

#include <vector>
#include "ExplorerManager.h"
#include "DriveManagersPanel.h"

namespace tools {
    namespace dir {
        class DirFileManager;
    }
}

/**
 * Explorer name space.
 */
namespace explorer
{
    class ExplorerDriveManagersData
    {
        public:
            /** Default constructor */
            ExplorerDriveManagersData();
            /** Default destructor */
            virtual ~ExplorerDriveManagersData();

            std::vector<ExplorerManager*>& getExplorerManagers() const;

            gui::explorer::DriveManagersPanel* getDriveManagersPanel();
            void setDriveManagersPanel(gui::explorer::DriveManagersPanel* driverManagerPanel);

            tools::dir::DirFileManager* getDirFileManager();
            void setDirFileManager(tools::dir::DirFileManager* dirFileManager);

        protected:
        private:
            std::vector<ExplorerManager*> *m_explorerManagers;
            gui::explorer::DriveManagersPanel *m_driveManagersPanel;
            tools::dir::DirFileManager* m_dirFileManager;
    };
}

#endif // EXPLORERDRIVEMANAGERSDATA_H
