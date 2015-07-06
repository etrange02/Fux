#ifndef DNDCIBLE_H
#define DNDCIBLE_H

#include <wx/wx.h>
#include <wx/dnd.h>
#include <wx/listctrl.h>
#include <wx/dataobj.h>
//#include "music/Musique.h"
#include "music/MusicManager.h"
#include "GUI/explorer/GestionPeriphMoitiePage.h"
#include "MusicPlayListDnDBufferData.h"

class PageGestionPeriph;

class DnDCible : public wxDropTarget
{
    public:
        DnDCible(wxListCtrl*);
        DnDCible(wxListCtrl*, wxWindow*);
        virtual wxDragResult OnDragOver(wxCoord, wxCoord, wxDragResult);
        virtual wxDragResult OnData(wxCoord, wxCoord, wxDragResult);
        long GetPositionCoord(int);

    private:
        wxListCtrl* m_liste;
        PageGestionPeriph* m_pageGestion;
};

#endif // DNDCIBLE_H
