#ifndef CONTAINERFILETRANSITIVEDATATARGET_H
#define CONTAINERFILETRANSITIVEDATATARGET_H

#include "tools/dnd/targets/TransitiveDataTarget.h"

namespace dragAndDrop
{
    class ContainerFileTransitiveDataTarget : public TransitiveDataTarget
    {
        public:
            /** Default constructor */
            ContainerFileTransitiveDataTarget(const wxListCtrl& source);
            /** Default destructor */
            virtual ~ContainerFileTransitiveDataTarget();

        protected:
            virtual bool isSameKind() const;
            virtual void doCopyProcessing(const wxArrayString& data, const long position);

        private:
    };
}

#endif // CONTAINERFILETRANSITIVEDATATARGET_H
