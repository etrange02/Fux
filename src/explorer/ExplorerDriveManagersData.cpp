#include "../../include/explorer/ExplorerDriveManagersData.h"

ExplorerDriveManagersData::ExplorerDriveManagersData()
{
    m_explorerManagers = new std::list<ExplorerManager*>();
}

ExplorerDriveManagersData::~ExplorerDriveManagersData()
{
    for (std::list<ExplorerManager*>::iterator iter = m_explorerManagers->begin(); iter != m_explorerManagers->end(); ++iter)
    {
        delete *iter;
    }
    delete m_explorerManagers;
}

DriveManagersPanel* ExplorerDriveManagersData::getDriverManagersPanel()
{
    return m_driveManagersPanel;
}

std::list<ExplorerManager*>* ExplorerDriveManagersData::getExplorerManagers()
{
    return m_explorerManagers;
}

