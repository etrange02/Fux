#ifndef FILERENAMINGTHREAD_H
#define FILERENAMINGTHREAD_H

#include <wx/wx.h>
#include <wx/event.h>
#include "IRunnable.h"

namespace tools
{
    namespace thread
    {
        class FileRenamingThread : tools::thread::IRunnable
        {
            public:
                /** Default constructor */
                FileRenamingThread(const wxArrayString& files);
                /** Default destructor */
                virtual ~FileRenamingThread();

                /** Overload */
                virtual void process();

            protected:
            private:
                wxArrayString m_files;
        };
    }
}

#endif // FILERENAMINGTHREAD_H
