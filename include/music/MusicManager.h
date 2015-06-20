#ifndef MUSICMANAGER_H
#define MUSICMANAGER_H

#include <wx/wx.h>
#include "MusicPlayer.h"
#include "MusicList.h"


extern const wxEventType wxEVT_FUX_MUSICMANAGER_NO_FILE;
extern const wxEventType wxEVT_FUX_MUSICMANAGER_SEARCH_DONE;
extern const wxEventType wxEVT_FUX_MUSICMANAGER_LINE_DELETED;


namespace music
{
    class MusicList;

    typedef std::shared_ptr<Music> MusicItem;
    typedef std::vector<MusicItem> MusicCollection;
    typedef MusicCollection::iterator MusicIterator;

    class MusicManager
    {
        public:
            MusicManager();
            virtual ~MusicManager();

            MusicCollection& getAllMusics       ();
            MusicCollection& getSearchedMusics  ();
            size_t getCurrentMusicPosition      ();
            long getCurrentMusicPositionInSearch();
            bool playMusicAt                (long position);
            bool playMusicAtInSearch        (long position);
            void moveIntTitlesAt            (const wxArrayString& titles, size_t position);
            void moveIntTitlesAtInSearch    (const wxArrayString& titles, unsigned long position);
            void placeStringTitlesAt        (const wxArrayString& titles, size_t position);
            void placeStringTitlesAtInSearch(const wxArrayString& titles, size_t position);
            void deleteTitleAt              (const size_t position);
            void deleteTitleAt              (const std::vector<unsigned long>& positions);
            void deleteTitleAtInSearch      (const size_t position);
            void deleteTitleAtInSearch      (const std::vector<unsigned long>& positions);
            void updateMusicContent         (const size_t position, Music* musicData);
            void updateMusicContentInSearch (const size_t position, Music* musicData);
            void deleteTitles               (wxArrayString& titles, bool update = false);

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
            void parse(const wxArrayString& filenames, bool update = true);

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
            void deleteTitle(const size_t position, const size_t positionInSearch);
            void updateMusicContent(const size_t position, Music* musicData, MusicCollection& collection);
            void updateCurrentMusic(Music* newMusicData);
            long deleteCurrentTitleInSearch();
            long deleteTitle(const Music& music);
            long deleteTitle(const size_t position);
            long deleteTitleInSearch(const Music& music);
            long deleteTitleInSearch(const size_t position);
            void deleteAllTitles();
            void deleteTitles(const std::vector<unsigned long>& positions, void (MusicManager::*func)(const size_t));
            bool changeToAnAvailableTitle(const std::vector<unsigned long>& positions);

            unsigned long findNextAvailablePosition(const std::vector<unsigned long>& positions, const std::vector<unsigned long>::const_iterator& beginIter, const unsigned long start);

            void sendMusicManagerLineDeleted(const long position, const long positionInSearch);

        private:
            MusicPlayer m_musicPlayer;
            wxString m_searchedWord;
            MusicCollection m_searchedMusicCollection;
            bool m_repete;
            bool m_random;
            size_t m_musicPosition;
            wxWindow* m_parent;
            Music* m_music;
            MusicList* m_musicList;
    };
}

#endif // MUSICMANAGER_H
