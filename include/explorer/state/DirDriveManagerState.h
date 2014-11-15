#ifndef DIRDRIVEMANAGERSTATE_H
#define DIRDRIVEMANAGERSTATE_H

#include "DriveManagerState.h"

class DirDriveManagerState : DriveManagerState
{
    public:
        /** Default constructor */
        DirDriveManagerState();
        /** Default destructor */
        virtual ~DirDriveManagerState();

        virtual bool IsDirectory();
    protected:
    private:
};

#endif // DIRDRIVEMANAGERSTATE_H
