/***************************************************************
 * Name:      OperationFile.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-08-07
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "OperationFile.h"
#include "DirFileManagerData.h"
#include "GUI\dialogs\RepeatedQuestionDialog.h"
#include <wx/filename.h>

using namespace tools::dir;

/** @brief Constructor.
 */
OperationFile::OperationFile(const wxString& source) :
    tools::thread::IRunnable(),
    m_source(source)
{
    //ctor
}

/** @brief Destructor.
 */
OperationFile::~OperationFile()
{
    //dtor
}

/** @brief Returns the file source
 *
 * @return const wxString&
 *
 */
const wxString& OperationFile::getSource() const
{
    return m_source;
}

/** @brief Returns a description of the operation
 *
 * @return wxString
 *
 */
wxString OperationFile::operationName() const
{
    return _("Aucune opération en cours");
}

/** @brief Processes operation. Must be overloaded.
 *
 * @return void
 *
 */
void OperationFile::process()
{
    doOperation();
    sendEvent();
}

/** @brief Displays a dialogue get information from the user. Also ask to be shown again.
 *
 * @param data DirFileManagerData&
 * @param message const wxString&
 * @return bool
 *
 */
bool OperationFile::askForRecursiveOperation(DirFileManagerData& data, const wxString& message)
{
    if (data.isRecursiveAsked())
        return data.isRecursive();

    gui::RepeatedQuestionDialog dialog(NULL, -1, message, _("Confirmation"));
    int answer = dialog.ShowModal();

    const bool isRecursive = dialog.isRecursiveChecked();
    if (isRecursive)
        data.setRecursiveAsked();
    data.setRecursive(isRecursive);

    if (answer != wxYES)
        return false;

    return true;
}

wxString OperationFile::getSourceFilename() const
{
    return getSource().AfterLast(wxFileName::GetPathSeparator());
}


