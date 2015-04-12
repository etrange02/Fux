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

            virtual bool isDirectory() const;
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

#endif // DIRDRIVEMANAGERSTATE_H
