#ifndef FILEDELETIONTHREAD_H
#define FILEDELETIONTHREAD_H

#include <wx/wx.h>
#include <wx/event.h>
#include "IRunnable.h"

namespace tools
{
    namespace thread
    {
        class FileDeletionThread : public tools::thread::IRunnable
{
            public:
                /** Default constructor */
                FileDeletionThread(const wxArrayString& files);
                /** Default destructor */
                virtual ~FileDeletionThread();

                /** Overload */
                virtual void process();

            protected:
            private:
                wxArrayString m_files;
        };
    }
}


#endif // FILEDELETIONTHREAD_H
