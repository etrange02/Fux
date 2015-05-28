#ifndef MUSICFILEWRITERTHREAD_H
#define MUSICFILEWRITERTHREAD_H

#include <wx/wx.h>
#include <wx/event.h>
#include "thread/IRunnable.h"
#include "MusicFileWriter.h"

extern const wxEventType wxEVT_FUX_MUSICFILE_WRITER_THREAD;

namespace music
{
    /** @brief Delegate for thread process
     */
    class MusicFileWriterThread : public tools::thread::IRunnable
    {
        public:
            /** Default constructor */
            MusicFileWriterThread(MusicFileWriter* musicFileWriter, wxWindow* parent);
            /** Default destructor */
            virtual ~MusicFileWriterThread();

            /** Overload */
            virtual void process();

        protected:
        private:
            void sendUpdatedLineEvent();

        private:
            MusicFileWriter* m_musicFileWriter;
            wxWindow* m_parent;
    };
}

#endif // MUSICFILEWRITERTHREAD_H
