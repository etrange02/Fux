#include "../../include/music/ChansonNomPos.h"

/** Default constructor */
ChansonNomPos::ChansonNomPos()
{
    m_pos = -1;
    m_nom = _("");
}

ChansonNomPos::ChansonNomPos(wxString nom, long pos)
{
    m_nom = nom;
    m_pos = pos;
}

/** Default destructor */
ChansonNomPos::~ChansonNomPos()
{
    //dtor
}

/** Assignment operator
 *  \param rhs Object to assign from
 *  \return A reference to this
 */
ChansonNomPos& ChansonNomPos::operator=(const ChansonNomPos& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

/** Access m_pos
 * \return The current value of m_pos
 */
long ChansonNomPos::GetPos()
{
    return m_pos;
}

/** Set m_pos
 * \param val New value to set
 */
void ChansonNomPos::SetPos(long val)
{
    m_pos = val;
}

/** Access m_nom
 * \return The current value of m_nom
 */
wxString ChansonNomPos::GetNom()
{
    return m_nom;
}

/** Set m_nom
 * \param val New value to set
 */
void ChansonNomPos::SetNom(wxString val)
{
    m_nom = val;
}

