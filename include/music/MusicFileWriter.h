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
        MusicFileWriter(const Music* src, Music& dst);
        /** Default destructor */
        virtual ~MusicFileWriter();

        virtual void process();
    protected:
    private:
        void renameFile();
        void fillData();
        void saveImage();

        const Music* m_musicSrc; //!< Member variable "m_musicIn"
        Music& m_musicDst; //!< Member variable "m_musicOut"
};

#endif // MUSICFILEWRITER_H
