/***************************************************************
 * Name:      MusicManager.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2014-05-08
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include <music/MusicManager.h>
#include <ctime>
#include <algorithm>
#include <wx/dir.h>
#include <tools/thread/ThreadManager.h>
#include <predicates/findPosition.h>
#include <predicates/findSharedMusicContainer.h>
#include <music/Factory.h>
#include <music/DeletedLines.h>
#include <tools/dnd/dataObjects/PlaylistTransitiveData.h>

#define useMethod(object, method) ((object).*(method))

using namespace music;

const wxEventType wxEVT_FUX_MUSICMANAGER_NO_FILE = wxNewEventType();
const wxEventType wxEVT_FUX_MUSICMANAGER_SEARCH_DONE = wxNewEventType();
const wxEventType wxEVT_FUX_MUSICMANAGER_LINE_DELETED = wxNewEventType();

/** @brief Default constructor
 */
MusicManager::MusicManager() :
    m_repete(false),
    m_random(false),
    m_musicPosition(0),
    m_parent(NULL),
    m_music(NULL),
    m_musicList(new MusicList)
{
    srand(time(NULL));
}

/** @brief Destructor
 */
MusicManager::~MusicManager()
{
    delete m_musicList;
}

/** @brief Repete mode
 *
 * @return true if repete
 *
 */
bool MusicManager::isRepete()
{
    return m_repete;
}

/** @brief Modifies the repete mode
 *
 * @param repete the repete mode
 * @return void
 *
 */
void MusicManager::setRepete(bool repete)
{
    m_repete = repete;
}

/** @brief Random mode
 *
 * @return true if random
 *
 */
bool MusicManager::isRandom()
{
    return m_random;
}

/** @brief Modifies the random mode
 *
 * @param random the random mode
 * @return void
 *
 */
void MusicManager::setRandom(bool random)
{
    m_random = random;
}

/** @brief Returns the music list
 *
 * @return the music list
 *
 */
std::vector<std::shared_ptr<Music>>& MusicManager::getAllMusics()
{
    return m_musicList->getCollection();
}

/** @brief Returns the music list
 *
 * @return the music list
 *
 */
std::vector<std::shared_ptr<Music>>& MusicManager::getSearchedMusics()
{
    return m_searchedMusicCollection;
}

/** @brief Returns the music player.
 * This object plays audio files
 * @return the music player
 *
 */
MusicPlayer& MusicManager::getMusicPlayer()
{
    return m_musicPlayer;
}

/** @brief Returns the current playing music.
 *
 * @return the actual playing title
 *
 */
Music* MusicManager::getMusic()
{
    return m_music;
}

/** @brief Returns the position of the playing music.
 * Returns the position of the playing music in the music list
 * @return the position
 *
 */
size_t MusicManager::getCurrentMusicPosition()
{
    return m_musicPosition;
}

/** @brief Returns the position of the playing music
 * Returns the position of the playing music in the music list
 * @return the position
 *
 */
