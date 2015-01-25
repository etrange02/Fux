#ifndef MUSICMANAGER_H
#define MUSICMANAGER_H

#include <wx/wx.h>
#include "MusicPlayer.h"
#include "MusicList.h"

class MusicList;

extern const wxEventType wxEVT_FUX_MUSICMANAGER_NO_FILE;
extern const wxEventType wxEVT_FUX_MUSICMANAGER_SEARCH_DONE;

class MusicManager
{
    public:
        MusicManager();
        virtual ~MusicManager();

        std::vector<Music*>& getAllMusics();
        std::vector<Music*>& getSearchedMusics();
        size_t getCurrentMusicPosition();
        size_t getCurrentMusicPositionInSearch();
        bool playMusicAt(long position);
        bool playMusicAtInSearch(long position);
        void moveIntTitlesAt(wxArrayString* titles, long position);
        void moveIntTitlesAtInSearch(wxArrayString* titles, long position);
        void placeStringTitlesAt(wxArrayString* titles, size_t position);
        void placeStringTitlesAtInSearch(wxArrayString* titles, size_t position);
        void deleteTitleAt(size_t position);
        void deleteTitleAtInSearch(size_t position);
        void updateMusicContent(const long position, Music* musicData);
        void updateMusicContentInSearch(const long position, Music* musicData);
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
        bool playMusic(const wxString& name);
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

    protected:
        bool playRandomMusic();
        void sendMusicNoFileEvent();
        void sendSearchEndingEvent();
        void launchSearching();
        void updateMusicContent(const long position, Music* musicData, std::vector<Music*>& collection);
        void updateCurrentMusic(Music* newMusicData);

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
