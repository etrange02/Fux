#ifndef CONTAINERFILETRANSITIVEDATATARGET_H
#define CONTAINERFILETRANSITIVEDATATARGET_H

#include "tools/dnd/targets/TransitiveDataTarget.h"

namespace explorer {
    class FileDriveManagerState;
}

namespace dragAndDrop
{
    class ContainerFileTransitiveDataTarget : public TransitiveDataTarget
    {
        public:
            /** Default constructor */
            ContainerFileTransitiveDataTarget(DroppedMarkedLineListCtrl& source, explorer::FileDriveManagerState& managerState);
            /** Default destructor */
            virtual ~ContainerFileTransitiveDataTarget();

        protected:
            virtual bool isSameKind() const;
            virtual void doCopyProcessing(const wxArrayString& data, const long position);
            virtual void doCutProcessing(TransitiveData& transitiveData, const long position);

        private:
            explorer::FileDriveManagerState& m_managerState;
    };
}

#endif // CONTAINERFILETRANSITIVEDATATARGET_H
