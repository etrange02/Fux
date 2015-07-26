/***************************************************************
 * Name:      ExplorerManager.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2014-11-19
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "explorer/ExplorerManager.h"
#include "explorer/ExplorerFactory.h"
#include "explorer/ExplorerDriveManagers.h"
#include "explorer/state/DriveManagerState.h"
#include "explorer/state/DefaultDriveManagerState.h"

using namespace ::explorer;

ExplorerManager::ExplorerManager(gui::explorer::ExplorerPanel& explorerPanel, ExplorerDriveManagers& explorerDriveManagers) :
    m_data(*(ExplorerFactory::createDefaultDriveManagerState(m_data, false)), explorerPanel, explorerDriveManagers)
{
    m_data.getExplorerPanel().setExplorerManager(this);
}

ExplorerManager::~ExplorerManager()
{
}

void ExplorerManager::setDirState(const wxString& path)
{
    m_data.setPath(path);
    m_data.setState(*(ExplorerFactory::createDirDriveManagerState(m_data)));
    m_data.getState().fillExplorerList();
    m_data.getExplorerDriveManagers().updateStreamButtonStates(m_data.getExplorerPanel());
    m_data.getExplorerPanel().getExplorerListCtrl().SetFocus();
}

void ExplorerManager::setPlayListState()
{
    m_data.setPath("");
    m_data.setState(*(ExplorerFactory::createPlaylistDriveManagerState(m_data)));
    m_data.getState().fillExplorerList();
    m_data.getExplorerDriveManagers().updateStreamButtonStates(m_data.getExplorerPanel());
    m_data.getExplorerPanel().getExplorerListCtrl().SetFocus();
}

void ExplorerManager::setFileState(const wxString& path)
{
    m_data.setPath(path);
    m_data.setState(*(explorer::ExplorerFactory::createFileDriveManagerState(m_data)));
    m_data.getState().fillExplorerList();
    m_data.getExplorerDriveManagers().updateStreamButtonStates(m_data.getExplorerPanel());
    m_data.getExplorerPanel().getExplorerListCtrl().SetFocus();
}

void ExplorerManager::setDefaultState()
{
    m_data.setPath("");
    m_data.setState(*(explorer::ExplorerFactory::createDefaultDriveManagerState(m_data, true)));
    m_data.getState().fillExplorerList();
    m_data.getExplorerDriveManagers().updateStreamButtonStates(m_data.getExplorerPanel());
    m_data.getExplorerPanel().getExplorerListCtrl().SetFocus();
}

void ExplorerManager::refresh()
{
    m_data.getState().fillExplorerList();
    m_data.getExplorerPanel().getExplorerListCtrl().SetFocus();
}

void ExplorerManager::makeParentDir()
{
    DriveManagerState& newState = m_data.getState().getPreviousState();
    m_data.setState(newState);

    const wxString path    = m_data.getPath().BeforeLast(wxFileName::GetPathSeparator());
    const wxString dirName = m_data.getPath().AfterLast (wxFileName::GetPathSeparator());

    m_data.setPath(path);
    m_data.getState().fillExplorerList(dirName);
    m_data.getExplorerDriveManagers().updateStreamButtonStates(m_data.getExplorerPanel());
    m_data.getExplorerPanel().getExplorerListCtrl().SetFocus();
}

void ExplorerManager::openElement()
{
    m_data.getState().openElement();
    m_data.getExplorerDriveManagers().updateStreamButtonStates(m_data.getExplorerPanel());
    m_data.getExplorerPanel().getExplorerListCtrl().SetFocus();
}

gui::explorer::ExplorerPanel& ExplorerManager::getExplorerPanel() const
{
    return m_data.getExplorerPanel();
}

DriveManagerState& ExplorerManager::getState() const
{
    return m_data.getState();
}

dragAndDrop::TransitiveData* ExplorerManager::getDraggedElements()
{
    return getState().getDraggedElements();
}

