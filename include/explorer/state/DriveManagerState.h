#ifndef DRIVEMANAGERSTATE_H
#define DRIVEMANAGERSTATE_H

#include "wx/wx.h"
#include "explorer/ExplorerPanel.h"
#include <vector>

class ExplorerManagerData;

namespace explorer
{
    class DriveManagerState
    {
        public:
            /** Default constructor */
            DriveManagerState(ExplorerManagerData& data);
            /** Default destructor */
            virtual ~DriveManagerState();

            virtual bool isDefault();
            virtual bool isDirectory();
            virtual bool isFile();
            virtual bool isPlaylist();
            virtual bool fillExplorerList() = 0;
            virtual bool fillExplorerList(const wxString& elementToSelect) = 0;

            virtual DriveManagerState& getPreviousState() = 0;
            virtual void openElement(const std::vector<long>& indexes) = 0;

            void addDriveManagerListElement(const wxString& filename);

        protected:
            ExplorerManagerData& m_data;
            wxArrayString convertPositionToString(const std::vector<long>& indexes);

        private:
    };
}


#endif // DRIVEMANAGERSTATE_H
