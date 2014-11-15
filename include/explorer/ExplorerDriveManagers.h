#ifndef EXPLORERDRIVEMANAGERS_H
#define EXPLORERDRIVEMANAGERS_H

#include "ExplorerDriveManagersData.h"
#include "../gui/explorer/DriveManagersPanel.h"

class ExplorerDriveManagers
{
    public:
        static ExplorerDriveManagers* getInstance();

        DriveManagersPanel *getDriverManagersPanel();

    protected:

    private:
        /** Default constructor */
        ExplorerDriveManagers();
        /** Default destructor */
        virtual ~ExplorerDriveManagers();
        void Initialize();

        ExplorerDriveManagersData *m_data;
};

#endif // EXPLORERDRIVEMANAGERS_H
