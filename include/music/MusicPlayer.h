#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <wx/wx.h>
#include <fmod.hpp>

//#include "IMusicPlayer.h"
//#include "Music.h"
#include "Duration.h"

extern const wxEventType wxEVT_FUX_MUSICPLAYER_CHANGE_TITLE;
extern const wxEventType wxEVT_FUX_MUSICPLAYER_UPDATE_GRAPH;
extern const wxEventType wxEVT_FUX_MUSICPLAYER_CHANGE_STATUS;

namespace music
{
    class MusicPlayer// : IMusicPlayer
    {
        public:
            MusicPlayer();
            virtual ~MusicPlayer();

            void play(const wxString& filename);
            void release();
            void stop();
            void setPause(bool state);
            void setVolume(int volume);
            void setPosition(unsigned int position);
            void setParent(wxWindow *parent);

            bool hasLoadedMusic();
            bool isPaused();
            bool isStopped();
            bool isPlaying();
            bool isEnding();

            float getVolume();
            void getSpectrum(float* spectrum, int size);
            Duration* getCurrentTime();
            Duration* getTotalTime();
            wxWindow* getParent();
            wxString& getFileName();
            unsigned int getPosition();

        protected:
            void initialize();
            void updateCurrentTime();
            void updateTotalTime();

            void sendMusicChangedTitleEvent();
            void sendMusicUpdateGraphEvent();
            void sendMusicChangedStatusEvent(int paused);

        private:
            FMOD_SOUND *m_sound;
            FMOD_CHANNEL *m_channel;
            FMOD_SYSTEM *m_system;
            wxWindow *m_parent;
            bool m_hasLoadedMusic;
            bool m_stopped;
            float m_volume;
            Duration *m_currentTime;
            Duration *m_totalTime;

            wxString m_filename;
    };
}

#endif // MUSICPLAYER_H
