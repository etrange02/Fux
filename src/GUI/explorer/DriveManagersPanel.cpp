#include "../../../include/gui/explorer/DriveManagersPanel.h"

DriveManagersPanel::DriveManagersPanel()
{
    //ctor
}

DriveManagersPanel::~DriveManagersPanel()
{
    for (std::list<ExplorerPanel*>::iterator iter = m_explorerPanels->begin(); iter != m_explorerPanels->end(); ++iter)
        delete *iter;
    delete m_explorerPanels;
}

void DriveManagersPanel::Initialize()
{
    m_explorerPanels = new std::list<ExplorerPanel*>();
}

ExplorerPanel* DriveManagersPanel::createNewExplorerPanel()
{
    //static int offset = 0;
    /*ExplorerPanel *explorerPanel =
            new ExplorerPanel(this,
                              ID_EXPLORER_PANEL_1 + offset,
                              ID_EXPLORER_PANEL_LIST_1 + offset,
                              ID_EXPLORER_PANEL_BUTTON_PREVIOUS_1 + offset,
                              ID_EXPLORER_PANEL_BUTTON_REFRESH_1 + offset,
                              ID_EXPLORER_PANEL_TEXT_FIELD_1 + offset,
                              ID_EXPLORER_PANEL_CHECKBOX_HIDDEN_FILE_1 + offset,
                              (0 == offset) ? EXPLORER_PANEL_1_NAME : EXPLORER_PANEL_2_NAME,
                              (0 == offset) ? EXPLORER_PANEL_1_DESCRIPTION : EXPLORER_PANEL_2_DESCRIPTION);
    m_explorerPanels->push_back(explorerPanel);
    ++offset;
    return explorerPanel;*/
    return NULL;
}



