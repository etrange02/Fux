#ifndef COPYFILE_H
#define COPYFILE_H

#include "ConflictingOperationFile.h"

extern const wxEventType wxEVT_FUX_DIR_FILE_COPY_DONE;

namespace tools
{
    namespace dir
    {
        class CopyFile : public ConflictingOperationFile
        {
            public:
                /** Default constructor */
                CopyFile(DirFileManagerData& data, const wxString& source, const wxString& destination);
                /** Default destructor */
                virtual ~CopyFile();

                virtual wxString operationName() const;

            protected:
                virtual void doOperation();
                virtual void sendEvent();

            private:
        };
    }
}

#endif // COPYFILE_H
