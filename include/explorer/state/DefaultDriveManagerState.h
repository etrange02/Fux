#ifndef DEFAULTDRIVEMANAGERSTATE_H
#define DEFAULTDRIVEMANAGERSTATE_H

#include "DriveManagerState.h"

namespace explorer
{
    class DefaultDriveManagerState : public DriveManagerState
    {
        public:
            /** Default constructor */
            DefaultDriveManagerState(ExplorerManagerData& data);
            /** Default destructor */
            virtual ~DefaultDriveManagerState();

            virtual bool isDefault();
            virtual bool fillExplorerList();
            virtual bool fillExplorerList(const wxString& elementToSelect);

            virtual DriveManagerState& getPreviousState();
            virtual void openElement(const std::vector<long>& indexes);

        protected:
        private:
    };
}

#endif // DEFAULTDRIVEMANAGERSTATE_H
