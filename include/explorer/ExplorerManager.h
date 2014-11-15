#ifndef EXPLORERMANAGER_H
#define EXPLORERMANAGER_H

#include "../Define.h"
#include "ExplorerManagerData.h"
#include "../gui/explorer/ExplorerPanel.h"

class ExplorerManager
{
    public:
        ExplorerManager();
        /** Default destructor */
        virtual ~ExplorerManager();

        void SetExplorerPanel(ExplorerPanel *explorerPanel);

    protected:

    private:
        void Initialize();

        ExplorerManagerData *m_data;
};

#endif // EXPLORERMANAGER_H
