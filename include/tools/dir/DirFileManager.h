#ifndef DIRFILEMANAGER_H
#define DIRFILEMANAGER_H

#include <wx/wx.h>
#include "DirFileManagerData.h"
#include "tools/thread/AbstractThreadManager.h"

namespace tools {
    namespace thread {
        class Runnable;
        class ThreadProcess;
    }
}

namespace tools
{
    namespace dir
    {
        class OperationFile;
        class DirFileUserInterface;
        class DirFileCommunicationFactory;

        class DirFileManager : public tools::thread::AbstractThreadManager
        {
            public:
                /** Default constructor */
                DirFileManager(DirFileCommunicationFactory& factory);
                /** Default destructor */
                virtual ~DirFileManager();

                void createCopyOperation  (const wxString& source, const wxString& destination);
                void createCutOperation   (const wxString& source, const wxString& destination);
                void createDeleteOperation(const wxString& source);

            protected:
                virtual unsigned int getThreadCount();
                virtual void doBeforeAddingWork(tools::thread::Runnable& work);
                virtual void doAfterAddingWork(tools::thread::Runnable& work);
                virtual void doBeforeProcessingWork(tools::thread::Runnable& work, tools::thread::ThreadProcess& threadProcess);
                virtual void doOnNoWork();
                /** Awakes a worker if one is sleeping */
                virtual void activateAWorker();

            private:
                DirFileManagerData& getCopyData();
                DirFileManagerData& getCutData();
                DirFileManagerData& getDeleteData();

            private:
                DirFileManagerData m_copyData;
                DirFileManagerData m_cutData;
                DirFileManagerData m_deleteData;
                DirFileCommunicationFactory& m_factory;
                DirFileUserInterface* m_interface;
                int m_range;
                int m_maxRange;
        };
    }
}

#endif // DIRFILEMANAGER_H
