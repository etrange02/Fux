#ifndef FILEDRIVEMANAGERSTATE_H
#define FILEDRIVEMANAGERSTATE_H

#include "DriveManagerState.h"

class FileDriveManagerState : DriveManagerState
{
    public:
        /** Default constructor */
        FileDriveManagerState();
        /** Default destructor */
        virtual ~FileDriveManagerState();

        virtual bool IsFile();

    protected:
    private:
};

#endif // FILEDRIVEMANAGERSTATE_H
