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
#include "MusicManagerSwitcher.h"

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

bool DirDriveManagerState::isDirectory()
{
    return true;
}

bool DirDriveManagerState::fillExplorerList()
{
    if (!wxDirExists(m_data.getPath()))
        return false;

    bool cont = true;
    const bool hidden = m_data.getExplorerPanel().isHiddenFilesChecked();
    const bool filtre = m_data.getExplorerPanel().isFilterActivated();
    wxString filename;
    wxDir repertoire(m_data.getPath());

    m_data.getExplorerPanel().getExplorerListCtrl().DeleteAllItems();
    m_data.getElements().clear();

    //Dossiers
    cont = (hidden) ? repertoire.GetFirst(&filename, wxEmptyString, wxDIR_DIRS | wxDIR_HIDDEN) : repertoire.GetFirst(&filename, wxEmptyString, wxDIR_DIRS);
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

void DirDriveManagerState::openElement(const std::vector<long>& indexes)
{
    const wxString& path = m_data.getElements().at(indexes.at(0)).getFilename();

    if (Parametre::get().isID3V2(path))
    {
        MusicManagerSwitcher::get().parse(convertPositionToString(indexes));
        MusicManagerSwitcher::get().playMusic(path);
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

