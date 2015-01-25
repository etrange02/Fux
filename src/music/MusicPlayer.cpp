#include "../../include/music/MusicPlayer.h"

const wxEventType wxEVT_FUX_MUSICPLAYER_CHANGE_TITLE = wxNewEventType();
const wxEventType wxEVT_FUX_MUSICPLAYER_UPDATE_GRAPH = wxNewEventType();
const wxEventType wxEVT_FUX_MUSICPLAYER_CHANGE_STATUS = wxNewEventType();

MusicPlayer::MusicPlayer() :
    m_sound(NULL),
    m_channel(NULL),
    m_parent(NULL),
    m_hasLoadedMusic(false),
    m_stopped(true)
{
    initialize();
}

MusicPlayer::~MusicPlayer()
{
    release();

    //FMOD_System_UnloadPlugin(m_system, codec);
    FMOD_System_Release(m_system);

    delete m_currentTime;
    delete m_totalTime;
}

/** @brief Initializes members
 * Initializes members
 * @return void
 *
 */
void MusicPlayer::initialize()
{
    FMOD_System_Create(&m_system);
    //wxString cheminPluginAAC = wxStandardPaths::Get()->GetDataDir(); cheminPluginAAC << wxFileName::GetPathSeparator() << "codec_aac.dll";
    //FMOD_System_LoadPlugin(m_system, cheminPluginAAC.c_str(), &codec, /*FMOD_PLUGINTYPE_CODEC, */2600);
    //FMOD_System_SetOutputByPlugin(m_system, codec);

    FMOD_System_Init(m_system, 1, FMOD_INIT_NORMAL, NULL);//(void*)cheminPluginAAC.c_str());//

    m_currentTime = new Duration();
    m_totalTime = new Duration();
}

/** @brief Plays a title
 * @param filename a music filename
 * @return void
 *
 */
void MusicPlayer::play(const wxString& filename)
{
    release();
    if (wxFileExists(filename))
    {
        m_stopped = false;
        m_hasLoadedMusic = true;
        FMOD_System_CreateStream(m_system, (char*) filename.wc_str(), FMOD_LOOP_OFF | FMOD_2D | FMOD_SOFTWARE | FMOD_UNICODE, 0, &m_sound);
        FMOD_System_PlaySound(m_system, FMOD_CHANNEL_FREE, m_sound, 0, &m_channel);
        FMOD_Channel_SetVolume(m_channel, getVolume());
        m_filename = filename;

        updateTotalTime();
    }

    sendMusicChangedTitleEvent();
    sendMusicUpdateGraphEvent();
}

/** @brief Stops the music and frees memory *
 * @return void
 *
 */
void MusicPlayer::release()
{
    if (!m_hasLoadedMusic)
        return;
    FMOD_Sound_Release(m_sound);
    m_hasLoadedMusic = false;
    m_stopped = true;
    m_filename = wxEmptyString;
}

/** @brief Indicates the presence of a music in memory
 *
 * @return true if present
 *
 */
bool MusicPlayer::hasLoadedMusic()
{
    return m_hasLoadedMusic;
}

/** @brief Pauses the music
 * @param state true means pause, false means play
 * @return void
 *
 */
void MusicPlayer::setPause(bool state)
{
    FMOD_BOOL result;
    FMOD_Channel_SetPaused(m_channel, state);
    FMOD_Channel_GetPaused(m_channel, &result);
    sendMusicChangedStatusEvent(state ? 1 : 0);
}

/** @brief Indicates if the music is paused
 *
 * @return true if paused
 *
 */
bool MusicPlayer::isPaused()
{
    FMOD_BOOL result;
    FMOD_Channel_GetPaused(m_channel, &result);

    return result;
}

/** @brief Indicates if the music is stopped
 *
 * @return true if stopped
 *
 */
bool MusicPlayer::isStopped()
{
    return m_stopped;
}

/** @brief Stops the music
 *
 * @return void
 *
 */
void MusicPlayer::stop()
{
    FMOD_Channel_Stop(m_channel);
    m_stopped = true;
}

/** @brief Indicates if a music is playing (loaded, not paused and not stopped)
 *
 * @return true if playing
 *
 */
bool MusicPlayer::isPlaying()
{
    return hasLoadedMusic() && !isPaused() && !isStopped();
}

void MusicPlayer::setVolume(int volume)
{
    float vol = volume *0.01;
    m_volume = vol;
    FMOD_Channel_SetVolume(m_channel, m_volume);
}

float MusicPlayer::getVolume()
{
    float volume;
    FMOD_Channel_GetVolume(m_channel, &volume);
    return volume;
}

void MusicPlayer::getSpectrum(float* spectrum, int size)
{
    FMOD_System_GetSpectrum(m_system, spectrum, size, 0, FMOD_DSP_FFT_WINDOW_RECT);
}

void MusicPlayer::updateCurrentTime()
{
    m_currentTime->SetMSecondeTot(getPosition());
}

bool MusicPlayer::isEnding()
{
    if (hasLoadedMusic())
    {
        updateCurrentTime();
        return (m_currentTime->GetMSecondeTot() >= m_totalTime->GetMSecondeTot() - 200);
    }
    return false;
}

Duration* MusicPlayer::getCurrentTime()
{
    return m_currentTime;
}

Duration* MusicPlayer::getTotalTime()
{
    return m_totalTime;
}

void MusicPlayer::updateTotalTime()
{
    unsigned int time;
    FMOD_Sound_GetLength(m_sound, &time, FMOD_TIMEUNIT_MS);

    m_totalTime->SetMSecondeTot(time);
}

void MusicPlayer::setPosition(unsigned int position)
{
    FMOD_Channel_SetPosition(m_channel, position, FMOD_TIMEUNIT_MS);
    updateCurrentTime();
}

void MusicPlayer::setParent(wxWindow* parent)
{
    m_parent = parent;
}

wxWindow* MusicPlayer::getParent()
{
    return m_parent;
}

void MusicPlayer::sendMusicChangedTitleEvent()
{
    if (NULL == m_parent)
        return;
    wxCommandEvent evt(wxEVT_FUX_MUSICPLAYER_CHANGE_TITLE, wxID_ANY);
    m_parent->GetEventHandler()->AddPendingEvent(evt);
}

void MusicPlayer::sendMusicUpdateGraphEvent()
{
    if (NULL == m_parent)
        return;
    wxCommandEvent evt(wxEVT_FUX_MUSICPLAYER_UPDATE_GRAPH, wxID_ANY);
    m_parent->GetEventHandler()->AddPendingEvent(evt);
}

void MusicPlayer::sendMusicChangedStatusEvent(int paused)
{
    if (NULL == m_parent)
        return;
    wxCommandEvent evt(wxEVT_FUX_MUSICPLAYER_CHANGE_STATUS, wxID_ANY);
    evt.SetInt(paused);
    m_parent->GetEventHandler()->AddPendingEvent(evt);
}

wxString& MusicPlayer::getFileName()
{
    return m_filename;
}

unsigned int MusicPlayer::getPosition()
{
    unsigned int position;
    FMOD_Channel_GetPosition(m_channel, &position, FMOD_TIMEUNIT_MS);
    return position;
}

