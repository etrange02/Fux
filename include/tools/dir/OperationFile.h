#ifndef OPERATIONFILE_H
#define OPERATIONFILE_H

#include <wx/wx.h>
#include "IRunnable.h"

namespace tools
{
    namespace dir
    {
        class DirFileManagerData;

        class OperationFile : public tools::thread::IRunnable
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

            protected:
                virtual void doOperation() = 0;
                virtual void sendEvent()   = 0;
                bool askForRecursiveOperation(DirFileManagerData& data, const wxString& message);
                wxString getSourceFilename() const;

            private:
                wxString m_source;
        };
    }
}

#endif // OPERATIONFILE_H
