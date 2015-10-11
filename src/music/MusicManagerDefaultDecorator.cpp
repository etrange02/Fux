/***************************************************************
 * Name:      MusicManagerDefaultDecorator.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-01-02
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include <MusicManagerDefaultDecorator.h>
#include <music/DeletedLines.h>

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

MusicCollection& MusicManagerDefaultDecorator::getMusics()
{
    return getDelegate().getAllMusics();
}

size_t MusicManagerDefaultDecorator::getCurrentMusicPosition()
{
    return getDelegate().getCurrentMusicPosition();
}

void MusicManagerDefaultDecorator::moveIntTitlesAt(const wxArrayString& titles, size_t position)
{
    getDelegate().moveIntTitlesAt(titles, position);
}

void MusicManagerDefaultDecorator::moveTitlesAt(const MusicCollection& titles, size_t position)
{
    getDelegate().moveTitlesAt(titles, position);
}

void MusicManagerDefaultDecorator::placeStringTitlesAt(const wxArrayString& titles, size_t position)
{
    getDelegate().placeStringTitlesAt(titles, position);
}

void MusicManagerDefaultDecorator::deleteTitleAt(size_t position)
{
    getDelegate().deleteTitleAt(position);
}

void MusicManagerDefaultDecorator::deleteTitleAt(const std::vector<unsigned long>& positions)
{
    getDelegate().deleteTitleAt(positions);
}

bool MusicManagerDefaultDecorator::playMusicAt(long position)
{
    return getDelegate().playMusicAt(position);
}

void MusicManagerDefaultDecorator::updateMusicContent(const size_t position, Music* music)
{
    getDelegate().updateMusicContent(position, music);
}

int MusicManagerDefaultDecorator::getDeletedLine(DeletedLines& deletedLines)
{
    return deletedLines.getPosition();
}

void MusicManagerDefaultDecorator::convertPositionsToTransitiveData(const std::vector<unsigned long>& positions, dragAndDrop::PlaylistTransitiveData& transitiveData)
{
    getDelegate().convertPositionsToTransitiveData(positions, transitiveData);
}


