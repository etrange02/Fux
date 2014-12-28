#ifndef ITHREADMANAGER_H
#define ITHREADMANAGER_H

#include "ThreadProcess.h"

/** @brief Interface for thread manager
 * Interface for thread manager
 * @class fux::thread::IThreadManager
 */

namespace fux
{
    namespace thread
    {
        class ThreadProcess;

        class IThreadManager
        {
            public:
                virtual void currentWorkFinished(ThreadProcess& threadProcess) = 0;
        };
    }
}

#endif // ITHREADMANAGER_H
