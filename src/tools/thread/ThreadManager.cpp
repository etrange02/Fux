/***************************************************************
 * Name:      ThreadManager.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2014-12-27
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/thread/ThreadManager.h"
#include <algorithm>
#include "tools/thread/ThreadFactory.h"
#include "tools/thread/ThreadProcess.h"

using namespace tools::thread;

static ThreadManager* s_threadManager = NULL;

/** @brief
 *
 * @param obj ThreadProcess*
 * @return bool
 *
 */
bool DeleteAll(ThreadProcess *obj)
{
    obj->Delete();
    obj->semaphorePost();
    obj->Wait();
    delete obj;
    return true;
};

/** @brief Constructor
 */
ThreadManager::ThreadManager() : IThreadManager()
{
    initialize();
}

/** @brief Destructor
 */
ThreadManager::~ThreadManager()
{
    clear();
}

/** @brief Singleton
 *
 * @return ThreadManager&
 *
 */
ThreadManager& ThreadManager::get()
{
    if (s_threadManager == NULL)
        s_threadManager = new ThreadManager;
    return *s_threadManager;
}

/** @brief Initializes thread workers
 * The number of workers depends on the number of cores present on the system
 * @return void
 *
 */
void ThreadManager::initialize()
{
    int CPUCount = std::max(wxThread::GetCPUCount()-1, 1);

    ThreadProcess *tp = NULL;
    for (int i = 0; i < wxThread::GetCPUCount() -1 ; ++i)
    {
        tp = ThreadFactory::createThreadProcess(this);
        m_workers.push_back(tp);
        tp->Create();
        tp->Run();
    }
}

/** @brief Deletes the instance
 *
 * @return void
 *
 */
void ThreadManager::deleteInstance()
{
    delete s_threadManager;
    s_threadManager = NULL;
}

/** @brief Clears work queue and workers
 *
 * @return void
 *
 */
void ThreadManager::clear()
{
    clearWorks();
    clearWorkers();
}

/** @brief Stops workers (threads)
 *
 * @return void
 *
 */
void ThreadManager::clearWorkers()
{
    std::remove_if(m_workers.begin(), m_workers.end(), DeleteAll);
}

/** @brief Empties the work queue
 *
 * @return void
 *
 */
void ThreadManager::clearWorks()
{
    wxMutexLocker locker(m_mutex);
    while (!m_works.empty())
        delete m_works.pop_front();
}

/** @brief Insert a work in the queue and awake a worker if one is sleeping
 *
 * @param runnable a work
 * @return void
 *
 */
void ThreadManager::addRunnable(IRunnable* runnable)
{
    #if DEBUG
    runnable->process();
    delete runnable;
    #else // DEBUG
    m_works.push(runnable);

    activateAWorker();
    #endif // DEBUG
}

/** @brief Called by workers when work is done.
 * If there is work in the queue, the thread take the first one (the oldest) ans process it. Otherwise it sleeps.
 * @param threadProcess the finisher worker
 * @return void
 *
 */
void ThreadManager::currentWorkFinished(ThreadProcess& threadProcess)
{
    wxMutexLocker locker(m_mutex);
    if (m_works.empty())
    {
        return;
    }

    threadProcess.setWork(m_works.pop_front());
    threadProcess.semaphorePost();
}

/** @brief Awakes a worker if one is sleeping
 *
 * @return void
 *
 */
void ThreadManager::activateAWorker()
{
    wxMutexLocker locker(m_mutex);
    ThreadProcess* tp = getAvailableWorker();
    if (NULL != tp)
    {
        tp->semaphorePost();
    }
}

/** @brief Gets a sleeping worker
 * A worker is sleeping when it does not have work object
 * @return ThreadProcess*
 *
 */
ThreadProcess* ThreadManager::getAvailableWorker()
{
    for (std::vector<ThreadProcess*>::iterator iter = m_workers.begin(); iter != m_workers.end(); ++iter)
    {
        if (!(*iter)->hasWork())
            return *iter;
    }
    return NULL;
}

