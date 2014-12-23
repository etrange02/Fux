#ifndef FACTORY_H
#define FACTORY_H

#include <wx/wx.h>
#include "Music.h"
#include "MusicFile.h"
#include "MusicFileReader.h"
#include "MusicFileWriter.h"

class Factory
{
    public:
        static Music* createMusic();
        static Music* createMusic(wxString& filename);
        static MusicFile* createMusicFileReader(Music& music);
        static MusicFile* createMusicFileWriter(const Music* inMusic, Music& outMusic);
};

#endif // FACTORY_H
