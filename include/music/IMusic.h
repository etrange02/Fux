#ifndef IMUSIC_H_INCLUDED
#define IMUSIC_H_INCLUDED

#include <wx/wx.h>
#include <wx/image.h>

namespace music
{
    class IMusic
    {
        public:
            virtual ~IMusic();
            virtual wxString GetName()          const = 0;
            virtual wxString GetArtists()       const = 0;
            virtual wxString GetAlbum()         const = 0;
            virtual wxString GetTitle()         const = 0;
            virtual wxString GetPath()          const = 0;
            virtual wxString GetGenres()        const = 0;
            virtual wxString GetExtension()     const = 0;
            virtual wxString GetFileName()      const = 0;
            virtual int GetYear()               const = 0;
            virtual int GetDuration()           const = 0;
            virtual int GetDebit()              const = 0;
            virtual int GetSize()               const = 0;
            virtual bool HasRecordSleeve()      const = 0;
            virtual wxImage *GetRecordSleeve()  const = 0;
            virtual wxString GetStringDuration()         ;
            virtual wxString GetStringYear()             ;

            bool IsMatching(const wxString& word);

            virtual bool EqualsFilename(const IMusic *music) const = 0;
            virtual bool operator==(const IMusic& other);
    };
}

#endif // IMUSIC_H_INCLUDED
