/***************************************************************
 * Name:      DriveManagersPanel.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2014-11-19
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include <algorithm>
#include "DriveManagersPanel.h"
#include "Define.h"
#include "Tools.h"
#include "ExplorerDriveManagers.h"
#include "ExplorerPanel.h"
#include "predicates/findPathMenuElement.h"
#include "predicates/findMenuElementById.h"
#include "Parametre.h"

using namespace gui::explorer;

BEGIN_EVENT_TABLE(DriveManagersPanel, wxPanel)
    EVT_BUTTON                    (ID_PAGE_PERIHERIQUE_BOUTON_MESDOC,        DriveManagersPanel::onButtonMyDocuments)
    EVT_BUTTON                    (ID_PAGE_PERIHERIQUE_BOUTON_PERIPH,        DriveManagersPanel::onButtonDrivers)
    EVT_BUTTON                    (ID_PAGE_PERIHERIQUE_BOUTON_AUTRE,         DriveManagersPanel::onButtonOthers)
    EVT_BUTTON                    (ID_PAGE_PERIHERIQUE_BOUTON_SUPPRIMER,     DriveManagersPanel::onButtonDelete)
    EVT_BUTTON                    (ID_PAGE_PERIHERIQUE_BOUTON_COPIE,         DriveManagersPanel::onButtonCopy)
    EVT_BUTTON                    (ID_PAGE_PERIHERIQUE_BOUTON_DEPLACE_POURG, DriveManagersPanel::onButtonMoveLeft)
    EVT_BUTTON                    (ID_PAGE_PERIHERIQUE_BOUTON_DEPLACE_POURD, DriveManagersPanel::onButtonMoveRight)
    EVT_MENU                      (ID_PAGE_PERIHERIQUE_MENU_MESDOC_GAUCHE,   DriveManagersPanel::onMenuItemMyDocumentsLeftSelected)
    EVT_MENU                      (ID_PAGE_PERIHERIQUE_MENU_MESDOC_DROITE,   DriveManagersPanel::onMenuItemMyDocumentsRightSelected)
    EVT_MENU                      (ID_PAGE_PERIHERIQUE_MENU_PLAYLIST_GAUCHE, DriveManagersPanel::onMenuItemPlayListLeftSelected)
    EVT_MENU                      (ID_PAGE_PERIHERIQUE_MENU_PLAYLIST_DROITE, DriveManagersPanel::onMenuItemPlayListRightSelected)
    EVT_FUX_EXPLORERLISTCTRL_FOCUS(DriveManagersPanel::onFocusChanged)
END_EVENT_TABLE()

DriveManagersPanel::DriveManagersPanel(wxWindow *parent, ExplorerDriveManagers& explorerDriveManagers) :
    m_explorerDriveManagers(explorerDriveManagers),
    m_leftExplorerPanels(NULL),
    m_rightExplorerPanels(NULL),
    m_focusedExplorerPanel(NULL)
{
    Initialize(parent);
}

DriveManagersPanel::~DriveManagersPanel()
{
    delete[] m_streamButton;
}

void DriveManagersPanel::Initialize(wxWindow *Parent)
{
    Create(Parent);
    wxSizer* sizer1V = new wxBoxSizer(wxVERTICAL);
    SetSizer(sizer1V);

    // Button bar
    wxSizer* flexGridSizerButton = new wxFlexGridSizer(1, 3, 10, 10);
    sizer1V->Add(flexGridSizerButton, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

    wxButton* myDocButton    = new wxButton(this, ID_PAGE_PERIHERIQUE_BOUTON_MESDOC, _("Mes Documents"));
    wxButton* computerButton = new wxButton(this, ID_PAGE_PERIHERIQUE_BOUTON_PERIPH, _("Ordinateur"));
    wxButton* otherButton    = new wxButton(this, ID_PAGE_PERIHERIQUE_BOUTON_AUTRE,  _("Autre"));
    flexGridSizerButton->Add(myDocButton,    0, wxALL | wxEXPAND, 0);
    flexGridSizerButton->Add(computerButton, 0, wxALL | wxEXPAND, 0);
    flexGridSizerButton->Add(otherButton,    0, wxALL | wxEXPAND, 0);

    myDocButton->SetToolTip(_("Accédez au dossier Mes Documents"));
    computerButton->SetToolTip(_("Accédez aux différents lecteurs de votre ordinateur"));
    otherButton->SetToolTip(_("Accédez aux enregistrements et à la liste de lecture de Fu(X)"));

    // Navigation
    m_leftExplorerPanels  = createNewExplorerPanel(tool::getResource(ID_EXPLORER_PANEL_1_NAME), tool::getResource(ID_EXPLORER_PANEL_1_DESCRIPTION));
    m_rightExplorerPanels = createNewExplorerPanel(tool::getResource(ID_EXPLORER_PANEL_2_NAME), tool::getResource(ID_EXPLORER_PANEL_2_DESCRIPTION));

    m_explorerDriveManagers.setDriveManagersPanel(this);
    m_explorerDriveManagers.addExplorerManager(*m_leftExplorerPanels);
    m_explorerDriveManagers.addExplorerManager(*m_rightExplorerPanels);

    wxSizer* sizer2G = new wxBoxSizer(wxHORIZONTAL);
    sizer1V->Add(sizer2G, 1, wxALL | wxEXPAND, 5);

    wxSizer* modificationButtonSizer = new wxGridSizer(4, 1, 0, 0);
    sizer2G->Add(m_leftExplorerPanels, 1, wxALL | wxEXPAND, 0);
    sizer2G->Add(modificationButtonSizer, 0, wxALIGN_CENTER_VERTICAL, 0);
    sizer2G->Add(m_rightExplorerPanels, 1, wxALL | wxEXPAND, 0);

    m_streamButton = new wxButton[4];
    m_streamButton[STREAM_MOVE_LEFT ].Create(this, ID_PAGE_PERIHERIQUE_BOUTON_DEPLACE_POURG, _T("<"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    m_streamButton[STREAM_COPY      ].Create(this, ID_PAGE_PERIHERIQUE_BOUTON_COPIE,         _T("="), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    m_streamButton[STREAM_MOVE_RIGHT].Create(this, ID_PAGE_PERIHERIQUE_BOUTON_DEPLACE_POURD, _T(">"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    m_streamButton[STREAM_DELETE    ].Create(this, ID_PAGE_PERIHERIQUE_BOUTON_SUPPRIMER,     _T("X"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    modificationButtonSizer->Add(&m_streamButton[STREAM_MOVE_LEFT ], 0, wxALL, 0);
    modificationButtonSizer->Add(&m_streamButton[STREAM_COPY      ], 0, wxALL, 0);
    modificationButtonSizer->Add(&m_streamButton[STREAM_MOVE_RIGHT], 0, wxALL, 0);
    modificationButtonSizer->Add(&m_streamButton[STREAM_DELETE    ], 0, wxALL, 0);
    enableButtonDelete   (false);
    enableButtonCopy     (false);
    enableButtonMoveLeft (false);
    enableButtonMoveRight(false);

    m_streamButton[STREAM_MOVE_LEFT ].SetToolTip(_("Déplacer l'élément sélectionné de la fenêtre droite vers la fenêtre gauche"));
    m_streamButton[STREAM_COPY      ].SetToolTip(_("Copier l'élément sélectionné dans l'autre fenêtre de navigation"));
    m_streamButton[STREAM_MOVE_RIGHT].SetToolTip(_("Déplacer l'élément sélectionné de la fenêtre gauche vers la fenêtre droite"));
    m_streamButton[STREAM_DELETE    ].SetToolTip(_("Supprimer l'élément sélectionné"));

    m_focusedExplorerPanel = m_leftExplorerPanels;
    /*
    ComparaisonStatut();
    */
    createMenus();
}

