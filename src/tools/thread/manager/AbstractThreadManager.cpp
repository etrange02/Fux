/***************************************************************
 * Name:      AbstractThreadManager.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2016-02-29
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/thread/manager/AbstractThreadManager.h"
#include <algorithm>
#include "tools/thread/ThreadFactory.h"
#include "tools/thread/ThreadProcess.h"

using namespace tools::thread;

/** @brief Constructor
 */
AbstractThreadManager::AbstractThreadManager() :
    IThreadManager(),
    m_isInitialized(false)
{
}

/** @brief Destructor
 */
AbstractThreadManager::~AbstractThreadManager()
{
}

/** @brief Initializes thread workers
 * The number of workers depends on the number of cores present on the system
 * @return void
 *
 */
void AbstractThreadManager::start()
{
    if (m_isInitialized)
        return;

    #ifndef DEBUG
    unsigned int threadCount = getThreadCount();

    for (unsigned int i = 0; i < threadCount ; ++i)
    {
        ThreadProcess* tp = ThreadFactory::createThreadProcess(this);
        m_workers.push_back(tp);
        tp->Create();
        tp->Run();
    }
    #endif // DEBUG
    m_isInitialized = true;
}

/** @brief Clears work queue and stops workers.
 *
 * @return void
 *
 */
void AbstractThreadManager::kill()
{
    clearWorks();
    clearWorkers();
    m_isInitialized = false;
}

/** @brief Stops workers (threads)
 *
 * @return void
 *
 */
void AbstractThreadManager::clearWorkers()
{
    for (ThreadProcess* obj : m_workers)
    {
        if (obj->IsAlive())
        {
            wxMutexLocker locker(m_mutex);
            obj->semaphorePost();
            obj->Delete(NULL, wxTHREAD_WAIT_BLOCK);
        }
        delete obj;
    }
    m_workers.clear();
}

/** @brief Empties the work queue
 *
 * @return void
 *
 */
void AbstractThreadManager::clearWorks()
{
    wxMutexLocker locker(m_mutex);
    while (!m_works.empty())
    {
        Runnable* task = m_works.top();
        m_works.pop();
        delete task;
    }
}

/** @brief Insert a work in the queue and awake a worker if one is sleeping
 *
 * @param runnable a work
 * @param priority priority of the task.
 * @return void
 *
 */
void AbstractThreadManager::addRunnable(Runnable* runnable, int priority)
{
    if (NULL == runnable)
        return;

    runnable->setPriority(priority);
    addRunnable(runnable, 50);
}

/** @brief Insert a work in the queue and awake a worker if one is sleeping. Priority of 50.
 *
 * @param runnable a work
 * @return void
 *
 */
void AbstractThreadManager::addRunnable(Runnable* runnable)
{
    if (NULL == runnable)
        return;

    doBeforeAddingWork(*runnable);
    #if DEBUG
    runnable->process();
    delete runnable;
    #else // DEBUG
    m_works.push(runnable);

    activateAWorker();
    #endif // DEBUG
    doAfterAddingWork(*runnable);
}

/** @brief Called by workers when work is done.
 * If there is work in the queue, the thread take the first one (the oldest) ans process it. Otherwise it sleeps.
 * @param threadProcess the finisher worker
 * @return void
 *
 */
void AbstractThreadManager::currentWorkFinished(ThreadProcess& threadProcess)
{
    wxMutexLocker locker(m_mutex);
    if (m_works.empty())
    {
        doOnNoWork();
        return;
    }

    //Runnable* task = m_works.pop_front();
    Runnable* task = m_works.top();
    m_works.pop();
    doBeforeProcessingWork(*task, threadProcess);
    threadProcess.setWork(task);
    threadProcess.semaphorePost();
}

/** @brief Awakes a worker if one is sleeping
 *
 * @return void
 *
 */
void AbstractThreadManager::activateAWorker()
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
ThreadProcess* AbstractThreadManager::getAvailableWorker()
{
    for (std::vector<ThreadProcess*>::iterator iter = m_workers.begin(); iter != m_workers.end(); ++iter)
    {
        if (!(*iter)->hasWork())
            return *iter;
    }
    return NULL;
}

/** @brief Gets the mutex to multi-thread operations
 *
 * @return wxMutex&
 *
 */
wxMutex& AbstractThreadManager::getMutex()
{
    return m_mutex;
}

