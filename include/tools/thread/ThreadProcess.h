#ifndef THREADPROCESS_H
#define THREADPROCESS_H

#include <wx/wx.h>
#include <wx/thread.h>
#include "IThreadManager.h"
#include "Runnable.h"

/** @brief Thread worker
 * Thread worker. The thread safety is based on semaphore (count)
 * @class tools::thread::ThreadProcess
 */

 namespace tools
{
    namespace thread
    {
        class IThreadManager;

        class ThreadProcess : public wxThread
        {
            public:
                /** Default constructor */
                ThreadProcess(IThreadManager* threadManager);
                /** Default destructor */
                virtual ~ThreadProcess();

                /** Sets a work (or task) */
                void setWork(Runnable* work);
                /** Tests the presence of a work */
                bool hasWork() const;
                /** Thread safety. Make the thread waiting if necessary */
                void semaphoreWait();
                /** Thread safety. Make the thread running if paused */
                void semaphorePost();

            protected:
                /** Overload. Thread works. */
                virtual ExitCode Entry();

            private:
                wxSemaphore m_semaphore;
                IThreadManager* m_threadManager;
                Runnable* m_work;
        };
    }
}

#endif // THREADPROCESS_H
