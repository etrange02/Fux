#ifndef MUSICFILEREADER_H
#define MUSICFILEREADER_H

#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/dir.h>
#include <wx/mstream.h>
#include <memory>
#include "Music.h"
#include "MusicFile.h"

// TagLib
#include <tag.h>
#include <fileref.h>
#include <taglib.h>
#include <mpegfile.h>
#include <id3v2tag.h>
#include <attachedpictureframe.h>

namespace music
{
    class MusicFileReader : public MusicFile
    {
        public:
            /** Default constructor */
            MusicFileReader(std::shared_ptr<Music>& music);
            /** Default destructor */
            virtual ~MusicFileReader();

            virtual void process();

            Music* getMusic();

        protected:
            void FillFields();
            void ImageExtracting();

        private:
            std::shared_ptr<Music> m_music; //!< Member variable "m_music"
    };
}

#endif // MUSICFILEREADER_H
