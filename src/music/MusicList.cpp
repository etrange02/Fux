/***************************************************************
 * Name:      MusicList.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2014-04-17
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../../include/music/MusicList.h"

const wxEventType wxEVT_FUX_MUSICLIST_LIST_UPDATE = wxNewEventType();

MusicList::MusicList()
{
    initialize();
}

MusicList::~MusicList()
{
    delete m_musicList;
}

void MusicList::initialize()
{
    m_musicList = new std::vector<Music*>();
	m_parent = NULL;
}

std::vector<Music*>* MusicList::getMusicList() const
{
    return m_musicList;
}

bool MusicList::empty() const
{

    return getMusicList()->empty();
}

size_t MusicList::size() const
{
    return getMusicList()->size();
}

void MusicList::parseDirectory(wxString dirname, bool recursive)
{
    if (recursive)
        parseDirectoryRecursively(dirname);
    else
        parseDirectoryWithoutRecurs(dirname);
}

void MusicList::parseDirectoryRecursively(wxString dirname)
{
    wxDir dir(dirname);
    Search research(this);
    dir.Traverse(research, _T("*.*"), wxDIR_DIRS|wxDIR_FILES|wxDIR_FILES);//Parametre::Get()->getFiltre()
}

void MusicList::parseDirectoryWithoutRecurs(wxString dirname)
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

void MusicList::clear()
{
    m_musicList->clear();
}

void MusicList::addLines(wxArrayString *pathArray)
{
    for ( wxArrayString::iterator iter = pathArray->begin(); iter != pathArray->end(); ++iter)
    {
        addUnknownKindLine(*iter);
    }
}

void MusicList::addUnknownKindLine(wxString path)
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

void MusicList::addFileLine(wxString path)
{
    m_musicList->push_back(new Music(path));
}

void MusicList::addDirLine(wxString path)
{
    parseDirectory(path, Parametre::Get()->getSousDossier());
}

void MusicList::importFileContent(wxString filename)
{
    wxTextFile m3uFile(filename);
    m3uFile.Open();

    if (m3uFile.GetLineCount() > 0 && !m3uFile.GetLine(0).IsSameAs(M3U_EXTENSION))
        addFileLine(m3uFile.GetLine(0));

    for (size_t i = 1; i < m3uFile.GetLineCount(); ++i)
        addFileLine(m3uFile.GetLine(i));

    m3uFile.Close();
}

wxString MusicList::getNameAtPosition(long position)
{
    if (position >= (long)m_musicList->size() || position < 0)
        return wxEmptyString;

    return getMusicList()->at(position)->GetFileName();
}

long MusicList::getPositionInList(wxString filename, long position)
{
    if (filename.IsEmpty())
        return -1;

    if (getNameAtPosition(position).IsSameAs(filename))
        return position;

    if (position == (int) m_musicList->size())
        position--;

    unsigned int i = (position == -1) ? 0 : position;
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

long MusicList::getPositionInList(Music* music)
{
    if (NULL == music)
        return -1;

    long index = 0;

    for (std::vector<Music*>::iterator iter = getMusicList()->begin(); iter != getMusicList()->end(); ++iter, ++index)
    {
        if (music == *iter)
            return index;
    }
    return -1;
}

void MusicList::removeLine(ChansonNomPos& title)
{
    long position = title.GetPos();
    if (position == -1)
        position = getPositionInList(title.GetNom());
    removeLine(position);
}

void MusicList::removeLine(size_t position)
{
    if (!getMusicList()->empty() && getMusicList()->size() > position)
    {
        std::vector<Music*>::iterator it = getMusicList()->begin() + position;
        getMusicList()->erase(it);
    }
}

void MusicList::removeLines(wxArrayString *filenameArray)
{
    size_t i = 0, maxArray = filenameArray->GetCount(), j = 0;
    bool seen = true, cont = true;

    while (j < maxArray && cont)
    {
        i = 0;
        while (i < getMusicList()->size() && cont)
        {
            if (getNameAtPosition(i).IsSameAs(filenameArray->Item(j)))
            {
                getMusicList()->erase(getMusicList()->begin() + i);
                ++j;
                --i;
                seen = false;
                if (j >= maxArray)
                    cont = false;
            }
            ++i;
        }
        if (seen)
        {
            seen = false;
            ++i;
        }
        else
            seen = true;
    }
}

void MusicList::exchangeLine(wxString filename1, wxString filename2)
{
    int lineToChange = getPositionInList(filename1);
    Music *music = getMusicList()->at(lineToChange);
    getMusicList()->assign(lineToChange, new Music(filename2));
    delete music;
}



void MusicList::insertLines(wxArrayString* filenameArray, long position)
{
    long insertionLine = position;

    if (insertionLine < 0)
        insertionLine = 0;
    else if (insertionLine > (long) m_musicList->size()+1)
        insertionLine = m_musicList->size() + 1;

    std::vector<Music*> *tmpArray = new std::vector<Music*>();

    for (wxArrayString::iterator iter = filenameArray->begin(); iter != filenameArray->end(); ++iter)
    {
        if (Parametre::Get()->islisable(iter->AfterLast('.').Lower()))
            tmpArray->push_back(new Music(*iter));
    }

    std::vector<Music*>::iterator musicIterator = m_musicList->begin() + insertionLine;
    m_musicList->insert(musicIterator, tmpArray->begin(), tmpArray->end());

    delete tmpArray;
}

void MusicList::setParent(wxWindow* parent)
{
    m_parent = parent;
}

wxWindow* MusicList::getParent() const
{
    return m_parent;
}

void MusicList::sendMusicListUpdatedEvent()
{
    if (NULL == getParent())
        return;
    wxCommandEvent evt(wxEVT_FUX_MUSICLIST_LIST_UPDATE, wxID_ANY);
    getParent()->GetEventHandler()->AddPendingEvent(evt);
}


