/***************************************************************
 * Name:      DirTransitiveData.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-06-24
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/dnd/sources/DirTransitiveData.h"

using namespace dragAndDrop;

DirTransitiveData::DirTransitiveData() :
    TransitiveData()
{
    //ctor
}

DirTransitiveData::~DirTransitiveData()
{
    //dtor
}

DirTransitiveData::DirTransitiveData(const DirTransitiveData& other) :
    TransitiveData(other)
{
    //copy ctor
}

DirTransitiveData& DirTransitiveData::operator=(const DirTransitiveData& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
