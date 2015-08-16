#ifndef DIRFILEMANAGER_H
#define DIRFILEMANAGER_H

#include <wx/wx.h>
#include <list>
#include "DirFileManagerData.h"

namespace tools
{
    namespace dir
    {
        class OperationFile;

        class DirFileManager
        {
            public:
                /** Default constructor */
                DirFileManager();
                /** Default destructor */
                virtual ~DirFileManager();

                void createCopyOperation  (const wxString& source, const wxString& destination);
                void createCutOperation   (const wxString& source, const wxString& destination);
                void createDeleteOperation(const wxString& source);

            private:
                void addOperationFile(OperationFile* operation);
                DirFileManagerData& getCopyData();
                DirFileManagerData& getCutData();
                DirFileManagerData& getDeleteData();

            private:
                std::list<OperationFile*> m_operations;
                DirFileManagerData m_copyData;
                DirFileManagerData m_cutData;
                DirFileManagerData m_deleteData;
        };
    }
}

#endif // DIRFILEMANAGER_H
