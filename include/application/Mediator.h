#ifndef MEDIATOR_H
#define MEDIATOR_H

#include "tools/dir/DirFileManager.h"
#include "tools/dir/DirFileDialogEvent.h"
#include "tools/dir/DirFileDialog.h"
#include "explorer/ExplorerDriveManagers.h"

class Mediator
{
    public:
        /** Default constructor */
        Mediator();
        /** Default destructor */
        virtual ~Mediator();

        tools::dir::DirFileManager& getDirFileManager();
        tools::dir::DirFileDialogEvent& getDirFileDialogEvent();
        tools::dir::DirFileDialog& getDirFileDialog();
        explorer::ExplorerDriveManagers& getExplorerDriveManagers();

    protected:
    private:
        tools::dir::DirFileDialog m_dirFileDialog;
        tools::dir::DirFileDialogEvent m_dirFileDialogEvent;
        tools::dir::DirFileManager m_dirFileManager;
        explorer::ExplorerDriveManagers m_explorerDriveManagers;
};

#endif // MEDIATOR_H
