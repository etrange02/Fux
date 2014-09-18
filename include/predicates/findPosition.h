#ifndef FINDPOSITION_H
#define FINDPOSITION_H

#include "../music/IMusic.h"

class findPosition
{
    public:
        /** Default constructor */
        findPosition(IMusic *music);
        /** Default destructor */
        virtual ~findPosition();

        bool operator()(const IMusic* music);

    private:
        IMusic* m_music;
};

#endif // FINDPOSITION_H
