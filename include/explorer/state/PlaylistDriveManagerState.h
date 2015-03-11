#ifndef PLAYLISTDRIVEMANAGERSTATE_H
#define PLAYLISTDRIVEMANAGERSTATE_H

#include "DriveManagerState.h"

namespace explorer
{
    class PlaylistDriveManagerState : public DriveManagerState
    {
        public:
            /** Default constructor */
            PlaylistDriveManagerState(ExplorerManagerData& data);
            /** Default destructor */
            virtual ~PlaylistDriveManagerState();

            virtual bool isPlaylist();
            virtual bool fillExplorerList();
            virtual bool fillExplorerList(const wxString& elementToSelect);

            virtual DriveManagerState& getPreviousState();
            virtual void openElement(const std::vector<long>& indexes);

        protected:
        private:
    };
}

#endif // PLAYLISTDRIVEMANAGERSTATE_H
