/***************************************************************
 * Name:      ContainerFileTransitiveData.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-06-24
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/dnd/dataObjects/ContainerFileTransitiveData.h"
#include <wx/textfile.h>

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

void ContainerFileTransitiveData::doCopy()
{

}

void ContainerFileTransitiveData::doCut()
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

wxArrayString ContainerFileTransitiveData::getFilenames() const
{
    const std::vector<unsigned long>& items = getItems();
    wxArrayString data;

    wxTextFile file(m_file);
    if (!file.Exists() || !file.Open())
        return data;

    for (std::vector<unsigned long>::const_iterator iter = items.begin(); iter != items.end(); ++iter)
    {
        data.Add(file.GetLine(*iter));
    }
    file.Close();

    return data;
}

const std::vector<unsigned long>& ContainerFileTransitiveData::deleteFromSource()
{
    const std::vector<unsigned long>& items = getItems();

    wxTextFile file(m_file);
    if (!file.Exists() || !file.Open())
        return items;

    for (std::vector<unsigned long>::const_reverse_iterator iter = items.rbegin(); iter != items.rend(); ++iter)
    {
        file.RemoveLine(*iter);
    }
    file.Write();
    file.Close();

    return items;
}

bool ContainerFileTransitiveData::isContainerFileKind() const
{
    return true;
}

