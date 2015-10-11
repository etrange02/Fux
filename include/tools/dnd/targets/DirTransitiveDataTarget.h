#ifndef DIRTRANSITIVEDATATARGET_H
#define DIRTRANSITIVEDATATARGET_H

#include "tools/dnd/targets/TransitiveDataTarget.h"

namespace tools {
    namespace dir {
        class DirFileManager;
    }
}

namespace dragAndDrop
{
    class DirTransitiveDataTarget : public TransitiveDataTarget
    {
        public:
            /** Default constructor */
            DirTransitiveDataTarget(DroppedMarkedLineListCtrl& source, const wxString& directory, tools::dir::DirFileManager* dirFileManager);
            /** Default destructor */
            virtual ~DirTransitiveDataTarget();
            void setDirectory(const wxString& directory);

        protected:
            virtual bool isSameKind() const;
            virtual void doCopyProcessing(const wxArrayString& data, const long position);
            virtual void doCutProcessing(TransitiveData& transitiveData, const long position);

        private:
            wxString m_directory;
            tools::dir::DirFileManager* m_dirFileManager;
    };
}

#endif // DIRTRANSITIVEDATATARGET_H
