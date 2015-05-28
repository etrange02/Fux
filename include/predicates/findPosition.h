#ifndef FINDPOSITION_H
#define FINDPOSITION_H

#include "music/IMusic.h"
#include <memory>

class findPosition
{
    public:
        /** Default constructor */
        findPosition(music::IMusic *music);
        /** Default destructor */
        virtual ~findPosition();

        bool operator()(const music::IMusic* music);
        bool operator()(const std::shared_ptr<music::IMusic>& music);

    private:
        music::IMusic* m_music;
};

#endif // FINDPOSITION_H
