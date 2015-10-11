/***************************************************************
 * Name:      TransitiveData.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-06-24
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/dnd/dataObjects/TransitiveData.h"

using namespace dragAndDrop;

/** @brief Constructor.
 */
TransitiveData::TransitiveData() :
    m_isCopy(false)
{
}

/** @brief Destructor.
 */
TransitiveData::~TransitiveData()
{
}

void TransitiveData::setCopy(const bool copy)
{
    m_isCopy = copy;
}

bool TransitiveData::isCopy() const
{
    return m_isCopy;
}

bool TransitiveData::isContainerFileKind() const
{
    return false;
}

bool TransitiveData::isPlaylistKind() const
{
    return false;
}

bool TransitiveData::isDirKind() const
{
    return false;
}

