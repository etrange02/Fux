/***************************************************************
 * Name:      FileDriveManagerState.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2014-11-19
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "explorer/state/FileDriveManagerState.h"
#include "MusicManagerSwitcher.h"
#include <wx/textfile.h>
#include "explorer/ExplorerManagerData.h"
#include "explorer/ExplorerFactory.h"
#include "tools/dnd/dataObjects/ContainerFileTransitiveData.h"
#include "tools/dnd/targets/ContainerFileTransitiveDataTarget.h"

using namespace explorer;
using namespace ::music;

FileDriveManagerState::FileDriveManagerState(ExplorerManagerData& data) :
    DriveManagerState(data)
{
    gui::explorer::ExplorerListCtrl& listCtrl = data.getExplorerPanel().getExplorerListCtrl();
    listCtrl.SetDropTarget(new dragAndDrop::ContainerFileTransitiveDataTarget(listCtrl, *this));
}

FileDriveManagerState::~FileDriveManagerState()
{
    //dtor
}

bool FileDriveManagerState::isFile() const
{
    return true;
}

bool FileDriveManagerState::fillExplorerList()
{
    wxTextFile file(m_data.getPath());
    if (!file.Exists() || !file.Open())
        return false;

    wxString filename;
    const size_t max = file.GetLineCount();

    m_data.getExplorerPanel().getExplorerListCtrl().DeleteAllItems();
    m_data.getElements().clear();

    const int start = 1;

    for (size_t i = start; i < max; i++)
    {
        filename = file.GetLine(i);

        if (wxFileExists(filename))
            m_data.getExplorerPanel().getExplorerListCtrl().addFile(filename);
        else
            m_data.getExplorerPanel().getExplorerListCtrl().addInexistantFile(filename);
        addDriveManagerListElement(filename);
    }
    file.Close();

    m_data.getExplorerPanel().setTexts("Fichier m3u", m_data.getPath());
    //SetFocus();
    //wxCommandEvent evt(wxEVT_LISTE_RENEW);
    //GetParent()->GetEventHandler()->AddPendingEvent(evt);
    return true;
}

bool FileDriveManagerState::fillExplorerList(const wxString& elementToSelect)
{
    fillExplorerList();
    return true;
}

DriveManagerState& FileDriveManagerState::getPreviousState()
{
    return *(explorer::ExplorerFactory::createDirDriveManagerState(m_data));
}

void FileDriveManagerState::openElement()
{
    std::vector<unsigned long> indexes = m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines();
    if (indexes.empty() || indexes.at(0) >= m_data.getElements().size())
        return;

    MusicManagerSwitcher::get().parse(convertPositionToString(indexes));
}

void FileDriveManagerState::deleteSelectedItems()
{
    wxTextFile file(m_data.getPath());
    if (!file.Exists() || !file.Open())
        return;

    const long startPosition = 1;
    std::vector<unsigned long> selectedItemsPosition = m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines();

    for (std::vector<unsigned long>::reverse_iterator iter = selectedItemsPosition.rbegin(); iter != selectedItemsPosition.rend(); ++iter)
    {
        file.RemoveLine(startPosition + *iter);
        m_data.getElements().erase(m_data.getElements().begin() + *iter);
    }
    m_data.getExplorerPanel().getExplorerListCtrl().removeSelectedLines();

    file.Write();
    file.Close();
    fillExplorerList();
}

bool FileDriveManagerState::canCopyTo(const DriveManagerState& other) const
{
    return true;
}

bool FileDriveManagerState::canMoveTo(const DriveManagerState& other) const
{
    return true;
}

bool FileDriveManagerState::canDeleteSelectedItems() const
{
    return !m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines().empty();
}

bool FileDriveManagerState::canSelectAll() const
{
    return true;
}

bool FileDriveManagerState::canCreateDir() const
{
    return 0 != m_data.getExplorerPanel().getExplorerListCtrl().GetItemCount();
}

bool FileDriveManagerState::canCreateContainerFile() const
{
    return !m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines().empty();;
}

bool FileDriveManagerState::canPlayItems() const
{
    return !m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines().empty();
}

bool FileDriveManagerState::canRename() const
{
    return false;
}

bool FileDriveManagerState::canCreateShortcut() const
{
    return false;
}

void FileDriveManagerState::copyElements(DriveManagerState& source)
{
    wxTextFile file(m_data.getPath());
    if (!file.Exists() || !file.Open())
        return;

    wxArrayString selectedItems = source.getSelectedItems();

    for (wxArrayString::iterator iter = selectedItems.begin(); iter != selectedItems.end(); ++iter)
    {
        file.AddLine(*iter);
    }

    file.Write();
    file.Close();

    fillExplorerList();
}

void FileDriveManagerState::moveElements(DriveManagerState& source)
{
    wxArrayString selectedItems = source.getSelectedItems();
    source.deleteSelectedItems();

    std::vector<unsigned long> selectedItemsPosition = m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines();

    long position = (selectedItemsPosition.empty()) ? -1 : selectedItemsPosition.at(0);

    insertElements(selectedItems, position);
    fillExplorerList();
}

void FileDriveManagerState::insertElements(const wxArrayString& filenames, long position)
{
    wxTextFile file(m_data.getPath());
    if (!file.Exists() || !file.Open())
        return;

    if (-1 == position)
        position = file.GetLineCount();

    const long startPosition = 1;

    for (wxArrayString::const_iterator iter = filenames.begin(); iter != filenames.end(); ++iter, ++position)
        file.InsertLine(*iter, position + startPosition);

    file.Write();
    file.Close();
    fillExplorerList();
}

void FileDriveManagerState::createDir()
{
    wxLogMessage("Must be implemented.");
}

void FileDriveManagerState::createContainerFile()
{
    wxLogMessage("Must be implemented.");
}

void FileDriveManagerState::playItems()
{
    wxLogMessage("Must be implemented.");
}

void FileDriveManagerState::rename()
{
    wxLogMessage("Must be implemented.");
}

void FileDriveManagerState::createShortcut()
{
    wxLogMessage("Must be implemented.");
}

dragAndDrop::TransitiveData* FileDriveManagerState::getDraggedElements()
{
    dragAndDrop::ContainerFileTransitiveData* transitiveData = new dragAndDrop::ContainerFileTransitiveData(*this);
    std::vector<unsigned long> positions = m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines();

    transitiveData->add(positions);
    transitiveData->setFilename(m_data.getPath());

    return transitiveData;
}



