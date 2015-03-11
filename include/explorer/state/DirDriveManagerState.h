#ifndef DIRDRIVEMANAGERSTATE_H
#define DIRDRIVEMANAGERSTATE_H

#include "DriveManagerState.h"

namespace explorer
{
    class DirDriveManagerState : public DriveManagerState
    {
        public:
            /** Default constructor */
            DirDriveManagerState(ExplorerManagerData& data);
            /** Default destructor */
            virtual ~DirDriveManagerState();

            virtual bool isDirectory();
            virtual bool fillExplorerList();
            virtual bool fillExplorerList(const wxString& elementToSelect);

            virtual DriveManagerState& getPreviousState();
            virtual void openElement(const std::vector<long>& indexes);

        protected:

        private:
    };
}

#endif // DIRDRIVEMANAGERSTATE_H
