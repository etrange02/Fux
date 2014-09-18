#ifndef IMUSIC_H_INCLUDED
#define IMUSIC_H_INCLUDED

#include <wx/wx.h>
#include <wx/image.h>

class IMusic
{
    public:
        virtual wxString& GetName() = 0;
        virtual wxString& GetArtists() = 0;
        virtual wxString& GetAlbum() = 0;
        virtual wxString& GetTitle() = 0;
        virtual wxString& GetPath() = 0;
        virtual wxString& GetGenres() = 0;
        virtual wxString& GetExtension() = 0;
        virtual wxString GetFileName() const = 0;
        virtual int GetYear() const = 0;
        virtual int GetDuration() const = 0;
        virtual int GetDebit() const = 0;
        virtual int GetSize() const = 0;
        virtual wxImage *GetRecordSleeve() = 0;

        virtual bool equalsFilename(const IMusic *music) = 0;
};

#endif // IMUSIC_H_INCLUDED
