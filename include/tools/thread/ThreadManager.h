#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include <vector>
#include "IThreadManager.h"
#include "ThreadSafeQueue.h"


/** @brief Manages thread on different cores
 * Manages thread on different cores. Producer-Consumer model
 * @class tools::thread::ThreadManager
 */


namespace tools
{
    namespace thread
    {
        class ThreadProcess;

        class ThreadManager : public tools::thread::IThreadManager
        {
            public:
                /** Singleton */
                static ThreadManager& get();

                /** Insert a work in the queue and awake a worker if one is sleeping */
                void addRunnable(IRunnable* runnable);

                /** Called by workers when work is done */
                virtual void currentWorkFinished(ThreadProcess& threadProcess);

                /** Deletes the instance */
                void deleteInstance();

            protected:
            private:
                /** Default constructor */
                ThreadManager();
                /** Default destructor */
                virtual ~ThreadManager();

                /** Initializes thread workers */
                void initialize();
                /** Clears work queue and workers */
                void clear();
                /** Stops workers (threads) */
                void clearWorkers();
                /** Empties the work queue */
                void clearWorks();
                /** Awakes a worker if one is sleeping */
                void activateAWorker();
                /** Gets a sleeping worker */
                ThreadProcess* getAvailableWorker();

            private:
                std::ThreadSafeQueue<IRunnable*> m_works; //!< Member variable "m_works"
                std::vector<ThreadProcess*> m_workers;
                wxMutex m_mutex;
        };
    }
}

#endif // THREADMANAGER_H
