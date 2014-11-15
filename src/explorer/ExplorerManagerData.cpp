#include "../../include/explorer/ExplorerManagerData.h"

ExplorerManagerData::ExplorerManagerData()
{
    Initialize();
}

ExplorerManagerData::~ExplorerManagerData()
{
    if (NULL != m_menu)
        delete m_menu;
}

void ExplorerManagerData::Initialize()
{
    m_menu = NULL;
    m_explorerPanel = NULL;
}

wxMenu* ExplorerManagerData::GetMenu()
{
    return m_menu;
}

void ExplorerManagerData::SetMenu(wxMenu* menu)
{
    if (NULL == menu)
        return;
    this->m_menu = menu;
}

void ExplorerManagerData::SetExplorerPanel(ExplorerPanel* explorerPanel)
{
    m_explorerPanel = explorerPanel;
}

ExplorerPanel* ExplorerManagerData::GetExplorerPanel()
{
    return m_explorerPanel;
}


