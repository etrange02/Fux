#include "tools/dnd/targets/DirTransitiveDataTarget.h"

using namespace dragAndDrop;

/** @brief Constructor.
 */
DirTransitiveDataTarget::DirTransitiveDataTarget(const wxListCtrl& source) :
    TransitiveDataTarget(source)
{
}

/** @brief Destructor.
 */
DirTransitiveDataTarget::~DirTransitiveDataTarget()
{
}

bool DirTransitiveDataTarget::isSameKind() const
{
    if (m_data == NULL)
        return false;
    return m_data->isDirKind();
}

void DirTransitiveDataTarget::doCopyProcessing(const wxArrayString& data, const long position)
{

}