long MusicManager::getCurrentMusicPositionInSearch()
{
    ///FIXME: Be careful with -1 size_t.
    MusicIterator iter = std::find_if(getSearchedMusics().begin(), getSearchedMusics().end(), findPosition(getMusic()));

    if (iter == getSearchedMusics().end())
        return -1;

    return std::distance(getSearchedMusics().begin(), iter);
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
 *
 * @param position the position
 * @return true on succes
 *
 */
bool MusicManager::playMusicAt(long position)
{
    if (empty())
    {
        m_musicPlayer.stop();
        m_musicPlayer.release();
        m_musicPosition = 0;
        sendMusicNoFileEvent();
        return false;
    }
    if (position < 0 || position >= (long)size())
        position = 0;

    m_musicPosition = position;
    m_music = m_musicList->getCollection().at(position).get();
    m_musicPlayer.play(m_music->GetFileName());
    return true;
}

/** @brief Plays the title found at position position
 *
 * @param position long
 * @return bool
 *
 */
bool MusicManager::playMusicAtInSearch(long position)
{
    if (position < 0 || position >= (long)getSearchedMusics().size())
        position = 0;
    return playMusicAt(m_musicList->getPositionInList(getSearchedMusics().at(position).get()));
}

/** @brief Plays a title.
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
    m_musicPlayer.play(filename);
    parse();
    m_musicPosition = m_musicList->getPositionInList(filename);
    m_music = m_musicList->getCollection().at(m_musicPosition).get();
    return true;
}

/** @brief Reorganizes the music list by moving some titles at a different place
 * Reorganizes the music list by moving some titles at a different place
 * @param titles a list of music name
 * @param position the position to place titles
 * @return void
 *
 */
void MusicManager::moveIntTitlesAt(const wxArrayString& titles, size_t position)
{
    MusicCollection *oldMusics = &m_musicList->getCollection();

    MusicCollection *selectedMusics     = new MusicCollection();
    MusicCollection *notSelectedMusics  = new MusicCollection();
    MusicCollection *newMusics          = new MusicCollection();

    wxArrayString::const_iterator positionIterator = titles.begin();
    long pos = 0;
    (*positionIterator).ToLong(&pos);
    size_t i = 0;

    for (MusicIterator iter = oldMusics->begin(); iter != oldMusics->end(); ++iter)
    {
        if (i == pos)
        {
            selectedMusics->push_back(*iter);
            ++positionIterator;
            if (positionIterator == titles.end())
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

    MusicIterator iter = std::find_if(m_musicList->getCollection().begin(), m_musicList->getCollection().end(), findPosition(getMusic()));

    size_t index = std::distance(m_musicList->getCollection().begin(), iter);
    if (index < m_musicList->getCollection().size())
        m_musicPosition = index;

    delete selectedMusics;
    delete notSelectedMusics;
    delete newMusics;

    m_musicList->sendMusicListUpdatedEvent();
}

/** @brief Not implemented
 *
 * @param titles wxArrayString*
 * @param position long
 * @param update
 * @param autoDelete
 * @return void
 * @deprecated
 */
void MusicManager::moveIntTitlesAtInSearch(const wxArrayString& WXUNUSED(titles), unsigned long WXUNUSED(position))
{

}

/** @brief Inserts titles at a specific position
 * Inserts titles at a specific position
 * @param titles a list of music name
 * @param position the position to place titles
 * @return void
 *
 */
void MusicManager::placeStringTitlesAt(const wxArrayString& titles, size_t position)
{
    bool startPlaying = empty();
    m_musicList->insertLines(titles, position);
    if (startPlaying)
        playMusicAt(0);
    if (position <= m_musicPosition)
        m_musicPosition += position;
    //m_musicList->sendMusicListUpdatedEvent();
    launchSearching();
}

/** @brief Not implemented
 *
 * @param titles wxArrayString*
 * @param position size_t
 * @param update
 * @return void
 * @deprecated
 */
void MusicManager::placeStringTitlesAtInSearch(const wxArrayString& WXUNUSED(titles), size_t WXUNUSED(position))
{

}

/** @brief Delete the current playing title
 * Delete the current playing title and play another title
 *
 */
void MusicManager::deleteCurrentTitle()
{
    if (NULL != getMusic())
    {
        const long positionInSearch = deleteCurrentTitleInSearch();
        const long position = deleteTitle(m_musicPosition);
        sendMusicManagerLineDeleted(position, positionInSearch);
        playMusicAt(m_musicPosition);
    }
}

/** @brief Delete the current playing title in the search list.
 *
 * @return position of the deleted line.
 *
 */
long MusicManager::deleteCurrentTitleInSearch()
{
    if (!getSearchedMusics().empty())
    {
        size_t position = getCurrentMusicPositionInSearch();
        deleteTitleAtInSearch(position);
        /*MusicCollection& musics = getSearchedMusics();
        findSharedMusicContainer finder(m_music);
        MusicIterator iter = std::find_if(musics.begin(), musics.end(), finder);
        getSearchedMusics().erase(iter);
        */
        return position;
    }
    else
        return -1;
}

/** @brief Delete a title from the music list
 * Delete a title from the music list
 * @param position position of the title to delete
 * @return void
 *
 */
void MusicManager::deleteTitleAt(size_t position)
{
    if (position >= m_musicList->size())
        return;
    if (position == m_musicPosition)
        deleteCurrentTitle();
    else
    {
        MusicItem& item = m_musicList->getCollection().at(position);
        const long positionInSearch = deleteTitleInSearch(*item.get());
        deleteTitle(position);
        sendMusicManagerLineDeleted(position, positionInSearch);
    }
    if (empty())
        sendMusicNoFileEvent();
}

/** @brief Delete titles identified by their position in normal mode
 *
 * @param positions const std::vector<unsignedlong>&
 * @return void
 *
 */
void MusicManager::deleteTitleAt(const std::vector<unsigned long>& positions)
{
    if (!changeToAnAvailableTitle(positions, m_musicPosition))
        return;

    for (std::vector<unsigned long>::const_reverse_iterator iter = positions.rbegin(); iter != positions.rend(); ++iter)
        deleteTitleAt(*iter);
}

/** @brief Delete titles identified by their position in search mode
 *
 * @param positions const std::vector<unsignedlong>&
 * @return void
 *
 */
void MusicManager::deleteTitleAtInSearch(const std::vector<unsigned long>& positions)
{
    if (!changeToAnAvailableTitle(positions, getCurrentMusicPositionInSearch()))
        return;

    for (std::vector<unsigned long>::const_reverse_iterator iter = positions.rbegin(); iter != positions.rend(); ++iter)
        deleteTitleAtInSearch(*iter);
}

/** @brief Play a title which is not identified in positions. If all is selected, stop music
 *
 * @param positions const std::vector<unsignedlong>&
 * @return indicates that all identifiers are not in positions
 *
 */
bool MusicManager::changeToAnAvailableTitle(const std::vector<unsigned long>& positions, const long musicPlayingPosition)
{
    if (positions.size() == size())
    {
        deleteAllTitles();
        return false;
    }

    if (musicPlayingPosition < 0)
        return true;

    std::vector<unsigned long>::const_iterator currentPosition = std::find(positions.begin(), positions.end(), musicPlayingPosition);
    if (positions.end() != currentPosition)
    {
        unsigned long position = *currentPosition;

        position = findNextAvailablePosition(positions, currentPosition, position);

        if (size() <= position)
        {
            position = findNextAvailablePosition(positions, positions.begin(), 0);
        }
        playMusicAt(position);
    }
    return true;
}

/** @brief Find the first integer not present in positions from the beginIter and superior to start
 *
 * @param positions const std::vector<unsignedlong>&
 * @param beginIter const std::vector<unsignedlong>::const_iterator&
 * @param start const unsignedlong
 * @return unsigned long
 *
 */
unsigned long MusicManager::findNextAvailablePosition(const std::vector<unsigned long>& positions, const std::vector<unsigned long>::const_iterator& beginIter, const unsigned long start)
{
    unsigned long position = start;
    std::vector<unsigned long>::const_iterator iter = beginIter;
    while (positions.end() != iter)
    {
        if (*iter != position)
            return position;
        ++position;
        ++iter;
    }
    return (positions.back()) + 1;
}

/** @brief Deletes a title from the search list
 *
 * @param position a position
 * @return void
 *
 */
void MusicManager::deleteTitleAtInSearch(size_t position)
{
    if (getSearchedMusics().size() <= position)
        return;

    Music* music = getSearchedMusics().at(position).get();

    const bool deleteCurrent = (getMusic() == music);

    const long musicPosition = deleteTitle(*music);
    deleteTitleInSearch(position);

    sendMusicManagerLineDeleted(musicPosition, position);

    if (deleteCurrent)
        playMusicAt(musicPosition);
}

long MusicManager::deleteTitle(size_t position)
{
    int musicPosition = m_musicList->removeLine(position) ? position : -1;
    if (m_musicPosition > position)
        m_musicPosition--;
    if (m_musicPosition >= m_musicList->size())
        m_musicPosition = m_musicList->size()-1;
    return musicPosition;
}

long MusicManager::deleteTitleInSearch(size_t position)
{
    if (position >= getSearchedMusics().size())
        return -1;

    MusicIterator iter = getSearchedMusics().begin() + position;
    //Music* music = getSearchedMusics().at(position).get();
    getSearchedMusics().erase(iter);

    return position;
}

long MusicManager::deleteTitle(const Music& music)
{
    long position = m_musicList->getPositionInList(&music);
    m_musicList->removeLine(position);
    return position;
}

long MusicManager::deleteTitleInSearch(const Music& music)
{
    findSharedMusicContainer finder(music);
    MusicIterator iter = std::find_if(getSearchedMusics().begin(), getSearchedMusics().end(), finder);

    if (iter == getSearchedMusics().end())
        return -1;

    int position = std::distance(getSearchedMusics().begin(), iter);
    getSearchedMusics().erase(iter);
    return position;
}

/** @brief Delete titles from the music list
 * Delete titles from the music list. If the current title is selected,
 * another one is played
 * @param titles list of titles
 * @param update send an UPDATED event to the frame
 * @return void
 *
 */
void MusicManager::deleteTitles(wxArrayString& titles, bool update)
{
    bool currentMusic = false;

    for (wxArrayString::iterator iter = titles.begin(); iter != titles.end() && !currentMusic; ++iter)
    {
        if ((*iter).IsSameAs(m_music->GetFileName()))
        {
            currentMusic = true;
        }
    }

    m_musicList->removeLines(titles);

    if (currentMusic)
    {
        playAMusic();
    }
    if (update)
        m_musicList->sendMusicListUpdatedEvent();
}

/** @brief Delete all titles and stop the music
 *
 * @return void
 *
 */
void MusicManager::deleteAllTitles()
{
    MusicCollection emptyCollection;
    m_musicList->getCollection().swap(emptyCollection);
    m_musicPlayer.release();
    sendMusicNoFileEvent();
}

/** @brief Explores the directory where the current music is located.
 *
 */
void MusicManager::parse()
{
    if (!getMusicPlayer().hasLoadedMusic())
        return;
    m_musicList->parseDirectory(getMusicPlayer().getFileName().BeforeLast(wxFileName::GetPathSeparator()), Parametre::Get()->getSousDossier());
    m_musicList->sendMusicListUpdatedEvent();
    launchSearching();
}

/** @brief Explores directories in filenames
 *
 * @param filenames wxArrayString&
 * @param update indicator to send an event
 * @return void
 *
 */
void MusicManager::parse(const wxArrayString& filenames, bool update)
{
    bool startPlaying = empty();
    m_musicList->addLines(filenames);
    if (startPlaying)
        playMusicAt(0);
    if (update)
        m_musicList->sendMusicListUpdatedEvent();
    launchSearching();
}

/** @brief
 *
 * @param filename const wxString&
 * @return void
 * @see MusicManger::parse
 */
void MusicManager::parse(const wxString& filename)
{
    wxArrayString arrayS;
    arrayS.Add(filename);
    parse(arrayS);
}

/** @brief Modifies the parent
 *
 * @param parent wxWindow*
 * @return void
 *
 */
void MusicManager::setParent(wxWindow* parent)
{
    m_parent = parent;
    m_musicList->setParent(m_parent);
    m_musicPlayer.setParent(m_parent);
}

/** @brief Return the parent window
 *
 * @return wxWindow*
 *
 */
wxWindow* MusicManager::getParent() const
{
    return m_parent;
}

/** @brief Indicates if the music list is empty
 *
 * @return bool
 *
 */
bool MusicManager::empty() const
{
    return m_musicList->empty();
}

/** @brief Returns the music list's size
 *
 * @return size_t
 *
 */
size_t MusicManager::size() const
{
    return m_musicList->size();
}

/** @brief Creates a play list file (M3U file) with the music list
 *
 * @param filename the output
 * @return bool
 *
 */
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
    for (MusicIterator iter = this->getAllMusics().begin(); iter != this->getAllMusics().end(); ++iter)
    {
        outputFile.AddLine((*iter)->GetFileName());
    }

    outputFile.Write();
    outputFile.Close();
    return true;
}

/** @brief Event - No music in play list
 *
 * @return void
 *
 */
void MusicManager::sendMusicNoFileEvent()
{
    if (NULL == m_parent)
        return;
    wxCommandEvent evt(wxEVT_FUX_MUSICMANAGER_NO_FILE, wxID_ANY);
    m_parent->GetEventHandler()->AddPendingEvent(evt);
}

/** @brief Event - Search done
 *
 * @return void
 *
 */
void MusicManager::sendSearchEndingEvent()
{
    if (NULL == m_parent)
        return;
    wxCommandEvent evt(wxEVT_FUX_MUSICMANAGER_SEARCH_DONE, wxID_ANY);
    m_parent->GetEventHandler()->AddPendingEvent(evt);
}

/** @brief Returns the keyword used to make search
 *
 * @return wxString
 *
 */
wxString MusicManager::getSearchedWord() const
{
    return m_searchedWord;
}

/** @brief Modifies the search keyword and refresh the research
 *
 * @param searchedWord const wxString&
 * @return void
 *
 */
void MusicManager::setSearchWord(const wxString& searchedWord)
{
    m_searchedWord = searchedWord.Lower();
    m_musicList->setSendEventWhenAdding(!hasEfficientSearchedWord());
    launchSearching();
}

/** @brief Process the research
 *
 * @return void
 *
 */
void MusicManager::launchSearching()
{
    m_searchedMusicCollection.clear();
    if (hasEfficientSearchedWord())
    {
        for (MusicIterator iter = m_musicList->getCollection().begin(); iter != m_musicList->getCollection().end(); ++iter)
        {
            if ((*iter)->IsMatching(m_searchedWord))
                m_searchedMusicCollection.push_back(*iter);
        }
        sendSearchEndingEvent();
    }
}

/** @brief Indicates if keyword is not empty
 *
 * @return bool
 *
 */
bool MusicManager::hasEfficientSearchedWord() const
{
    return !getSearchedWord().IsEmpty();/* && !getSearchedWord().IsSameAs(_T("*"));*/
}

/** @brief Updates the content of a music file.
 * Position defined in the music list
 * @param position position in the music list
 * @param musicData
 *
 */
void MusicManager::updateMusicContent(const size_t position, Music* musicData)
{
    updateMusicContent(position, musicData, getAllMusics());
}

/** @brief Updates the content of a music file.
 * Position defined in the search list
 * @param position position in the search list
 * @param musicData
 * @see MusicManager::updateMusicContent
 */
void MusicManager::updateMusicContentInSearch(const size_t position, Music* musicData)
{
    updateMusicContent(position, musicData, getSearchedMusics());
}

/** @brief Updates the content of a music file.
 * Process the treatment
 * @param position a position of a music
 * @param musicData data
 * @param collection a collection of musics
 *
 */
void MusicManager::updateMusicContent(const size_t position, Music* musicData, MusicCollection& collection)
{
    if (position >= collection.size())
        return;
    std::shared_ptr<Music>& musicToModify = collection.at(position);

    if (musicToModify.get() == getMusic()) // on modifie le titre courant
        updateCurrentMusic(musicData);
    else // on modifie un autre titre
        tools::thread::ThreadManager::get().addRunnable(Factory::createMusicFileWriterThread(musicData, musicToModify, getParent()));
}

/** @brief Updates the content of the current music file played.
 * Specific treatment, which can not be threaded
 * @param newMusicData data
 *
 */
void MusicManager::updateCurrentMusic(Music* newMusicData)
{
    // before
    Music* music = getMusic();
    unsigned int time = getMusicPlayer().getPosition();
    getMusicPlayer().release();

    // modification
    std::shared_ptr<Music> musicPtr(music);
    MusicFile* musicFile = Factory::createMusicFileWriter(newMusicData, musicPtr);
    musicFile->process();

    //after
    getMusicPlayer().play(music->GetFileName());
    getMusicPlayer().setPosition(time);
    delete musicFile;
}

/** @brief Event - Give information about a newly deleted title (position in the two modes).
 *
 * @param position const long
 * @param positionInSearch const long
 * @return void
 *
 */
void MusicManager::sendMusicManagerLineDeleted(const long position, const long positionInSearch)
{
    if (NULL == getParent())
        return;
    wxCommandEvent evt(wxEVT_FUX_MUSICMANAGER_LINE_DELETED, wxID_ANY);

    DeletedLines* deletedLines = new DeletedLines(position, positionInSearch);
    //DeletedLines deletedLines(position, positionInSearch);
    evt.SetClientData(deletedLines);
    getParent()->GetEventHandler()->AddPendingEvent(evt);
}

/** @brief Fills the transitiveData with shared Musics found at positions.
 *
 * @param positions std::vector<unsigned long>&
 * @param transitiveData dragAndDrop::PlaylistTransitiveData&
 * @return void
 *
 */
void MusicManager::convertPositionsToTransitiveData(const std::vector<unsigned long>& positions, dragAndDrop::PlaylistTransitiveData& transitiveData)
{
    MusicCollection& musics = getAllMusics();
    for (std::vector<unsigned long>::const_iterator iter = positions.begin(); iter != positions.end(); ++iter)
    {
        transitiveData.add(musics.at(*iter));
    }
}

