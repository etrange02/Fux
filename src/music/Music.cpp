/***************************************************************
 * Name:      Music.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2014-04-16
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../../include/music/Music.h"

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
    m_filename(filename),
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
}

/**
 * Destructor
 */
Music::~Music()
{
    delete m_recordSleeve;
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
wxString Music::GetName() const
{
    return m_name;
}

/** @brief Gets the artists
 * Gets the artists
 * @return the artists
 *
 */
wxString Music::GetArtists() const
{
    return m_artists;
}

/** @brief Gets the album
 * Gets the album
 * @return the album
 *
 */
wxString Music::GetAlbum() const
{
    return m_album;
}

/** @brief Gets the title
 * Gets the title
 * @return the title
 *
 */
wxString Music::GetTitle() const
{
    return m_title;
}

/** @brief Gets the path
 * Gets the path, ie the directory name where the file is written
 * @return the path
 *
 */
wxString Music::GetPath() const
{
    return m_path;
}

/** @brief Gets the genres
 * Gets the genres
 * @return the genres
 *
 */
wxString Music::GetGenres() const
{
    return m_genres;
}

/** @brief Gets the file extension
 * Gets the file extension
 * @return the extension
 *
 */
wxString Music::GetExtension() const
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

bool Music::HasRecordSleeve() const
{
    return NULL != GetRecordSleeve();
}

/** @brief Gets the sleeve
 * Gets the record sleeve (image)
 * @return the sleeve
 *
 */
wxImage* Music::GetRecordSleeve() const
{
    return m_recordSleeve;
}

/** @brief Equality test
 * Tests the equality between this instance and the parameter. Equality based on filenames.
 * @param music an instance
 * @return true if same
 *
 */
bool Music::EqualsFilename(const IMusic *music) const
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

bool Music::IsMatching(const wxString& word)
{
    return !(
                      wxNOT_FOUND == GetFileName()      .Lower().Find(word)
                 &&   wxNOT_FOUND == GetArtists()       .Lower().Find(word)
                 &&   wxNOT_FOUND == GetAlbum()         .Lower().Find(word)
                 &&   wxNOT_FOUND == GetTitle()         .Lower().Find(word)
                 &&   wxNOT_FOUND == GetGenres()        .Lower().Find(word)
                 &&   wxNOT_FOUND == GetStringDuration().Lower().Find(word)
                 &&   wxNOT_FOUND == GetStringYear()    .Lower().Find(word)
             );
}

void Music::ShrinkData()
{
    m_name.Shrink();
    m_artists.Shrink();
    m_album.Shrink();
    m_title.Shrink();
    m_path.Shrink();
    m_genres.Shrink();
    m_extension.Shrink();
    m_filename.Shrink();
}

