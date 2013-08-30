/***************************************************************
 * Name:      DnDCible.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2012-06-26
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../../include/DnD/DnDCible.h"

/**
 * @class DnDCible
 * @brief Représente la cible d'un Drag&Drop pour une wxListCtrl
 */

/**
 * Constructeur
 * @param liste la liste cible
 */
DnDCible::DnDCible(wxListCtrl *liste) : wxDropTarget(new DnDBufferData)
{
    m_liste = liste;
    m_pageGestion = NULL;
}

/**
 * Constructeur
 * @param liste la liste cible
 * @param pageGestion la fenêtre parente de la liste cible (c'est elle qui traite les informations)
 */
DnDCible::DnDCible(wxListCtrl *liste, wxWindow* pageGestion) : wxDropTarget(new DnDBufferData)
{
    m_liste = liste;
    m_pageGestion = (PageGestionPeriph*) pageGestion;
}

/**
 * Surcharge
 */
wxDragResult DnDCible::OnDragOver(wxCoord WXUNUSED(x), wxCoord WXUNUSED(y), wxDragResult def)
{   return (def == wxDragMove ? wxDragCopy : def);}

/**
 * Surcharge - Traitement d'un évènement de Drag&Drop
 * @param y l'ordonnée du relâché
 * @return
 */
wxDragResult DnDCible::OnData(wxCoord WXUNUSED(x), wxCoord y, wxDragResult WXUNUSED(def))
{
    if (!GetData())
        return wxDragNone;

    DnDListeFichier* TransFile;
    TransFile = ((DnDBufferData *)GetDataObject())->GetTransFile();

    if (m_pageGestion == NULL)
    {
        if (TransFile->Item(0).IsNumber())
            Musique::Get()->PlacerLigneInt(TransFile->arrayString(), GetPositionCoord(y), true);
        else
            Musique::Get()->PlacerLigneString(TransFile->arrayString(), GetPositionCoord(y), true);//Les coordonnées commencent au coin sup gauche de la liste, dans les en-têtes
    }
    else
        m_pageGestion->GlisserTraitement(TransFile->arrayString(), GetPositionCoord(y));//Les coordonnées commencent au coin sup gauche de la liste, dans les en-têtes

    TransFile->Clear();
    return wxDragCopy;
}

/**
 * Calcul la position du premier élément en fonction de ce qui est affiché dans la liste
 * @param y la coordonnée en pixels
 * @return l'indice de début de DnD
 */
long DnDCible::GetPositionCoord(int y)
{
    long pos = 0, i = m_liste->GetItemCount(), min = m_liste->GetTopItem();
    bool continuer = true;
    wxPoint point;
    //position du dernier item visible
    if (i < m_liste->GetCountPerPage() ||i == (m_liste->GetCountPerPage() + min))//Le dernier item est visible
    {
        wxRect rect;
        m_liste->GetItemRect(i-1, rect);//emplacement physique du dernier item
        if (rect.GetY() + rect.GetHeight() < y)//le relâchement de la souris est après le dernier item
            return i;
        pos = m_liste->GetItemCount();
    }
    else
        pos = min + m_liste->GetCountPerPage();

    while ((i > 0 && pos >= min) && continuer)//Recherche la position par rapport au bord supérieur de la case
    {
        pos--;
        m_liste->GetItemPosition(pos, point);
        if (y>point.y)
            continuer = false;
        i--;
    }
    return pos;
}
