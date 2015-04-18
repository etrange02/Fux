#ifndef EXPLORERMANAGERDATA_H
#define EXPLORERMANAGERDATA_H

#include <wx/wx.h>
#include <vector>
#include "explorer/DriveManagerListElement.h"
#include "Define.h"
#include "gui/explorer/ExplorerPanel.h"

namespace explorer
{
    class DriveManagerState;
    class ExplorerDriveManagers;
}


/**
 * Explorer name space.
 */
namespace explorer
{
    class ExplorerManagerData
    {
        public:
            /** Default constructor */
            ExplorerManagerData(DriveManagerState& state, gui::explorer::ExplorerPanel& explorer, ExplorerDriveManagers& explorerDriveManagers);
            /** Default destructor */
            virtual ~ExplorerManagerData();

            gui::explorer::ExplorerPanel& getExplorerPanel() const;

            wxMenu *GetMenu() const;
            void SetMenu(wxMenu *menu);

            void setState(DriveManagerState& state);
            DriveManagerState& getState() const;

            void setPath(const wxString& path);
            const wxString& getPath() const;

            std::vector<DriveManagerListElement>& getElements();

            ExplorerDriveManagers& getExplorerDriveManagers() const;

        protected:
        private:
            wxString m_path;
            std::vector<DriveManagerListElement> m_elements;
            gui::explorer::ExplorerPanel& m_explorerPanel;
            ExplorerDriveManagers& m_explorerDriveManagers;
            wxMenu *m_menu;
            DriveManagerState* m_state;
    };
}

#endif // EXPLORERMANAGERDATA_H
