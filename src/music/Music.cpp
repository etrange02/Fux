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
Music::Music() : Music::Music(wxEmptyString)
{
}

/**
 * Constructor
 * @param filename a file name
 */
Music::Music(wxString filename) :
    m_name(wxEmptyString),
    m_artists(wxEmptyString),
    m_album(wxEmptyString),
    m_title(wxEmptyString),
    m_path(wxEmptyString),
    m_genres(wxEmptyString),
    m_extension(wxEmptyString),
    m_year(0),
    m_duration(0),
    m_debit(0),
    m_size(0),
    m_recordSleeve(NULL)
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

/** @brief Fill music data
 * Fill music data thanks to filename
 * @param filename a music filename
 * @return void
 *
 */
void Music::FillFields(wxString filename)
{
    TagLib::FileRef fileTAG;

    if (filename.IsEmpty() || !wxFileExists(filename))
        return;

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

/** @brief Fill sleeves (images)
 * Fill images associated with the music file
 * @param filename a music filename
 * @return void
 *
 */
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

/** @brief Modifies the name
 * Modifies the name
 * @param name the name
 * @return void
 *
 */
void Music::SetName(wxString name)
{
    m_name = name;
}

/** @brief Modifies the artists
 * Modifies the artists
 * @param artists the artists
 * @return void
 *
 */
void Music::SetArtists(wxString artists)
{
    m_artists = artists;
}

/** @brief Modifies the album
 * Modifies the album
 * @param album the album
 * @return void
 *
 */
void Music::SetAlbum(wxString album)
{
    m_album = album;
}

/** @brief Modifies the title
 * Modifies the title
 * @param title the title
 * @return void
 *
 */
void Music::SetTitle(wxString title)
{
    m_title = title;
}

/** @brief Modifies the access path
 * Modifies the access path
 * @param path the access path
 * @return void
 *
 */
void Music::SetPath(wxString path)
{
    m_path = path;
}

/** @brief Modifies the sleeve
 * Modifies the record sleeve
 * @param recordSleeve the record sleeve
 * @return void
 *
 */
void Music::SetRecordSleeve(wxImage* recordSleeve)
{
    m_recordSleeve = recordSleeve;
}

/** @brief Modifies the genres
 * Modifies the genres
 * @param genres the genres
 * @return void
 *
 */
void Music::SetGenres(wxString genres)
{
    m_genres = genres;
}

/** @brief Modifies the extension
 * Modifies the extension
 * @param extension the extension
 * @return void
 *
 */
void Music::SetExtension(wxString extension)
{
    m_extension = extension;
}

/** @brief Modifies the filename
 * Modifies the filename (path + name + extension)
 * @param filename the filename
 * @return void
 *
 */
void Music::SetFileName(wxString filename)
{
    m_filename = filename;
}

/** @brief Modifies the year
 * Modifies the year
 * @param year the year
 * @return void
 *
 */
void Music::SetYear(int year)
{
    m_year = year;
}

/** @brief Modifies the music duration
 * Modifies the music duration
 * @param duration the duration
 * @return void
 *
 */
void Music::SetDuration(int duration)
{
    m_duration = duration;
}

/** @brief Modifies the debit
 * Modifies the debit
 * @param debit the debit
 * @return void
 *
 */
void Music::SetDebit(int debit)
{
    m_debit = debit;
}

/** @brief Modifies the file size
 * Modifies the file
 * @param size the size
 * @return void
 *
 */
void Music::SetSize(int size)
{
    m_size = size;
}

/** @brief Gets the name of the file
 * Gets the name of the file
 * @return the name of the file
 *
 */
wxString& Music::GetName()
{
    return this->m_name;
}

/** @brief Gets the artists
 * Gets the artists
 * @return the artists
 *
 */
wxString& Music::GetArtists()
{
    return m_artists;
}

/** @brief Gets the album
 * Gets the album
 * @return the album
 *
 */
wxString& Music::GetAlbum()
{
    return m_album;
}

/** @brief Gets the title
 * Gets the title
 * @return the title
 *
 */
wxString& Music::GetTitle()
{
    return m_title;
}

/** @brief Gets the path
 * Gets the path, ie the directory name where the file is written
 * @return the path
 *
 */
wxString& Music::GetPath()
{
    return m_path;
}

/** @brief Gets the genres
 * Gets the genres
 * @return the genres
 *
 */
wxString& Music::GetGenres()
{
    return m_genres;
}

/** @brief Gets the file extension
 * Gets the file extension
 * @return the extension
 *
 */
wxString& Music::GetExtension()
{
    return m_extension;
}

/** @brief Gets the music filename
 * Gets the music filename (path + name + extension)
 * @return the filename
 *
 */
wxString Music::GetFileName() const
{
    return m_filename;
}

/** @brief Gets the year
 * Gets the year
 * @return the year
 *
 */
int Music::GetYear() const
{
    return m_year;
}

/** @brief Gets the duration
 * Gets the duration, ie music lenght en ms
 * @return the duration in ms
 *
 */
int Music::GetDuration() const
{
    return m_duration;
}

/** @brief Gets the debit
 * Gets the debit in kb/s
 * @return the debit
 *
 */
int Music::GetDebit() const
{
    return m_debit;
}

/** @brief Gets the file size
 * Getss the file size
 * @return the file size
 *
 */
int Music::GetSize() const
{
    return m_size;
}

/** @brief Gets the sleeve
 * Gets the record sleeve (image)
 * @return the sleeve
 *
 */
wxImage* Music::GetRecordSleeve()
{
    return m_recordSleeve;
}

/** @brief Equality test
 * Tests the equality between this instance and the parameter. Equality based on filenames.
 * @param music an instance
 * @return true if same
 *
 */
bool Music::equalsFilename(const IMusic *music)
{
    if (NULL == music)
        return false;
    return this->GetFileName().IsSameAs(music->GetFileName());
}

/** @brief Gets the duration under dd:dd format
 * Gets the duration under dd:dd format. 0 inserted if necessary
 * @return a dd:dd string
 *
 */
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

/** @brief Gets the year under string format
 * Gets the year under string format
 * @return the year under string format
 *
 */
wxString Music::GetStringYear()
{
    wxString str = wxString::Format(_("%d"), GetYear());
    return str;
}



