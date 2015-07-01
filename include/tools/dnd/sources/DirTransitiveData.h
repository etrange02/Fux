#ifndef DIRTRANSITIVEDATA_H
#define DIRTRANSITIVEDATA_H

#include <wx/wx.h>
#include "tools/dnd/sources/TransitiveData.h"

namespace dragAndDrop
{
    class DirTransitiveData : public TransitiveData<wxString>
    {
        public:
            /** Default constructor */
            DirTransitiveData();
            /** Default destructor */
            virtual ~DirTransitiveData();
            /** Copy constructor
             *  \param other Object to copy from
             */
            DirTransitiveData(const DirTransitiveData& other);
            /** Assignment operator
             *  \param other Object to assign from
             *  \return A reference to this
             */
            DirTransitiveData& operator=(const DirTransitiveData& other);
        protected:
        private:
    };
}

#endif // DIRTRANSITIVEDATA_H
