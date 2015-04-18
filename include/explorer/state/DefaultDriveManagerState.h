#ifndef DEFAULTDRIVEMANAGERSTATE_H
#define DEFAULTDRIVEMANAGERSTATE_H

#include "DriveManagerState.h"

/**
 * Explorer name space.
 */
namespace explorer
{
    class DefaultDriveManagerState : public DriveManagerState
    {
        public:
            /** Default constructor */
            DefaultDriveManagerState(ExplorerManagerData& data);
            /** Default destructor */
            virtual ~DefaultDriveManagerState();

            virtual bool isDefault() const;
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

#endif // DEFAULTDRIVEMANAGERSTATE_H
