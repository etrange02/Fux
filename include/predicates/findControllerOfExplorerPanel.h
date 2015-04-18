#ifndef FINDCONTROLLEROFEXPLORERPANEL_H
#define FINDCONTROLLEROFEXPLORERPANEL_H

namespace gui {
    namespace explorer {
        class ExplorerPanel;
    }
}
namespace explorer {
    class ExplorerManager;
}

class findControllerOfExplorerPanel
{
    public:
        /** Default constructor */
        findControllerOfExplorerPanel(const gui::explorer::ExplorerPanel& explorerPanel);
        /** Default destructor */
        virtual ~findControllerOfExplorerPanel();

        bool operator()(::explorer::ExplorerManager* manager);

    private:
        const gui::explorer::ExplorerPanel& m_explorerPanel;
};

#endif // FINDCONTROLLEROFEXPLORERPANEL_H
