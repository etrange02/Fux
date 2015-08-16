/***************************************************************
 * Name:      DirTransitiveDataTarget.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-06-26
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/dnd/targets/DirTransitiveDataTarget.h"
#include "tools/dnd/dataObjects/DirTransitiveData.h"

using namespace dragAndDrop;

/** @brief Constructor.
 */
DirTransitiveDataTarget::DirTransitiveDataTarget(DroppedMarkedLineListCtrl& source) :
    TransitiveDataTarget(source)
{
}

/** @brief Destructor.
 */
DirTransitiveDataTarget::~DirTransitiveDataTarget()
{
}

bool DirTransitiveDataTarget::isSameKind() const
{
    if (m_data == NULL)
        return false;
    return m_data->isDirKind();
}

void DirTransitiveDataTarget::doCopyProcessing(const wxArrayString& data, const long position)
{
    wxLogMessage("Must be implemented");
    ///TODO: DirTransitiveDataTarget::doCopyProcessing
}

void DirTransitiveDataTarget::doCutProcessing(TransitiveData& transitiveData, const long position)
{
    wxLogMessage("Must be implemented");
    ///TODO: DirTransitiveDataTarget::doCutProcessing
    DirTransitiveData& fileTransitiveData = static_cast<DirTransitiveData&>(transitiveData);
}




