#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include "AbstractThreadManager.h"


/** @brief Manages thread on different cores
 * Manages thread on different cores. Producer-Consumer model
 * @class tools::thread::ThreadManager
 */

namespace tools
{
    namespace thread
    {
        class ThreadProcess;

        class ThreadManager : public tools::thread::AbstractThreadManager
        {
            public:
                /** Default constructor */
                ThreadManager();
                /** Default destructor */
                virtual ~ThreadManager();

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
