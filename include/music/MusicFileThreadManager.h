#ifndef MUSICFILETHREADMANAGER_H
#define MUSICFILETHREADMANAGER_H

#include <wx/wx.h>
#include "ThreadSafeQueue.h"
#include "MusicFile.h"
#include "MusicFileReader.h"
#include "MusicFileWriter.h"

class MusicFileThreadManager
{
    public:
        /** Default constructor */
        MusicFileThreadManager();
        /** Default destructor */
        virtual ~MusicFileThreadManager();
        /** Copy constructor
         *  \param other Object to copy from
         */
        MusicFileThreadManager(const MusicFileThreadManager& other);
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        MusicFileThreadManager& operator=(const MusicFileThreadManager& other);

        void addMusicFile(MusicFile* musicFile);

        void start();

    private:
        void processQueue();

        std::ThreadSafeQueue<MusicFile*> m_musicFiles;
};

#endif // MUSICFILETHREADMANAGER_H
