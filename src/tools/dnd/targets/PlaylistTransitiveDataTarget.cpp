/***************************************************************
 * Name:      PlaylistTransitiveDataTarget.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-06-26
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/dnd/targets/PlaylistTransitiveDataTarget.h"
#include "tools/dnd/dataObjects/PlaylistTransitiveData.h"
#include "music/MusicManagerSwitcher.h"

using namespace dragAndDrop;

/** @brief Constructor.
 */
PlaylistTransitiveDataTarget::PlaylistTransitiveDataTarget(DroppedMarkedLineListCtrl& source, const bool isAssociatedToPlayListCtrl) :
    TransitiveDataTarget(source),
    m_isAssociatedToPlayListCtrl(isAssociatedToPlayListCtrl)
{
}

/** @brief Destructor.
 */
PlaylistTransitiveDataTarget::~PlaylistTransitiveDataTarget()
{
}

bool PlaylistTransitiveDataTarget::isSameKind() const
{
    if (m_data == NULL)
        return false;
    return m_data->isPlaylistKind();
}

void PlaylistTransitiveDataTarget::doCopyProcessing(const wxArrayString& data, const long position)
{
    music::MusicManagerSwitcher::get().placeStringTitlesAt(data, position);
}

void PlaylistTransitiveDataTarget::doCutProcessing(TransitiveData& transitiveData, const long position)
{
    wxLogMessage("Must be implemented");
    ///TODO (David): PlaylistTransitiveDataTarget::doCutProcessing
    PlaylistTransitiveData& fileTransitiveData = static_cast<PlaylistTransitiveData&>(transitiveData);
    //fileTransitiveData.
    //music::MusicManagerSwitcher::get().moveIntTitlesAt(, position);
}

wxDragResult PlaylistTransitiveDataTarget::OnDragOver(wxCoord x, wxCoord y, wxDragResult def)
{
    if (m_isAssociatedToPlayListCtrl && music::MusicManagerSwitcher::get().hasEfficientSearchedWord())
        return wxDragNone;

    return TransitiveDataTarget::OnDragOver(x, y, def);
}


