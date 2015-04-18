/***************************************************************
 * Name:      MusicFileReader.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2014-12-17
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "MusicFileReader.h"

using namespace TagLib;
using namespace ::music;

MusicFileReader::MusicFileReader(Music& music) :
    m_music(music)
{
    m_music.SetName(m_music.GetFileName().AfterLast(wxFileName::GetPathSeparator()).BeforeLast('.'));
}

MusicFileReader::~MusicFileReader()
{
    //dtor
}

void MusicFileReader::process()
{
    if (m_music.GetFileName().IsEmpty() || !wxFileExists(m_music.GetFileName()))
        return;

    FillFields();
    ImageExtracting();
    m_music.ShrinkData();
}

/** @brief Fill music data
 * Fill music data thanks to filename
 * @return void
 *
 */
void MusicFileReader::FillFields()
{
    m_music.SetPath(m_music.GetFileName().BeforeLast(wxFileName::GetPathSeparator()));
    m_music.SetExtension(m_music.GetFileName().AfterLast('.'));

    TagLib::FileRef fileTAG = TagLib::FileRef(TagLib::FileName(m_music.GetFileName().fn_str()));

    m_music.SetArtists(wxString(fileTAG.tag()->artist().toCString(true), wxConvUTF8));
    m_music.SetAlbum(wxString(fileTAG.tag()->album().toCString(true), wxConvUTF8));
    m_music.SetTitle(wxString(fileTAG.tag()->title().toCString(true), wxConvUTF8));
    m_music.SetGenres(wxString(fileTAG.tag()->genre().toCString(true), wxConvUTF8));
    m_music.SetYear(fileTAG.tag()->year());
    m_music.SetDuration(fileTAG.audioProperties()->length());
    m_music.SetDebit(fileTAG.audioProperties()->bitrate());
    m_music.SetSize(fileTAG.file()->length());
}

/** @brief Fill sleeves (images)
 * Fill images associated with the music file
 * @return void
 *
 */
void MusicFileReader::ImageExtracting()
{
    TagLib::MPEG::File f(TagLib::FileName(m_music.GetFileName().fn_str()));
    if(f.ID3v2Tag())
    {
        TagLib::ID3v2::FrameList l = f.ID3v2Tag()->frameList("APIC");
        if (!l.isEmpty())
        {
            TagLib::ID3v2::AttachedPictureFrame *p = static_cast<TagLib::ID3v2::AttachedPictureFrame *>(l.front());

            if (p != NULL && !p->picture().isEmpty())
            {
                wxMemoryOutputStream imgStreamOut;
                imgStreamOut.Write(p->picture().data(), p->picture().size());
                wxMemoryInputStream stream(imgStreamOut);
                wxString typeImage(p->mimeType().toCString(true), wxConvLocal);

                if (typeImage.IsSameAs(_T("image/jpeg")) || typeImage.IsSameAs(_T("image/jpg")))
                    m_music.SetRecordSleeve(new wxImage(stream, _T("image/jpeg")));
            }
        }
    }
}

Music* MusicFileReader::getMusic()
{
    return &m_music;
}

