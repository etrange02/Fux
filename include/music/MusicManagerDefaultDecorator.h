#ifndef MUSICMANAGERDEFAULTDECORATOR_H
#define MUSICMANAGERDEFAULTDECORATOR_H

#include "AbstractMusicManagerDecorator.h"
#include "MusicManager.h"

class MusicManagerDefaultDecorator : public AbstractMusicManagerDecorator
{
    public:
        /** Default constructor */
        MusicManagerDefaultDecorator(MusicManager& musicManager);
        /** Default destructor */
        virtual ~MusicManagerDefaultDecorator();

        virtual std::vector<Music*>& getMusics();
        virtual size_t getCurrentMusicPosition();
        virtual void moveIntTitlesAt(wxArrayString* titles, long position);
        virtual void placeStringTitlesAt(wxArrayString* titles, size_t position);
        virtual void deleteTitleAt(size_t position);
        virtual bool playMusicAt(long position);
};

#endif // MUSICMANAGERDEFAULTDECORATOR_H
