/***************************************************************
 * Name:      findSharedMusicContainer.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-05-29
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "predicates/findSharedMusicContainer.h"
#include "music/IMusic.h"
#include "music/Music.h"

findSharedMusicContainer::findSharedMusicContainer(const music::IMusic& music) :
    m_music(music)
{
}

bool findSharedMusicContainer::operator()(std::shared_ptr<music::Music>& item)
{
    return &m_music == item.get();
}
