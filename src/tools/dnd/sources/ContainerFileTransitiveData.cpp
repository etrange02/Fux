/***************************************************************
 * Name:      ContainerFileTransitiveData.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-06-24
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/dnd/sources/ContainerFileTransitiveData.h"

using namespace dragAndDrop;

ContainerFileTransitiveData::ContainerFileTransitiveData() :
    TransitiveData()
{
    //ctor
}

ContainerFileTransitiveData::~ContainerFileTransitiveData()
{
    //dtor
}

ContainerFileTransitiveData::ContainerFileTransitiveData(const ContainerFileTransitiveData& other) :
    TransitiveData(other)
{
    //copy ctor
}

ContainerFileTransitiveData& ContainerFileTransitiveData::operator=(const ContainerFileTransitiveData& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
