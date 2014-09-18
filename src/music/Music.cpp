/***************************************************************
 * Name:      Music.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2014-04-16
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../../include/music/Music.h"

using namespace TagLib;

/**
 * @class Music
 * @brief Handles music properties (file and sound)
 */

/**
 * Default constructor
 */
Music::Music()
{
    Initialize();
}

/**
 * Constructor
 * @param filename a file name
 */
Music::Music(wxString filename)
{
    FillFields(filename);
}

/**
 * Destructor
 */
Music::~Music()
{
    delete m_recordSleeve;
}

void Music::Initialize()
{
    SetName(wxEmptyString);
    SetArtists(wxEmptyString);
    SetAlbum(wxEmptyString);
    SetTitle(wxEmptyString);
    SetPath(wxEmptyString);
    SetGenres(wxEmptyString);
    SetExtension(wxEmptyString);
    SetYear(0);
    SetDuration(0);
    SetDebit(0);
    SetSize(0);
    SetRecordSleeve(NULL);
}

void Music::FillFields(wxString filename)
{
    TagLib::FileRef fileTAG;

    Initialize();
    /*if (filename.IsEmpty() || !wxFileExists(filename))
        return;*/

    SetFileName(filename);
    SetName(filename.AfterLast(wxFileName::GetPathSeparator()));
    SetPath(filename.BeforeLast(wxFileName::GetPathSeparator()));
    SetExtension(filename.AfterLast('.'));

    fileTAG = TagLib::FileRef(TagLib::FileName(filename.fn_str()));

    SetArtists(wxString(fileTAG.tag()->artist().toCString(true), wxConvUTF8));
    SetAlbum(wxString(fileTAG.tag()->album().toCString(true), wxConvUTF8));
    SetTitle(wxString(fileTAG.tag()->title().toCString(true), wxConvUTF8));
    SetGenres(wxString(fileTAG.tag()->genre().toCString(true), wxConvUTF8));
    SetYear(fileTAG.tag()->year());
    SetDuration(fileTAG.audioProperties()->length());
    SetDebit(fileTAG.audioProperties()->bitrate());
    SetSize(fileTAG.file()->length());
    ImageExtracting(filename);
    //.....
}

void Music::ImageExtracting(wxString filename)
{
    TagLib::MPEG::File f(TagLib::FileName(filename.fn_str()));
    if(f.ID3v2Tag())
    {
        TagLib::ID3v2::FrameList l = f.ID3v2Tag()->frameList("APIC");
        if (!l.isEmpty())
        {
            TagLib::ID3v2::AttachedPictureFrame *p = static_cast<TagLib::ID3v2::AttachedPictureFrame *>(l.front());
            int imgSize = p->picture().size();

            if (p != NULL)
            {
                wxMemoryOutputStream imgStreamOut;
                imgStreamOut.Write(p->picture().data(), imgSize);
                wxMemoryInputStream stream(imgStreamOut);
                wxString typeImage(p->mimeType().toCString(true), wxConvLocal);

                if (typeImage.IsSameAs(_T("image/jpeg")) || typeImage.IsSameAs(_T("image/jpg")))
                    SetRecordSleeve(new wxImage(stream, _T("image/jpeg")));
            }
        }
    }
}

void Music::SetName(wxString name)
{
    m_name = name;
}

void Music::SetArtists(wxString artists)
{
    m_artists = artists;
}

void Music::SetAlbum(wxString album)
{
    m_album = album;
}

void Music::SetTitle(wxString title)
{
    m_title = title;
}

void Music::SetPath(wxString path)
{
    m_path = path;
}

void Music::SetRecordSleeve(wxImage* recordSleeve)
{
    m_recordSleeve = recordSleeve;
}

void Music::SetGenres(wxString genres)
{
    m_genres = genres;
}

void Music::SetExtension(wxString extension)
{
    m_extension = extension;
}

void Music::SetFileName(wxString filename)
{
    m_filename = filename;
}

void Music::SetYear(int year)
{
    m_year = year;
}

void Music::SetDuration(int duration)
{
    m_duration = duration;
}

void Music::SetDebit(int debit)
{
    m_debit = debit;
}

void Music::SetSize(int size)
{
    m_size = size;
}

wxString& Music::GetName()
{
    return this->m_name;
}

wxString& Music::GetArtists()
{
    return m_artists;
}

wxString& Music::GetAlbum()
{
    return m_album;
}

wxString& Music::GetTitle()
{
    return m_title;
}

wxString& Music::GetPath()
{
    return m_path;
}

wxString& Music::GetGenres()
{
    return m_genres;
}

wxString& Music::GetExtension()
{
    return m_extension;
}

wxString Music::GetFileName() const
{
    return m_filename;
}

int Music::GetYear() const
{
    return m_year;
}

int Music::GetDuration() const
{
    return m_duration;
}

int Music::GetDebit() const
{
    return m_debit;
}

int Music::GetSize() const
{
    return m_size;
}

wxImage* Music::GetRecordSleeve()
{
    return m_recordSleeve;
}

bool Music::equalsFilename(const IMusic *music)
{
    if (NULL == music)
        return false;
    return this->GetFileName().IsSameAs(music->GetFileName());
}

wxString Music::GetStringDuration()
{
    wxString str;
    str << GetDuration()/60 << _T(":");
    if (GetDuration()%60 < 10)
        str << _T("0") << GetDuration()%60;
    else
        str << GetDuration()%60;
    return str;
}

wxString Music::GetStringYear()
{
    wxString str = wxString::Format(_("%d"), GetYear());
    return str;
}



