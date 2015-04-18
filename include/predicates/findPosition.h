#ifndef FINDPOSITION_H
#define FINDPOSITION_H

#include "music/IMusic.h"

class findPosition
{
    public:
        /** Default constructor */
        findPosition(music::IMusic *music);
        /** Default destructor */
        virtual ~findPosition();

        bool operator()(const music::IMusic* music);

    private:
        music::IMusic* m_music;
};

#endif // FINDPOSITION_H
