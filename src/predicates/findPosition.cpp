/***************************************************************
 * Name:      findPosition.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2014-09-18
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "predicates/findPosition.h"

using namespace ::music;

findPosition::findPosition(IMusic *music)
{
    m_music = music;
}

findPosition::~findPosition()
{}

bool findPosition::operator()(const IMusic* music)
{
    return (m_music == music);
}

