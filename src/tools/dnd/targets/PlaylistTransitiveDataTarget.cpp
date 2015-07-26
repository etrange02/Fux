#include "tools/dnd/targets/PlaylistTransitiveDataTarget.h"
#include "music/MusicManagerSwitcher.h"

using namespace dragAndDrop;

/** @brief Constructor.
 */
PlaylistTransitiveDataTarget::PlaylistTransitiveDataTarget(const wxListCtrl& source) :
    TransitiveDataTarget(source)
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




