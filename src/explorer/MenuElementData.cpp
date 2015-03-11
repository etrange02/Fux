#include "MenuElementData.h"

MenuElementData::MenuElementData()
{
    //ctor
}

MenuElementData::~MenuElementData()
{
    //dtor
}

MenuElementData::MenuElementData(const MenuElementData& other)
{
    *this = other;
}

MenuElementData& MenuElementData::operator=(const MenuElementData& other)
{
    if (this == &other)
        return *this;

    m_label = other.m_label;
    m_path  = other.m_path;
    return *this;
}

void MenuElementData::setLabel(const wxString& label)
{
    m_label = label;
}

void MenuElementData::setPath(const wxString& path)
{
    m_path = path;
}

const wxString& MenuElementData::getLabel() const
{
    return m_label;
}

const wxString& MenuElementData::getPath() const
{
    return m_path;
}

