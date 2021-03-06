#ifndef DIRDRIVEMANAGERSTATE_H
#define DIRDRIVEMANAGERSTATE_H

#include "DriveManagerState.h"

namespace dragAndDrop {
    class DirTransitiveDataTarget;
}

/**
 * Explorer name space.
 */
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
            virtual void playItems();
            virtual void rename();
            virtual void createShortcut();
            virtual dragAndDrop::TransitiveData* getDraggedElements();

        protected:

        private:
            dragAndDrop::DirTransitiveDataTarget* m_transitiveDataTarget;
    };
}

#endif // DIRDRIVEMANAGERSTATE_H
