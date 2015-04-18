/***************************************************************
 * Name:      DriveManagerListElement.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-03-12
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "DriveManagerListElement.h"

using namespace explorer;

DriveManagerListElement::DriveManagerListElement()
{
    //ctor
}

DriveManagerListElement::~DriveManagerListElement()
{
    //dtor
}

const wxString& DriveManagerListElement::getFilename() const
{
    return m_filename;
}

void DriveManagerListElement::setFilename(const wxString& filename)
{
    m_filename = filename;
}

