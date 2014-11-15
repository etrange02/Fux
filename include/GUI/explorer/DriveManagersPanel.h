#ifndef DRIVEMANAGERSPANEL_H
#define DRIVEMANAGERSPANEL_H

#include <list>

#include "../../Define.h"
#include <wx/wx.h>
#include "../explorer/ExplorerPanel.h"

class DriveManagersPanel : public wxPanel
{
    public:
        /** Default constructor */
        DriveManagersPanel();
        /** Default destructor */
        virtual ~DriveManagersPanel();
        ExplorerPanel* createNewExplorerPanel();

    protected:
    private:
        void Initialize();

        std::list<ExplorerPanel*> *m_explorerPanels;
};

#endif // DRIVERMANAGERSPANEL_H
