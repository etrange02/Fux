/***************************************************************
 * Name:      DeletedLines.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-06-13
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "DeletedLines.h"

using namespace music;

DeletedLines::DeletedLines() :
    m_position(-1),
    m_positionInSearch(-1)
{
}

DeletedLines::DeletedLines(const long position, const long positionInSearch) :
    m_position(position),
    m_positionInSearch(positionInSearch)
{

}

DeletedLines::~DeletedLines()
{
}

void DeletedLines::setPosition(const long position)
{
    m_position = position;
}

void DeletedLines::setPositionInSearch(const long position)
{
    m_positionInSearch = position;
}

long DeletedLines::getPosition() const
{
    return m_position;
}

long DeletedLines::getPositionInSearch() const
{
    return m_positionInSearch;
}

