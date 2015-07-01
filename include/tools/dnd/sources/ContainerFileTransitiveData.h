#ifndef CONTAINERFILETRANSITIVEDATA_H
#define CONTAINERFILETRANSITIVEDATA_H

#include <wx/wx.h>
#include "tools/dnd/sources/TransitiveData.h"

namespace dragAndDrop
{
    class ContainerFileTransitiveData : public TransitiveData<int>
    {
        public:
            /** Default constructor */
            ContainerFileTransitiveData();
            /** Default destructor */
            virtual ~ContainerFileTransitiveData();
            /** Copy constructor
             *  \param other Object to copy from
             */
            ContainerFileTransitiveData(const ContainerFileTransitiveData& other);
            /** Assignment operator
             *  \param other Object to assign from
             *  \return A reference to this
             */
            ContainerFileTransitiveData& operator=(const ContainerFileTransitiveData& other);
        protected:
        private:
            wxString m_file;
    };
}

#endif // CONTAINERFILETRANSITIVEDATA_H
