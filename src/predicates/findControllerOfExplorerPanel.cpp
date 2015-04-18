/***************************************************************
 * Name:      findControllerOfExplorerPanel.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-02-24
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "predicates/findControllerOfExplorerPanel.h"
#include "ExplorerPanel.h"
#include "ExplorerManager.h"

findControllerOfExplorerPanel::findControllerOfExplorerPanel(const gui::explorer::ExplorerPanel& explorerPanel) :
    m_explorerPanel(explorerPanel)
{
    //ctor
}

findControllerOfExplorerPanel::~findControllerOfExplorerPanel()
{
    //dtor
}

bool findControllerOfExplorerPanel::operator()(explorer::ExplorerManager* manager)
{
    if (NULL == manager)
        return false;
    return &manager->getExplorerPanel() == &m_explorerPanel;
}
