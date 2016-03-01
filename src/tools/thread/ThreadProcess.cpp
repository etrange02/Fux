/***************************************************************
 * Name:      ThreadProcess.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2014-12-27
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/thread/ThreadProcess.h"

using namespace tools::thread;

/** @brief Constructor
 *
 * @param threadManager manager to signal current work is done
 *
 */
ThreadProcess::ThreadProcess(IThreadManager* threadManager) :
    wxThread(wxTHREAD_JOINABLE),
    m_semaphore(0, 1),
    m_threadManager(threadManager),
    m_work(NULL)
{
}

/** @brief Destructor
 */
ThreadProcess::~ThreadProcess()
{
}

/** @brief Sets a work (or task)
 * Sets a work (or task)
 * @param work a runnable object
 * @return void
 *
 */
void ThreadProcess::setWork(Runnable* work)
{
    m_work = work;
}

/** @brief Tests the presence of a work
 * Tests the presence of a work
 * @return true if present
 *
 */
bool ThreadProcess::hasWork() const
{
    return NULL != m_work;
}

/** @brief Thread safety. Make the thread waiting if necessary
 *
 * @return void
 *
 */
void ThreadProcess::semaphoreWait()
{
    m_semaphore.Wait();
}

/** @brief Thread safety. Make the thread running if paused
 *
 * @return void
 *
 */
void ThreadProcess::semaphorePost()
{
    m_semaphore.Post();
}

/** @brief Overload. Thread works.
 *
 * @return wxThread::ExitCode
 *
 */
wxThread::ExitCode ThreadProcess::Entry()
{
    while (!TestDestroy())
    {
        if (NULL != m_work)
        {
            try
            {
                m_work->process();
                delete m_work;
                m_work = NULL;
            }
            catch (std::exception& e)
            {
                wxLogMessage(e.what());
            }
        }

        if (m_threadManager)
            m_threadManager->currentWorkFinished(*this);
        semaphoreWait();
    }
    return (wxThread::ExitCode) 0;
}

