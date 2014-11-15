#ifndef DRIVEMANAGERSTATE_H
#define DRIVEMANAGERSTATE_H

#include "wx/wx.h"
#include "../../gui/explorer/ExplorerListCtrl.h"

class DriveManagerState
{
    public:
        virtual bool IsDefault();
        virtual bool IsDirectory();
        virtual bool IsFile();
        virtual bool IsPlaylist();
        virtual void FillExplorerList(ExplorerListCtrl *explorerList, wxString &path) = 0;

    protected:
        /** Default constructor */
        DriveManagerState();
        /** Default destructor */
        virtual ~DriveManagerState();

    private:
};

#endif // DRIVEMANAGERSTATE_H
