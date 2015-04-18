/***************************************************************
 * Name:      MusicManagerDefaultDecorator.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-01-02
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "MusicManagerDefaultDecorator.h"

using namespace ::music;

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

void MusicManagerDefaultDecorator::moveIntTitlesAt(const wxArrayString& titles, long position)
{
    getDelegate().moveIntTitlesAt(titles, position);
}

void MusicManagerDefaultDecorator::placeStringTitlesAt(const wxArrayString& titles, size_t position)
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

void MusicManagerDefaultDecorator::updateMusicContent(const long position, Music* music)
{
    getDelegate().updateMusicContent(position, music);
}


