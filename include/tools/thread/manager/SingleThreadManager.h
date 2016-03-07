#ifndef SINGLETHREADMANAGER_H
#define SINGLETHREADMANAGER_H

#include "AbstractThreadManager.h"


/** @brief Manages one thread
 * Manages one thread Producer-Consumer model
 * @class tools::thread::SingleThreadManager
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

        /** @brief Thread system 1 thread.
         */
        class SingleThreadManager : public tools::thread::AbstractThreadManager
        {
            public:
                /** Default constructor */
                SingleThreadManager();
                /** Default destructor */
                virtual ~SingleThreadManager();

            protected:
                virtual unsigned int getThreadCount();
                virtual void doBeforeAddingWork(Runnable& work);
                virtual void doAfterAddingWork(Runnable& work);
                virtual void doBeforeProcessingWork(Runnable& work, tools::thread::ThreadProcess& threadProcess);
                virtual void doOnNoWork();
        };
    }
}

#endif // SINGLETHREADMANAGER_H
