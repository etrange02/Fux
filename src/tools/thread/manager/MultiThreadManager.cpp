/***************************************************************
 * Name:      MultiThreadManager.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2014-12-27
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/thread/manager/MultiThreadManager.h"
#include <algorithm>
#include "tools/thread/ThreadFactory.h"
#include "tools/thread/ThreadProcess.h"

using namespace tools::thread;

/** @brief Constructor
 */
MultiThreadManager::MultiThreadManager() : AbstractThreadManager()
{
    start();
}

/** @brief Destructor
 */
MultiThreadManager::~MultiThreadManager()
{
    kill();
}

/** @brief Returns a number of thread to create.
 *
 * @return unsigned int
 *
 */
unsigned int MultiThreadManager::getThreadCount()
{
    return std::max(wxThread::GetCPUCount()-1, 1);
}

/** @brief
 *
 * @param Runnable&
 * @return void
 *
 */
void MultiThreadManager::doBeforeAddingWork(Runnable&)
{
}

/** @brief
 *
 * @param Runnable&
 * @return void
 *
 */
void MultiThreadManager::doAfterAddingWork(Runnable&)
{
}

/** @brief
 *
 * @param Runnable&
 * @return void
 *
 */
void MultiThreadManager::doBeforeProcessingWork(Runnable&, tools::thread::ThreadProcess&)
{
}

/** @brief
 *
 * @return void
 *
 */
void MultiThreadManager::doOnNoWork()
{
}

