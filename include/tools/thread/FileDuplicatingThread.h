#ifndef FILEDUPLICATINGTHREAD_H
#define FILEDUPLICATINGTHREAD_H

#include <wx/wx.h>
#include <wx/event.h>
#include "IRunnable.h"

namespace tools
{
    namespace thread
    {
        class FileDuplicatingThread : tools::thread::IRunnable
        {
            public:
                /** Default constructor */
                FileDuplicatingThread(const wxArrayString& files);
                /** Default destructor */
                virtual ~FileDuplicatingThread();

                /** Overload */
                virtual void process();

            protected:
            private:
                wxArrayString m_files;
        };
    }
}

#endif // FILEDUPLICATINGTHREAD_H
