#include "MusicManagerDefaultDecorator.h"

MusicManagerDefaultDecorator::MusicManagerDefaultDecorator(MusicManager& musicManager) :
    AbstractMusicManagerDecorator(musicManager)
{
    //ctor
}

MusicManagerDefaultDecorator::~MusicManagerDefaultDecorator()
{
    //dtor
}

std::vector<Music*>& MusicManagerDefaultDecorator::getMusics()
{
    return getDelegate().getAllMusics();
}

size_t MusicManagerDefaultDecorator::getCurrentMusicPosition()
{
    return getDelegate().getCurrentMusicPosition();
}

void MusicManagerDefaultDecorator::moveIntTitlesAt(wxArrayString* titles, long position)
{
    getDelegate().moveIntTitlesAt(titles, position);
}

void MusicManagerDefaultDecorator::placeStringTitlesAt(wxArrayString* titles, size_t position)
{
    getDelegate().placeStringTitlesAt(titles, position);
}

void MusicManagerDefaultDecorator::deleteTitleAt(size_t position)
{
    getDelegate().deleteTitleAt(position);
}

bool MusicManagerDefaultDecorator::playMusicAt(long position)
{
    return getDelegate().playMusicAt(position);
}


