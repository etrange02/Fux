#ifndef PLAYLISTDRIVEMANAGERSTATE_H
#define PLAYLISTDRIVEMANAGERSTATE_H

#include "DriveManagerState.h"

/**
 * Explorer name space.
 */
namespace explorer
{
    class PlaylistDriveManagerState : public DriveManagerState
    {
        public:
            /** Default constructor */
            PlaylistDriveManagerState(ExplorerManagerData& data);
            /** Default destructor */
            virtual ~PlaylistDriveManagerState();

            virtual bool isPlaylist() const;
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
            virtual void playItems();
            virtual void rename();
            virtual void createShortcut();
            virtual dragAndDrop::TransitiveData* getDraggedElements();

        protected:
        private:
    };
}

#endif // PLAYLISTDRIVEMANAGERSTATE_H
