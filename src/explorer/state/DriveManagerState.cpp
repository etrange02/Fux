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

bool DriveManagerState::isDefault() const
{
    return false;
}

bool DriveManagerState::isDirectory() const
{
    return false;
}

bool DriveManagerState::isFile() const
{
    return false;
}

bool DriveManagerState::isPlaylist() const
{
    return false;
}

void DriveManagerState::addDriveManagerListElement(const wxString& filename)
{
    DriveManagerListElement element;
    element.setFilename(filename);
    m_data.getElements().push_back(element);
}

wxArrayString DriveManagerState::convertPositionToString(const std::vector<unsigned long>& indexes)
{
    const size_t length = m_data.getElements().size();
    wxArrayString names;

    for (std::vector<unsigned long>::const_iterator it = indexes.begin(); it != indexes.end(); ++it)
    {
        if (*it < length)
            names.push_back(m_data.getElements().at(*it).getFilename());
    }
    return names;
}

bool DriveManagerState::isSameKind(const DriveManagerState& other) const
{
    return     isDefault()   == other.isDefault()
            && isDirectory() == other.isDirectory()
            && isPlaylist()  == other.isPlaylist()
            && isFile()      == other.isFile();
}

const wxString& DriveManagerState::getPath() const
{
    return m_data.getPath();
}

wxArrayString DriveManagerState::getSelectedItems()
{
    return convertPositionToString(m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines());
}

wxArrayString DriveManagerState::getSelectedItemsPosition()
{
    wxArrayString positions;
    std::vector<unsigned long> longPosition = m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines();
    for (std::vector<unsigned long>::iterator iter = longPosition.begin(); iter != longPosition.end(); ++iter)
        positions.Add(wxString::Format("%d", *iter));
    return positions;
}

