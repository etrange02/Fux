/***************************************************************
 * Name:      ContainerFileTransitiveData.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-06-24
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/dnd/dataObjects/ContainerFileTransitiveData.h"

using namespace dragAndDrop;

/** @brief Constructor.
 */
ContainerFileTransitiveData::ContainerFileTransitiveData() :
    TTransitiveData()
{
    //ctor
}

/** @brief Destructor
 */
ContainerFileTransitiveData::~ContainerFileTransitiveData()
{
    //dtor
}

/** @brief Copy constructor.
 *
 * @param other const ContainerFileTransitiveData&
 *
 */
ContainerFileTransitiveData::ContainerFileTransitiveData(const ContainerFileTransitiveData& other) :
    TTransitiveData(other)
{
    *this = other;
}

/** @brief Copy operator.
 *
 * @param rhs source.
 * @return ContainerFileTransitiveData& the current instance.
 *
 */
ContainerFileTransitiveData& ContainerFileTransitiveData::operator=(const ContainerFileTransitiveData& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

/** @brief Gets the filename
 *
 * @return const wxString&
 *
 */
const wxString ContainerFileTransitiveData::getName() const
{
    return m_file;
}

bool ContainerFileTransitiveData::isSameKind() const
{
    return false;
}

void ContainerFileTransitiveData::doCopy()
{

}

void ContainerFileTransitiveData::doCut()
{

}

void ContainerFileTransitiveData::doPaste()
{

}

/** @brief Returns the filename.
 *
 * @param filename const wxString&
 * @return void
 *
 */
void ContainerFileTransitiveData::setFilename(const wxString& filename)
{
    m_file = filename;
}

