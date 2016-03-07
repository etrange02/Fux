#ifndef ASKFORRECURSIVEOPERATIONDATA_H
#define ASKFORRECURSIVEOPERATIONDATA_H

#include <wx/wx.h>

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
        class AskForRecursiveOperationData
        {
            public:
                /** Default constructor */
                AskForRecursiveOperationData(tools::thread::ThreadProcess* thread, const wxString& message);
                /** Copy constructor
                 *  \param other Object to copy from
                 */
                AskForRecursiveOperationData(const AskForRecursiveOperationData& other);
                /** Default destructor */
                virtual ~AskForRecursiveOperationData();

                bool isRecursive();
                void setRecursive(bool isRecursive);
                bool canBeOverWritten();
                void setOverWrite(bool overWrite);
                void postThread();
                void waitThread();
                const wxString& getMessage() const;

                tools::thread::ThreadProcess* m_threadProcess;
            protected:

            private:
                const wxString& m_message;
                bool m_isRecursive; //!< Member variable "m_isRecursive"
                bool m_canBeOverWritten; //!< Member variable "m_canBeOverWrite"
        };
    }
}

#endif // ASKFORRECURSIVEOPERATIONDATA_H
