#ifndef FILEDRIVEMANAGERSTATE_H
#define FILEDRIVEMANAGERSTATE_H

#include "DriveManagerState.h"

/**
 * Explorer name space.
 */
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
            virtual void insertElements(const wxArrayString& filenames, long position);
            virtual void copyElements(DriveManagerState& source);
            virtual void playItems();
            virtual void rename();
            virtual void createShortcut();
            virtual dragAndDrop::TransitiveData* getDraggedElements();

        protected:
        private:
    };
}

#endif // FILEDRIVEMANAGERSTATE_H
