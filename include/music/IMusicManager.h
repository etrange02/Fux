#ifndef IMUSICMANAGER_H
#define IMUSICMANAGER_H

#include <vector>
#include <memory>

#include "Music.h"
#include "MusicPlayer.h"

namespace music
{
    typedef std::vector<std::shared_ptr<Music>> MusicCollection;
    typedef MusicCollection::iterator MusicIterator;
    class DeletedLines;

    class IMusicManager
    {
        public:
            IMusicManager();
            virtual ~IMusicManager();

            /**/virtual MusicCollection& getMusics() = 0;
            /**/virtual size_t getCurrentMusicPosition() = 0;
            /**/virtual void moveIntTitlesAt(const wxArrayString& titles, size_t position) = 0;
            /**/virtual void placeStringTitlesAt(const wxArrayString& titles, size_t position) = 0;
            /**/virtual void deleteTitleAt(size_t position) = 0;
            /**/virtual void deleteTitleAt(const std::vector<unsigned long>& positions) = 0;
            /**/virtual bool playMusicAt(long position) = 0;
            /**/virtual void updateMusicContent(const size_t position, Music* music) = 0;
            /**/virtual int  getDeletedLine(DeletedLines& deletedLines) = 0;

            virtual bool isRepete() = 0;
            virtual bool isRandom() = 0;
            virtual Music *getMusic() = 0;
            virtual MusicPlayer& getMusicPlayer() = 0;

            virtual void setRepete(bool repete) = 0;
            virtual void setRandom(bool random) = 0;

            virtual bool playNextMusic() = 0;
            virtual bool playPreviousMusic() = 0;
            virtual bool playNextOrRandomMusic() = 0;
            virtual bool playPreviousOrRandomMusic() = 0;
            virtual bool playAMusic() = 0;
            virtual bool playMusic(const wxString& name) = 0;
            virtual bool playMusicThenParse(wxString filename) = 0;
            virtual bool playSameMusic() = 0;

            virtual void deleteCurrentTitle() = 0;
            virtual void deleteTitles(wxArrayString& titles, bool update = false) = 0;

            virtual void parse() = 0;
            virtual void parse(const wxString& filename) = 0;
            virtual void parse(const wxArrayString& filenames, bool update = true) = 0;

            virtual void setParent(wxWindow* parent) = 0;
            virtual wxWindow* getParent() const = 0;

            virtual bool saveMusicListIntoFile(wxString const &filename) = 0;

            virtual bool empty() const = 0;
            virtual size_t size() const = 0;

            virtual wxString getSearchedWord() const = 0;
            virtual void setSearchWord(const wxString& searchedWord) = 0;
            virtual bool hasEfficientSearchedWord() const = 0;
    };
}

#endif // IMUSICMANAGER_H
