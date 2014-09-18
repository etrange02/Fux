#ifndef MUSIC_H_INCLUDED
#define MUSIC_H_INCLUDED

#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/dir.h>
#include <wx/mstream.h>
#include <wx/image.h>
// TagLib
#include <tag.h>
#include <fileref.h>
#include <taglib.h>
#include <mpegfile.h>
#include <id3v2tag.h>
#include <attachedpictureframe.h>

#include "IMusic.h"

class Music : public IMusic
{
    public:
        Music();
        Music(wxString filename);
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

        wxString& GetName();
        wxString& GetArtists();
        wxString& GetAlbum();
        wxString& GetTitle();
        wxString& GetPath();
        wxString& GetGenres();
        wxString& GetExtension();
        wxString GetFileName() const;
        wxString GetStringDuration();
        wxString GetStringYear();
        int GetYear() const;
        int GetDuration() const;
        int GetDebit() const;
        int GetSize() const;
        wxImage *GetRecordSleeve();

        bool equalsFilename(const IMusic *music);

    protected:
        void Initialize();
        void FillFields(wxString filename);
        void ImageExtracting(wxString filename);

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

#endif // MUSIC_H_INCLUDED
