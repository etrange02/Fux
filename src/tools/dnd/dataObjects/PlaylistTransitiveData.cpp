/***************************************************************
 * Name:      PlaylistTransitiveData.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-06-24
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/dnd/dataObjects/PlaylistTransitiveData.h"

using namespace dragAndDrop;

/** @brief Constructor.
 */
PlaylistTransitiveData::PlaylistTransitiveData() :
    TTransitiveData()
{
}

/** @brief Destructor.
 */
PlaylistTransitiveData::~PlaylistTransitiveData()
{
}

/** @brief Copy constructor.
 *
 * @param other const PlaylistTransitiveData&
 *
 */
PlaylistTransitiveData::PlaylistTransitiveData(const PlaylistTransitiveData& other) :
    TTransitiveData(other)
{
}

/** @brief Copy operator.
 *
 * @param rhs const PlaylistTransitiveData&
 * @return PlaylistTransitiveData&
 *
 */
PlaylistTransitiveData& PlaylistTransitiveData::operator=(const PlaylistTransitiveData& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

const wxString PlaylistTransitiveData::getName() const
{
    return getItems().at(0)->GetFileName();
}

bool PlaylistTransitiveData::isSameKind() const
{
    return false;
}

void PlaylistTransitiveData::doCopy()
{

}

void PlaylistTransitiveData::doCut()
{

}

void PlaylistTransitiveData::doPaste()
{

}