ExplorerPanel* DriveManagersPanel::createNewExplorerPanel(const wxString& managerName, const wxString& managerDescription)
{
    ExplorerPanel *explorerPanel = new ExplorerPanel(this, managerName, managerDescription);
    return explorerPanel;
}

void DriveManagersPanel::createMenus()
{
    m_myDocumentsMenu = new wxMenu;
    m_myDocumentsMenu->Append(ID_PAGE_PERIHERIQUE_MENU_MESDOC_GAUCHE, _("Gauche"));
    m_myDocumentsMenu->Append(ID_PAGE_PERIHERIQUE_MENU_MESDOC_DROITE, _("Droite"));

    m_driversMenu = new wxMenu;

    m_otherMenu = new wxMenu;
    m_containerFilesMenu = new wxMenu;
    m_otherMenu->AppendSubMenu(m_containerFilesMenu, _("Fichiers m3u"));

    wxMenu *playlistMenu = new wxMenu;
    playlistMenu->Append(ID_PAGE_PERIHERIQUE_MENU_PLAYLIST_GAUCHE, _("Gauche"));
    playlistMenu->Append(ID_PAGE_PERIHERIQUE_MENU_PLAYLIST_DROITE, _("Droite"));
    m_otherMenu->AppendSubMenu(playlistMenu, _("Liste de lecture"));
}

