/***************************************************************
 * Name:      ContainerFileTransitiveData.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-06-24
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/dnd/dataObjects/ContainerFileTransitiveData.h"
#include "explorer/state/FileDriveManagerState.h"
#include <wx/textfile.h>

using namespace dragAndDrop;

/** @brief Constructor.
 */
ContainerFileTransitiveData::ContainerFileTransitiveData(explorer::FileDriveManagerState& managerState) :
    TTransitiveData(),
    m_managerState(managerState)
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
    TTransitiveData(other),
    m_managerState(other.m_managerState)
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

    const long startPosition = 1;
    for (std::vector<unsigned long>::const_iterator iter = items.begin(); iter != items.end(); ++iter)
    {
        data.Add(file.GetLine(*iter + startPosition));
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

    const long startPosition = 1;
    for (std::vector<unsigned long>::const_reverse_iterator iter = items.rbegin(); iter != items.rend(); ++iter)
    {
        file.RemoveLine(*iter + startPosition);
    }
    file.Write();
    file.Close();

    m_managerState.fillExplorerList();
    return items;
}

bool ContainerFileTransitiveData::isContainerFileKind() const
{
    return true;
}

