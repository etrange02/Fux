/***************************************************************
 * Name:      DirFileDialog.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-09-25
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/dir/DirFileDialog.h"

using namespace tools::dir;

DirFileDialog::DirFileDialog() :
    DirFileUserInterface(),
    m_dialog(NULL)
{
}

DirFileDialog::~DirFileDialog()
{
    delete m_dialog;
}

void DirFileDialog::close()
{
    if (NULL == m_dialog)
        return;

    m_dialog->Hide();
    delete m_dialog;
    m_dialog = NULL;
}

void DirFileDialog::setRange(int range)
{
    if (NULL == m_dialog)
        m_dialog = new wxGenericProgressDialog("Opérations en cours", "In progress...", range, NULL, wxPD_AUTO_HIDE);
    m_dialog->Show();
    m_dialog->SetRange(range);
}

void DirFileDialog::update(int value)
{
    update(value, "");
}

void DirFileDialog::update(int value, const wxString& message)
{
    if (NULL == m_dialog)
        return;
    m_dialog->Update(value, message);
    m_dialog->Fit();
}

