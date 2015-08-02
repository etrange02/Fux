/***************************************************************
 * Name:      ExplorerPanel.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2014-11-19
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "ExplorerPanel.h"
#include "DriveManagersPanel.h"
#include "explorer/ExplorerManager.h"
#include "explorer/state/DriveManagerState.h"
#include <algorithm>
#include "tools/dnd/dataObjects/TransitiveData.h"
#include "tools/dnd/dataObjects/DataObject.h"

const wxEventType wxEVT_FUX_EXPLORERLISTCTRL_FOCUS = wxNewEventType();

using namespace gui::explorer;


ExplorerPanel::ExplorerPanel(DriveManagersPanel& managerPanel, const wxString& managerName, const wxString& managerDescription) :
    wxPanel(&managerPanel, wxNewId()),
    m_managerName(managerName),
    m_managerDescription(managerDescription),
    m_explorerManager(NULL),
    m_driveManagersPanel(managerPanel)
{
    create();
}

ExplorerPanel::~ExplorerPanel()
{
    delete m_listMenu;
}

bool ExplorerPanel::operator==(const ExplorerPanel& other)
{
    return m_explorerList == other.m_explorerList;
}

void ExplorerPanel::create()
{
    m_previousButton        = new wxButton  (this, wxNewId(), _T("<"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    m_pathTextCtrl          = new wxTextCtrl(this, wxNewId(), m_managerDescription, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    m_refreshButton         = new wxButton  (this, wxNewId(), _T("?"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    m_hiddenFilesCheckBox   = new wxCheckBox(this, wxNewId(), _("Fichiers cachés"));
    m_filterCheckBox        = new wxCheckBox(this, wxNewId(), _("Filtrer"));
    m_filterCheckBox->SetValue(true);
    m_explorerList          = new ExplorerListCtrl(this, wxNewId());

    m_previousButton     ->SetToolTip(_("Aller au dossier précédent"));
    m_refreshButton      ->SetToolTip(_("Actualiser"));
    m_hiddenFilesCheckBox->SetToolTip(_("Afficher les fichiers cachés"));
    m_filterCheckBox     ->SetToolTip(_("Afficher uniquement les fichiers que Fu(X) peut lire"));

    m_sizer1V = new wxStaticBoxSizer(wxVERTICAL, this, m_managerName);
    SetSizer(m_sizer1V);
    m_sizer1H = new wxBoxSizer(wxHORIZONTAL);
    m_sizer1V->Add(m_sizer1H,           0, wxALL|wxEXPAND, 5);
    m_sizer1H->Add(m_previousButton,    0, wxALL, 0);
    m_sizer1H->Add(m_pathTextCtrl,      1, wxALL|wxEXPAND, 0);
    m_sizer1H->Add(m_refreshButton,     0, wxALL, 0);

    m_sizer2H = new wxBoxSizer(wxHORIZONTAL);
    m_sizer1V->Add(m_sizer2H,               0, wxLEFT|wxRIGHT|wxEXPAND, 5);
    m_sizer2H->Add(m_hiddenFilesCheckBox,   0, wxALL |wxEXPAND, 0);
    m_sizer2H->Add(m_filterCheckBox,        0, wxLEFT|wxEXPAND, 5);
    m_sizer1V->Add(m_explorerList,          1, wxALL |wxEXPAND, 5);

    createMenu();

//    Connect(-1, wxEVT_LISTE_PERIPH_CLAVIER, wxKeyEventHandler(PageGestionPeriph::OnKey));
//    Connect(-1, wxEVT_LISTE_PERIPH_SOURIS, wxCommandEventHandler(PageGestionPeriph::OnMenu));
    m_previousButton->Bind     (wxEVT_COMMAND_BUTTON_CLICKED,      &ExplorerPanel::onPreviousButton,            this);
    m_refreshButton->Bind      (wxEVT_COMMAND_BUTTON_CLICKED,      &ExplorerPanel::onRefreshButton,             this);
    m_hiddenFilesCheckBox->Bind(wxEVT_COMMAND_CHECKBOX_CLICKED,    &ExplorerPanel::onHiddenFilesCheckBox,       this);
    m_filterCheckBox->Bind     (wxEVT_COMMAND_CHECKBOX_CLICKED,    &ExplorerPanel::onFilterKnownFormatCheckBox, this);
    m_explorerList->Bind       (wxEVT_COMMAND_LIST_ITEM_ACTIVATED, &ExplorerPanel::onItemActivatedInListCtrl,   this);
    m_explorerList->Bind       (wxEVT_COMMAND_LIST_BEGIN_DRAG,     &ExplorerPanel::onDragBeginInListCtrl,       this);
    m_explorerList->Bind       (wxEVT_CHILD_FOCUS,                 &ExplorerPanel::onListFocused,               this);
    m_explorerList->Bind       (wxEVT_RIGHT_DOWN,                  &ExplorerPanel::onRightButtonMouseClicked,   this);

    SetMinSize(wxSize(10, 10)); //< Allows the listctrl to be resized as little as we want
}

void ExplorerPanel::createMenu()
{
    m_createDirMenuItem             = new wxMenuItem(NULL, wxNewId(), _("Créer un dossier"));
    m_createContainerFileMenuItem   = new wxMenuItem(NULL, wxNewId(), _("Créer un m3u"));
    //m_cutMenuItem                   = new wxMenuItem(NULL, wxNewId(), _("Couper\tCtrl-X"));
    m_copyMenuItem                  = new wxMenuItem(NULL, wxNewId(), _("Copier\tCtrl-C"));
    m_pasteMenuItem                 = new wxMenuItem(NULL, wxNewId(), _("Coller\tCtrl-V"));
    m_deleteMenuItem                = new wxMenuItem(NULL, wxNewId(), _("Supprimer\tSuppr"));
    m_renameDirMenuItem             = new wxMenuItem(NULL, wxNewId(), _("Renommer"));
    m_createShortcutDirMenuItem     = new wxMenuItem(NULL, wxNewId(), _("Raccourci"));
    m_selectAllDirMenuItem          = new wxMenuItem(NULL, wxNewId(), _("Tout Sélectionner\tCtrl-A"));
    m_playDirMenuItem               = new wxMenuItem(NULL, wxNewId(), _("Lire"));

    m_listMenu = new wxMenu();
    m_listMenu->Append(m_playDirMenuItem);
    m_listMenu->Append(m_createDirMenuItem);
    m_listMenu->Append(m_createContainerFileMenuItem);
    m_listMenu->AppendSeparator();
    //m_listMenu->Append(m_cutMenuItem);
    m_listMenu->Append(m_copyMenuItem);
    m_listMenu->Append(m_pasteMenuItem);
    m_listMenu->AppendSeparator();
    m_listMenu->Append(m_deleteMenuItem);
    m_listMenu->Append(m_renameDirMenuItem);
    m_listMenu->Append(m_createShortcutDirMenuItem);
    m_listMenu->AppendSeparator();
    m_listMenu->Append(m_selectAllDirMenuItem);

	Bind(wxEVT_MENU, &ExplorerPanel::onMenuCreateDir, 			this, m_createDirMenuItem             ->GetId());
    Bind(wxEVT_MENU, &ExplorerPanel::onMenuCreateContainerFile, this, m_createContainerFileMenuItem   ->GetId());
    Bind(wxEVT_MENU, &ExplorerPanel::onMenuCopy,  				this, m_copyMenuItem                  ->GetId());
    Bind(wxEVT_MENU, &ExplorerPanel::onMenuPaste, 				this, m_pasteMenuItem                 ->GetId());
    Bind(wxEVT_MENU, &ExplorerPanel::onMenuDelete,  			this, m_deleteMenuItem                ->GetId());
    Bind(wxEVT_MENU, &ExplorerPanel::onMenuRenameDir,  			this, m_renameDirMenuItem             ->GetId());
    Bind(wxEVT_MENU, &ExplorerPanel::onMenuCreateShortcut,  	this, m_createShortcutDirMenuItem     ->GetId());
    Bind(wxEVT_MENU, &ExplorerPanel::onMenuSelectAll, 			this, m_selectAllDirMenuItem          ->GetId());
    Bind(wxEVT_MENU, &ExplorerPanel::onMenuPlay,  				this, m_playDirMenuItem               ->GetId());
}

void ExplorerPanel::setExplorerManager(::explorer::ExplorerManager* explorerManager)
{
    m_explorerManager = explorerManager;
}

ExplorerListCtrl& ExplorerPanel::getExplorerListCtrl()
{
    return *m_explorerList;
}

void ExplorerPanel::onFilterKnownFormatCheckBox(wxCommandEvent& WXUNUSED(event))
{
    refreshListCtrl();
}

void ExplorerPanel::onHiddenFilesCheckBox(wxCommandEvent& WXUNUSED(event))
{
    refreshListCtrl();
}

void ExplorerPanel::onPreviousButton(wxCommandEvent& WXUNUSED(event))
{
    m_explorerManager->makeParentDir();
}

void ExplorerPanel::onRefreshButton(wxCommandEvent& WXUNUSED(event))
{
    refreshListCtrl();
}

void ExplorerPanel::onItemActivatedInListCtrl(wxCommandEvent& WXUNUSED(event))
{
    m_explorerManager->openElement();
}

void ExplorerPanel::onDragBeginInListCtrl(wxCommandEvent& WXUNUSED(event))
{
    dragAndDrop::TransitiveData* data = m_explorerManager->getDraggedElements();

    if (data == NULL)
        return;

    if (!data->isEmpty())
    {
        dragAndDrop::DataObject container(data);
        wxDropSource source(this, wxDROP_ICON(dnd_copy), wxDROP_ICON(dnd_move), wxDROP_ICON(dnd_none));
        source.SetData(container);
        source.DoDragDrop(true);
    }

    delete data;
}

bool ExplorerPanel::isHiddenFilesChecked() const
{
    return m_hiddenFilesCheckBox->GetValue();
}

bool ExplorerPanel::isFilterActivated() const
{
    return m_filterCheckBox->GetValue();
}

void ExplorerPanel::setTexts(const wxString& name, const wxString& description)
{
    m_sizer1V->GetStaticBox()->SetLabel(m_managerName + " : " + name);
    m_pathTextCtrl->SetValue(description);
}

void ExplorerPanel::setTexts()
{
    m_sizer1V->GetStaticBox()->SetLabel(m_managerName);
    m_pathTextCtrl->SetValue(m_managerDescription);
}

void ExplorerPanel::onListFocused(wxChildFocusEvent& WXUNUSED(event))
{
    sendExplorerListCtrlFocusEvent();
}

void ExplorerPanel::sendExplorerListCtrlFocusEvent()
{
    if (NULL == GetParent())
        return;

    wxCommandEvent evt(wxEVT_FUX_EXPLORERLISTCTRL_FOCUS);
    evt.SetClientData(this);
    wxQueueEvent(GetParent(), evt.Clone());
}

void ExplorerPanel::onRightButtonMouseClicked(wxMouseEvent& event)
{
    int flag = wxLIST_HITTEST_ONITEM | wxLIST_HITTEST_ONITEMRIGHT | wxLIST_HITTEST_TOLEFT | wxLIST_HITTEST_TORIGHT;
    long pos = m_explorerList->HitTest(event.GetPosition(), flag, NULL);

    std::vector<unsigned long> selectedLines = m_explorerList->getSelectedLines();
    if (std::find(selectedLines.begin(), selectedLines.end(), pos) == selectedLines.end())
    {
        m_explorerList->deselectLines();
        m_explorerList->selectLine(pos);
    }
    enableMenuElements();

    PopupMenu(m_listMenu);
}

void ExplorerPanel::enableMenuElements()
{
    ::explorer::DriveManagerState& state = m_explorerManager->getState();

    m_createDirMenuItem             ->Enable(state.canCreateDir());
    m_createContainerFileMenuItem   ->Enable(state.canCreateContainerFile());
//    m_driveManagersPanel.
//    m_cutMenuItem                 ->Enable(state.);
    m_copyMenuItem                  ->Enable(false);
    m_pasteMenuItem                 ->Enable(false);
    m_deleteMenuItem                ->Enable(state.canDeleteSelectedItems());
    m_renameDirMenuItem             ->Enable(state.canRename());
    m_createShortcutDirMenuItem     ->Enable(state.canCreateShortcut());
    m_selectAllDirMenuItem          ->Enable(state.canSelectAll());
    m_playDirMenuItem               ->Enable(state.canPlayItems());
}

void ExplorerPanel::onMenuCreateDir(wxCommandEvent& WXUNUSED(event))
{
    m_explorerManager->getState().createDir();
}

void ExplorerPanel::onMenuCreateContainerFile(wxCommandEvent& WXUNUSED(event))
{
    m_explorerManager->getState().createContainerFile();
}

void ExplorerPanel::onMenuCut(wxCommandEvent& WXUNUSED(event))
{
    m_explorerManager->getState();
}

void ExplorerPanel::onMenuCopy(wxCommandEvent& WXUNUSED(event))
{
    m_explorerManager->getState();
}

void ExplorerPanel::onMenuPaste(wxCommandEvent& WXUNUSED(event))
{
    m_explorerManager->getState();
}

void ExplorerPanel::onMenuDelete(wxCommandEvent& WXUNUSED(event))
{
    m_explorerManager->getState().deleteSelectedItems();
}

void ExplorerPanel::onMenuRenameDir(wxCommandEvent& WXUNUSED(event))
{
    m_explorerManager->getState().rename();
}

void ExplorerPanel::onMenuCreateShortcut(wxCommandEvent& WXUNUSED(event))
{
    m_explorerManager->getState().createShortcut();
}

void ExplorerPanel::onMenuSelectAll(wxCommandEvent& WXUNUSED(event))
{
    if (hasLinkedExplorerListCtrl())
        m_explorerList->selectAll();
}

void ExplorerPanel::onMenuPlay(wxCommandEvent& WXUNUSED(event))
{
    m_explorerManager->getState().playItems();
}

bool ExplorerPanel::hasLinkedExplorerListCtrl() const
{
    return NULL != m_explorerList;
}

void ExplorerPanel::refreshListCtrl()
{
    m_explorerManager->refresh();
}

