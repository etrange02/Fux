#ifndef THREAD_FACTORY_H
#define THREAD_FACTORY_H

#include <wx/wx.h>

/** @brief Thread Factory
 *
 * @class tools::thread::Factory
 */

namespace tools
{
    namespace thread
    {
        class ThreadProcess;
        class IThreadManager;
        class Runnable;

        class ThreadFactory
        {
            public:
                /** Creates a ThreadProcess */
                static ThreadProcess* createThreadProcess(IThreadManager* threadManager);
                static Runnable* createFileDeletionThread(const wxArrayString& files);
        };
    }
}

#endif // THREAD_FACTORY_H
