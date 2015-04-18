#ifndef IMUSICPLAYER_H_INCLUDED
#define IMUSICPLAYER_H_INCLUDED

#include "Duration.h"

namespace music
{
    class IMusicPlayer
    {
        public:
            virtual void stop() = 0;

            virtual bool hasLoadedMusic() = 0;
            virtual bool isPaused() = 0;
            virtual bool isStopped() = 0;
            virtual bool isPlaying() = 0;
            virtual bool isEnding() = 0;

            virtual float getVolume() = 0;
            virtual void getSpectrum(float* spectrum, int size) = 0;
            virtual Duration *getCurrentTime() = 0;
            virtual Duration *getTotalTime() = 0;
            virtual wxWindow *getParent() = 0;
    };
}

#endif // IMUSICPLAYER_H_INCLUDED
