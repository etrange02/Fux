#ifndef CONFLICTINGOPERATIONFILE_H
#define CONFLICTINGOPERATIONFILE_H

#include "OperationFile.h"

namespace tools
{
    namespace dir
    {
        class DirFileManagerData;

        class ConflictingOperationFile : public OperationFile
        {
            public:
                /** Default constructor */
                ConflictingOperationFile(DirFileManagerData& data, const wxString& source, const wxString& destination);
                /** Default destructor */
                virtual ~ConflictingOperationFile();

                virtual void process();

            protected:
                DirFileManagerData& getData();
                const wxString& getDestination() const;

            private:
                DirFileManagerData& m_data;
                wxString m_destination;
        };
    }
}

#endif // CONFLICTINGOPERATIONFILE_H
