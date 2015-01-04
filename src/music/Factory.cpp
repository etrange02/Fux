/***************************************************************
 * Name:      Factory.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2014-12-17
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "../../include/music/Factory.h"

using namespace fux::music;

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
MusicFileReaderThread* Factory::createMusicFileReaderThread(Music& music, wxWindow* parent, int position)
{
    return new MusicFileReaderThread(new MusicFileReader(music), parent, position);
}

/** @brief Creates a MusicFile for writing TAG value in music file.
 * Can rename file if needed.
 * @param inMusic source
 * @param outMusic target
 * @return MusicFile*
 *
 */
MusicFile* Factory::createMusicFileWriter(const Music* inMusic, Music& outMusic)
{
    return new MusicFileWriter(inMusic, outMusic);
}

