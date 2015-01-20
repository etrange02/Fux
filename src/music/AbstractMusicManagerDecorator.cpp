#include "AbstractMusicManagerDecorator.h"

AbstractMusicManagerDecorator::AbstractMusicManagerDecorator(MusicManager& musicManager) :
    m_musiqManager(musicManager)
{
    //ctor
}

AbstractMusicManagerDecorator::~AbstractMusicManagerDecorator()
{
    //dtor
}

MusicManager& AbstractMusicManagerDecorator::getDelegate() const
{
    return m_musiqManager;
}

MusicManager& AbstractMusicManagerDecorator::getDelegate()
{
    return m_musiqManager;
}


bool AbstractMusicManagerDecorator::isRepete()
{
    return getDelegate().isRepete();
}

bool AbstractMusicManagerDecorator::isRandom()
{
    return getDelegate().isRandom();
}

Music *AbstractMusicManagerDecorator::getMusic()
{
    return getDelegate().getMusic();
}

MusicPlayer& AbstractMusicManagerDecorator::getMusicPlayer()
{
    return getDelegate().getMusicPlayer();
}

void AbstractMusicManagerDecorator::setRepete(bool repete)
{
    getDelegate().setRepete(repete);
}

void AbstractMusicManagerDecorator::setRandom(bool random)
{
    getDelegate().setRandom(random);
}

bool AbstractMusicManagerDecorator::playNextMusic()
{
    return getDelegate().playNextMusic();
}

bool AbstractMusicManagerDecorator::playPreviousMusic()
{
    return getDelegate().playPreviousMusic();
}

bool AbstractMusicManagerDecorator::playNextOrRandomMusic()
{
    return getDelegate().playNextOrRandomMusic();
}

bool AbstractMusicManagerDecorator::playPreviousOrRandomMusic()
{
    return getDelegate().playPreviousOrRandomMusic();
}

bool AbstractMusicManagerDecorator::playAMusic()
{
    return getDelegate().playAMusic();
}

bool AbstractMusicManagerDecorator::playMusicAt(long position)
{
    return getDelegate().playMusicAt(position);
}

bool AbstractMusicManagerDecorator::playMusicAtInShownCollection(long position)
{
    return getDelegate().playMusicAtInShownCollection(position);
}

bool AbstractMusicManagerDecorator::playMusic(const wxString& name)
{
    return getDelegate().playMusic(name);
}

bool AbstractMusicManagerDecorator::playMusicThenParse(wxString filename)
{
    return getDelegate().playMusicThenParse(filename);
}

bool AbstractMusicManagerDecorator::playSameMusic()
{
    return getDelegate().playSameMusic();
}

void AbstractMusicManagerDecorator::deleteCurrentTitle()
{
    getDelegate().deleteCurrentTitle();
}

void AbstractMusicManagerDecorator::deleteTitles(wxArrayString& titles, bool update/* = false*/)
{
    getDelegate().deleteTitles(titles, update);
}

void AbstractMusicManagerDecorator::parse()
{
    getDelegate().parse();
}

void AbstractMusicManagerDecorator::parse(const wxString& filename)
{
    getDelegate().parse(filename);
}

void AbstractMusicManagerDecorator::parse(wxArrayString& filenames, bool update)
{
    getDelegate().parse(filenames, update);
}

void AbstractMusicManagerDecorator::setParent(wxWindow* parent)
{
    getDelegate().setParent(parent);
}

wxWindow* AbstractMusicManagerDecorator::getParent() const
{
    return getDelegate().getParent();
}

bool AbstractMusicManagerDecorator::saveMusicListIntoFile(wxString const &filename)
{
    return getDelegate().saveMusicListIntoFile(filename);
}

bool AbstractMusicManagerDecorator::empty() const
{
    return getDelegate().empty();
}

size_t AbstractMusicManagerDecorator::size() const
{
    return getDelegate().size();
}

wxString AbstractMusicManagerDecorator::getSearchedWord() const
{
    return getDelegate().getSearchedWord();
}

void AbstractMusicManagerDecorator::setSearchWord(const wxString& searchedWord)
{
    getDelegate().setSearchWord(searchedWord);
}

bool AbstractMusicManagerDecorator::hasEfficientSearchedWord() const
{
    return getDelegate().hasEfficientSearchedWord();
}

