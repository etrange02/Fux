/***************************************************************
 * Name:      OperationFile.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-08-07
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/dir/operations/ConflictingOperationFile.h"
#include "tools/dir/DirFileManagerData.h"

using namespace tools::dir;

/** @brief Constructor.
 */
ConflictingOperationFile::ConflictingOperationFile(DirFileManagerData& data, const wxString& source, const wxString& destination) :
    OperationFile(source),
    m_data(data),
    m_destination(destination)
{
    //ctor
}

/** @brief Destructor.
 */
ConflictingOperationFile::~ConflictingOperationFile()
{
    //dtor
}

/** @brief Returns the new name of the file.
 *
 * @return const wxString&
 *
 */
const wxString& ConflictingOperationFile::getDestination() const
{
    return m_destination;
}

/** @brief Returns data shared between each operation kind.
 *
 * @return DirFileManagerData&
 *
 */
DirFileManagerData& ConflictingOperationFile::getData()
{
    return m_data;
}

/** @brief Makes the operation if possible.
 *
 * @return void
 *
 */
void ConflictingOperationFile::process()
{
    if (getSource() == getDestination())
        return;

    bool canProcessOperation = true;
    if (wxFileExists(getDestination()))
    {
        wxString message = _("Le fichier cible ") + getDestination() + _(" existe déjà.\nVoulez-vous le remplacer ?");
        canProcessOperation = askForRecursiveOperation(getData(), message);
    }

    if (canProcessOperation)
    {
        doOperation();
        sendEvent();
    }
}

