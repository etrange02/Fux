/***************************************************************
 * Name:      SingleThreadManager.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2014-12-27
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/thread/manager/SingleThreadManager.h"

using namespace tools::thread;

/** @brief Constructor.
 */
SingleThreadManager::SingleThreadManager() : AbstractThreadManager()
{
    //ctor
}

/** @brief Destructor.
 */
SingleThreadManager::~SingleThreadManager()
{
    //dtor
}

/** @brief
 *
 * @return unsigned int
 *
 */
unsigned int SingleThreadManager::getThreadCount()
{
    return 1;
}

/** @brief
 *
 * @param tools::thread::Runnable&
 * @return void
 *
 */
void SingleThreadManager::doBeforeAddingWork(tools::thread::Runnable&)
{
}

/** @brief
 *
 * @param tools::thread::Runnable&
 * @return void
 *
 */
void SingleThreadManager::doAfterAddingWork(tools::thread::Runnable&)
{
}

/** @brief
 *
 * @param tools::thread::Runnable&
 * @param tools::thread::ThreadProcess&
 * @return void
 *
 */
void SingleThreadManager::doBeforeProcessingWork(tools::thread::Runnable&, tools::thread::ThreadProcess&)
{
}

/** @brief
 *
 * @return void
 *
 */
void SingleThreadManager::doOnNoWork()
{
}




