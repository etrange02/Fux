/***************************************************************
 * Name:      findMenuElementById.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-02-24
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "predicates/findMenuElementById.h"
#include "MenuElement.h"

findMenuElementById::findMenuElementById(const int id) :
    m_id(id)
{
    //ctor
}

findMenuElementById::~findMenuElementById()
{
    //dtor
}

bool findMenuElementById::operator()(const explorer::MenuElement& element)
{
    return (m_id == element.getLeftID()) || (m_id == element.getRightID());
}
