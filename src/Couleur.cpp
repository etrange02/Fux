#include "../include/Couleur.h"

Couleur::Couleur(unsigned int red, unsigned int green, unsigned int blue)
{
    m_red = red;
    m_green = green;
    m_blue = blue;
}

Couleur::~Couleur()
{
}

unsigned int Couleur::GetRed()
{
    return m_red;
}

void Couleur::SetRed(unsigned int val)
{
    m_red = val;
}

unsigned int Couleur::GetBlue()
{
    return m_blue;
}

void Couleur::SetBlue(unsigned int val)
{
    m_blue = val;
}

unsigned int Couleur::GetGreen()
{
    return m_green;
}

void Couleur::SetGreen(unsigned int val)
{
    m_green = val;
}

void Couleur::SetRGB(unsigned int red, unsigned int green, unsigned int blue)
{
    m_red = red;
    m_green = green;
    m_blue = blue;
}

/*Couleur& Couleur::operator=(const Couleur& other)
{
    m_red = other.GetRed();
    m_green = other.GetGreen();
    m_blue = other.GetBlue();
    return *this;
}*/
