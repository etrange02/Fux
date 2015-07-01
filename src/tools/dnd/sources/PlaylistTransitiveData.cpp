/***************************************************************
 * Name:      PlaylistTransitiveData.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-06-24
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/dnd/sources/PlaylistTransitiveData.h"

using namespace dragAndDrop;

PlaylistTransitiveData::PlaylistTransitiveData() :
    TransitiveData()
{
    //ctor
}

PlaylistTransitiveData::~PlaylistTransitiveData()
{
    //dtor
}

PlaylistTransitiveData::PlaylistTransitiveData(const PlaylistTransitiveData& other) :
    TransitiveData(other)
{
    //copy ctor
}

PlaylistTransitiveData& PlaylistTransitiveData::operator=(const PlaylistTransitiveData& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
