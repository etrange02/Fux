/***************************************************************
 * Name:      ExplorerDriveManagers.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2014-11-19
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "ExplorerDriveManagers.h"
#include "MenuElementData.h"
#include "Parametre.h"
#include "../predicates/findControllerOfExplorerPanel.h"
#include <wx/volume.h>

ExplorerDriveManagers ExplorerDriveManagers::s_explorerDriveManagersInstance = ExplorerDriveManagers();

ExplorerDriveManagers& ExplorerDriveManagers::get()
{
    return s_explorerDriveManagersInstance;
}

ExplorerDriveManagers::ExplorerDriveManagers()
{
}

ExplorerDriveManagers::~ExplorerDriveManagers()
{
}

gui::explorer::DriveManagersPanel* ExplorerDriveManagers::getDriveManagersPanel()
{
    return m_data.getDriveManagersPanel();
}

void ExplorerDriveManagers::setDriveManagersPanel(gui::explorer::DriveManagersPanel* driveManagersPanel)
{
    m_data.setDriveManagersPanel(driveManagersPanel);
}

void ExplorerDriveManagers::addExplorerManager(gui::explorer::ExplorerPanel& explorerPanel)
{
    m_data.getExplorerManagers().push_back(new ExplorerManager(explorerPanel, *this));
}


std::vector<MenuElementData> ExplorerDriveManagers::getContainersFiles()
{
    std::vector<MenuElementData> elements;
    wxArrayString filenames;
    wxString containerFilesDirectory = Parametre::Get()->getRepertoireParametre(_T("Play_list_M3U"));
    wxDir::GetAllFiles(containerFilesDirectory, &filenames, _T("*.m3u"));

    for (wxArrayString::iterator it = filenames.begin(); it != filenames.end(); ++it)
    {
        MenuElementData data;
        data.setLabel(it->Mid(containerFilesDirectory.Length()+1, it->Length()));
        data.setPath(*it);
        elements.push_back(data);
    }

    return elements;
}

std::vector<MenuElementData> ExplorerDriveManagers::getDrivers()
{
    std::vector<MenuElementData> elements;
    wxArrayString dirNames = wxFSVolume::GetVolumes();

    for (wxArrayString::iterator it = dirNames.begin(); it != dirNames.end(); ++it)
    {
        MenuElementData data;
        wxFSVolume volume(*it);
        data.setLabel(volume.GetDisplayName());
        data.setPath((*it).BeforeLast(wxFileName::GetPathSeparator()));
        elements.push_back(data);
    }

    return elements;
}

void ExplorerDriveManagers::setDirState(gui::explorer::ExplorerPanel& explorerPanel, const wxString& path)
{
    ExplorerManager& manager = getControllerOf(explorerPanel);
    manager.setDirState(path);
}

void ExplorerDriveManagers::setPlayListState(gui::explorer::ExplorerPanel& explorerPanel)
{
    ExplorerManager& manager = getControllerOf(explorerPanel);
    manager.setPlayListState();
}

void ExplorerDriveManagers::setFileState(gui::explorer::ExplorerPanel& explorerPanel, const wxString& path)
{
    ExplorerManager& manager = getControllerOf(explorerPanel);
    manager.setFileState(path);
}

ExplorerManager& ExplorerDriveManagers::getControllerOf(gui::explorer::ExplorerPanel& explorerPanel)
{
    findControllerOfExplorerPanel finder(explorerPanel);
    std::vector<ExplorerManager*>::iterator it = std::find_if(m_data.getExplorerManagers().begin(), m_data.getExplorerManagers().end(), finder);
    if (it != m_data.getExplorerManagers().end())
        return **it;
    else
        throw wxString("No controller found.");
}

void ExplorerDriveManagers::updateStreamButtonStates()
{
}

