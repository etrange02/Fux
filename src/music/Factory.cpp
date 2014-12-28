/***************************************************************
 * Name:      Factory.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2014-12-17
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "../../include/music/Factory.h"

using namespace fux::music;

Music* Factory::createMusic()
{
    return new Music;
}

Music* Factory::createMusic(wxString& filename)
{
    return new Music(filename);
}

MusicFile* Factory::createMusicFileReader(Music& music)
{
    return new MusicFileReader(music);
}

MusicFileReaderThread* Factory::createMusicFileReaderThread(Music& music)
{
    return new MusicFileReaderThread(new MusicFileReader(music));
}

MusicFile* Factory::createMusicFileWriter(const Music* inMusic, Music& outMusic)
{
    return new MusicFileWriter(inMusic, outMusic);
}

