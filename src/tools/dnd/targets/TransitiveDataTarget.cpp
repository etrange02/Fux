/***************************************************************
 * Name:      TransitiveDataTarget.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-06-26
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/dnd/targets/TransitiveDataTarget.h"
#include "tools/dnd/dataObjects/DataObject.h"

using namespace dragAndDrop;

/** @brief Constructor.
 */
TransitiveDataTarget::TransitiveDataTarget(DroppedMarkedLineListCtrl& source) :
    wxDropTarget(new DataObject),
    m_source(source),
    m_data(NULL),
    m_isSignificantLine(false),
    m_overDroppedLine(-1)
{
}

/** @brief Destructor.
 */
TransitiveDataTarget::~TransitiveDataTarget()
{
}

/** @brief Overload.
 *
 * @param WXUNUSED(x wxCoord
 * @return wxDragResult
 *
 */
wxDragResult TransitiveDataTarget::OnDragOver(wxCoord WXUNUSED(x), wxCoord y, wxDragResult WXUNUSED(def))
{
    if (m_source.GetItemCount() == 0)
        return wxDragCopy;

    m_isSignificantLine = true;

    const long position = m_source.convertCoordToPosition(y);
    if (position != m_overDroppedLine)
    {
        m_overDroppedLine = position;
        m_source.updateUI();
    }
    return wxDragCopy;//(def == wxDragMove) ? wxDragCopy : def;
}

/** @brief Overload.
 *
 * @param x wxCoord
 * @param y wxCoord
 * @return bool
 *
 */
bool TransitiveDataTarget::OnDrop(wxCoord x, wxCoord y)
{
    setNoSignificantDroppedLine();
    m_source.updateUI();
    return wxDropTarget::OnDrop(x, y);
}

/** @brief Overload.
 *
 * @return void
 *
 */
void TransitiveDataTarget::OnLeave()
{
    setNoSignificantDroppedLine();
    m_source.updateUI();
}

/** @brief Overload.
 *
 * @param WXUNUSED(x wxCoord
 * @return wxDragResult
 *
 */
wxDragResult TransitiveDataTarget::OnData(wxCoord WXUNUSED(x), wxCoord y, wxDragResult WXUNUSED(def))
{
    if (!GetData())
        return wxDragNone;

    DataObject* dataObject = (DataObject*) GetDataObject();
    m_data = dataObject->getData();
    m_data->displayName();
    doPaste(y);

    return wxDragCopy;
}

void TransitiveDataTarget::doPaste(wxCoord y)
{
    if (!m_data->isCopy() && isSameKind())
        doCut(y);
    else
        doCopy(y);
}

void TransitiveDataTarget::doCut(wxCoord y)
{
    const long position = m_source.convertCoordToPosition(y);
    doCutProcessing(*m_data, position);
}

void TransitiveDataTarget::doCopy(wxCoord y)
{
    wxArrayString items = m_data->getFilenames();
    const long position = m_source.convertCoordToPosition(y);
    doCopyProcessing(items, position);
}

void TransitiveDataTarget::setNoSignificantDroppedLine()
{
    m_isSignificantLine = false;
    m_overDroppedLine = -1;
}

bool TransitiveDataTarget::isSignificantDroppedLine() const
{
    return m_isSignificantLine;
}

long TransitiveDataTarget::getOverDroppedLine() const
{
    return m_overDroppedLine;
}

