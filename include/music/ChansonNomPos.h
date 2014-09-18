#ifndef CHANSONNOMPOS_H
#define CHANSONNOMPOS_H

#include "wx/wx.h"

/**
 * @struct ChansonNomPos
 * @brief Structure contenant le nom et la position de la chanson dans le fichier musique.liste
 */

class ChansonNomPos
{
    public:
        ChansonNomPos();
        ChansonNomPos(wxString nom, long pos);
        virtual ~ChansonNomPos();
        ChansonNomPos& operator=(const ChansonNomPos& other);
        long GetPos();
        void SetPos(long val);
        wxString GetNom();
        void SetNom(wxString val);

    protected:
    private:
        long m_pos; //!< Member variable "m_pos"
        wxString m_nom; //!< Member variable "m_nom"
};

#endif // CHANSONNOMPOS_H
