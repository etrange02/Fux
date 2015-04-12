#include "MusicManagerSearchDecorator.h"

MusicManagerSearchDecorator::MusicManagerSearchDecorator(MusicManager& musicManager) :
    AbstractMusicManagerDecorator(musicManager)
{
    //ctor
}

MusicManagerSearchDecorator::~MusicManagerSearchDecorator()
{
    //dtor
}

std::vector<Music*>& MusicManagerSearchDecorator::getMusics()
{
    return getDelegate().getSearchedMusics();
}

size_t MusicManagerSearchDecorator::getCurrentMusicPosition()
{
    return getDelegate().getCurrentMusicPositionInSearch();
}

void MusicManagerSearchDecorator::moveIntTitlesAt(const wxArrayString& titles, long position)
{
    getDelegate().moveIntTitlesAtInSearch(titles, position);
}

void MusicManagerSearchDecorator::placeStringTitlesAt(const wxArrayString& titles, size_t position)
{
    getDelegate().placeStringTitlesAtInSearch(titles, position);
}

void MusicManagerSearchDecorator::deleteTitleAt(size_t position)
{
    getDelegate().deleteTitleAtInSearch(position);
}

bool MusicManagerSearchDecorator::playMusicAt(long position)
{
    return getDelegate().playMusicAtInSearch(position);
}

void MusicManagerSearchDecorator::updateMusicContent(const long position, Music* music)
{
    getDelegate().updateMusicContentInSearch(position, music);
}

