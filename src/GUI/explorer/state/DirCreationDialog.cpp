/***************************************************************
 * Name:      DirCreationDialog.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2016-01-31
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "GUI/explorer/state/DirCreationDialog.h"
#include <wx/valtext.h>
#include <wx/dirdlg.h>
#include <wx/filename.h>

//(*InternalHeaders(DirCreationDialog)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/radiobut.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
//*)

//(*IdInit(DirCreationDialog)
const long DirCreationDialog::ID_DIR_CREATION_DIALOG_DIR_PATH = wxNewId();
const long DirCreationDialog::ID_DIR_CREATION_DIALOG_OPEN_BUTTON = wxNewId();
const long DirCreationDialog::ID_DIR_CREATION_DIALOG_DIR_NAME = wxNewId();
const long DirCreationDialog::ID_DIR_CREATION_DIALOG_RADIOBUTTON_LEFT_EXPLORER = wxNewId();
const long DirCreationDialog::ID_DIR_CREATION_DIALOG_RADIOBUTTON_RIGHT_EXPLORER = wxNewId();
const long DirCreationDialog::ID_DIR_CREATION_DIALOG_RADIOBUTTON_NO_EXPLORER = wxNewId();
//*)

BEGIN_EVENT_TABLE(DirCreationDialog, wxDialog)
	//(*EventTable(DirCreationDialog)
	//*)
	//EVT_BUTTON(wxID_OK, DirCreationDialog::onClickOKButton)
END_EVENT_TABLE()

DirCreationDialog::DirCreationDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(DirCreationDialog)
	wxBoxSizer* BoxSizer4;
	wxStaticText* StaticText1;
	wxBoxSizer* BoxSizer2;
	wxGridSizer* GridSizer1;
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer3;
	wxStdDialogButtonSizer* StdDialogButtonSizer1;

	Create(parent, wxID_ANY, _("Création d\'un répertoire"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	m_dirPath = new wxTextCtrl(this, ID_DIR_CREATION_DIALOG_DIR_PATH, wxEmptyString, wxDefaultPosition, wxSize(257,21), 0, wxDefaultValidator, _T("ID_DIR_CREATION_DIALOG_DIR_PATH"));
	m_dirPath->Disable();
	m_dirPath->SetToolTip(_("Chemin du nouveau répertoire"));
	BoxSizer2->Add(m_dirPath, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_dirSelectionButton = new wxButton(this, ID_DIR_CREATION_DIALOG_OPEN_BUTTON, _("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT, wxDefaultValidator, _T("ID_DIR_CREATION_DIALOG_OPEN_BUTTON"));
	BoxSizer2->Add(m_dirSelectionButton, 0, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer2, 0, wxALL|wxEXPAND, 5);
	m_dirNameCtrl = new wxTextCtrl(this, ID_DIR_CREATION_DIALOG_DIR_NAME, wxEmptyString, wxDefaultPosition, wxSize(273,20), 0, wxTextValidator(wxFILTER_ALPHANUMERIC, &m_dirName), _T("ID_DIR_CREATION_DIALOG_DIR_NAME"));
	m_dirNameCtrl->SetToolTip(_("Nom du nouveau répertoire"));
	BoxSizer1->Add(m_dirNameCtrl, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND, 5);
	BoxSizer4 = new wxBoxSizer(wxVERTICAL);
	StaticText1 = new wxStaticText(this, wxID_ANY, _("Dans quel navigateur souhaitez-vous ouvrir le nouveau répertoire \?"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	BoxSizer4->Add(StaticText1, 1, wxALL|wxEXPAND, 5);
	GridSizer1 = new wxGridSizer(0, 3, 0, 0);
	m_sameExplorer = new wxRadioButton(this, ID_DIR_CREATION_DIALOG_RADIOBUTTON_LEFT_EXPLORER, _("Le même"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_DIR_CREATION_DIALOG_RADIOBUTTON_LEFT_EXPLORER"));
	m_sameExplorer->SetToolTip(_("Afficher dans le navigateur de gauche"));
	GridSizer1->Add(m_sameExplorer, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_otherExplorer = new wxRadioButton(this, ID_DIR_CREATION_DIALOG_RADIOBUTTON_RIGHT_EXPLORER, _("L\'autre"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_DIR_CREATION_DIALOG_RADIOBUTTON_RIGHT_EXPLORER"));
	m_otherExplorer->SetToolTip(_("Afficher dans le navigateur de droite"));
	GridSizer1->Add(m_otherExplorer, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_noExplorer = new wxRadioButton(this, ID_DIR_CREATION_DIALOG_RADIOBUTTON_NO_EXPLORER, _("Aucun"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_DIR_CREATION_DIALOG_RADIOBUTTON_NO_EXPLORER"));
	m_noExplorer->SetToolTip(_("Ne pas afficher"));
	GridSizer1->Add(m_noExplorer, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer4->Add(GridSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer4, 1, wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	StdDialogButtonSizer1 = new wxStdDialogButtonSizer();
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_OK, wxEmptyString));
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_CANCEL, wxEmptyString));
	StdDialogButtonSizer1->Realize();
	BoxSizer3->Add(StdDialogButtonSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer3, 0, wxALL|wxALIGN_RIGHT, 0);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_DIR_CREATION_DIALOG_OPEN_BUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DirCreationDialog::onClickDirSelectionButton);
	//*)
}

DirCreationDialog::~DirCreationDialog()
{
	//(*Destroy(DirCreationDialog)
	//*)
}

void DirCreationDialog::onClickDirSelectionButton(wxCommandEvent& event)
{
    wxString path = m_dirPath->GetValue();
    wxDirDialog dialog(this, _("Sélectionnez le répertoire parent"), path, wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

    if (wxID_OK == dialog.ShowModal())
    {
        setDirPath(dialog.GetPath());
    }
}

wxString DirCreationDialog::getFullPath() const
{
    wxString dir = m_dirPath->GetValue();
    if (!dir.EndsWith(wxFileName::GetPathSeparator()))
        dir << wxFileName::GetPathSeparator();
    dir << m_dirName;
    return dir;
}

bool DirCreationDialog::isShowInSameExplorer() const
{
    return m_sameExplorer->GetValue();
}

bool DirCreationDialog::isShowInOtherExplorer() const
{
    return m_otherExplorer->GetValue();
}

bool DirCreationDialog::isNoShowInExplorer() const
{
    return m_noExplorer->GetValue();
}

bool DirCreationDialog::isDataOK() const
{
    bool isOK = true;

    isOK &= !m_dirPath->IsEmpty();
    isOK &= !m_dirName.IsEmpty();
    isOK &= (isShowInOtherExplorer() || isShowInSameExplorer() || isNoShowInExplorer());

    return isOK;
}

void DirCreationDialog::setDirPath(const wxString& dirPath)
{
    m_dirPath->SetValue(dirPath);
}

void DirCreationDialog::setDirName(const wxString& dirName)
{
    m_dirName = dirName;
    m_dirNameCtrl->SetValue(dirName);
}

