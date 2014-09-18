#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <wx/wx.h>
#include <fmod.hpp>

//#include "IMusicPlayer.h"
//#include "Music.h"
#include "Duree.h"

extern const wxEventType wxEVT_FUX_MUSICPLAYER_CHANGE_TITLE;
extern const wxEventType wxEVT_FUX_MUSICPLAYER_UPDATE_GRAPH;
extern const wxEventType wxEVT_FUX_MUSICPLAYER_CHANGE_STATUS;

class MusicPlayer// : IMusicPlayer
{
    public:
        MusicPlayer();
        virtual ~MusicPlayer();

        void play(wxString filename);
        void release();
        void stop();
        void setPause(bool state);
        void setVolume(int volume);
        void setPosition(int position);
        void setParent(wxWindow *parent);

        bool hasLoadedMusic();
        bool isPaused();
        bool isStopped();
        bool isPlaying();
        bool isEnding();

        float getVolume();
        void getSpectrum(float* spectrum, int size);
        Duree *getCurrentTime();
        Duree *getTotalTime();
        wxWindow *getParent();
        wxString& getFileName();

    protected:
        void initialize();
        void updateCurrentTime();
        void updateTotalTime();

        void sendMusicChangedTitleEvent();
        void sendMusicUpdateGraphEvent();
        void sendMusicChangedStatusEvent(int paused);

    private:
        bool m_hasLoadedMusic;
        bool m_stopped;
        float m_volume;
        FMOD_SYSTEM *m_system;
        FMOD_SOUND *m_sound;
        FMOD_CHANNEL *m_channel;
        Duree *m_currentTime;
        Duree *m_totalTime;

        wxString m_filename;
        wxWindow *m_parent;
};

#endif // MUSICPLAYER_H
