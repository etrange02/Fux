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

/** @brief Default constructor
 */
MusicManager::MusicManager()
{
    initialize();
}

/** @brief Destructor
 */
MusicManager::~MusicManager()
{
    delete m_musicPlayer;
    delete m_musicList;
}

/** @brief Singleton
 * Singleton
 * @return the MusicManager
 *
 */
MusicManager& MusicManager::get()
{
    if (NULL == s_musicManager_instance)
        s_musicManager_instance = new MusicManager();
    return *s_musicManager_instance;
}

/** @brief Initialize members
 * Initialize members
 * @return void
 *
 */
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

/** @brief Repete mode
 * Repete mode
 * @return true if repete
 *
 */
bool MusicManager::isRepete()
{
    return m_repete;
}

/** @brief Modifies the repete mode
 * Modifies the repete mode
 * @param repete the repete mode
 * @return void
 *
 */
void MusicManager::setRepete(bool repete)
{
    m_repete = repete;
}

/** @brief Random mode
 * Random mode
 * @return true if random
 *
 */
bool MusicManager::isRandom()
{
    return m_random;
}

/** @brief Modifies the random mode
 * Modifies the random mode
 * @param random the random mode
 * @return void
 *
 */
void MusicManager::setRandom(bool random)
{
    m_random = random;
}

/** @brief Returns the music list
 * Returns the music list
 * @return the music list
 *
 */
std::vector<Music*>& MusicManager::getMusics()
{
    if (!hasEfficientSearchedWord())
        return m_musicList->getCollection();
    else
        return m_searchedMusicCollection;
}

/** @brief Returns the music player
 * Returns the music player. This object plays audio files
 * @return the music player
 *
 */
MusicPlayer& MusicManager::getMusicPlayer()
{
    return *m_musicPlayer;
}

/** @brief Returns the current playing music
 * Returns the current playing music
 * @return the actual playing title
 *
 */
Music* MusicManager::getMusic()
{
    return m_music;
}

/** @brief Returns the position of the playing music
 * Returns the position of the playing music in the music list
 * @return the position
 *
 */
size_t MusicManager::getCurrentMusicPosition()
{
    return m_musicPosition;
}

/** @brief Plays the next title in the playlist
 * Plays the next title in the playlist. If the end is reached,
 * the first one is played
 * @return true on success
 *
 */
bool MusicManager::playNextMusic()
{
    size_t newPosition = m_musicPosition + 1;
    if (newPosition >= size())
        newPosition = 0;

    return playMusicAt(newPosition);
}

/** @brief Plays the next or a random title
 * Plays the next or a random title
 * @return true on success
 *
 */
bool MusicManager::playNextOrRandomMusic()
{
    if (isRandom())
        return playRandomMusic();
    else
        return playNextMusic();
}

/** @brief Plays the previous title in the playlist
 * Plays the previous title in the playlist. If the begin is reached,
 * the last one is played
 * @return true on success
 *
 */
bool MusicManager::playPreviousMusic()
{
    long newPosition = m_musicPosition;
    newPosition--;
    if (newPosition < 0)
        newPosition = size() -1;

    return playMusicAt(newPosition);
}

/** @brief Plays the previous or a random title
 * Plays the previous or a random title
 * @return true on success
 *
 */
bool MusicManager::playPreviousOrRandomMusic()
{
    if (isRandom())
        return playRandomMusic();
    else
        return playPreviousMusic();
}

/** @brief Plays the title found at position position
 * Plays the title found at position position
 * @param position the position
 * @return true on succes
 *
 */
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
    if (position < 0 || position >= (long)size())
        position = 0;

    m_musicPosition = position;
    m_music = m_musicList->getCollection().at(position);
    m_musicPlayer->play(m_music->GetFileName());
    return true;
}

bool MusicManager::playMusicAtInShownCollection(long position)
{
    bool play = false;
    if (hasEfficientSearchedWord())
    {
        if (position < 0 || position >= (long)m_searchedMusicCollection.size())
            position = 0;
        play = playMusicAt(m_musicList->getPositionInList(m_searchedMusicCollection.at(position)));
    }
    else
        play = playMusicAt(position);
    return play;
}

/** @brief Plays a title
 * Default behaviour when a title ends
 * @return true on success
 *
 */
bool MusicManager::playAMusic()
{
    if (isRepete())
        return playMusicAt(m_musicPosition);
    else if (isRandom())
        return playRandomMusic();
    else
        return playNextMusic();
}

/** @brief Plays a random title
 * Plays a random title
 * @return true on success
 *
 */
