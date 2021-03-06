/***************************************************************
 * Name:      GenericTreePanel.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2013-07-21
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "../../../include/gui/widgets/GenericTreePanel.h"

const wxEventType wxEVT_PREFERENCE_MAJ_LISTE = wxNewEventType();

/**
 * @class GenericTreePanel
 * @brief Inteface générique pour les préférences
 */

/**
 * Constructeur
 */
GenericTreePanel::GenericTreePanel(wxWindow *Parent, wxWindowID Id, wxWindowID IdTreeCtrl)
{
    GenericTreePanel::Create(Parent, Id, IdTreeCtrl);
}

/**
 * Destructeur
 */
GenericTreePanel::~GenericTreePanel()
{
    m_arrayPanel->Clear();
}

void GenericTreePanel::Create(wxWindow *Parent, wxWindowID Id, wxWindowID IdTreeCtrl)
{
    wxScrolledWindow::Create(Parent, Id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxVSCROLL | wxHSCROLL);
    SetScrollbars(20, 20, 50, 50);

    m_sizer1H = new wxBoxSizer(wxHORIZONTAL);
    SetSizer(m_sizer1H);

    m_sizer2V = new wxBoxSizer(wxVERTICAL);
    m_sizer1H->Add(m_sizer2V, 0, wxALL|wxEXPAND|wxFIXED_MINSIZE, 0);
    m_treeFiles = new wxTreeCtrl(this, IdTreeCtrl, wxDefaultPosition, wxSize(120, -1), wxTR_NO_BUTTONS|wxTR_EDIT_LABELS|wxTR_NO_LINES|wxTR_FULL_ROW_HIGHLIGHT|wxTR_SINGLE|wxTR_HIDE_ROOT);
    m_sizer2V->Add(m_treeFiles, 1, wxALL|wxEXPAND|wxFIXED_MINSIZE, 5);
    wxTreeItemId root = m_treeFiles->AddRoot(_T("root"));
    m_nodeExistant = m_treeFiles->AppendItem(root, _("Existants"));
    m_nodeNouveau = m_treeFiles->AppendItem(root, _("Nouveau"));

    m_sizer2Preferences = new wxBoxSizer(wxVERTICAL);
    m_sizer1H->Add(m_sizer2Preferences, 0, wxUP|wxDOWN|wxRIGHT|wxEXPAND, 5);

    m_arrayPanel = new ArrayOfwxPanel;
}

void GenericTreePanel::AddListener(wxPanel *panel)
{
    m_arrayPanel->Add(panel);
}

void GenericTreePanel::CallListeners()
{
    for (ArrayOfwxPanel::iterator iter = m_arrayPanel->begin(); iter != m_arrayPanel->end(); ++iter)
    {
        wxCommandEvent evt(wxEVT_PREFERENCE_MAJ_LISTE, wxID_ANY);
        (*iter)->GetEventHandler()->AddPendingEvent(evt);
    }
}


