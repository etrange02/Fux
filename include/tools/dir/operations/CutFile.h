#ifndef CUTFILE_H
#define CUTFILE_H

#include "tools/dir/operations/ConflictingOperationFile.h"

extern const wxEventType wxEVT_FUX_DIR_FILE_CUT_DONE;

/**
 * Name space of tools
 */
namespace tools
{
    namespace dir
    {
        class CutFile : public ConflictingOperationFile
        {
            public:
                /** Default constructor */
                CutFile(DirFileManagerData& data, const wxString& source, const wxString& destination);
                /** Default destructor */
                virtual ~CutFile();

                virtual wxString operationName() const;

            protected:
                virtual void doOperation();
                virtual void sendEvent();

            private:
        };
    }
}

#endif // CUTFILE_H
