#ifndef OPERATIONFILE_H
#define OPERATIONFILE_H

#include <wx/wx.h>
#include "tools/thread/Runnable.h"

namespace tools {
    namespace thread {
        class ThreadProcess;
    }
}

/**
 * Name space of tools
 */
namespace tools
{
    namespace dir
    {
        class DirFileManagerData;
        class DirFileCommunicationFactory;

        class OperationFile : public tools::thread::Runnable
        {
            public:
                /** Default constructor */
                OperationFile(const wxString& source);
                /** Default destructor */
                virtual ~OperationFile();

                /** Overload */
                virtual void process();

                const wxString& getSource() const;

                virtual wxString operationName() const;

                void setThread(tools::thread::ThreadProcess* thread);
                void setFactory(DirFileCommunicationFactory* factory);

            protected:
                virtual void doOperation() = 0;
                virtual void sendEvent()   = 0;
                bool askForRecursiveOperation(DirFileManagerData& data, const wxString& message);
                wxString getSourceFilename() const;

            private:
                wxString m_source;
                tools::thread::ThreadProcess* m_thread;
                DirFileCommunicationFactory* m_factory;
        };
    }
}

#endif // OPERATIONFILE_H
