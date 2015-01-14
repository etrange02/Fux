#ifndef MUSICFILEREADERTHREAD_H
#define MUSICFILEREADERTHREAD_H

#include <wx/wx.h>
#include <wx/event.h>
#include "IRunnable.h"
#include "MusicFileReader.h"

extern const wxEventType wxEVT_FUX_MUSICFILE_READER_THREAD;

/** @brief Delegate for thread processing
 */
class MusicFileReaderThread : public fux::thread::IRunnable
{
    public:
        /** Default constructor */
        MusicFileReaderThread(MusicFileReader* musicFileReader, wxWindow* parent);
        /** Default destructor */
        virtual ~MusicFileReaderThread();

        /** Overload */
        virtual void process();

    protected:
    private:
        void sendUpdatedLineEvent();

        MusicFileReader* m_musicFileReader;
        wxWindow* m_parent;
};

#endif // MUSICFILEREADERTHREAD_H
