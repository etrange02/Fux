/***************************************************************
 * Name:      DriveManagerState.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2014-11-19
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "explorer/state/DriveManagerState.h"
#include "explorer/ExplorerManagerData.h"

using namespace explorer;

DriveManagerState::DriveManagerState(ExplorerManagerData& data) :
    m_data(data)
{
    //ctor
}

DriveManagerState::~DriveManagerState()
{
    //dtor
}

bool DriveManagerState::isDefault()
{
    return false;
}

bool DriveManagerState::isDirectory()
{
    return false;
}

bool DriveManagerState::isFile()
{
    return false;
}

bool DriveManagerState::isPlaylist()
{
    return false;
}

void DriveManagerState::addDriveManagerListElement(const wxString& filename)
{
    DriveManagerListElement element;
    element.setFilename(filename);
    m_data.getElements().push_back(element);
}

wxArrayString DriveManagerState::convertPositionToString(const std::vector<long>& indexes)
{
    const size_t length = m_data.getElements().size();
    wxArrayString names;

    for (std::vector<long>::const_iterator it = indexes.begin(); it != indexes.end(); ++it)
    {
        if (*it < length)
            names.push_back(m_data.getElements().at(*it).getFilename());
    }
    return names;
}