void DriveManagersPanel::onButtonMyDocuments(wxCommandEvent& event)
{
    PopupMenu(m_myDocumentsMenu);
}

void DriveManagersPanel::onButtonDrivers(wxCommandEvent& event)
{
    fillDriversMenu();
    PopupMenu(m_driversMenu);
}

void DriveManagersPanel::onButtonOthers(wxCommandEvent& event)
{
    fillContainerFilesMenu();
    PopupMenu(m_otherMenu);
}

void DriveManagersPanel::fillDriversMenu()
{
    emptyMenu(*m_driversMenu, m_driversMenuElement);
    mergeAndMarkPresentMenuElements(m_driversMenuElement, m_explorerDriveManagers.getDrivers(), &DriveManagersPanel::onMenuItemDriversLeftSelected, &DriveManagersPanel::onMenuItemDriversRightSelected);
    fillMenu(*m_driversMenu, m_driversMenuElement);
}

void DriveManagersPanel::fillContainerFilesMenu()
{
    emptyMenu(*m_containerFilesMenu, m_containerFilesMenuElement);
    mergeAndMarkPresentMenuElements(m_containerFilesMenuElement, m_explorerDriveManagers.getContainersFiles(), &DriveManagersPanel::onMenuItemContainerFilesLeftSelected, &DriveManagersPanel::onMenuItemContainerFilesRightSelected);
    fillMenu(*m_containerFilesMenu, m_containerFilesMenuElement);
}

void DriveManagersPanel::mergeAndMarkPresentMenuElements(std::vector<MenuElement>& menuElements, std::vector<MenuElementData> menuElementData, void (DriveManagersPanel::*funcMappingLeft)(wxCommandEvent&), void (DriveManagersPanel::*funcMappingRight)(wxCommandEvent&))
{
    for (std::vector<MenuElementData>::iterator it = menuElementData.begin(); it != menuElementData.end(); ++it)
    {
        findPathMenuElement finder(it->getPath());
        std::vector<MenuElement>::iterator menuElementIterator = std::find_if(menuElements.begin(), menuElements.end(), finder);

        if (menuElements.end() == menuElementIterator)
        {
            MenuElement element(*it);
            element.setLeftID (wxNewId());
            element.setRightID(wxNewId());

            Bind(wxEVT_COMMAND_MENU_SELECTED, funcMappingLeft,  this, element.getLeftID());
            Bind(wxEVT_COMMAND_MENU_SELECTED, funcMappingRight, this, element.getRightID());

            element.setUsed();
            element.generateMenu();
            menuElements.push_back(element);
        }
        else
            menuElementIterator->setUsed();
    }
}

void DriveManagersPanel::emptyMenu(wxMenu& menu, std::vector<MenuElement>& menuElements)
{
    for (std::vector<MenuElement>::iterator it = menuElements.begin(); it != menuElements.end(); ++it)
    {
        if ((*it).isUsed())
        {
            menu.Delete((*it).getMenuItem());
            (*it).setUnused();
            (*it).setMenuItem(NULL);
        }
    }
}

void DriveManagersPanel::fillMenu(wxMenu& menu, std::vector<MenuElement>& menuElements)
{
    for (std::vector<MenuElement>::iterator it = menuElements.begin(); it != menuElements.end(); ++it)
    {
        if ((*it).isUsed())
            (*it).setMenuItem(menu.AppendSubMenu((*it).getMenu(), (*it).getLabel()));
    }
}

