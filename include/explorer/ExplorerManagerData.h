#ifndef EXPLORERMANAGERDATA_H
#define EXPLORERMANAGERDATA_H

#include <wx/wx.h>
#include "../Define.h"
#include "../gui/explorer/ExplorerPanel.h"

class ExplorerManagerData
{
    public:
        /** Default constructor */
        ExplorerManagerData();
        /** Default destructor */
        virtual ~ExplorerManagerData();

        wxMenu *GetMenu();
        void SetMenu(wxMenu *menu);

        void SetExplorerPanel(ExplorerPanel *explorerPanel);
        ExplorerPanel* GetExplorerPanel();

    protected:
    private:
        void Initialize();
        wxMenu *m_menu;
        ExplorerPanel *m_explorerPanel;
};

#endif // EXPLORERMANAGERDATA_H
