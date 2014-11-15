#ifndef PLAYLISTDRIVEMANAGERSTATE_H
#define PLAYLISTDRIVEMANAGERSTATE_H

#include "DriveManagerState.h"

class PlaylistDriveManagerState : DriveManagerState
{
    public:
        /** Default constructor */
        PlaylistDriveManagerState();
        /** Default destructor */
        virtual ~PlaylistDriveManagerState();
        virtual bool IsPlaylist();

    protected:
    private:
};

#endif // PLAYLISTDRIVEMANAGERSTATE_H