void DriveManagersPanel::onMenuItemMyDocumentsLeftSelected(wxCommandEvent& event)
{
    m_explorerDriveManagers.setDirState(*m_leftExplorerPanels, Parametre::get().getRepertoireDefaut());
}

void DriveManagersPanel::onMenuItemMyDocumentsRightSelected(wxCommandEvent& event)
{
    m_explorerDriveManagers.setDirState(*m_rightExplorerPanels, Parametre::get().getRepertoireDefaut());
}

void DriveManagersPanel::onMenuItemPlayListLeftSelected(wxCommandEvent& event)
{
    m_explorerDriveManagers.setPlayListState(*m_leftExplorerPanels);
}

void DriveManagersPanel::onMenuItemPlayListRightSelected(wxCommandEvent& event)
{
    m_explorerDriveManagers.setPlayListState(*m_rightExplorerPanels);
}

void DriveManagersPanel::onMenuItemDriversLeftSelected(wxCommandEvent& event)
{
    MenuElement& menuElement = getMenuElementById(m_driversMenuElement, event.GetId());
    m_explorerDriveManagers.setDirState(*m_leftExplorerPanels, menuElement.getPath());
}

void DriveManagersPanel::onMenuItemDriversRightSelected(wxCommandEvent& event)
{
    MenuElement& menuElement = getMenuElementById(m_driversMenuElement, event.GetId());
    m_explorerDriveManagers.setDirState(*m_rightExplorerPanels, menuElement.getPath());
}

void DriveManagersPanel::onMenuItemContainerFilesLeftSelected(wxCommandEvent& event)
{
    MenuElement& menuElement = getMenuElementById(m_containerFilesMenuElement, event.GetId());
    m_explorerDriveManagers.setFileState(*m_leftExplorerPanels, menuElement.getPath());
}

void DriveManagersPanel::onMenuItemContainerFilesRightSelected(wxCommandEvent& event)
{
    MenuElement& menuElement = getMenuElementById(m_containerFilesMenuElement, event.GetId());
    m_explorerDriveManagers.setFileState(*m_rightExplorerPanels, menuElement.getPath());
}

MenuElement& DriveManagersPanel::getMenuElementById(std::vector<MenuElement>& menuElements, const int id)
{
    findMenuElementById finder(id);
    std::vector<MenuElement>::iterator it = std::find_if(menuElements.begin(), menuElements.end(), finder);
    if (it != menuElements.end())
        return *it;
    else
        throw wxString("No menu element found.");
}

void DriveManagersPanel::onButtonDelete(wxCommandEvent& event)
{
    m_explorerDriveManagers.deleteSelectedLines(*m_focusedExplorerPanel);
}

void DriveManagersPanel::onButtonCopy(wxCommandEvent& event)
{
    ExplorerPanel* otherPanel = (m_focusedExplorerPanel == m_leftExplorerPanels) ? m_rightExplorerPanels : m_leftExplorerPanels;
    m_explorerDriveManagers.copySelectedLines(*m_focusedExplorerPanel , *otherPanel);
}

void DriveManagersPanel::onButtonMoveLeft(wxCommandEvent& event)
{
    m_explorerDriveManagers.moveSelectedLines(*m_rightExplorerPanels, *m_leftExplorerPanels);
}

void DriveManagersPanel::onButtonMoveRight(wxCommandEvent& event)
{
    m_explorerDriveManagers.moveSelectedLines(*m_leftExplorerPanels , *m_rightExplorerPanels);
}

void DriveManagersPanel::enableButtonDelete(const bool enable)
{
    m_streamButton[STREAM_DELETE    ].Enable(enable);
}

void DriveManagersPanel::enableButtonCopy(const bool enable)
{
    m_streamButton[STREAM_COPY      ].Enable(enable);
}

void DriveManagersPanel::enableButtonMoveLeft(const bool enable)
{
    m_streamButton[STREAM_MOVE_LEFT ].Enable(enable);
}

void DriveManagersPanel::enableButtonMoveRight(const bool enable)
{
    m_streamButton[STREAM_MOVE_RIGHT].Enable(enable);
}

void DriveManagersPanel::onFocusChanged(wxCommandEvent& event)
{
    m_focusedExplorerPanel = (ExplorerPanel*) event.GetClientData();
    m_explorerDriveManagers.updateStreamButtonStates(*m_focusedExplorerPanel);
}

