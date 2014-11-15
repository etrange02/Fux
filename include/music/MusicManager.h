#ifndef MUSICMANAGER_H
#define MUSICMANAGER_H

#include <wx/wx.h>
#include <ctime>
#include <algorithm>
//#include "../Define.h"
#include "IMusic.h"
#include "MusicPlayer.h"
#include "MusicList.h"
#include "../predicates/findPosition.h"

class MusicList;

extern const wxEventType wxEVT_FUX_MUSICMANAGER_NO_FILE;

class MusicManager
{
    public:
        static MusicManager* get();

        bool isRepete();
        bool isRandom();
        Music *getMusic();
        MusicList *getMusicList();
        MusicPlayer *getMusicPlayer();

        size_t getCurrentMusicPosition();

        void setRepete(bool repete);
        void setRandom(bool random);

        bool playNextMusic();
        bool playPreviousMusic();
        bool playNextOrRandomMusic();
        bool playPreviousOrRandomMusic();
        bool playAMusic();
        bool playMusicAt(long position);
        bool playMusic(wxString& name/*, long position*/);
        bool playMusicThenParse(wxString filename);
        bool playSameMusic();

        void moveIntTitlesAt(wxArrayString* titles, long position, bool update = true, bool autoDelete = true);
        void placeStringTitlesAt(wxArrayString* titles, size_t position, bool update = true);

        ChansonNomPos deleteCurrentTitle();
        void deleteTitleAt(long position);
        void deleteTitles(wxArrayString *titles, bool update = false);

        void parse();
        void parse(wxArrayString* filenames, bool update = true);
        void parse(wxString filename);

        void setParent(wxWindow* parent);
        wxWindow* getParent() const;

        bool saveMusicListIntoFile(wxString const &filename);

        bool empty() const;
        size_t size() const;

    protected:
        void initialize();
        bool playRandomMusic();
        void sendMusicNoFileEvent();

    private:
        MusicManager();
        virtual ~MusicManager();

        wxWindow* m_parent;
        bool m_repete, m_random;
        MusicList* m_musicList;
        MusicPlayer* m_musicPlayer;
        Music* m_music;
        size_t m_musicPosition;
};

#endif // MUSICMANAGER_H
