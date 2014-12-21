/***************************************************************
 * Name:      Duree.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2013-07-06
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../../include/music/Duree.h"

/** Default constructor */
Duree::Duree()
{
    m_minute = 0;
    m_seconde = 0;
    m_msecondeTot = 0;
}

/** Default destructor */
Duree::~Duree()
{
    //dtor
}

/** Assignment operator
 *  \param rhs Object to assign from
 *  \return A reference to this
 */
Duree& Duree::operator=(const Duree& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    m_minute = rhs.m_minute;
    m_seconde = rhs.m_seconde;
    m_msecondeTot = rhs.m_msecondeTot;
    return *this;
}

unsigned int Duree::GetMinute()
{
    return m_minute;
}

/** Set m_minute
 * \param val New value to set
 */
void Duree::SetMinute(unsigned int val)
{
    m_minute = val;
}

/** Access m_seconde
 * \return The current value of m_seconde
 */
unsigned int Duree::GetSeconde()
{
    return m_seconde;
}

/** Set m_seconde
 * \param val New value to set
 */
void Duree::SetSeconde(unsigned int val)
{
    m_seconde = val;
}

/** Access m_msecondeTot
 * \return The current value of m_msecondeTot
 */
unsigned int Duree::GetMSecondeTot()
{
    return m_msecondeTot;
}

/** Set m_msecondeTot
 * \param val New value to set
 */
void Duree::SetMSecondeTot(unsigned int val)
{
    m_msecondeTot = val;
    val/=1000;
    m_seconde = val%60;
    m_minute = val/60;
}

