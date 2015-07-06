#ifndef CONTAINERFILETRANSITIVEDATA_H
#define CONTAINERFILETRANSITIVEDATA_H

#include <wx/wx.h>
#include "tools/dnd/dataObjects/TTransitiveData.h"

namespace dragAndDrop
{
    class ContainerFileTransitiveData : public TTransitiveData<int>
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
            virtual const wxString getName() const;

            virtual bool isSameKind() const;
            virtual void doCopy();
            virtual void doCut();
            virtual void doPaste();

            void setFilename(const wxString& filename);
        protected:
        private:
            wxString m_file;
    };
}

#endif // CONTAINERFILETRANSITIVEDATA_H
