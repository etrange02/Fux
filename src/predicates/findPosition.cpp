#include "../../include/predicates/findPosition.h"

findPosition::findPosition(IMusic *music)
{
    m_music = music;
}

findPosition::~findPosition()
{}

bool findPosition::operator()(const IMusic* music)
{
    return (m_music == music);
}

