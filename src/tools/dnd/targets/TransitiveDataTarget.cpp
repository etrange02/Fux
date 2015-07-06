#include "tools/dnd/targets/TransitiveDataTarget.h"
#include "tools/dnd/dataObjects/DataObject.h"
#include "tools/dnd/dataObjects/TransitiveData.h"

using namespace dragAndDrop;

/** @brief Constructor.
 */
TransitiveDataTarget::TransitiveDataTarget() :
    wxDropTarget(new DataObject)
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
wxDragResult TransitiveDataTarget::OnData(wxCoord WXUNUSED(x), wxCoord WXUNUSED(y), wxDragResult WXUNUSED(def))
{
    if (!GetData())
        return wxDragNone;

    DataObject* dataObject = (DataObject*) GetDataObject();
    TransitiveData* data = dataObject->getData();
    data->displayName();

    data->doPaste();

    return wxDragCopy;
}

