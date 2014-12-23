/***************************************************************
 * Name:      MusicFileWriter.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2014-12-17
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "MusicFileWriter.h"

using namespace TagLib;

MusicFileWriter::MusicFileWriter(const Music* src, Music& dst) :
    m_musicSrc(src),
    m_musicDst(dst)
{
}

MusicFileWriter::~MusicFileWriter()
{
}

void MusicFileWriter::process()
{
    fillData();
    saveImage();
    renameFile();
}

void MusicFileWriter::fillData()
{
    TagLib::FileRef fileRef(TagLib::FileName(m_musicDst.GetFileName().fn_str()));

    if (!fileRef.isNull())
    {
        wxString artists = m_musicSrc->GetArtists();
        artists.Replace(_T("/"), _T(";"), true);

        fileRef.tag()->setAlbum (TagLib::String(m_musicSrc->GetAlbum() .fn_str()));
        fileRef.tag()->setArtist(TagLib::String(artists));
        fileRef.tag()->setTitle (TagLib::String(m_musicSrc->GetTitle() .fn_str()));
        fileRef.tag()->setGenre (TagLib::String(m_musicSrc->GetGenres().fn_str()));
        fileRef.tag()->setYear  (               m_musicSrc->GetYear());
        fileRef.save();
    }
}

void MusicFileWriter::saveImage()
{
    if (!m_musicSrc->HasRecordSleeve() || (m_musicDst.HasRecordSleeve() && m_musicSrc->GetRecordSleeve()->IsSameAs(*m_musicDst.GetRecordSleeve())))
        return;

    TagLib::FileRef fileRef(TagLib::FileName(m_musicDst.GetFileName().fn_str()));
    if (!fileRef.isNull() && fileRef.file()->isValid())
    {
        TagLib::MPEG::File f(TagLib::FileName(m_musicDst.GetFileName().fn_str()));
        if (f.ID3v2Tag())
        {
            ID3v2::Tag *tagv2 = f.ID3v2Tag(true);
            if(tagv2)
            {
                TagLib::ID3v2::AttachedPictureFrame *pict;
                TagLib::ID3v2::FrameList FrameList = tagv2->frameListMap()["APIC"];
                for( std::list<TagLib::ID3v2::Frame*>::iterator iter = FrameList.begin(); iter != FrameList.end(); ++iter )
                {
                    pict = static_cast<TagLib::ID3v2::AttachedPictureFrame *>( *iter );
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

void MusicFileWriter::renameFile()
{
    if (m_musicSrc->GetFileName().IsSameAs(m_musicDst.GetFileName()))
        return;
    wxRenameFile(m_musicDst.GetFileName(), m_musicSrc->GetFileName());
}

