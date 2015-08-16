#ifndef DELETEFILE_H
#define DELETEFILE_H

#include "OperationFile.h"

extern const wxEventType wxEVT_FUX_DIR_FILE_DELETE_DONE;

namespace tools
{
    namespace dir
    {
        class DirFileManagerData;

        class DeleteFile : public OperationFile
        {
            public:
                /** Default constructor */
                DeleteFile(DirFileManagerData& data, const wxString& source);
                /** Default destructor */
                virtual ~DeleteFile();

                virtual wxString operationName() const;

            protected:
                DirFileManagerData& getData();
                virtual void doOperation();
                virtual void sendEvent();

            private:
                DirFileManagerData& m_data;
        };
    }
}

#endif // DELETEFILE_H
