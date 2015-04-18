#ifndef FACTORY_H
#define FACTORY_H

#include <wx/wx.h>
#include "Music.h"
#include "MusicFile.h"
#include "MusicFileReader.h"
#include "MusicFileWriter.h"
#include "MusicFileReaderThread.h"
#include "MusicFileWriterThread.h"

/** @brief Music Factory
 *
 * @class fux::music::Factory
 */

namespace music
{
    class Factory
    {
        public:
            static Music* createMusic();
            static Music* createMusic(wxString& filename);
            static Music* createMusic(const Music& music);
            static MusicFile* createMusicFileReader(Music& music);
            static MusicFile* createMusicFileWriter(Music* inMusic, Music* outMusic);
            static MusicFileReaderThread* createMusicFileReaderThread(Music& music, wxWindow* parent);
            static MusicFileWriterThread* createMusicFileWriterThread(Music* inMusic, Music* outMusic, wxWindow* parent);
    };
}


#endif // FACTORY_H
