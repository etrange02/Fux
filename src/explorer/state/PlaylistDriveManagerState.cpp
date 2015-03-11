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

bool PlaylistDriveManagerState::isPlaylist()
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

void PlaylistDriveManagerState::openElement(const std::vector<long>& indexes)
{
    MusicManagerSwitcher::get().playMusicAt(indexes.at(0));
}

