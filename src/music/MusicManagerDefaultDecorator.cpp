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

void MusicManagerDefaultDecorator::moveIntTitlesAt(wxArrayString* titles, long position, bool update, bool autoDelete)
{
    getDelegate().moveIntTitlesAt(titles, position, update, autoDelete);
}

void MusicManagerDefaultDecorator::placeStringTitlesAt(wxArrayString* titles, size_t position, bool update)
{
    getDelegate().placeStringTitlesAt(titles, position, update);
}

void MusicManagerDefaultDecorator::deleteTitleAt(size_t position)
{
    getDelegate().deleteTitleAt(position);
}


