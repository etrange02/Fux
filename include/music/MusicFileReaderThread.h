#ifndef MUSICFILEREADERTHREAD_H
#define MUSICFILEREADERTHREAD_H

#include "IRunnable.h"
#include "MusicFileReader.h"

/** @brief Delegate for thread processing
 */
class MusicFileReaderThread : public fux::thread::IRunnable
{
    public:
        /** Default constructor */
        MusicFileReaderThread(MusicFileReader* musicFileReader);
        /** Default destructor */
        virtual ~MusicFileReaderThread();

        virtual void process();

    protected:
    private:
        MusicFileReader* m_musicFileReader;
};

#endif // MUSICFILEREADERTHREAD_H
