/***************************************************************
 * Name:      RepeatedQuestionDialog.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-08-09
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "RepeatedQuestionDialog.h"
#include "wx/sizer.h"

using namespace gui;

/** @brief Constructor.
 *
 * @param parent wxWindow*
 * @param id const wxWindowID
 * @param message const wxString&
 * @param caption const wxString&
 *
 */
RepeatedQuestionDialog::RepeatedQuestionDialog(wxWindow* parent, const wxWindowID id, const wxString& message, const wxString& caption) :
    wxDialog(parent, id, caption, wxDefaultPosition, wxDefaultSize, wxCAPTION|wxCLOSE_BOX|wxSYSTEM_MENU),
    m_message(message),
    m_isRecursiveChecked(false)
{
    initialize();
}

/** @brief Destructor.
 */
RepeatedQuestionDialog::~RepeatedQuestionDialog()
{
    //dtor
}

/** @brief Indicates if the recursive checkbox has been checked by the user.
 *
 * @return bool
 *
 */
bool RepeatedQuestionDialog::isRecursiveChecked() const
{
    return m_isRecursiveChecked;
}

/** @brief Initializes components.
 *
 * @return void
 *
 */
void RepeatedQuestionDialog::initialize()
{
    wxBoxSizer* verticalSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(verticalSizer);

    wxTextCtrl* text            = new wxTextCtrl(this, -1, m_message, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    wxCheckBox* recurseCheckBox = new wxCheckBox(this, wxNewId(), _("Ne plus demander."));
    verticalSizer->Add(text,            1, wxEXPAND|wxLEFT, 5);
    verticalSizer->Add(recurseCheckBox, 1, wxEXPAND|wxLEFT, 5);
    verticalSizer->SetSizeHints(this);

    Bind(wxEVT_CHECKBOX, &RepeatedQuestionDialog::onRecursiveCheckBox, this, recurseCheckBox->GetId());
}

/** @brief Event. Click on the checkbox for the recursive asking.
 *
 * @param event wxCommandEvent&
 * @return void
 *
 */
void RepeatedQuestionDialog::onRecursiveCheckBox(wxCommandEvent& event)
{
    m_isRecursiveChecked = event.IsChecked();
}


