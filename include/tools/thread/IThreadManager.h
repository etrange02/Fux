#ifndef ITHREADMANAGER_H
#define ITHREADMANAGER_H

#include "ThreadProcess.h"

/** @brief Interface for thread manager
 * Interface for thread manager
 * @class tools::thread::IThreadManager
 */

/**
 * Name space of tools
 */
namespace tools
{
    /**
     * Name space of multi-threading tools
     */
    namespace thread
    {
        class ThreadProcess;

        /** @brief Interface of a thread system
         */
        class IThreadManager
        {
            public:
                virtual ~IThreadManager() {};
                virtual void currentWorkFinished(ThreadProcess& threadProcess) = 0;
        };
    }
}

#endif // ITHREADMANAGER_H
