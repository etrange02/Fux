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
            /** Constructor */
            DefaultDriveManagerState(ExplorerManagerData& data, const bool initDragAndDrop);
            /** Default destructor */
            virtual ~DefaultDriveManagerState();

            virtual bool isDefault() const;
            virtual bool fillExplorerList();
            virtual bool fillExplorerList(const wxString& elementToSelect);

            virtual DriveManagerState& getPreviousState();
            virtual void openElement();

            virtual bool canCopyTo(const DriveManagerState& other) const;
            virtual bool canMoveTo(const DriveManagerState& other) const;
            virtual bool canDeleteSelectedItems() const;
            virtual bool canPlayItems() const;
            virtual bool canRename() const;
            virtual bool canCreateShortcut() const;
            virtual bool canSelectAll() const;
            virtual bool canCreateDir() const;
            virtual bool canCreateContainerFile() const;

            virtual void deleteSelectedItems();
            virtual void moveElements(DriveManagerState& source);
            virtual void copyElements(DriveManagerState& source);
            virtual void createDir(ExplorerManager& explorerManager);
            virtual void createContainerFile(ExplorerManager& explorerManager);
            virtual void playItems();
            virtual void rename();
            virtual void createShortcut();
            virtual dragAndDrop::TransitiveData* getDraggedElements();

        protected:
        private:
    };
}

#endif // DEFAULTDRIVEMANAGERSTATE_H
