/***************************************************************
 * Name:      CopyFile.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-08-07
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/dir/operations/CopyFile.h"

using namespace tools::dir;

const wxEventType wxEVT_FUX_DIR_FILE_COPY_DONE = wxNewEventType();

/** @brief Constructor.
 */
CopyFile::CopyFile(DirFileManagerData& data, const wxString& source, const wxString& destination) :
    ConflictingOperationFile(data, source, destination)
{
}

/** @brief Destructor.
 */
CopyFile::~CopyFile()
{
}

/** @brief Overload.
 *
 * @return wxString
 *
 */
wxString CopyFile::operationName() const
{
    return _("Copie de ") + getSource() + _("\nvers ") + getDestination();
}

/** @brief Overload. Copies a file.
 *
 * @return void
 *
 */
void CopyFile::doOperation()
{
    wxCopyFile(getSource(), getDestination());
}

void CopyFile::sendEvent()
{
    ///TODO :sendEvent
    wxThreadEvent evt(wxEVT_FUX_DIR_FILE_COPY_DONE, wxID_ANY);
    evt.SetString(getSource() + "\n" + getDestination());
    wxTheApp->QueueEvent(evt.Clone());
}



