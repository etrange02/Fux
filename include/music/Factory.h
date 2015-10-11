#ifndef FACTORY_H
#define FACTORY_H

#include <wx/wx.h>
#include <memory>
#include "music/Music.h"
#include "music/MusicFile.h"
#include "music/MusicFileReader.h"
#include "music/MusicFileWriter.h"
#include "music/MusicFileReaderThread.h"
#include "music/MusicFileWriterThread.h"

/** @brief Music Factory
 *
 * @class music::Factory
 */

namespace music
{
    class Factory
    {
        public:
            static Music* createMusic();
            static Music* createMusic(wxString& filename);
            static Music* createMusic(const Music& music);
            static MusicFileReader* createMusicFileReader(std::shared_ptr<Music>& music);
            static MusicFileWriter* createMusicFileWriter(Music* inMusic, std::shared_ptr<Music>& outMusic);
            static MusicFileReaderThread* createMusicFileReaderThread(std::shared_ptr<Music>& music, wxWindow* parent);
            static MusicFileWriterThread* createMusicFileWriterThread(Music* inMusic, std::shared_ptr<Music>& outMusic, wxWindow* parent);
    };
}


#endif // FACTORY_H
