/***************************************************************
 * Name:      MusicFileWriter.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2014-12-17
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "MusicFileWriter.h"
#include "Tools.h"

using namespace TagLib;
using namespace ::music;

MusicFileWriter::MusicFileWriter(Music* src, std::shared_ptr<Music>& dst) :
    m_musicSrc(src),
    m_musicDst(dst)
{
}

MusicFileWriter::~MusicFileWriter()
{
    delete m_musicSrc;
}

void MusicFileWriter::process()
{
    if (NULL == m_musicSrc)// || NULL == m_musicDst)
        return;
    fillData();
    saveImage();
    renameFile();
    copy();
}

void MusicFileWriter::fillData()
{
    Music* musicDest = m_musicDst.get();
    TagLib::FileRef fileRef(TagLib::FileName(musicDest->GetFileName().fn_str()));

    if (!fileRef.isNull())
    {
        wxString artists = m_musicSrc->GetArtists();
        artists.Replace(_T("/"), _T(";"), true);

        fileRef.tag()->setAlbum (TagLib::String(m_musicSrc->GetAlbum() .fn_str()));
        fileRef.tag()->setArtist(TagLib::String(artists.fn_str()));
        fileRef.tag()->setTitle (TagLib::String(m_musicSrc->GetTitle() .fn_str()));
        fileRef.tag()->setGenre (TagLib::String(m_musicSrc->GetGenres().fn_str()));
        fileRef.tag()->setYear  (               m_musicSrc->GetYear());
        fileRef.save();
    }
}

void MusicFileWriter::saveImage()
{
    Music* musicDest = m_musicDst.get();
    if (!m_musicSrc->HasRecordSleeve() || (musicDest->HasRecordSleeve() && m_musicSrc->GetRecordSleeve()->IsSameAs(*musicDest->GetRecordSleeve())))
        return;

    TagLib::FileRef fileRef(TagLib::FileName(m_musicSrc->GetFileName().fn_str()));
    if (!fileRef.isNull() && fileRef.file()->isValid())
    {
        TagLib::MPEG::File f(TagLib::FileName(m_musicSrc->GetFileName().fn_str()));
        if (f.ID3v2Tag())
        {
            ID3v2::Tag *tagv2 = f.ID3v2Tag(true);
            if(tagv2)
            {
                TagLib::ID3v2::FrameList FrameList = tagv2->frameListMap()["APIC"];
                for( std::list<TagLib::ID3v2::Frame*>::iterator iter = FrameList.begin(); iter != FrameList.end(); ++iter )
                {
                    TagLib::ID3v2::AttachedPictureFrame *pict = static_cast<TagLib::ID3v2::AttachedPictureFrame *>( *iter );
                    tagv2->removeFrame(pict, true);
                }

                TagLib::ID3v2::AttachedPictureFrame *p = new TagLib::ID3v2::AttachedPictureFrame;
                p->setMimeType(_T("image/jpeg"));
                p->setType(TagLib::ID3v2::AttachedPictureFrame::FrontCover);
                wxMemoryOutputStream imgStreamOut;
                if(m_musicSrc->GetRecordSleeve()->SaveFile(imgStreamOut, wxBITMAP_TYPE_JPEG))
                {
                    ByteVector ImgData((TagLib::uint)imgStreamOut.GetSize());
                    imgStreamOut.CopyTo(ImgData.data(), imgStreamOut.GetSize());
                    p->setPicture(ImgData);
                    tagv2->addFrame(p);
                    f.save();
                }
            }
        }
    }
}

/** @brief Renames the music file.
 * If it is impossible, previous value are restored.
 */
void MusicFileWriter::renameFile()
{
    Music* musicDest = m_musicDst.get();
    refreshFileName(*m_musicSrc);
    if (m_musicSrc->EqualsFilename(musicDest))
        return;

    if (tools::containsInvalidCharacter(m_musicSrc->GetFileName()))
        return;

    if (wxRenameFile(musicDest->GetFileName(), m_musicSrc->GetFileName()))
        musicDest->SetFileName(m_musicSrc->GetFileName());
    else
    {
        m_musicSrc->SetFileName(musicDest->GetFileName());
        m_musicSrc->SetName(musicDest->GetName());
        m_musicSrc->SetPath(musicDest->GetPath());
    }
}

Music* MusicFileWriter::getMusic() const
{
    return m_musicDst.get();
}

void MusicFileWriter::copy()
{
    *m_musicDst = *m_musicSrc;
}

void MusicFileWriter::refreshFileName(Music& music)
{
    wxString newFileName;
    newFileName << music.GetPath()
                << wxFileName::GetPathSeparator()
                << music.GetName()
                << '.'
                << music.GetExtension().Lower();
    music.SetFileName(newFileName);
}

