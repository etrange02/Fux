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

using namespace explorer;

DirDriveManagerState::DirDriveManagerState(ExplorerManagerData& data) :
    DriveManagerState(data)
{
    //ctor
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
    return *(explorer::ExplorerFactory::createDefaultDriveManagerState(m_data));
}

void DirDriveManagerState::openElement(const std::vector<unsigned long>& indexes)
{
    const wxString& path = m_data.getElements().at(indexes.at(0)).getFilename();

    if (Parametre::get().isID3V2(path))
    {
        MusicManagerSwitcher::get().parse(convertPositionToString(indexes));
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

void DirDriveManagerState::copyElements(DriveManagerState& source)
{
    // insertion de nouveaux fichiers dans le dossier courant -> thread
}

void DirDriveManagerState::moveElements(DriveManagerState& source)
{
    // renommage de fichiers (changement de chemin) d'une r�pertoire � l'autre
}

