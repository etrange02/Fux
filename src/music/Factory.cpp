/***************************************************************
 * Name:      Factory.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2014-12-17
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "music/Factory.h"

using namespace music;

/** @brief Creates an empty Music instance
 *
 * @return Music*
 *
 */
Music* Factory::createMusic()
{
    return new Music;
}

/** @brief Creates a music instance
 *
 * @param filename the file name of the music file
 * @return Music*
 *
 */
Music* Factory::createMusic(wxString& filename)
{
    return new Music(filename);
}

/** @brief Creates a copy of a music.
 *
 * @param music instance to copy
 * @return Music*
 *
 */
Music* Factory::createMusic(const Music& music)
{
    return new Music(music);
}

/** @brief Creates a MusicFile for reading TAG value in music file
 *
 * @param music a music
 * @return MusicFile*
 *
 */
MusicFile* Factory::createMusicFileReader(Music& music)
{
    return new MusicFileReader(music);
}

/** @brief Creates an envelop to thread reading
 *
 * @param music Music&
 * @return MusicFileReaderThread*
 * @see Factory::createMusicFileReader
 */
MusicFileReaderThread* Factory::createMusicFileReaderThread(Music& music, wxWindow* parent)
{
    return new MusicFileReaderThread(new MusicFileReader(music), parent);
}

/** @brief Creates a MusicFile for writing TAG value in music file.
 * Can rename file if needed.
 * @param inMusic source
 * @param outMusic target
 * @return MusicFile*
 *
 */
MusicFile* Factory::createMusicFileWriter(Music* inMusic, Music* outMusic)
{
    return new MusicFileWriter(inMusic, outMusic);
}

MusicFileWriterThread* Factory::createMusicFileWriterThread(Music* inMusic, Music* outMusic, wxWindow* parent)
{
    return new MusicFileWriterThread(new MusicFileWriter(inMusic, outMusic), parent);
}

