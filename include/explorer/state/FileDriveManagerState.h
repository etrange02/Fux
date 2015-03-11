#ifndef FILEDRIVEMANAGERSTATE_H
#define FILEDRIVEMANAGERSTATE_H

#include "DriveManagerState.h"

namespace explorer
{
    class FileDriveManagerState : public DriveManagerState
    {
        public:
            /** Default constructor */
            FileDriveManagerState(ExplorerManagerData& data);
            /** Default destructor */
            virtual ~FileDriveManagerState();

            virtual bool isFile();
            virtual bool fillExplorerList();
            virtual bool fillExplorerList(const wxString& elementToSelect);

            virtual DriveManagerState& getPreviousState();
            virtual void openElement(const std::vector<long>& indexes);

        protected:
        private:
    };
}

#endif // FILEDRIVEMANAGERSTATE_H
