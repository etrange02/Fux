/***************************************************************
 * Name:      MusicList.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2014-04-17
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "music/MusicList.h"
#include "tools/thread/ThreadManager.h"
#include "music/Factory.h"
#include "settings/Parametre.h"

using namespace ::music;

const wxEventType wxEVT_FUX_MUSICLIST_LIST_UPDATE = wxNewEventType();
const wxEventType wxEVT_FUX_MUSICLIST_LIST_LINE_DELETED = wxNewEventType();
/// TODO (David): Complete wxEVT_FUX_MUSICLIST_LIST_LINE_DELETED event by using it to refresh PlayListTableau and explorers...


/** @brief Default constructor
 */
MusicList::MusicList() :
    ISearchTraversable(),
    m_musicList(new MusicCollection),
    m_parent(NULL),
    m_sendEventWhenAdding(true)
{
}

/** @brief Default destructor
 */
MusicList::~MusicList()
{
    delete m_musicList;
}

/** @brief Gets the music list
 * Get the music list, in which the playlist is stored
 * @return the music list
 *
 */
MusicCollection& MusicList::getCollection() const
{
    return *m_musicList;
}

/** @brief Indicates the presence of elements
 * Indicates the presence of elements
 * @return true if the list is empty
 *
 */
bool MusicList::empty() const
{
    return getCollection().empty();
}

/** @brief Gets the list size
 * Gets the list
 * @return the list size
 *
 */
size_t MusicList::size() const
{
    return getCollection().size();
}

/** @brief Parse the directory given in parameter
 * Parse the directory given in parameter
 * @param dirname the directory name
 * @param recursive recurs all subdirectories
 *
 */
void MusicList::parseDirectory(const wxString& dirname, bool recursive)
{
    if (recursive)
        parseDirectoryRecursively(dirname);
    else
        parseDirectoryWithoutRecurs(dirname);
}

/** @brief Parse the directory given in parameter and subdirectories
 * Parse the directory given in parameter and subdirectories
 * @param dirname the directory name
 *
 */
void MusicList::parseDirectoryRecursively(const wxString& dirname)
{
    wxDir dir(dirname);
    Search research(this);
    dir.Traverse(research, _T("*.*"), wxDIR_DIRS|wxDIR_FILES|wxDIR_FILES);//Parametre::Get()->getFiltre()
}

/** @brief Parse only the directory given in parameter
 * Parse only the directory given in parameter and not subdirectories
 * @param dirname the directory name
 *
 */
void MusicList::parseDirectoryWithoutRecurs(const wxString& dirname)
{
    wxDir dir(dirname);
    wxString temp;
    bool cont = dir.GetFirst(&temp, wxEmptyString, wxDIR_FILES);

    while (cont)
    {
        if (Parametre::Get()->islisable(temp.AfterLast('.').Lower()))
            addFileLine(dirname + wxFileName::GetPathSeparator() + temp);
        cont = dir.GetNext(&temp);
    }
}

/** @brief Clears the list
 * Clears the list
 *
 */
void MusicList::clear()
{
    m_musicList->clear();
}

/** @brief Adds in the list some lines
 * Adds some lines in the list according to their kind (music file, playlist file, directory)
 * @param pathArray paths
 *
 */
void MusicList::addLines(const wxArrayString& pathArray)
{
    for ( wxArrayString::const_iterator iter = pathArray.begin(); iter != pathArray.end(); ++iter)
    {
        addUnknownKindLine(*iter);
    }
}

/** @brief Adds the path in the list after verifications
 * Adds the path in the list after verifications of its kind
 * @param path a file or directory path
 *
 */
void MusicList::addUnknownKindLine(const wxString& path)
{
    if (wxFileExists(path))
    {
        if (Parametre::Get()->isContainerFile(path.AfterLast('.')))
        {
            importFileContent(path);
        }
        else if (Parametre::Get()->islisable(path.AfterLast('.')))
        {
            addFileLine(path);
        }
    }
    else if (wxDirExists(path))
        parseDirectory(path, Parametre::Get()->getSousDossier());
}

/** @brief Adds a music file in the list
 * Adds a music file in the list
 * @param path a music path
 *
 */
void MusicList::addFileLine(const wxString& path)
{
    Music* music = Factory::createMusic(path);
    std::shared_ptr<Music> sp(music);
    m_musicList->push_back(sp);
    wxWindow *parent = isSendEventWhenAdding() ? m_parent : NULL;
    tools::thread::ThreadManager::get().addRunnable(Factory::createMusicFileReaderThread(sp, parent));
}

/** @brief Parse the directory
 * Parse the directory
 * @param path the directory path
 *
 */
void MusicList::addDirLine(const wxString& path)
{
    parseDirectory(path, Parametre::Get()->getSousDossier());
}

/** @brief Adds the content of the file into the list
 *
 * @param filename a filename
 *
 */
void MusicList::importFileContent(const wxString& filename)
{
    wxTextFile m3uFile(filename);
    m3uFile.Open();

    for (wxString line = m3uFile.GetFirstLine(); !m3uFile.Eof(); line = m3uFile.GetNextLine() )
    {
        addUnknownKindLine(line);
    }

    m3uFile.Close();
}

/** @brief Gets the filename at the wanted position
 * Gets the filename at the wanted position
 * @param position a position
 * @return a filename if found, an empty string otherwise
 *
 */
wxString MusicList::getNameAtPosition(long position)
{
    if (position >= (long)m_musicList->size() || position < 0)
        return wxEmptyString;

    return getCollection().at(position)->GetFileName();
}

