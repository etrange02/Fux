#ifndef ABSTRACTMUSICMANAGERDECORATOR_H
#define ABSTRACTMUSICMANAGERDECORATOR_H

#include <vector>

#include "IMusicManager.h"
#include "MusicManager.h"

namespace music
{
    class AbstractMusicManagerDecorator : public IMusicManager
    {
        public:
            /** Default constructor */
            AbstractMusicManagerDecorator(MusicManager& musicManager);
            /** Default destructor */
            virtual ~AbstractMusicManagerDecorator();

    //        virtual std::vector<Music*>& getMusics() = 0;
    //        /**/virtual size_t getCurrentMusicPosition() = 0;
    //        /**/virtual void moveIntTitlesAt(wxArrayString* titles, long position) = 0;
    //        /**/virtual void placeStringTitlesAt(wxArrayString* titles, size_t position) = 0;
    //        /**/virtual void deleteTitleAt(size_t position) = 0;
    //        /**/virtual bool playMusicAt(long position) = 0;
    //        /**/virtual int  getDeletedLine(DeletedLines& deletedLines) = 0;

            virtual bool isRepete();
            virtual bool isRandom();
            virtual Music *getMusic();
            virtual MusicPlayer& getMusicPlayer();

            virtual void setRepete(bool repete);
            virtual void setRandom(bool random);

            virtual bool playNextMusic();
            virtual bool playPreviousMusic();
            virtual bool playNextOrRandomMusic();
            virtual bool playPreviousOrRandomMusic();
            virtual bool playAMusic();
            virtual bool playMusic(const wxString& name);
            virtual bool playMusicThenParse(wxString filename);
            virtual bool playSameMusic();

            virtual void deleteCurrentTitle();
            virtual void deleteTitles(wxArrayString& titles, bool update = false);

            virtual void parse();
            virtual void parse(const wxString& filename);
            virtual void parse(const wxArrayString& filenames, bool update = true);

            virtual void setParent(wxWindow* parent);
            virtual wxWindow* getParent() const;

            virtual bool saveMusicListIntoFile(wxString const &filename);

            virtual bool empty() const;
            virtual size_t size() const;

            virtual wxString getSearchedWord() const;
            virtual void setSearchWord(const wxString& searchedWord);
            virtual bool hasEfficientSearchedWord() const;

        protected:
            MusicManager& getDelegate();
            MusicManager& getDelegate() const;

        private:
            MusicManager& m_musiqManager;
    };
}

#endif // ABSTRACTMUSICMANAGERDECORATOR_H
