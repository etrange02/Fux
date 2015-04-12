/***************************************************************
 * Name:      ExplorerPanel.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2014-11-19
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "ExplorerPanel.h"
#include "explorer/ExplorerManager.h"

const wxEventType wxEVT_FUX_EXPLORERLISTCTRL_FOCUS = wxNewEventType();

using namespace gui::explorer;


ExplorerPanel::ExplorerPanel(wxWindow* parent, const wxString& managerName, const wxString& managerDescription) :
    wxPanel(parent, wxNewId()),
    m_managerName(managerName),
    m_managerDescription(managerDescription),
    m_explorerManager(NULL)
{
    create();
}

ExplorerPanel::~ExplorerPanel()
{
    //dtor
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

    m_previousButton->SetToolTip(_("Aller au dossier précédent"));
    m_refreshButton->SetToolTip(_("Actualiser"));
    m_hiddenFilesCheckBox->SetToolTip(_("Afficher les fichiers cachés"));
    m_filterCheckBox->SetToolTip(_("Afficher uniquement les fichiers que Fu(X) peut lire"));

    m_sizer1V = new wxStaticBoxSizer(wxVERTICAL, this, m_managerName);
    SetSizer(m_sizer1V);
    m_sizer1H = new wxBoxSizer(wxHORIZONTAL);
    m_sizer1V->Add(m_sizer1H, 0, wxALL|wxEXPAND, 5);
    m_sizer1H->Add(m_previousButton, 0, wxALL, 0);
    m_sizer1H->Add(m_pathTextCtrl, 1, wxALL|wxEXPAND, 0);
    m_sizer1H->Add(m_refreshButton, 0, wxALL, 0);

    m_sizer2H = new wxBoxSizer(wxHORIZONTAL);
    m_sizer1V->Add(m_sizer2H, 0, wxLEFT|wxRIGHT|wxEXPAND, 5);
    m_sizer2H->Add(m_hiddenFilesCheckBox, 0, wxALL|wxEXPAND, 0);
    m_sizer2H->Add(m_filterCheckBox, 0, wxLEFT|wxEXPAND, 5);
    m_sizer1V->Add(m_explorerList, 1, wxALL|wxEXPAND, 5);

//    Connect(-1, wxEVT_LISTE_PERIPH_CLAVIER, wxKeyEventHandler(PageGestionPeriph::OnKey));
//    Connect(-1, wxEVT_LISTE_PERIPH_SOURIS, wxCommandEventHandler(PageGestionPeriph::OnMenu));
    m_previousButton->Bind     (wxEVT_COMMAND_BUTTON_CLICKED,      &ExplorerPanel::onPreviousButton,            this);
    m_refreshButton->Bind      (wxEVT_COMMAND_BUTTON_CLICKED,      &ExplorerPanel::onRefreshButton,             this);
    m_hiddenFilesCheckBox->Bind(wxEVT_COMMAND_CHECKBOX_CLICKED,    &ExplorerPanel::onHiddenFilesCheckBox,       this);
    m_filterCheckBox->Bind     (wxEVT_COMMAND_CHECKBOX_CLICKED,    &ExplorerPanel::onFilterKnownFormatCheckBox, this);
    m_explorerList->Bind       (wxEVT_COMMAND_LIST_ITEM_ACTIVATED, &ExplorerPanel::onItemActivatedInListCtrl,   this);
    m_explorerList->Bind       (wxEVT_COMMAND_LIST_BEGIN_DRAG,     &ExplorerPanel::onDragBeginInListCtrl,       this);
    m_explorerList->Bind       (wxEVT_CHILD_FOCUS,                 &ExplorerPanel::onListFocused,               this);

    SetMinSize(wxSize(10, 10)); //< Allows the listctrl to be resized as little as we want
}

void ExplorerPanel::setExplorerManager(ExplorerManager* explorerManager)
{
    m_explorerManager = explorerManager;
}

ExplorerListCtrl& ExplorerPanel::getExplorerListCtrl()
{
    return *m_explorerList;
}

void ExplorerPanel::onFilterKnownFormatCheckBox(wxCommandEvent& event)
{
    m_explorerManager->refresh();
}

void ExplorerPanel::onHiddenFilesCheckBox(wxCommandEvent& event)
{
    m_explorerManager->refresh();
}

void ExplorerPanel::onPreviousButton(wxCommandEvent& event)
{
    m_explorerManager->makeParentDir();
}

void ExplorerPanel::onRefreshButton(wxCommandEvent& event)
{
    m_explorerManager->refresh();
}

void ExplorerPanel::onItemActivatedInListCtrl(wxCommandEvent& event)
{
    m_explorerManager->openElement(getSelectedItems());
}

void ExplorerPanel::onDragBeginInListCtrl(wxCommandEvent& event)
{

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

std::vector<unsigned long> ExplorerPanel::getSelectedItems()
{
    std::vector<unsigned long> selectedIndexes;
    long index = m_explorerList->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    while (index != -1)
    {
        selectedIndexes.push_back(index);
        index = m_explorerList->GetNextItem(index, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    }
    return selectedIndexes;
}

void ExplorerPanel::onListFocused(wxChildFocusEvent& event)
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

