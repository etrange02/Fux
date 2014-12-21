#include "MusicFileThreadManager.h"

MusicFileThreadManager::MusicFileThreadManager()
{
    //ctor
}

MusicFileThreadManager::~MusicFileThreadManager()
{
    //dtor
}

MusicFileThreadManager::MusicFileThreadManager(const MusicFileThreadManager& other)
{
    *this = other;
}

MusicFileThreadManager& MusicFileThreadManager::operator=(const MusicFileThreadManager& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    this->m_musicFiles = rhs.m_musicFiles;
    return *this;
}

void MusicFileThreadManager::addMusicFile(MusicFile* musicFile)
{
    m_musicFiles.push(musicFile);
}

void MusicFileThreadManager::start()
{
    processQueue();
}

void MusicFileThreadManager::processQueue()
{
    MusicFile* musicFile = NULL;
    while (!m_musicFiles.empty())
    {
        musicFile = m_musicFiles.pop_front();
        musicFile->process();
        delete musicFile;
    }
}

