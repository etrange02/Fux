/***************************************************************
 * Name:      PlaylistDriveManagerState.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2014-11-19
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "explorer/state/PlaylistDriveManagerState.h"
#include <vector>
#include "MusicManagerSwitcher.h"
#include "Music.h"
#include "explorer/ExplorerManagerData.h"

using namespace explorer;

PlaylistDriveManagerState::PlaylistDriveManagerState(ExplorerManagerData& data) :
    DriveManagerState(data)
{
    //ctor
}

PlaylistDriveManagerState::~PlaylistDriveManagerState()
{
    //dtor
}

bool PlaylistDriveManagerState::isPlaylist() const
{
    return true;
}

bool PlaylistDriveManagerState::fillExplorerList()
{
    m_data.getExplorerPanel().getExplorerListCtrl().DeleteAllItems();
    m_data.getElements().clear();

    std::vector<Music*>& musics = MusicManagerSwitcher::get().getMusics();
    for (std::vector<Music*>::iterator it = musics.begin(); it != musics.end(); ++it)
    {
        m_data.getExplorerPanel().getExplorerListCtrl().addLine((*it)->GetName(), (*it)->GetExtension());
        addDriveManagerListElement((*it)->GetFileName());
    }

    m_data.getExplorerPanel().setTexts(_("Liste de lecture"), "");

    return true;
}

bool PlaylistDriveManagerState::fillExplorerList(const wxString& elementToSelect)
{
    fillExplorerList();
    return true;
}

DriveManagerState& PlaylistDriveManagerState::getPreviousState()
{
    return *this;
}

void PlaylistDriveManagerState::openElement(const std::vector<unsigned long>& indexes)
{
    MusicManagerSwitcher::get().playMusicAt(indexes.at(0));
}

void PlaylistDriveManagerState::deleteSelectedItems()
{
    std::vector<unsigned long> selectedItemsPosition = m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines();

    for (std::vector<unsigned long>::reverse_iterator iter = selectedItemsPosition.rbegin(); iter != selectedItemsPosition.rend(); ++iter)
    {
        MusicManagerSwitcher::get().deleteTitleAt(*iter);
        m_data.getElements().erase(m_data.getElements().begin() + *iter);
    }
    m_data.getExplorerPanel().getExplorerListCtrl().removeSelectedLines();
}

bool PlaylistDriveManagerState::canCopyTo(const DriveManagerState& other) const
{
    return true;
}

bool PlaylistDriveManagerState::canMoveTo(const DriveManagerState& other) const
{
    return true;
}

void PlaylistDriveManagerState::copyElements(DriveManagerState& source)
{
    MusicManagerSwitcher::get().parse(source.getSelectedItems());
    fillExplorerList();
}

void PlaylistDriveManagerState::moveElements(DriveManagerState& source)
{
    std::vector<unsigned long> selectedItemsPosition = m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines();

    const long position = (selectedItemsPosition.empty()) ? MusicManagerSwitcher::get().size() : selectedItemsPosition.at(0);

    wxArrayString itemsPosition = source.getSelectedItemsPosition();
    MusicManagerSwitcher::get().moveIntTitlesAt(itemsPosition, position);

    fillExplorerList();
    source.fillExplorerList();
}

