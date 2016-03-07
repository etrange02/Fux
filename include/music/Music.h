#ifndef MUSIC_H_INCLUDED
#define MUSIC_H_INCLUDED

#include <wx/wx.h>
#include <wx/image.h>

#include "IMusic.h"

namespace music
{
    /**
     * @class Music
     * @brief Handles music properties (file and sound)
     */
    class Music : public IMusic
    {
        public:
            Music();
            Music(const wxString& filename);
            Music(const Music& music);
            Music& operator=(const Music& music);
            virtual ~Music();

            void SetName(wxString name);
            void SetArtists(wxString artists);
            void SetAlbum(wxString album);
            void SetTitle(wxString title);
            void SetPath(wxString path);
            void SetGenres(wxString genres);
            void SetExtension(wxString extension);
            void SetFileName(wxString filename);
            void SetYear(int year);
            void SetDuration(int duration);
            void SetDebit(int debit);
            void SetSize(int size);
            void SetRecordSleeve(wxImage *recordSleeve);

            wxString GetName() const;
            wxString GetArtists() const;
            wxString GetAlbum() const;
            wxString GetTitle() const;
            wxString GetPath() const;
            wxString GetGenres() const;
            wxString GetExtension() const;
            wxString GetFileName() const;
            int GetYear() const;
            int GetDuration() const;
            int GetDebit() const;
            int GetSize() const;
            bool HasRecordSleeve() const;
            wxImage *GetRecordSleeve() const;

            bool EqualsFilename(const IMusic *music) const;

            void ShrinkData();

        private:
            wxString m_name;
            wxString m_artists;
            wxString m_album;
            wxString m_title;
            wxString m_path;
            wxString m_genres;
            wxString m_extension;
            wxString m_filename;
            int m_year;
            int m_duration;
            int m_debit;
            int m_size;
            //wxStringArray *m_allArtist;
            wxImage *m_recordSleeve;
    };
}

#endif // MUSIC_H_INCLUDED
