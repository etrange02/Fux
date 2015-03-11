/***************************************************************
 * Name:      findPathMenuElement.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-02-24
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "predicates/findPathMenuElement.h"
#include "MenuElement.h"
#include "MenuElementData.h"

findPathMenuElement::findPathMenuElement(const wxString& path) :
    m_path(path)
{
    //ctor
}

findPathMenuElement::~findPathMenuElement()
{
    //dtor
}

bool findPathMenuElement::operator()(const MenuElement& element)
{
    return element.getPath().IsSameAs(m_path);
}

bool findPathMenuElement::operator()(const MenuElementData& element)
{
    return element.getPath().IsSameAs(m_path);
}

