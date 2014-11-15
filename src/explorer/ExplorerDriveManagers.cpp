#include "../../include/explorer/ExplorerDriveManagers.h"

static ExplorerDriveManagers* s_explorerDriveManagersInstance = NULL;

ExplorerDriveManagers* ExplorerDriveManagers::getInstance()
{
    if (NULL == s_explorerDriveManagersInstance)
        s_explorerDriveManagersInstance = new ExplorerDriveManagers();
    return s_explorerDriveManagersInstance;
}

ExplorerDriveManagers::ExplorerDriveManagers()
{
    Initialize();
}

ExplorerDriveManagers::~ExplorerDriveManagers()
{
    delete m_data;
}

void ExplorerDriveManagers::Initialize()
{
    m_data = new ExplorerDriveManagersData();
//    m_data->setDriverManagersPanel(new DriveManagersPanel());
}

DriveManagersPanel* ExplorerDriveManagers::getDriverManagersPanel()
{
    return m_data->getDriverManagersPanel();
}


