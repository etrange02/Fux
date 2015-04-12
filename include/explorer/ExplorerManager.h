#ifndef EXPLORERMANAGER_H
#define EXPLORERMANAGER_H

#include "Define.h"
#include "ExplorerManagerData.h"
#include "ExplorerPanel.h"

class ExplorerDriveManagers;
namespace explorer
{
    class DriveManagerState;
}

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
        void openElement(const std::vector<unsigned long>& indexes);

        gui::explorer::ExplorerPanel& getExplorerPanel() const;

        explorer::DriveManagerState& getState() const;

    protected:

    private:
        ExplorerManagerData m_data;
};

#endif // EXPLORERMANAGER_H
