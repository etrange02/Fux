#ifndef DIRFILEMANAGER_H
#define DIRFILEMANAGER_H

#include <wx/wx.h>
#include "DirFileManagerData.h"
#include "tools/thread/IThreadManager.h"
#include "tools/thread/ThreadProcess.h"
#include "ThreadSafeQueue.h"

namespace tools
{
    namespace dir
    {
        class OperationFile;
        class DirFileUserInterface;

        class DirFileManager : public tools::thread::IThreadManager
        {
            public:
                /** Default constructor */
                DirFileManager(DirFileUserInterface& userInterface);
                /** Default destructor */
                virtual ~DirFileManager();

                void createCopyOperation  (const wxString& source, const wxString& destination);
                void createCutOperation   (const wxString& source, const wxString& destination);
                void createDeleteOperation(const wxString& source);
                void kill();
                void start();

                virtual void currentWorkFinished(tools::thread::ThreadProcess& threadProcess);

            private:
                void addOperationFile(OperationFile* operation);
                DirFileManagerData& getCopyData();
                DirFileManagerData& getCutData();
                DirFileManagerData& getDeleteData();
                void processOperation();
                void runThread();

            private:
                std::ThreadSafeQueue<OperationFile*> m_operations;
                DirFileManagerData m_copyData;
                DirFileManagerData m_cutData;
                DirFileManagerData m_deleteData;
                DirFileUserInterface& m_interface;
                tools::thread::ThreadProcess m_thread;
                int m_range;
                int m_maxRange;
                wxMutex m_mutex;
        };
    }
}

#endif // DIRFILEMANAGER_H