bool MusicManager::playRandomMusic()
{
    size_t newPosition = 0;
    do
    {
        newPosition = rand() % size();
    } while (newPosition == m_musicPosition);

    return playMusicAt(newPosition);
}

/** @brief Replay the current title
 * Replay the current title
 * @return true on success
 *
 */
bool MusicManager::playSameMusic()
{
    return playMusicAt(m_musicPosition);
}

/** @brief Plays the file
 * Plays the file if it is in the playlist
 * @param name a filename
 * @return true on success
 *
 */
bool MusicManager::playMusic(const wxString& name)
{
    long position = m_musicList->getPositionInList(name, -1);

    return playMusicAt(position);
}

/** @brief Plays the file then parse the directory
 * Plays the file then parse the directory
 * @param filename a music filename
 * @return true on success
 *
 */
bool MusicManager::playMusicThenParse(wxString filename)
{
    m_musicPlayer->play(filename);
    return true;
    parse();
    m_musicPosition = m_musicList->getPositionInList(filename);
    m_music = m_musicList->getCollection().at(m_musicPosition);
    return true;
}

/** @brief Reorganizes the music list by moving some titles at a different place
 * Reorganizes the music list by moving some titles at a different place
 * @param titles a list of music name
 * @param position the position to place titles
 * @param update ??? not used - must be deleted
 * @param autoDelete ??? not used - must be deleted
 * @return void
 *
 */
void MusicManager::moveIntTitlesAt(wxArrayString* titles, long position, bool update, bool autoDelete)
{
    std::vector<Music*> *oldMusics = &m_musicList->getCollection();

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

    std::vector<Music*>::iterator iter = std::find_if(m_musicList->getCollection().begin(), m_musicList->getCollection().end(), findPosition(getMusic()));

    size_t index = std::distance(m_musicList->getCollection().begin(), iter);
    if (index < m_musicList->getCollection().size())
        m_musicPosition = index;

    delete selectedMusics;
    delete notSelectedMusics;
    delete newMusics;

    m_musicList->sendMusicListUpdatedEvent();
}

/** @brief Inserts titles at a specific position
 * Inserts titles at a specific position
 * @param titles a list of music name
 * @param position the position to place titles
 * @param update ??? not used - must be deleted
 * @return void
 *
 */
void MusicManager::placeStringTitlesAt(wxArrayString* titles, size_t position, bool update)
{
    m_musicList->insertLines(titles, position);
    if (position <= m_musicPosition)
        m_musicPosition += position;
}

/** @brief Delete the current playing title
 * Delete the current playing title and play another title
 *
 */
void MusicManager::deleteCurrentTitle()
{
    if (NULL != m_music)
    {
        m_musicList->removeLine(m_musicPosition);
        if (m_musicList->size() <= m_musicPosition)
            m_musicPosition--;
        playMusicAt(m_musicPosition);
    }
}

/** @brief Delete a title from the music list
 * Delete a title from the music list
 * @param position position of the title to delete
 * @return void
 *
 */
void MusicManager::deleteTitleAt(size_t position)
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

/** @brief Delete titles from the music list
 * Delete titles from the music list. If the current title is selected,
 * another one is played
 * @param titles list of titles
 * @param update ??? not used - must be deleted
 * @return void
 *
 */
void MusicManager::deleteTitles(wxArrayString* titles, bool update)
{
    bool change = false;

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
    if (!getMusicPlayer().hasLoadedMusic())
        return;
    m_musicList->parseDirectory(getMusicPlayer().getFileName().BeforeLast(wxFileName::GetPathSeparator()), Parametre::Get()->getSousDossier());
}

void MusicManager::parse(wxArrayString* filenames, bool update)
{
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
    for (std::vector<Music*>::iterator iter = this->getMusics().begin(); iter != this->getMusics().end(); ++iter)
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

wxString MusicManager::getSearchedWord() const
{
    return m_searchedWord;
}

void MusicManager::setSearchWord(const wxString& searchedWord)
{
    m_searchedWord = searchedWord;
    launchSearching();
}

void MusicManager::launchSearching()
{
    m_searchedMusicCollection.clear();
    if (hasEfficientSearchedWord())
    {
        for (vector<Music*>::iterator iter = m_musicList->getCollection().begin(); iter != m_musicList->getCollection().end(); ++iter)
        {
            if ((*iter)->IsMatching(m_searchedWord))
                m_searchedMusicCollection.push_back(*iter);
        }
    }
}

bool MusicManager::hasEfficientSearchedWord() const
{
    return !getSearchedWord().IsEmpty();/* && !getSearchedWord().IsSameAs(_T("*"));*/
}

