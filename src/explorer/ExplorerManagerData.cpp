/***************************************************************
 * Name:      ExplorerManagerData.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2014-11-19
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "ExplorerManagerData.h"
#include "DriveManagerState.h"
#include "explorer/ExplorerDriveManagers.h"

ExplorerManagerData::ExplorerManagerData(explorer::DriveManagerState& state, gui::explorer::ExplorerPanel& explorer, ExplorerDriveManagers& explorerDriveManagers) :
    m_state(&state),
    m_explorerPanel(explorer),
    m_menu(NULL),
    m_explorerDriveManagers(explorerDriveManagers)
{
}

ExplorerManagerData::~ExplorerManagerData()
{
    delete m_menu;
    delete m_state;
}

gui::explorer::ExplorerPanel& ExplorerManagerData::getExplorerPanel() const
{
    return m_explorerPanel;
}

wxMenu* ExplorerManagerData::GetMenu() const
{
    return m_menu;
}

void ExplorerManagerData::SetMenu(wxMenu* menu)
{
    if (NULL == menu)
        return;
    m_menu = menu;
}

void ExplorerManagerData::setState(explorer::DriveManagerState& state)
{
    if (m_state == &state)
        return;
    delete m_state;
    m_state = &state;
}

explorer::DriveManagerState& ExplorerManagerData::getState() const
{
    return *m_state;
}

void ExplorerManagerData::setPath(const wxString& path)
{
    m_path = path;
}

const wxString& ExplorerManagerData::getPath() const
{
    return m_path;
}

std::vector<DriveManagerListElement>& ExplorerManagerData::getElements()
{
    return m_elements;
}

ExplorerDriveManagers& ExplorerManagerData::getExplorerDriveManagers() const
{
    return m_explorerDriveManagers;
}

