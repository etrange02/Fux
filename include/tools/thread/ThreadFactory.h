#ifndef THREAD_FACTORY_H
#define THREAD_FACTORY_H

#include <wx/wx.h>

/** @brief Thread Factory
 *
 * @class tools::thread::Factory
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
        class IThreadManager;
        class Runnable;

        /** @brief Factory
         */
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
