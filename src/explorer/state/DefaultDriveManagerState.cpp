/***************************************************************
 * Name:      DefaultDriveManagerState.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2014-11-19
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "DefaultDriveManagerState.h"
#include "explorer/ExplorerManagerData.h"

using namespace explorer;

DefaultDriveManagerState::DefaultDriveManagerState(ExplorerManagerData& data) :
    DriveManagerState(data)
{
    //ctor
}

DefaultDriveManagerState::~DefaultDriveManagerState()
{
    //dtor
}

bool DefaultDriveManagerState::isDefault() const
{
    return true;
}

bool DefaultDriveManagerState::fillExplorerList()
{
    m_data.getExplorerPanel().getExplorerListCtrl().DeleteAllItems();
    m_data.getExplorerPanel().setTexts();
    return true;
}

bool DefaultDriveManagerState::fillExplorerList(const wxString& elementToSelect)
{
    fillExplorerList();
    return true;
}

DriveManagerState& DefaultDriveManagerState::getPreviousState()
{
    return *this;
}

void DefaultDriveManagerState::openElement(const std::vector<unsigned long>& indexes)
{
}

void DefaultDriveManagerState::deleteSelectedItems()
{

}

bool DefaultDriveManagerState::canCopyTo(const DriveManagerState& other) const
{
    return false;
}

bool DefaultDriveManagerState::canMoveTo(const DriveManagerState& other) const
{
    return false;
}

void DefaultDriveManagerState::copyElements(DriveManagerState& source)
{

}

void DefaultDriveManagerState::moveElements(DriveManagerState& source)
{

}


