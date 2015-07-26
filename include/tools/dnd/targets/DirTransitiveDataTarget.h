#ifndef DIRTRANSITIVEDATATARGET_H
#define DIRTRANSITIVEDATATARGET_H

#include "tools/dnd/targets/TransitiveDataTarget.h"

namespace dragAndDrop
{
    class DirTransitiveDataTarget : public TransitiveDataTarget
    {
        public:
            /** Default constructor */
            DirTransitiveDataTarget(const wxListCtrl& source);
            /** Default destructor */
            virtual ~DirTransitiveDataTarget();

        protected:
            virtual bool isSameKind() const;
            virtual void doCopyProcessing(const wxArrayString& data, const long position);

        private:
    };
}

#endif // DIRTRANSITIVEDATATARGET_H
