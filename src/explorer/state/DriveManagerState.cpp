#include "../../../include/explorer/state/DriveManagerState.h"

DriveManagerState::DriveManagerState()
{
    //ctor
}

DriveManagerState::~DriveManagerState()
{
    //dtor
}

bool DriveManagerState::IsDefault()
{
    return false;
}

bool DriveManagerState::IsDirectory()
{
    return false;
}

bool DriveManagerState::IsFile()
{
    return false;
}

bool DriveManagerState::IsPlaylist()
{
    return false;
}
