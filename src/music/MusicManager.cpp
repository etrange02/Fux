/***************************************************************
 * Name:      MusicManager.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2014-05-08
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../../include/music/MusicManager.h"

static MusicManager* s_musicManager_instance = NULL;

const wxEventType wxEVT_FUX_MUSICMANAGER_NO_FILE = wxNewEventType();

MusicManager::MusicManager()
{
    initialize();
}

MusicManager::~MusicManager()
{
    delete m_musicPlayer;
    delete m_musicList;
}

MusicManager* MusicManager::get()
{
    if (NULL == s_musicManager_instance)
        s_musicManager_instance = new MusicManager();
    return s_musicManager_instance;
}

void MusicManager::initialize()
{
    m_repete = false;
    m_random = false;
    m_musicPosition = 0;
    m_parent = NULL;
    srand(time(NULL));
    m_musicList = new MusicList();
    m_musicPlayer = new MusicPlayer();
    m_music = NULL;
}

bool MusicManager::isRepete()
{
    return m_repete;
}

void MusicManager::setRepete(bool repete)
{
    m_repete = repete;
}

bool MusicManager::isRandom()
{
    return m_random;
}

void MusicManager::setRandom(bool random)
{
    m_random = random;
}

MusicList* MusicManager::getMusicList()
{
    return m_musicList;
}

MusicPlayer* MusicManager::getMusicPlayer()
{
    return m_musicPlayer;
}

Music* MusicManager::getMusic()
{
    return m_music;
}

size_t MusicManager::getCurrentMusicPosition()
{
    return m_musicPosition;
    //return getMusicList()->getPositionInList(getMusic());
}

bool MusicManager::playNextMusic()
{
    size_t newPosition = m_musicPosition;
    newPosition++;
    if (newPosition >= size())
        newPosition = 0;

    return playMusicAt(newPosition);
}

bool MusicManager::playNextOrRandomMusic()
{
    if (isRandom())
        return playRandomMusic();
    else
        return playNextMusic();
}

bool MusicManager::playPreviousMusic()
{
    long newPosition = m_musicPosition;
    newPosition--;
    if (newPosition < 0)
        newPosition = size() -1;

    return playMusicAt(newPosition);
}

bool MusicManager::playPreviousOrRandomMusic()
{
    if (isRandom())
        return playRandomMusic();
    else
        return playPreviousMusic();
}

bool MusicManager::playMusicAt(long position)
{
    if (empty())
    {
        m_musicPlayer->stop();
        m_musicPlayer->release();
        m_musicPosition = 0;
        sendMusicNoFileEvent();
        return false;
    }
    if (position < 0 || position >= size())
        position = 0;

    m_musicPosition = position;
    m_music = m_musicList->getMusicList()->at(position);
    m_musicPlayer->play(m_music->GetFileName());
    return true;
}

bool MusicManager::playAMusic()
{
    if (isRepete())
        return playMusicAt(m_musicPosition);
    else if (isRandom())
        return playRandomMusic();
    else
        return playNextMusic();
}

bool MusicManager::playRandomMusic()
{
    long newPosition = 0;
    do
    {
        newPosition = rand() % size();
    } while (newPosition == m_musicPosition);

    return playMusicAt(newPosition);
}

bool MusicManager::playSameMusic()
{
    return playMusicAt(m_musicPosition);
}

bool MusicManager::playMusic(wxString name/*, long position*/)
{
    //if (position < 0)
    long position = m_musicList->getPositionInList(name, -1);

    return playMusicAt(position);
}

void MusicManager::moveIntTitlesAt(wxArrayString* titles, long position, bool update, bool autoDelete)
{
    std::vector<Music*> *oldMusics = m_musicList->getMusicList();

    std::vector<Music*> *selectedMusics = new std::vector<Music*>();
    std::vector<Music*> *notSelectedMusics = new std::vector<Music*>();
    std::vector<Music*> *newMusics = new std::vector<Music*>();

    wxArrayString::iterator positionIterator = titles->begin();
    long pos = 0;
    (*positionIterator).ToLong(&pos);
    long i = 0;

    for (std::vector<Music*>::iterator iter = oldMusics->begin(); iter != oldMusics->end(); ++iter)
    {
        if (i == pos)
        {
            selectedMusics->push_back(*iter);
            ++positionIterator;
            if (positionIterator == titles->end())
                pos = -1;
            else
                (*positionIterator).ToLong(&pos);
            // position is updated to place musics at the good place that is to say between musics and not between lines
            if (position > i)
                --position;
        }
        else
        {
            notSelectedMusics->push_back(*iter);
        }
        ++i;
    }

    if (!notSelectedMusics->empty())
        newMusics->insert(newMusics->end(), notSelectedMusics->begin(), notSelectedMusics->begin() + position);

    newMusics->insert(newMusics->end(), selectedMusics->begin(), selectedMusics->end());

    if (!notSelectedMusics->empty() && position != oldMusics->size() && position < notSelectedMusics->size())
            newMusics->insert(newMusics->end(), notSelectedMusics->begin() + position, notSelectedMusics->end());

    oldMusics->swap(*newMusics);

    std::vector<Music*>::iterator iter = std::find_if(m_musicList->getMusicList()->begin(), m_musicList->getMusicList()->end(), findPosition(getMusic()));

    size_t index = std::distance(m_musicList->getMusicList()->begin(), iter);
    if (index < m_musicList->getMusicList()->size())
        m_musicPosition = index;

    delete selectedMusics;
    delete notSelectedMusics;
    delete newMusics;

    m_musicList->sendMusicListUpdatedEvent();
}

