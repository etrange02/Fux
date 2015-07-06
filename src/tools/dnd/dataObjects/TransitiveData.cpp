/***************************************************************
 * Name:      TransitiveData.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-06-24
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/dnd/dataObjects/TransitiveData.h"

using namespace dragAndDrop;

/** @brief Constructor.
 */
TransitiveData::TransitiveData()
{
}

/** @brief Destructor.
 */
TransitiveData::~TransitiveData()
{
}

void TransitiveData::displayName() const
{
    wxString name = getName();
    wxLogMessage(getName());
}

void TransitiveData::doPaste()
{
    if (isSameKind())
        doCut();
    else
        doCopy();
}

