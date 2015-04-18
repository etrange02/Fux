/***************************************************************
 * Name:      MusicManagerSwitcher.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-01-02
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "MusicManagerSwitcher.h"

using namespace ::music;

MusicManagerSwitcher *s_musicManagerSwitcher_instance = NULL;

MusicManagerSwitcher& MusicManagerSwitcher::getInstance()
{
    if (NULL == s_musicManagerSwitcher_instance)
        s_musicManagerSwitcher_instance = new MusicManagerSwitcher();
    return *s_musicManagerSwitcher_instance;
}

IMusicManager& MusicManagerSwitcher::get()
{
    return getInstance().getDefaultDecorator();
}

IMusicManager& MusicManagerSwitcher::getSearch()
{
    if (MusicManagerSwitcher::get().hasEfficientSearchedWord())
        return getInstance().getSearchDecorator();
    else
        return get();
}

MusicManagerSwitcher::MusicManagerSwitcher() :
    m_defaultDecorator(m_musicManager),
    m_searchDecorator(m_musicManager)
{
    //ctor
}

void MusicManagerSwitcher::deleteInstance()
{
    delete s_musicManagerSwitcher_instance;
    s_musicManagerSwitcher_instance = NULL;
}

MusicManagerSwitcher::~MusicManagerSwitcher()
{
    //dtor
}

IMusicManager& MusicManagerSwitcher::getDefaultDecorator()
{
    return m_defaultDecorator;
}

IMusicManager& MusicManagerSwitcher::getSearchDecorator()
{
    return m_searchDecorator;
}


