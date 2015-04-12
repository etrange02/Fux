#ifndef MUSICMANAGERSEARCHDECORATOR_H
#define MUSICMANAGERSEARCHDECORATOR_H

#include "AbstractMusicManagerDecorator.h"
#include "MusicManager.h"

class MusicManagerSearchDecorator : public AbstractMusicManagerDecorator
{
    public:
        /** Default constructor */
        MusicManagerSearchDecorator(MusicManager& musicManager);
        /** Default destructor */
        virtual ~MusicManagerSearchDecorator();

        virtual std::vector<Music*>& getMusics();
        virtual size_t getCurrentMusicPosition();
        virtual void moveIntTitlesAt(const wxArrayString& titles, long position);
        virtual void placeStringTitlesAt(const wxArrayString& titles, size_t position);
        virtual void deleteTitleAt(size_t position);
        virtual bool playMusicAt(long position);
        virtual void updateMusicContent(const long position, Music* music);
};

#endif // MUSICMANAGERSEARCHDECORATOR_H
