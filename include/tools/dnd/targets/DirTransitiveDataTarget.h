#ifndef DIRTRANSITIVEDATATARGET_H
#define DIRTRANSITIVEDATATARGET_H

#include "tools/dnd/targets/TransitiveDataTarget.h"

namespace dragAndDrop
{
    class DirTransitiveDataTarget : public TransitiveDataTarget
    {
        public:
            /** Default constructor */
            DirTransitiveDataTarget();
            /** Default destructor */
            virtual ~DirTransitiveDataTarget();
        protected:
        private:
    };
}

#endif // DIRTRANSITIVEDATATARGET_H
