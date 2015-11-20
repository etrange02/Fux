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
#include "tools/dnd/dataObjects/PlaylistTransitiveData.h"
#include "tools/dnd/targets/PlaylistTransitiveDataTarget.h"

using namespace explorer;
using namespace ::music;

PlaylistDriveManagerState::PlaylistDriveManagerState(ExplorerManagerData& data) :
    DriveManagerState(data)
{
    gui::explorer::ExplorerListCtrl& listCtrl = data.getExplorerPanel().getExplorerListCtrl();
    listCtrl.SetDropTarget(new dragAndDrop::PlaylistTransitiveDataTarget(listCtrl, false));
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

    music::MusicCollection& musics = MusicManagerSwitcher::get().getMusics();
    for (MusicIterator it = musics.begin(); it != musics.end(); ++it)
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

void PlaylistDriveManagerState::openElement()
{
    std::vector<unsigned long> indexes = m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines();
    if (indexes.empty() || indexes.at(0) >= m_data.getElements().size())
        return;

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

bool PlaylistDriveManagerState::canDeleteSelectedItems() const
{
    return !m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines().empty();
}

bool PlaylistDriveManagerState::canSelectAll() const
{
    return true;
}

bool PlaylistDriveManagerState::canCreateDir() const
{
    return 0 != m_data.getExplorerPanel().getExplorerListCtrl().GetItemCount();
}

bool PlaylistDriveManagerState::canCreateContainerFile() const
{
    return !m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines().empty();
}

bool PlaylistDriveManagerState::canPlayItems() const
{
    return !m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines().empty();
}

bool PlaylistDriveManagerState::canRename() const
{
    return false;
}

bool PlaylistDriveManagerState::canCreateShortcut() const
{
    return false;
}

void PlaylistDriveManagerState::copyElements(DriveManagerState& source)
{
    MusicManagerSwitcher::get().parse(source.getSelectedItems());
    fillExplorerList();
}

void PlaylistDriveManagerState::moveElements(DriveManagerState& source)
{
    std::vector<unsigned long> selectedItemsPosition = m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines();

    const unsigned long position = (selectedItemsPosition.empty()) ? MusicManagerSwitcher::get().size() : selectedItemsPosition.at(0);

    wxArrayString itemsPosition = source.getSelectedItemsPosition();
    MusicManagerSwitcher::get().moveIntTitlesAt(itemsPosition, position);

    fillExplorerList();
    source.fillExplorerList();
}

void PlaylistDriveManagerState::createDir()
{
    wxLogMessage("Must be implemented.");
    ///TODO (David): PlaylistDriveManagerState::createDir
    /*
    cf FileDriveManagerState::createDir
    - Sélectionner le répertoire où créer le dossier
    - (Pré-remplir le nom du dossier avec le nom du m3u)
    - Copier les titres sélectionnés dans le répertoire nouvellement créé
    --> prendre en compte les lignes sélectionnées dans la colonne de gauche
    */
}

void PlaylistDriveManagerState::createContainerFile()
{
    wxLogMessage("Must be implemented.");
    ///TODO (David): PlaylistDriveManagerState::createContainerFile
    /*
    cf FileDriveManagerState::createContainerFile
    - Demander le nom du fichier m3u
    - Création dans le répertoire habituel
    - Le remplir avec les lignes sélectionnées dans la colonne de gauche.
    */
}

void PlaylistDriveManagerState::playItems()
{
    //std::vector<unsigned long> selectedItemsPosition = m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines();
    openElement();
}

void PlaylistDriveManagerState::rename()
{
    // Nothing to do.
}

void PlaylistDriveManagerState::createShortcut()
{
    // Nothing to do.
}

dragAndDrop::TransitiveData* PlaylistDriveManagerState::getDraggedElements()
{
    dragAndDrop::PlaylistTransitiveData* transitiveData = new dragAndDrop::PlaylistTransitiveData;
    std::vector<unsigned long> selectedItemsPosition = m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines();
    MusicManagerSwitcher::get().convertPositionsToTransitiveData(selectedItemsPosition, *transitiveData);

    return transitiveData;
}


