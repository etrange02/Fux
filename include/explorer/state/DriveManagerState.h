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
            virtual void openElement(const std::vector<unsigned long>& indexes) = 0;

            void addDriveManagerListElement(const wxString& filename);
            bool isSameKind(const DriveManagerState& other) const;

            virtual bool canCopyTo(const DriveManagerState& other) const = 0;
            virtual bool canMoveTo(const DriveManagerState& other) const = 0;
            virtual void deleteSelectedItems() = 0;
            virtual void moveElements(DriveManagerState& source) = 0;
            virtual void copyElements(DriveManagerState& source) = 0;
            wxArrayString getSelectedItems();
            wxArrayString getSelectedItemsPosition();

            const wxString& getPath() const;

        protected:
            ExplorerManagerData& m_data;
            wxArrayString convertPositionToString(const std::vector<unsigned long>& indexes);
    };
}


#endif // DRIVEMANAGERSTATE_H
