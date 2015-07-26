#include "tools/dnd/targets/ContainerFileTransitiveDataTarget.h"

using namespace dragAndDrop;

/** @brief Constructor.
 */
ContainerFileTransitiveDataTarget::ContainerFileTransitiveDataTarget(const wxListCtrl& source) :
    TransitiveDataTarget(source)
{
}

/** @brief Destructor.
 */
ContainerFileTransitiveDataTarget::~ContainerFileTransitiveDataTarget()
{
}

bool ContainerFileTransitiveDataTarget::isSameKind() const
{
    if (m_data == NULL)
        return false;
    return m_data->isContainerFileKind();
}

void ContainerFileTransitiveDataTarget::doCopyProcessing(const wxArrayString& data, const long position)
{

}

