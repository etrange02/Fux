#ifndef EXPLORERDRIVEMANAGERSDATA_H
#define EXPLORERDRIVEMANAGERSDATA_H

#include <vector>
#include "ExplorerManager.h"
#include "DriveManagersPanel.h"

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

    protected:
    private:
        std::vector<ExplorerManager*> *m_explorerManagers;
        gui::explorer::DriveManagersPanel *m_driveManagersPanel;
};

#endif // EXPLORERDRIVEMANAGERSDATA_H
