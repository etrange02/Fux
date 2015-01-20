#ifndef MUSICMANAGER_H
#define MUSICMANAGER_H

#include <wx/wx.h>
#include <ctime>
#include <algorithm>
//#include "../Define.h"
//#include "IMusic.h"
#include "IMusicManager.h"
#include "MusicPlayer.h"
#include "MusicList.h"
#include "../tools/thread/ThreadManager.h"
#include "../predicates/findPosition.h"

class MusicList;

extern const wxEventType wxEVT_FUX_MUSICMANAGER_NO_FILE;
extern const wxEventType wxEVT_FUX_MUSICMANAGER_SEARCH_DONE;

class MusicManager
{
    public:
        //static MusicManager& get();

        std::vector<Music*>& getAllMusics();
        std::vector<Music*>& getSearchedMusics();
        size_t getCurrentMusicPosition();
        size_t getCurrentMusicPositionInSearch();
        bool playMusicAt(long position);
        bool playMusicAtInShownCollection(long position);// to delete
        bool playMusicAtInSearch(long position);
        void moveIntTitlesAt(wxArrayString* titles, long position, bool update = true, bool autoDelete = true);
        void moveIntTitlesAtInSearch(wxArrayString* titles, long position, bool update = true, bool autoDelete = true);
        void placeStringTitlesAt(wxArrayString* titles, size_t position, bool update = true);
        void placeStringTitlesAtInSearch(wxArrayString* titles, size_t position, bool update = true);
        void deleteTitleAt(size_t position);
        void deleteTitleAtInSearch(size_t position);
        void deleteTitles(wxArrayString& titles, bool update = false);

        bool isRepete();
        bool isRandom();
        Music *getMusic();
        MusicPlayer& getMusicPlayer();

        void setRepete(bool repete);
        void setRandom(bool random);

        bool playNextMusic();
        bool playPreviousMusic();
        bool playNextOrRandomMusic();
        bool playPreviousOrRandomMusic();
        bool playAMusic();
        bool playMusic(const wxString& name/*, long position*/);
        bool playMusicThenParse(wxString filename);
        bool playSameMusic();

        void deleteCurrentTitle();
        void parse();
        void parse(const wxString& filename);
        void parse(wxArrayString& filenames, bool update = true);

        void setParent(wxWindow* parent);
        wxWindow* getParent() const;

        bool saveMusicListIntoFile(wxString const &filename);

        bool empty() const;
        size_t size() const;

        wxString getSearchedWord() const;
        void setSearchWord(const wxString& searchedWord);
        bool hasEfficientSearchedWord() const;
        MusicManager();
        virtual ~MusicManager();

    protected:
        bool playRandomMusic();
        void sendMusicNoFileEvent();
        void sendSearchEndingEvent();
        void launchSearching();

    private:

        wxWindow* m_parent;
        bool m_repete;
        bool m_random;
        MusicPlayer m_musicPlayer;
        MusicList* m_musicList;
        Music* m_music;
        size_t m_musicPosition;
        wxString m_searchedWord;
        std::vector<Music*> m_searchedMusicCollection;
};

#endif // MUSICMANAGER_H
