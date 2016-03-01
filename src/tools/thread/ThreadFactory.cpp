/***************************************************************
 * Name:      ThreadFactory.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2014-12-27
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/thread/ThreadFactory.h"
#include "tools/thread/FileDeletionThread.h"
#include "tools/thread/ThreadProcess.h"
#include "tools/thread/IThreadManager.h"

using namespace tools::thread;

/** @brief Creates a ThreadProcess
 *
 * @param threadManager a manager to inform
 * @return a ThreadProcess
 *
 */
ThreadProcess* ThreadFactory::createThreadProcess(IThreadManager* threadManager)
{
    return new ThreadProcess(threadManager);
}

Runnable* ThreadFactory::createFileDeletionThread(const wxArrayString& files)
{
    return new FileDeletionThread(files);
}

