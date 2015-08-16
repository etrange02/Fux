#ifndef OPERATIONFILE_H
#define OPERATIONFILE_H

#include <wx/wx.h>

namespace tools
{
    namespace dir
    {
        class DirFileManagerData;

        class OperationFile
        {
            public:
                /** Default constructor */
                OperationFile(const wxString& source);
                /** Default destructor */
                virtual ~OperationFile();

                const wxString& getSource() const;

                virtual wxString operationName() const;
                virtual void doWork();

            protected:
                virtual void doOperation() = 0;
                virtual void sendEvent()   = 0;
                bool askForRecursiveOperation(DirFileManagerData& data, const wxString& message);

            private:
                wxString m_source;
        };
    }
}

#endif // OPERATIONFILE_H
