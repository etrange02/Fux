/***************************************************************
 * Name:      ContainerFileTransitiveDataTarget.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-06-26
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/dnd/targets/ContainerFileTransitiveDataTarget.h"
#include "explorer/state/FileDriveManagerState.h"
#include "tools/dnd/dataObjects/ContainerFileTransitiveData.h"
#include <algorithm>

using namespace dragAndDrop;

/** @brief Constructor.
 */
ContainerFileTransitiveDataTarget::ContainerFileTransitiveDataTarget(DroppedMarkedLineListCtrl& source, explorer::FileDriveManagerState& managerState) :
    TransitiveDataTarget(source),
    m_managerState(managerState)
{
}

/** @brief Destructor.
 */
ContainerFileTransitiveDataTarget::~ContainerFileTransitiveDataTarget()
{
}

bool ContainerFileTransitiveDataTarget::isSameKind() const
{
    if (m_data == NULL)
        return false;
    return m_data->isContainerFileKind();
}

void ContainerFileTransitiveDataTarget::doCopyProcessing(const wxArrayString& data, const long position)
{
    m_managerState.insertElements(data, position);
}

void ContainerFileTransitiveDataTarget::doCutProcessing(TransitiveData& transitiveData, const long position)
{
    ContainerFileTransitiveData& fileTransitiveData = static_cast<ContainerFileTransitiveData&>(transitiveData);

    const unsigned long pos = position;
    const std::vector<unsigned long>& items = fileTransitiveData.getItems();
    std::vector<unsigned long>::const_iterator iter = std::find(items.begin(), items.end(), pos);
    if (iter == items.end())
        return;

    m_managerState.insertElements(fileTransitiveData.getFilenames(), position);
    fileTransitiveData.deleteFromSource();
}

