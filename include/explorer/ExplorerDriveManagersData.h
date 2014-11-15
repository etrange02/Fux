#ifndef EXPLORERDRIVEMANAGERSDATA_H
#define EXPLORERDRIVEMANAGERSDATA_H

#include <list>
#include "ExplorerManager.h"
#include "../gui/explorer/DriveManagersPanel.h"

class ExplorerDriveManagersData
{
    public:
        /** Default constructor */
        ExplorerDriveManagersData();
        /** Default destructor */
        virtual ~ExplorerDriveManagersData();

        std::list<ExplorerManager*>* getExplorerManagers();

        DriveManagersPanel* getDriverManagersPanel();
        //void setDriverManagersPanel(DriveManagersPanel* driverManagerPanel);

    protected:
    private:
        std::list<ExplorerManager*> *m_explorerManagers;
        DriveManagersPanel *m_driveManagersPanel;
};

#endif // EXPLORERDRIVEMANAGERSDATA_H
