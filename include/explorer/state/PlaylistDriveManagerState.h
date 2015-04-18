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

#endif // PLAYLISTDRIVEMANAGERSTATE_H
