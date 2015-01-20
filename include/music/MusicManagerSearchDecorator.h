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
        virtual void moveIntTitlesAt(wxArrayString* titles, long position, bool update = true, bool autoDelete = true);
        virtual void placeStringTitlesAt(wxArrayString* titles, size_t position, bool update = true);
        virtual void deleteTitleAt(size_t position);
};

#endif // MUSICMANAGERSEARCHDECORATOR_H