void MusicManager::placeStringTitlesAt(wxArrayString* titles, long position, bool update)
{
    m_musicList->insertLines(titles, position);
    if (position <= m_musicPosition)
        m_musicPosition += position;
}

ChansonNomPos MusicManager::deleteCurrentTitle()
{
    ChansonNomPos deletedTitle;

    if (NULL != m_music)
    {
        deletedTitle.SetNom(m_music->GetFileName());
        deletedTitle.SetPos(m_musicPosition);
        m_musicList->removeLine(m_musicPosition);
        if (m_musicList->size() <= m_musicPosition)
            m_musicPosition--;
        playMusicAt(m_musicPosition);
    }

    return deletedTitle;
}

void MusicManager::deleteTitleAt(long position)
{
    if (position == m_musicPosition)
        deleteCurrentTitle();
    else
    {
        m_musicList->removeLine(position);
        if (m_musicPosition > position)
            m_musicPosition--;
    }
}

void MusicManager::deleteTitles(wxArrayString* titles, bool update)
{
    bool change = false;
    long position = 0;

    for (wxArrayString::iterator iter = titles->begin(); iter != titles->end() && !change; ++iter)
    {
        if ((*iter).IsSameAs(m_music->GetFileName()))
        {
            change = true;
            //position = m_musicPosition-i;
            break;
        }
    }

    m_musicList->removeLines(titles);

    if (change)
    {
        playAMusic();
    }
}

void MusicManager::parse()
{
    if (!getMusicPlayer()->hasLoadedMusic())
        return;
    m_musicList->parseDirectory(getMusicPlayer()->getFileName().BeforeLast(wxFileName::GetPathSeparator()), Parametre::Get()->getSousDossier());
}

void MusicManager::parse(wxArrayString* filenames, bool update)
{
    //m_musicList->addLines(filenames);
    bool startPlaying = empty();
    m_musicList->addLines(filenames);
    if (startPlaying)
        playMusicAt(0);
}

void MusicManager::parse(wxString filename)
{
    if (Parametre::Get()->islisable(filename.AfterLast('.')))
    {
        if (empty())
        {
            m_musicList->addDirLine(filename.BeforeLast(wxFileName::GetPathSeparator()));
            playMusic(filename);
        }
        else
        {
            m_musicList->addFileLine(filename);
        }
        /*if (m_musicPlayer->hasLoadedMusic())
        {
            //m_musicPlayer->play(filename);
            //playMusic(filename);
            playMusicAt(0);
            //parse();
        }*/
    }
    else if (Parametre::Get()->isContainerFile(filename.AfterLast('.')))
    {
        bool startPlaying = empty();
        m_musicList->importFileContent(filename);
        if (startPlaying)
            playMusicAt(0);
    }
    else if (wxDirExists(filename))
    {
        bool startPlaying = empty();
        m_musicList->addDirLine(filename);
        if (startPlaying)
            playMusicAt(0);
    }
}

void MusicManager::setParent(wxWindow* parent)
{
    m_parent = parent;
    m_musicList->setParent(m_parent);
    m_musicPlayer->setParent(m_parent);
}

wxWindow* MusicManager::getParent() const
{
    return m_parent;
}

bool MusicManager::empty() const
{
    return m_musicList->empty();
}

size_t MusicManager::size() const
{
    return m_musicList->size();
}

bool MusicManager::saveMusicListIntoFile(wxString const &filename)
{
    wxTextFile outputFile(filename);
    if (outputFile.Exists())
    {
        outputFile.Open();
        outputFile.Clear();
    }
    else if (!outputFile.Create())
    {
        return false;
    }

    outputFile.AddLine(M3U_EXTENSION);
    for (std::vector<Music*>::iterator iter = this->getMusicList()->getMusicList()->begin(); iter != this->getMusicList()->getMusicList()->end(); ++iter)
    {
        outputFile.AddLine((*iter)->GetFileName());
    }

    outputFile.Write();
    outputFile.Close();
    return true;
}

void MusicManager::sendMusicNoFileEvent()
{
    if (NULL == m_parent)
        return;
    wxCommandEvent evt(wxEVT_FUX_MUSICMANAGER_NO_FILE, wxID_ANY);
    m_parent->GetEventHandler()->AddPendingEvent(evt);
}

