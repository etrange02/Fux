#ifndef EXPLORERMANAGER_H
#define EXPLORERMANAGER_H

#include "Define.h"
#include "ExplorerManagerData.h"
#include "ExplorerPanel.h"

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
    class ExplorerManager
    {
        public:
            ExplorerManager(gui::explorer::ExplorerPanel& explorerPanel, ExplorerDriveManagers& explorerDriveManagers);
            /** Default destructor */
            virtual ~ExplorerManager();

            void setDirState     (const wxString& path);
            void setPlayListState();
            void setFileState    (const wxString& path);
            void setDefaultState ();

            void refresh();
            void makeParentDir();
            void openElement();

            gui::explorer::ExplorerPanel& getExplorerPanel() const;

            DriveManagerState& getState() const;

        protected:

        private:
            ExplorerManagerData m_data;
    };
}

#endif // EXPLORERMANAGER_H
