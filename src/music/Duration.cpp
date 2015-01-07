/***************************************************************
 * Name:      Duration.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2013-07-06
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "../../include/music/Duration.h"

/// TODO (David): Update class name

/** Default constructor */
Duration::Duration()
{
    m_minute = 0;
    m_seconde = 0;
    m_msecondeTot = 0;
}

/** Default destructor */
Duration::~Duration()
{
    //dtor
}

/** Assignment operator
 *  \param rhs Object to assign from
 *  \return A reference to this
 */
Duration& Duration::operator=(const Duration& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    m_minute = rhs.m_minute;
    m_seconde = rhs.m_seconde;
    m_msecondeTot = rhs.m_msecondeTot;
    return *this;
}

unsigned int Duration::GetMinute()
{
    return m_minute;
}

/** Set m_minute
 * \param val New value to set
 */
void Duration::SetMinute(unsigned int val)
{
    m_minute = val;
}

/** Access m_seconde
 * \return The current value of m_seconde
 */
unsigned int Duration::GetSeconde()
{
    return m_seconde;
}

/** Set m_seconde
 * \param val New value to set
 */
void Duration::SetSeconde(unsigned int val)
{
    m_seconde = val;
}

/** Access m_msecondeTot
 * \return The current value of m_msecondeTot
 */
unsigned int Duration::GetMSecondeTot()
{
    return m_msecondeTot;
}

/** Set m_msecondeTot
 * \param val New value to set
 */
void Duration::SetMSecondeTot(unsigned int val)
{
    m_msecondeTot = val;
    val/=1000;
    m_seconde = val%60;
    m_minute = val/60;
}

