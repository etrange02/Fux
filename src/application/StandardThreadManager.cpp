/***************************************************************
 * Name:      StandardThreadManager.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2016-02-25
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "StandardThreadManager.h"

using namespace thread;

static StandardThreadManager* s_threadManager = NULL;

StandardThreadManager::StandardThreadManager() : ThreadManager()
{
    //ctor
}

StandardThreadManager::~StandardThreadManager()
{
    //dtor
}

/** @brief Singleton
 *
 * @return StandardThreadManager&
 *
 */
StandardThreadManager& StandardThreadManager::get()
{
    if (s_threadManager == NULL)
        s_threadManager = new StandardThreadManager;
    return *s_threadManager;
}

/** @brief Deletes the instance
 *
 * @return void
 *
 */
void StandardThreadManager::deleteInstance()
{
    delete s_threadManager;
    s_threadManager = NULL;
}

