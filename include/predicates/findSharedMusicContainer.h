#ifndef FINDSHAREDMUSICCONTAINER_H
#define FINDSHAREDMUSICCONTAINER_H

#include <memory>

namespace music {
    class IMusic;
    class Music;
}

class findSharedMusicContainer
{
    public:
        /** Default constructor */
        findSharedMusicContainer(const music::IMusic& music);
        bool operator()(std::shared_ptr<music::Music>& item);

    private:
        const music::IMusic& m_music;
};

#endif // FINDSHAREDMUSICCONTAINER_H
