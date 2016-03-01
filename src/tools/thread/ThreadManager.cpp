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

/** @brief Constructor
 */
ThreadManager::ThreadManager() : AbstractThreadManager()
{
    start();
}

/** @brief Destructor
 */
ThreadManager::~ThreadManager()
{
    kill();
}

/** @brief Returns a number of thread to create.
 *
 * @return unsigned int
 *
 */
unsigned int ThreadManager::getThreadCount()
{
    return std::max(wxThread::GetCPUCount()-1, 1);
}

/** @brief
 *
 * @param Runnable&
 * @return void
 *
 */
void ThreadManager::doBeforeAddingWork(Runnable&)
{
}

/** @brief
 *
 * @param Runnable&
 * @return void
 *
 */
void ThreadManager::doAfterAddingWork(Runnable&)
{
}

/** @brief
 *
 * @param Runnable&
 * @return void
 *
 */
void ThreadManager::doBeforeProcessingWork(Runnable&, tools::thread::ThreadProcess&)
{
}

/** @brief
 *
 * @return void
 *
 */
void ThreadManager::doOnNoWork()
{
}

