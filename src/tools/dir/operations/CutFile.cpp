/***************************************************************
 * Name:      CutFile.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-08-07
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/dir/operations/CutFile.h"

using namespace tools::dir;

const wxEventType wxEVT_FUX_DIR_FILE_CUT_DONE = wxNewEventType();

/** @brief Constructor.
 */
CutFile::CutFile(DirFileManagerData& data, const wxString& source, const wxString& destination) :
    ConflictingOperationFile(data, source, destination)
{
    //ctor
}

/** @brief Destructor.
 */
CutFile::~CutFile()
{
    //dtor
}

/** @brief Overload.
 *
 * @return wxString
 *
 */
wxString CutFile::operationName() const
{
    return _("Déplacement de ") + getSourceFilename();// + _("\nvers ") + getDestination();
}

/** @brief Overload.
 *
 * @return void
 *
 */
void CutFile::doOperation()
{
    wxRenameFile(getSource(), getDestination());
}

void CutFile::sendEvent()
{
    ///TODO :sendEvent
    wxThreadEvent evt(wxEVT_FUX_DIR_FILE_CUT_DONE, wxID_ANY);
    evt.SetString(getSource() + "\n" + getDestination());
    wxTheApp->QueueEvent(evt.Clone());
}


