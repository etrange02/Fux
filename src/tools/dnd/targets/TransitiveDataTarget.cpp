#include "tools/dnd/targets/TransitiveDataTarget.h"
#include "tools/dnd/dataObjects/DataObject.h"

using namespace dragAndDrop;

/** @brief Constructor.
 */
TransitiveDataTarget::TransitiveDataTarget(const wxListCtrl& source) :
    wxDropTarget(new DataObject),
    m_source(source),
    m_data(NULL)
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
wxDragResult TransitiveDataTarget::OnDragOver(wxCoord WXUNUSED(x), wxCoord WXUNUSED(y), wxDragResult WXUNUSED(def))
{
    return wxDragCopy;//(def == wxDragMove) ? wxDragCopy : def;
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

void TransitiveDataTarget::doCut(wxCoord y) // = 0
{

}

void TransitiveDataTarget::doCopy(wxCoord y)
{
    wxArrayString items = m_data->getFilenames();
    const long position = convertCoordToPosition(y);
    doCopyProcessing(items, position);
}

long TransitiveDataTarget::convertCoordToPosition(wxCoord y)
{
    long itemCount = m_source.GetItemCount();

    if (itemCount == 0)
        return 0;

    long position = 0;
    long min = m_source.GetTopItem();
    bool found = false;
    wxPoint point;
    //position du dernier item visible
    if (itemCount < m_source.GetCountPerPage() || itemCount == (m_source.GetCountPerPage() + min))//Le dernier item est visible
    {
        wxRect rect;
        m_source.GetItemRect(itemCount-1, rect);//emplacement physique du dernier item
        if (rect.GetY() + rect.GetHeight() < y)//le relâchement de la souris est après le dernier item
            return itemCount;
        position = m_source.GetItemCount();
    }
    else
        position = min + m_source.GetCountPerPage();

    while (itemCount > 0 && position >= min && !found)//Recherche la position par rapport au bord supérieur de la case
    {
        --position;
        m_source.GetItemPosition(position, point);
        found = (y > point.y);
        --itemCount;
    }
    return position;
}

