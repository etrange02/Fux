/***************************************************************
 * Name:      DirDriveManagerState.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2014-11-19
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "explorer/state/DirDriveManagerState.h"
#include <wx/dir.h>
#include "Parametre.h"
#include "explorer/ExplorerFactory.h"
#include "explorer/ExplorerManagerData.h"
#include "music/MusicManagerSwitcher.h"
#include "tools/thread/ThreadManager.h"
#include "tools/thread/ThreadFactory.h"
#include "tools/dnd/dataObjects/DirTransitiveData.h"
#include "tools/dnd/targets/DirTransitiveDataTarget.h"

using namespace explorer;

DirDriveManagerState::DirDriveManagerState(ExplorerManagerData& data) :
    DriveManagerState(data)
{
    gui::explorer::ExplorerListCtrl& listCtrl = data.getExplorerPanel().getExplorerListCtrl();
    listCtrl.SetDropTarget(new dragAndDrop::DirTransitiveDataTarget(listCtrl));
}

DirDriveManagerState::~DirDriveManagerState()
{
    //dtor
}

bool DirDriveManagerState::isDirectory() const
{
    return true;
}

bool DirDriveManagerState::fillExplorerList()
{
    if (!wxDirExists(m_data.getPath()))
        return false;

    const bool hidden = m_data.getExplorerPanel().isHiddenFilesChecked();
    const bool filtre = m_data.getExplorerPanel().isFilterActivated();
    wxString filename;
    wxDir repertoire(m_data.getPath());

    m_data.getExplorerPanel().getExplorerListCtrl().DeleteAllItems();
    m_data.getElements().clear();

    //Dossiers
    bool cont = (hidden) ? repertoire.GetFirst(&filename, wxEmptyString, wxDIR_DIRS | wxDIR_HIDDEN) : repertoire.GetFirst(&filename, wxEmptyString, wxDIR_DIRS);
    while (cont)
    {
        addDriveManagerListElement(repertoire.GetNameWithSep() + filename);
        m_data.getExplorerPanel().getExplorerListCtrl().addDir(filename);
        cont = repertoire.GetNext(&filename);
    }

    //Fichiers
    cont = (hidden) ? repertoire.GetFirst(&filename, wxEmptyString, wxDIR_FILES | wxDIR_HIDDEN) : repertoire.GetFirst(&filename, wxEmptyString, wxDIR_FILES);
    if (filtre)
    {
        while (cont)
        {
            if (Parametre::Get()->islisable(filename) || Parametre::get().isContainerFile(filename))
            {
                addDriveManagerListElement(repertoire.GetNameWithSep() + filename);
                m_data.getExplorerPanel().getExplorerListCtrl().addFile(filename);
            }
            cont = repertoire.GetNext(&filename);
        }
    }
    else
    {
        while (cont)
        {
            addDriveManagerListElement(repertoire.GetNameWithSep() + filename);
            m_data.getExplorerPanel().getExplorerListCtrl().addFile(filename);
            cont = repertoire.GetNext(&filename);
        }
    }
    //m_data.getExplorerPanel().getExplorerListCtrl().selectLine(0);
    m_data.getExplorerPanel().setTexts("Dossier", m_data.getPath());

    //SetFocus();
    //wxCommandEvent evt(wxEVT_LISTE_RENEW);
    //GetParent()->GetEventHandler()->AddPendingEvent(evt);
    return true;
}

bool DirDriveManagerState::fillExplorerList(const wxString& elementToSelect)
{
    bool result = fillExplorerList();
    m_data.getExplorerPanel().getExplorerListCtrl().selectLine(elementToSelect);
    return result;
}

DriveManagerState& DirDriveManagerState::getPreviousState()
{
    const wxString path = m_data.getPath().BeforeLast(wxFileName::GetPathSeparator());
    if (wxDirExists(path))
        return *this;
    return *(explorer::ExplorerFactory::createDefaultDriveManagerState(m_data, true));
}

void DirDriveManagerState::openElement()
{
    std::vector<unsigned long> indexes = m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines();
    if (indexes.empty() || indexes.at(0) >= m_data.getElements().size())
        return;

    const wxString& path = m_data.getElements().at(indexes.at(0)).getFilename();

    if (Parametre::get().isID3V2(path))
    {
        music::MusicManagerSwitcher::get().parse(convertPositionToString(indexes));
        //MusicManagerSwitcher::get().playMusic(path);
    }
    else if (Parametre::get().isContainerFile(path))
    {
        explorer::DriveManagerState& newState = *(explorer::ExplorerFactory::createFileDriveManagerState(m_data));
        m_data.setPath(path);
        newState.fillExplorerList();
        m_data.setState(newState);
    }
    else
    {
        m_data.setPath(path);
        fillExplorerList();
    }
}

void DirDriveManagerState::deleteSelectedItems()
{
    tools::thread::ThreadManager::get().addRunnable(tools::thread::ThreadFactory::createFileDeletionThread(getSelectedItems()));
}

bool DirDriveManagerState::canCopyTo(const DriveManagerState& other) const
{
    return !this->getPath().IsSameAs(other.getPath());
}

bool DirDriveManagerState::canMoveTo(const DriveManagerState& other) const
{
    return other.isDirectory() && !this->getPath().IsSameAs(other.getPath());
}

bool DirDriveManagerState::canDeleteSelectedItems() const
{
    return !m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines().empty();
}

bool DirDriveManagerState::canSelectAll() const
{
    return true;
}

bool DirDriveManagerState::canCreateDir() const
{
    return true;
}

bool DirDriveManagerState::canCreateContainerFile() const
{
    return true;
}

bool DirDriveManagerState::canPlayItems() const
{
    return !m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines().empty();
}

bool DirDriveManagerState::canRename() const
{
    return !m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines().empty();
}

bool DirDriveManagerState::canCreateShortcut() const
{
    return !m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines().empty();
}

void DirDriveManagerState::copyElements(DriveManagerState& source)
{
    wxLogMessage("Must be implemented.");
    // insertion de nouveaux fichiers dans le dossier courant -> thread
}

void DirDriveManagerState::moveElements(DriveManagerState& source)
{
    wxLogMessage("Must be implemented.");
    // renommage de fichiers (changement de chemin) d'une répertoire à l'autre
    // Attention au changement de lecteur. Le move peut être plus long que prévu dans ce cas.
}

void DirDriveManagerState::createDir()
{
    wxLogMessage("Must be implemented.");
}

void DirDriveManagerState::createContainerFile()
{
    wxLogMessage("Must be implemented.");
}

void DirDriveManagerState::playItems()
{
    wxLogMessage("Must be implemented.");
}

void DirDriveManagerState::rename()
{
    wxLogMessage("Must be implemented.");
}

void DirDriveManagerState::createShortcut()
{
    wxLogMessage("Must be implemented.");
}

dragAndDrop::TransitiveData* DirDriveManagerState::getDraggedElements()
{
    dragAndDrop::DirTransitiveData* transitiveData = new dragAndDrop::DirTransitiveData;
    wxArrayString selectedLines = getSelectedItems();
    for (wxArrayString::iterator it = selectedLines.begin(); it != selectedLines.end(); ++it)
        transitiveData->add(*it);

    return transitiveData;
}


