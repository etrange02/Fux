/***************************************************************
 * Name:      MusicManagerSearchDecorator.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-01-02
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "MusicManagerSearchDecorator.h"

using namespace ::music;

MusicManagerSearchDecorator::MusicManagerSearchDecorator(MusicManager& musicManager) :
    AbstractMusicManagerDecorator(musicManager)
{
    //ctor
}

MusicManagerSearchDecorator::~MusicManagerSearchDecorator()
{
    //dtor
}

MusicCollection& MusicManagerSearchDecorator::getMusics()
{
    return getDelegate().getSearchedMusics();
}

size_t MusicManagerSearchDecorator::getCurrentMusicPosition()
{
    return getDelegate().getCurrentMusicPositionInSearch();
}

void MusicManagerSearchDecorator::moveIntTitlesAt(const wxArrayString& titles, size_t position)
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

void MusicManagerSearchDecorator::updateMusicContent(const size_t position, Music* music)
{
    getDelegate().updateMusicContentInSearch(position, music);
}

