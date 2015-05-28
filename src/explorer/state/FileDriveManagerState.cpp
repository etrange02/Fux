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

using namespace explorer;
using namespace ::music;

FileDriveManagerState::FileDriveManagerState(ExplorerManagerData& data) :
    DriveManagerState(data)
{
    //ctor
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

    m_data.getExplorerPanel().setTexts("Ficher m3u", m_data.getPath());
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

void FileDriveManagerState::openElement(const std::vector<unsigned long>& indexes)
{
    MusicManagerSwitcher::get().parse(convertPositionToString(indexes));
}

void FileDriveManagerState::deleteSelectedItems()
{
    wxTextFile file(m_data.getPath());
    if (!file.Exists() || !file.Open())
        return;

    const int start = 1;
    std::vector<unsigned long> selectedItemsPosition = m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines();

    for (std::vector<unsigned long>::reverse_iterator iter = selectedItemsPosition.rbegin(); iter != selectedItemsPosition.rend(); ++iter)
    {
        file.RemoveLine(start + *iter);
        m_data.getElements().erase(m_data.getElements().begin() + *iter);
    }
    m_data.getExplorerPanel().getExplorerListCtrl().removeSelectedLines();

    file.Write();
    file.Close();
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
    wxTextFile file(m_data.getPath());
    if (!file.Exists() || !file.Open())
        return;

    wxArrayString selectedItems = source.getSelectedItems();
    source.deleteSelectedItems();

    const long startPosition = 1;
    std::vector<unsigned long> selectedItemsPosition = m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines();

    long position = (selectedItemsPosition.empty()) ? file.GetLineCount() : startPosition + selectedItemsPosition.at(0);

    for (wxArrayString::iterator iter = selectedItems.begin(); iter != selectedItems.end(); ++iter, ++position)
        file.InsertLine(*iter, position);

    file.Write();
    file.Close();
    fillExplorerList();
}

void FileDriveManagerState::createDir()
{
}

void FileDriveManagerState::createContainerFile()
{
}

void FileDriveManagerState::playItems()
{
}

void FileDriveManagerState::rename()
{
}

void FileDriveManagerState::createShortcut()
{
}

