#ifndef MUSICFILEWRITER_H
#define MUSICFILEWRITER_H

#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/dir.h>
#include <wx/mstream.h>
#include "Music.h"
#include "MusicFile.h"

// TagLib
#include <tag.h>
#include <fileref.h>
#include <taglib.h>
#include <mpegfile.h>
#include <id3v2tag.h>
#include <attachedpictureframe.h>

class MusicFileWriter : public MusicFile
{
    public:
        /** Default constructor */
        MusicFileWriter(Music* src, Music* dst);
        /** Default destructor */
        virtual ~MusicFileWriter();

        /** Overload */
        virtual void process();

        Music* getMusic() const;

    protected:
    private:
        /** Renames the music file. */
        void renameFile();
        void fillData();
        void saveImage();
        void copy();
        void refreshFileName(Music& music);

        Music* m_musicSrc; //!< Member variable "m_musicIn"
        Music* m_musicDst; //!< Member variable "m_musicOut"
};

#endif // MUSICFILEWRITER_H
