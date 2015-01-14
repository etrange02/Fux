#ifndef MUSICFILEREADER_H
#define MUSICFILEREADER_H

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

class MusicFileReader : public MusicFile
{
    public:
        /** Default constructor */
        MusicFileReader(Music& music);
        /** Default destructor */
        virtual ~MusicFileReader();

        virtual void process();

        Music* getMusic();

    protected:
        void FillFields();
        void ImageExtracting();

    private:
        Music& m_music; //!< Member variable "m_music"
};

#endif // MUSICFILEREADER_H
