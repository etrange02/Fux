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

            virtual bool isFile() const;
            virtual bool fillExplorerList();
            virtual bool fillExplorerList(const wxString& elementToSelect);

            virtual DriveManagerState& getPreviousState();
            virtual void openElement(const std::vector<unsigned long>& indexes);

            virtual bool canCopyTo(const DriveManagerState& other) const;
            virtual bool canMoveTo(const DriveManagerState& other) const;
            virtual void deleteSelectedItems();
            virtual void moveElements(DriveManagerState& source);
            virtual void copyElements(DriveManagerState& source);

        protected:
        private:
    };
}

#endif // FILEDRIVEMANAGERSTATE_H
