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
#include "predicates/findControllerOfExplorerPanel.h"
#include <wx/volume.h>
#include "DriveManagerState.h"

using namespace explorer;

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

::explorer::ExplorerManager& ExplorerDriveManagers::getControllerOf(gui::explorer::ExplorerPanel& explorerPanel)
{
    findControllerOfExplorerPanel finder(explorerPanel);
    std::vector<ExplorerManager*>::iterator it = std::find_if(m_data.getExplorerManagers().begin(), m_data.getExplorerManagers().end(), finder);
    if (it != m_data.getExplorerManagers().end())
        return **it;
    else
        throw wxString("No controller found.");
}

void ExplorerDriveManagers::updateStreamButtonStates(gui::explorer::ExplorerPanel& explorerPanel)
{
    const bool isFirst = ( explorerPanel == m_data.getExplorerManagers().at(0)->getExplorerPanel() );
    ExplorerManager& focusedEM = getControllerOf(explorerPanel);
    ExplorerManager& other = *m_data.getExplorerManagers().at(isFirst ? 1 : 0);

    m_data.getDriveManagersPanel()->enableButtonCopy     (!focusedEM.getState().isDefault() && !other.getState().isDefault());
    m_data.getDriveManagersPanel()->enableButtonDelete   (!focusedEM.getState().isDefault());
    m_data.getDriveManagersPanel()->enableButtonMoveLeft (   !isFirst
                                                          && !focusedEM.getState().isDefault()
                                                          &&  focusedEM.getState().isSameKind(other.getState())
                                                         );
    m_data.getDriveManagersPanel()->enableButtonMoveRight( isFirst
                                                          && !focusedEM.getState().isDefault()
                                                          &&  focusedEM.getState().isSameKind(other.getState())
                                                         );
}

void ExplorerDriveManagers::deleteSelectedLines(gui::explorer::ExplorerPanel& explorerPanel)
{
    ExplorerManager& manager = getControllerOf(explorerPanel);
    manager.getState().deleteSelectedItems();
}

void ExplorerDriveManagers::copySelectedLines(gui::explorer::ExplorerPanel& sourceExplorerPanel, gui::explorer::ExplorerPanel& destinationExplorerPanel)
{
    ExplorerManager& source = getControllerOf(sourceExplorerPanel);
    ExplorerManager& destination = getControllerOf(destinationExplorerPanel);
    if (!source.getState().canCopyTo(destination.getState()))
        return;

    destination.getState().copyElements(source.getState());
}

void ExplorerDriveManagers::moveSelectedLines(gui::explorer::ExplorerPanel& sourceExplorerPanel, gui::explorer::ExplorerPanel& destinationExplorerPanel)
{
    ExplorerManager& source = getControllerOf(sourceExplorerPanel);
    ExplorerManager& destination = getControllerOf(destinationExplorerPanel);
    if (!source.getState().canMoveTo(destination.getState()))
        return;

    destination.getState().moveElements(source.getState());
}

