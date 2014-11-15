#ifndef DEFAULTDRIVEMANAGERSTATE_H
#define DEFAULTDRIVEMANAGERSTATE_H

#include "DriveManagerState.h"

class DefaultDriveManagerState : DriveManagerState
{
    public:
        /** Default constructor */
        DefaultDriveManagerState();
        /** Default destructor */
        virtual ~DefaultDriveManagerState();

        virtual bool IsDefault();
    protected:
    private:
};

#endif // DEFAULTDRIVEMANAGERSTATE_H
