#ifndef FILEDELETIONTHREAD_H
#define FILEDELETIONTHREAD_H

#include <wx/wx.h>
#include <wx/event.h>
#include "Runnable.h"

/**
 * Name space of tools
 */
namespace tools
{
    /**
     * Name space of multi-threading tools
     */
    namespace thread
    {
        /** @brief File deleting as a task.
         */
        class FileDeletionThread : public tools::thread::Runnable
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
