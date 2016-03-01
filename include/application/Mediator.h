#ifndef MEDIATOR_H
#define MEDIATOR_H

#include "tools/dir/DirFileManager.h"
#include "tools/dir/interface/DirFileDialog.h"
#include "explorer/ExplorerDriveManagers.h"

class Mediator
{
    public:
        /** Default constructor */
        Mediator();
        /** Default destructor */
        virtual ~Mediator();

        void setDirFileManager(tools::dir::DirFileManager* manager);

        tools::dir::DirFileManager& getDirFileManager();
        tools::dir::DirFileDialog& getDirFileDialog();
        explorer::ExplorerDriveManagers& getExplorerDriveManagers();

    protected:
    private:
        tools::dir::DirFileManager* m_dirFileManager;
        tools::dir::DirFileDialog m_dirFileDialog;
        explorer::ExplorerDriveManagers m_explorerDriveManagers;
};

#endif // MEDIATOR_H
