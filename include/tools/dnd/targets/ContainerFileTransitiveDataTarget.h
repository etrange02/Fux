#ifndef CONTAINERFILETRANSITIVEDATATARGET_H
#define CONTAINERFILETRANSITIVEDATATARGET_H

#include "tools/dnd/targets/TransitiveDataTarget.h"

namespace dragAndDrop
{
    class ContainerFileTransitiveDataTarget : public TransitiveDataTarget
    {
        public:
            /** Default constructor */
            ContainerFileTransitiveDataTarget();
            /** Default destructor */
            virtual ~ContainerFileTransitiveDataTarget();
        protected:
        private:
    };
}

#endif // CONTAINERFILETRANSITIVEDATATARGET_H
