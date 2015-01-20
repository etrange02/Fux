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

void MusicManagerSearchDecorator::moveIntTitlesAt(wxArrayString* titles, long position, bool update, bool autoDelete)
{
    getDelegate().moveIntTitlesAtInSearch(titles, position, update, autoDelete);
}

void MusicManagerSearchDecorator::placeStringTitlesAt(wxArrayString* titles, size_t position, bool update)
{
    getDelegate().placeStringTitlesAtInSearch(titles, position, update);
}

void MusicManagerSearchDecorator::deleteTitleAt(size_t position)
{
    getDelegate().deleteTitleAtInSearch(position);
}


