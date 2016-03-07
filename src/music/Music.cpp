/***************************************************************
 * Name:      Music.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2014-04-16
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "music/Music.h"

using namespace ::music;

/**
 * Default constructor
 */
Music::Music() : Music("")
{
}

/**
 * Constructor
 * @param filename a file name
 */
Music::Music(const wxString& filename) :
    m_filename(filename),
    m_year(0),
    m_duration(0),
    m_debit(0),
    m_size(0),
    m_recordSleeve(NULL)
{
}

Music::Music(const Music& music) :
    m_recordSleeve(NULL)
{
    *this = music;
}

/**
 * Destructor
 */
Music::~Music()
{
    delete m_recordSleeve;
}


Music& Music::operator=(const Music& music)
{
    if (this == &music)
        return *this;
    m_filename      = music.m_filename;
    m_name          = music.m_name;
    m_artists       = music.m_artists;
    m_album         = music.m_album;
    m_title         = music.m_title;
    m_path          = music.m_path;
    m_genres        = music.m_genres;
    m_extension     = music.m_extension;
    m_year          = music.m_year;
    m_duration      = music.m_duration;
    m_debit         = music.m_debit;
    m_size          = music.m_size;

    if (NULL != m_recordSleeve)
        delete m_recordSleeve;
    m_recordSleeve = NULL;
    if (NULL != music.m_recordSleeve)
        m_recordSleeve = new wxImage(*music.m_recordSleeve);

    return *this;
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
    return this->GetFileName().IsSameAs(music->GetFileName(), false);
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

