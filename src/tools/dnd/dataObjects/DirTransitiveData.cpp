/***************************************************************
 * Name:      DirTransitiveData.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-06-24
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/dnd/dataObjects/DirTransitiveData.h"

using namespace dragAndDrop;

/** @brief Constructor.
 */
DirTransitiveData::DirTransitiveData() :
    TTransitiveData()
{
}

/** @brief Destructor.
 */
DirTransitiveData::~DirTransitiveData()
{
}

/** @brief Copy construtor.
 *
 * @param other const DirTransitiveData&
 *
 */
DirTransitiveData::DirTransitiveData(const DirTransitiveData& other) :
    TTransitiveData(other)
{
}

/** @brief Copy operator.
 *
 * @param rhs const DirTransitiveData&
 * @return DirTransitiveData&
 *
 */
DirTransitiveData& DirTransitiveData::operator=(const DirTransitiveData& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

const wxString DirTransitiveData::getName() const
{
    return getItems().at(0);
}

bool DirTransitiveData::isSameKind() const
{
    return false;
}

void DirTransitiveData::doCopy()
{

}

void DirTransitiveData::doCut()
{

}

void DirTransitiveData::doPaste()
{

}


