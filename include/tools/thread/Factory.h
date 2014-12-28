#ifndef FACTORY_H
#define FACTORY_H

#include "ThreadProcess.h"
#include "IThreadManager.h"

/** @brief Thread Factory
 * Thread Factory
 * @class fux::thread::Factory
 */

namespace fux
{
    namespace thread
    {
        class Factory
        {
            public:
                /** Creates a ThreadProcess */
                static ThreadProcess* createThreadProcess(IThreadManager* threadManager);
        };
    }
}

#endif // FACTORY_H
