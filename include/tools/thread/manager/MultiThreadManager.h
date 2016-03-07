#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include "AbstractThreadManager.h"


/** @brief Manages thread on different cores
 * Manages thread on different cores. Producer-Consumer model
 * @class tools::thread::MultiThreadManager
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

        /** @brief Thread system with cores-1 threads.
         */
        class MultiThreadManager : public tools::thread::AbstractThreadManager
        {
            public:
                /** Default constructor */
                MultiThreadManager();
                /** Default destructor */
                virtual ~MultiThreadManager();

            protected:
                virtual unsigned int getThreadCount();
                virtual void doBeforeAddingWork(Runnable& work);
                virtual void doAfterAddingWork(Runnable& work);
                virtual void doBeforeProcessingWork(Runnable& work, tools::thread::ThreadProcess& threadProcess);
                virtual void doOnNoWork();
        };
    }
}

#endif // THREADMANAGER_H
