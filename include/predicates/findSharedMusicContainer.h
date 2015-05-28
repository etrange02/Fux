#ifndef FINDSHAREDMUSICCONTAINER_H
#define FINDSHAREDMUSICCONTAINER_H

#include <memory>

namespace music {
    class Music;
}

class findSharedMusicContainer
{
    public:
        /** Default constructor */
        findSharedMusicContainer(const music::Music& music);
        bool operator()(std::shared_ptr<music::Music>& item);

    private:
        const music::Music& m_music;
};

#endif // FINDSHAREDMUSICCONTAINER_H
