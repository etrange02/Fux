#ifndef CONTAINERFILETRANSITIVEDATA_H
#define CONTAINERFILETRANSITIVEDATA_H

#include <wx/wx.h>
#include "tools/dnd/dataObjects/TTransitiveData.h"

namespace explorer {
    class FileDriveManagerState;
}

namespace dragAndDrop
{
    class ContainerFileTransitiveData : public TTransitiveData<unsigned long>
    {
        public:
            /** Default constructor */
            ContainerFileTransitiveData(explorer::FileDriveManagerState& managerState);
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
            virtual wxArrayString getFilenames() const;
            virtual const std::vector<unsigned long>& deleteFromSource();

            virtual void doCopy();
            virtual void doCut();

            void setFilename(const wxString& filename);
            virtual bool isContainerFileKind() const;

        protected:
        private:
            wxString m_file;
            explorer::FileDriveManagerState& m_managerState;
    };
}

#endif // CONTAINERFILETRANSITIVEDATA_H