/** @brief Gets the nearest position of the pair <filename, position>
 * Gets the nearest position of the filename at the wanted position.
 * @param filename a filename
 * @param position a position if known, else a negative number
 * @return a positive number indicating the position if found, -1 otherwise
 *
 */
long MusicList::getPositionInList(const wxString& filename, long position)
{
    if (filename.IsEmpty())
        return -1;

    if (getNameAtPosition(position).IsSameAs(filename))
        return position;

    if (position == (int) m_musicList->size())
        position--;

    unsigned int i = (position < 0) ? 0 : position;
    bool cont = true;

    while (i<m_musicList->size() && cont)
    {
        if (getNameAtPosition(i).IsSameAs(filename))
        {
            cont = false;
            --i;
        }
        ++i;
    }

    if (cont)
    {
        i = position;
        while (i > 0 && cont)
        {
            if (getNameAtPosition(i).IsSameAs(filename))
            {
                cont = false;
                ++i;
            }
            --i;
        }
    }

    return cont ? -1 : i;
}

/** @brief Gets the position of music
 * Gets the position of the Music music in the list
 * @param music an instance
 * @return a positive number if found, -1 otherwise
 *
 */
long MusicList::getPositionInList(const IMusic* music)
{
    if (NULL == music)
        return -1;

    long index = 0;

    for (MusicIterator iter = getCollection().begin(); iter != getCollection().end(); ++iter, ++index)
    {
        if (music == (*iter).get())
            return index;
    }
    return -1;
}

/** @brief Removes the title at the given position
 *
 * @param position the position to remove
 *
 */
void MusicList::removeLine(size_t position)
{
    if (!getCollection().empty() && getCollection().size() > position)
    {
        MusicIterator it = getCollection().begin() + position;
        getCollection().erase(it);
        sendMusicListLineDeleted(position);
        //sendMusicListUpdatedEvent();
    }
}

/** @brief Removes from the current list each filename in filenameArray
 *
 * @param filenameArray A list of filenames
 *
 */
void MusicList::removeLines(wxArrayString& filenameArray)
{
    wxArrayString::iterator iterFilename = filenameArray.begin();
    MusicIterator iterMusic = getCollection().begin();
    MusicIterator iterMusicOld;
    while (iterFilename != filenameArray.end() && iterMusic != getCollection().end())
    {
        if ((*iterMusic)->GetFileName().IsSameAs(*iterFilename))
        {
            iterMusicOld = iterMusic;
            --iterMusic;
            getCollection().erase(iterMusicOld);
            // removeLine ??
            ++iterFilename;
        }
        ++iterMusic;
    }
}

/** @brief Exchange two lines
 * @param filename1 First line
 * @param filename2 Second line
 *
 */
/// TODO (David): Mauvaise idée, utiliser les positions sera plus efficaces, et remplissage avec un filereader
/// TODO (David): Pas utilisé dans le code, à supprimer ?? L'idée de base devait être la mise à jour d'une ligne
/// => on crée un nouvel objet avec les bonne valeurs, on le met à la place de l'ancien, on supprime l'ancien
void MusicList::exchangeLine(const wxString& filename1, const wxString& filename2)
{
    int lineToChange = getPositionInList(filename1);
    //std::shared_ptr<Music> music = getCollection().at(lineToChange);
    getCollection().assign(lineToChange, std::make_shared<Music>(filename2));
    //delete music;
    sendMusicListUpdatedEvent();
}

/** @brief Insert filenames at a specific position
 * Insert filenames at a specific position
 * @param filenameArray A list of filenames
 * @param position position to put filenames
 *
 */
void MusicList::insertLines(const wxArrayString& filenameArray, long position)
{
    long insertionLine = position;

    if (insertionLine < 0)
        insertionLine = 0;
    else if (insertionLine > (long) m_musicList->size()+1)
        insertionLine = m_musicList->size() + 1;

    MusicCollection *tmpArray = new MusicCollection();

    for (wxArrayString::const_iterator iter = filenameArray.begin(); iter != filenameArray.end(); ++iter)
    {
        if (Parametre::Get()->islisable(iter->AfterLast('.').Lower()))
        {
            addFileLine(*iter);
        }
    }

    MusicIterator musicIterator = m_musicList->begin() + insertionLine;
    m_musicList->insert(musicIterator, tmpArray->begin(), tmpArray->end());

    delete tmpArray;
}

/** @brief Modifies the parent window
 * Modifies the parent window
 * @param parent The parent
 *
 */
void MusicList::setParent(wxWindow* parent)
{
    m_parent = parent;
}

/** @brief Gets the parent window
 * Gets the parent window
 * @return the parent window
 *
 */
wxWindow* MusicList::getParent() const
{
    return m_parent;
}

/** @brief Send an event - the music list has been modified
 * Send an event to the parent window - the music list has been modified
 *
 */
void MusicList::sendMusicListUpdatedEvent()
{
    if (NULL == getParent())
        return;
    wxCommandEvent evt(wxEVT_FUX_MUSICLIST_LIST_UPDATE, wxID_ANY);
    getParent()->GetEventHandler()->AddPendingEvent(evt);
}

bool MusicList::isSendEventWhenAdding() const
{
    return m_sendEventWhenAdding;
}

void MusicList::setSendEventWhenAdding(bool send)
{
    m_sendEventWhenAdding = true;//send;
}

void MusicList::sendMusicListLineDeleted(const int position)
{
    if (NULL == getParent())
        return;
    wxCommandEvent evt(wxEVT_FUX_MUSICLIST_LIST_LINE_DELETED, wxID_ANY);
    evt.SetInt(position);
    getParent()->GetEventHandler()->AddPendingEvent(evt);
}

