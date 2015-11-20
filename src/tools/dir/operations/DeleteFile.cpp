/***************************************************************
 * Name:      DeleteFile.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-08-07
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/dir/operations/DeleteFile.h"
#include "tools/dir/DirFileManagerData.h"
#include <wx/filename.h>

using namespace tools::dir;

const wxEventType wxEVT_FUX_DIR_FILE_DELETE_DONE = wxNewEventType();

/** @brief Constructor.
 */
DeleteFile::DeleteFile(DirFileManagerData& data, const wxString& source) :
    OperationFile(source),
    m_data(data)
{
    //ctor
}

/** @brief Destructor.
 */
DeleteFile::~DeleteFile()
{
    //dtor
}

/** @brief Overload.
 *
 * @return wxString
 *
 */
wxString DeleteFile::operationName() const
{
    return _("Suppression de ") + getSource();
}

/** @brief Returns data shared between each operation kind.
 *
 * @return DirFileManagerData&
 *
 */
DirFileManagerData& DeleteFile::getData()
{
    return m_data;
}

/** @brief Overload.
 *
 * @return void
 *
 */
void DeleteFile::doOperation()
{
    wxFileName filename(getSource());

    if (filename.FileExists())
        wxRemoveFile(getSource());
    else if (filename.DirExists())
    {
        bool canProcessOperation = true;
        if (filename.GetDirCount() > 0)
        {
            wxString message = _("Le dossier cible ") + getSource() + _(" n'est pas vide. Voulez-vous supprimer son contenu ?");
            canProcessOperation = askForRecursiveOperation(getData(), message);
        }
        if (canProcessOperation)
            filename.Rmdir(wxPATH_RMDIR_FULL | wxPATH_RMDIR_RECURSIVE);
    }
}

void DeleteFile::sendEvent()
{
    ///TODO :sendEvent
    wxThreadEvent evt(wxEVT_FUX_DIR_FILE_DELETE_DONE, wxID_ANY);
    evt.SetString(getSource());
    wxTheApp->QueueEvent(evt.Clone());
}

