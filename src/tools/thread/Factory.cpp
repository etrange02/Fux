/***************************************************************
 * Name:      Factory.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2014-12-27
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "../../../include/tools/thread/Factory.h"

using namespace fux::thread;

/** @brief Creates a ThreadProcess
 *
 * @param threadManager a manager to inform
 * @return a ThreadProcess
 *
 */
ThreadProcess* Factory::createThreadProcess(IThreadManager* threadManager)
{
    return new ThreadProcess(threadManager);
}

