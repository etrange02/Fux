#ifndef DRIVEMANAGERSTATE_H
#define DRIVEMANAGERSTATE_H

#include "wx/wx.h"
#include "explorer/ExplorerPanel.h"
#include <vector>


/**
 * Explorer name space.
 */
namespace explorer
{
    class ExplorerManagerData;

    class DriveManagerState
    {
        public:
            /** Default constructor */
            DriveManagerState(ExplorerManagerData& data);
            /** Default destructor */
            virtual ~DriveManagerState();

            virtual bool isDefault() const;
            virtual bool isDirectory() const;
            virtual bool isFile() const;
            virtual bool isPlaylist() const;
            virtual bool fillExplorerList() = 0;
            virtual bool fillExplorerList(const wxString& elementToSelect) = 0;

            virtual DriveManagerState& getPreviousState() = 0;
            virtual void openElement() = 0;

            void addDriveManagerListElement(const wxString& filename);
            bool isSameKind(const DriveManagerState& other) const;

            virtual bool canCopyTo(const DriveManagerState& other) const = 0;
            virtual bool canMoveTo(const DriveManagerState& other) const = 0;
            virtual bool canDeleteSelectedItems() const = 0;
            virtual bool canSelectAll() const = 0;
            virtual bool canCreateDir() const = 0;
            virtual bool canCreateContainerFile() const = 0;
            virtual bool canPlayItems() const = 0;
            virtual bool canRename() const = 0;
            virtual bool canCreateShortcut() const = 0;

            virtual void deleteSelectedItems() = 0;
            virtual void moveElements(DriveManagerState& source) = 0;
            virtual void copyElements(DriveManagerState& source) = 0;
            virtual void selectAll();
            virtual void createDir() = 0;
            virtual void createContainerFile() = 0;
            virtual void playItems() = 0;
            virtual void rename() = 0;
            virtual void createShortcut() = 0;

            wxArrayString getSelectedItems();
            wxArrayString getSelectedItemsPosition();

            const wxString& getPath() const;

        protected:
            ExplorerManagerData& m_data;
            wxArrayString convertPositionToString(const std::vector<unsigned long>& indexes);
    };
}


#endif // DRIVEMANAGERSTATE_H
