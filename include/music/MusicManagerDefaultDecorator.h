#ifndef MUSICMANAGERDEFAULTDECORATOR_H
#define MUSICMANAGERDEFAULTDECORATOR_H

#include "AbstractMusicManagerDecorator.h"
#include "MusicManager.h"

namespace music
{
    class MusicManagerDefaultDecorator : public AbstractMusicManagerDecorator
    {
        public:
            /** Default constructor */
            MusicManagerDefaultDecorator(MusicManager& musicManager);
            /** Default destructor */
            virtual ~MusicManagerDefaultDecorator();

            virtual MusicCollection& getMusics();
            virtual size_t getCurrentMusicPosition();
            virtual void moveIntTitlesAt(const wxArrayString& titles, size_t position);
            virtual void placeStringTitlesAt(const wxArrayString& titles, size_t position);
            virtual void deleteTitleAt(size_t position);
            virtual void deleteTitleAt(const std::vector<unsigned long>& positions);
            virtual bool playMusicAt(long position);
            virtual void updateMusicContent(const size_t position, Music* music);
            virtual int  getDeletedLine(DeletedLines& deletedLines);
    };
}

#endif // MUSICMANAGERDEFAULTDECORATOR_H
