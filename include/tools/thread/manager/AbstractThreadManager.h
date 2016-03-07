#ifndef ABSTRACTTHREADMANAGER_H
#define ABSTRACTTHREADMANAGER_H

#include <vector>
#include "IThreadManager.h"
#include "ThreadSafePriorityQueue.h"
#include "ThreadSafeQueue.h"
#include "RunnableComparator.h"


/** @brief Manages thread on different cores
 * Manages thread on different cores. Producer-Consumer model
 * @class tools::thread::ThreadManager
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

        /** @brief Abstract implementation of a thread system management
         */
        class AbstractThreadManager : public tools::thread::IThreadManager
        {
            public:
                /** Default constructor */
                AbstractThreadManager();
                /** Default destructor */
                virtual ~AbstractThreadManager();

                /** Insert a work in the queue and awake a worker if one is sleeping */
                void addRunnable(Runnable* runnable);

                /** Insert a work in the queue and awake a worker if one is sleeping */
                void addRunnable(Runnable* runnable, int priority);

                /** Called by workers when work is done */
                virtual void currentWorkFinished(ThreadProcess& threadProcess);

                /** Initializes thread workers */
                void start();

                /** Clears work queue and stops workers */
                void kill();

            protected:
                virtual unsigned int getThreadCount() = 0;
                virtual void doBeforeAddingWork(Runnable& work) = 0;
                virtual void doAfterAddingWork(Runnable& work) = 0;
                virtual void doBeforeProcessingWork(Runnable& work, tools::thread::ThreadProcess& threadProcess) = 0;
                virtual void doOnNoWork() = 0;
                /** Awakes a worker if one is sleeping */
                virtual void activateAWorker();
                /** Gets the mutex to multi-thread operations */
                wxMutex& getMutex();
                /** Stops workers (threads) */
                void clearWorkers();
                /** Empties the work queue */
                void clearWorks();
                /** Gets a sleeping worker */
                ThreadProcess* getAvailableWorker();

            private:
                std::ThreadSafePriorityQueue<Runnable*, std::vector<Runnable*>, RunnableComparator> m_works; //!< Member variable "m_works"
                //std::ThreadSafeQueue<Runnable*> m_works; //!< Member variable "m_works"
                std::vector<ThreadProcess*> m_workers;
                wxMutex m_mutex;
                bool m_isInitialized;
        };
    }
}

#endif // ABSTRACTTHREADMANAGER_H
