#include "../../include/explorer/ExplorerManager.h"

ExplorerManager::ExplorerManager()
{
    Initialize();
}

ExplorerManager::~ExplorerManager()
{
    delete m_data;
}

void ExplorerManager::SetExplorerPanel(ExplorerPanel *explorerPanel)
{
    m_data->SetExplorerPanel(explorerPanel);
}

void ExplorerManager::Initialize()
{
    m_data = new ExplorerManagerData();
}


