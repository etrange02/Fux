/***************************************************************
 * Name:      DirFileDialog.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-11-01
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "DirFileDialog.h"
#include "tools/dir/AskForRecursiveOperationData.h"

//(*InternalHeaders(DirFileDialog)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/gauge.h>
//*)

using namespace tools::dir;

//(*IdInit(DirFileDialog)
const long DirFileDialog::ID_STATICTEXT1 = wxNewId();
const long DirFileDialog::ID_GAUGE1 = wxNewId();
const long DirFileDialog::ID_STATICTEXT2 = wxNewId();
const long DirFileDialog::ID_CHECKBOX1 = wxNewId();
const long DirFileDialog::ID_BUTTON1 = wxNewId();
const long DirFileDialog::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(DirFileDialog,wxDialog)
	//(*EventTable(DirFileDialog)
	//*)
END_EVENT_TABLE()

/** @brief Constructor
 *
 * @param parent wxWindow*
 *
 */
DirFileDialog::DirFileDialog(wxWindow* parent) :
    DirFileUserInterface(),
    RepeatedQuestionInterface(),
    m_data(NULL)
{
	//(*Initialize(DirFileDialog)
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer3;

	Create(parent, wxID_ANY, _("Opération en cours"), wxDefaultPosition, wxDefaultSize, wxCAPTION|wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxCLOSE_BOX|wxDIALOG_NO_PARENT|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxFRAME_SHAPED, _T("wxID_ANY"));
	SetClientSize(wxSize(586,327));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	m_stateText = new wxStaticText(this, ID_STATICTEXT1, _("Label"), wxDefaultPosition, wxSize(508,44), wxALIGN_LEFT, _T("ID_STATICTEXT1"));
	BoxSizer1->Add(m_stateText, 1, wxALL|wxEXPAND, 5);
	m_gauge = new wxGauge(this, ID_GAUGE1, 100, wxDefaultPosition, wxSize(508,32), 0, wxDefaultValidator, _T("ID_GAUGE1"));
	BoxSizer1->Add(m_gauge, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND, 5);
	m_questionSizer = new wxBoxSizer(wxVERTICAL);
	m_questionText = new wxStaticText(this, ID_STATICTEXT2, _("Label"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT, _T("ID_STATICTEXT2"));
	m_questionSizer->Add(m_questionText, 1, wxALL|wxEXPAND, 5);
	m_recurseCheckBox = new wxCheckBox(this, ID_CHECKBOX1, _("Ne plus poser cette question"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	m_recurseCheckBox->SetValue(false);
	m_questionSizer->Add(m_recurseCheckBox, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	m_yesButton = new wxButton(this, ID_BUTTON1, _("Oui"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer3->Add(m_yesButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_noButton = new wxButton(this, ID_BUTTON2, _("Non"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer3->Add(m_noButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_questionSizer->Add(BoxSizer3, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(m_questionSizer, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND, 5);
	SetSizer(BoxSizer1);
	SetSizer(BoxSizer1);
	Layout();

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DirFileDialog::onClickYesButton);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DirFileDialog::onClickNoButton);
	//*)

	m_questionSizer->Show(false);
}

/** @brief Destructor
 */
DirFileDialog::~DirFileDialog()
{
	//(*Destroy(DirFileDialog)
	//*)
}

/** @brief Event - Yes clicked to overwrite file.
 *
 * @param event wxCommandEvent&
 * @return void
 *
 */
void DirFileDialog::onClickYesButton(wxCommandEvent& event)
{
    respondToRecurse(true);
}

/** @brief Event - No clicked, no overwrite.
 *
 * @param event wxCommandEvent&
 * @return void
 *
 */
void DirFileDialog::onClickNoButton(wxCommandEvent& event)
{
    respondToRecurse(false);
}

/** @brief Fills shared data with operation file thread and unlock it.
 *
 * @param overwrite if true, file is overwritten.
 * @return void
 *
 */
void DirFileDialog::respondToRecurse(bool overwrite)
{
    if (NULL == m_data)
        return;

    AskForRecursiveOperationData* tmpData = m_data;
    m_data = NULL;
    tmpData->setOverWrite(overwrite);
    tmpData->setRecursive(m_recurseCheckBox->IsChecked());

	m_questionSizer->Show(false);
	Fit();
    tmpData->postThread();
}

/** @brief Hide the dialog.
 *
 * @return void
 *
 */
void DirFileDialog::close()
{
    Hide();
}

/** @brief Modifies the max range of the progress bar. Show the dialog if hidden.
 *
 * @param range int
 * @return void
 *
 */
void DirFileDialog::setRange(int range)
{
    m_gauge->SetRange(range);
    if (!IsShown())
        Show();
}

/** @brief Modifies the current range of the progress bar.
 *
 * @param value int
 * @return void
 *
 */
void DirFileDialog::update(int value)
{
    update(value, "");
}

/** @brief Modifies the current range of the progress bar and text of the operation in progress.
 *
 * @param value int
 * @param message Current operation name
 * @return void
 *
 */
void DirFileDialog::update(int value, const wxString& message)
{
    m_gauge->SetValue(value);
    m_stateText->SetLabel(message);
    //if (!IsShown())
      //  Show();
}

/** @brief Shows a specific part of the dialog for operations conflicts
 *
 * @param data AskForRecursiveOperationData&
 * @return void
 *
 */
void DirFileDialog::askQuestion(AskForRecursiveOperationData& data)
{
	m_questionSizer->Show(true);
    m_questionText->SetLabel(data.getMessage());
	Fit();
	m_data = &data;
}

