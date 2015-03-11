#include "DriveManagerListElement.h"

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

