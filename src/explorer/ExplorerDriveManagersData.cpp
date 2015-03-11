/***************************************************************
 * Name:      ExplorerDriveManagersData.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2014-11-19
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "explorer/ExplorerDriveManagersData.h"
#include <algorithm>

bool deleteAll(ExplorerManager* item) {delete item; return true;}

ExplorerDriveManagersData::ExplorerDriveManagersData() :
    m_driveManagersPanel(NULL)
{
    m_explorerManagers = new std::vector<ExplorerManager*>();
}

ExplorerDriveManagersData::~ExplorerDriveManagersData()
{
    std::remove_if(m_explorerManagers->begin(), m_explorerManagers-> end(), deleteAll);
    delete m_explorerManagers;
}

gui::explorer::DriveManagersPanel* ExplorerDriveManagersData::getDriveManagersPanel()
{
    return m_driveManagersPanel;
}

void ExplorerDriveManagersData::setDriveManagersPanel(gui::explorer::DriveManagersPanel* driveManagersPanel)
{
    m_driveManagersPanel = driveManagersPanel;
}

std::vector<ExplorerManager*>& ExplorerDriveManagersData::getExplorerManagers() const
{
    return *m_explorerManagers;
}

