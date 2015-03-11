#ifndef FINDCONTROLLEROFEXPLORERPANEL_H
#define FINDCONTROLLEROFEXPLORERPANEL_H

namespace gui
{
    namespace explorer
    {
        class ExplorerPanel;
    }
}
class ExplorerManager;

class findControllerOfExplorerPanel
{
    public:
        /** Default constructor */
        findControllerOfExplorerPanel(const gui::explorer::ExplorerPanel& explorerPanel);
        /** Default destructor */
        virtual ~findControllerOfExplorerPanel();

        bool operator()(ExplorerManager* manager);

    private:
        const gui::explorer::ExplorerPanel& m_explorerPanel;
};

#endif // FINDCONTROLLEROFEXPLORERPANEL_H
