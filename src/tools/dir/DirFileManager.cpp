/***************************************************************
 * Name:      DirFileManager.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-08-07
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "DirFileManager.h"
#include "CopyFile.h"
#include "CutFile.h"
#include "DeleteFile.h"

using namespace tools::dir;

/** @brief Constructor.
 */
DirFileManager::DirFileManager()
{
    //ctor
}

/** @brief Destructor.
 */
DirFileManager::~DirFileManager()
{
    //dtor
}

/** @brief Appends an operationFile
 *
 * @param operation OperationFile*
 * @return void
 *
 */
void DirFileManager::addOperationFile(OperationFile* operation)
{
    if (NULL == operation)
        return;
    m_operations.push_back(operation);
}

/** @brief Gets data relative to Copy operation.
 *
 * @return DirFileManagerData&
 *
 */
DirFileManagerData& DirFileManager::getCopyData()
{
    return m_copyData;
}

/** @brief Gets data relative to Cut operation.
 *
 * @return DirFileManagerData&
 *
 */
DirFileManagerData& DirFileManager::getCutData()
{
    return m_cutData;
}

/** @brief Gets data relative to Delete operation.
 *
 * @return DirFileManagerData&
 *
 */
DirFileManagerData& DirFileManager::getDeleteData()
{
    return m_deleteData;
}

/** @brief Appends a copy operation
 *
 * @param source const wxString&
 * @param destination const wxString&
 * @return void
 *
 */
void DirFileManager::createCopyOperation(const wxString& source, const wxString& destination)
{
    OperationFile* operation = new CopyFile(getCopyData(), source, destination);
    addOperationFile(operation);
}

/** @brief Appends a cut operation. It is similar to a file renaming.
 *
 * @param source const wxString&
 * @param destination const wxString&
 * @return void
 *
 */
void DirFileManager::createCutOperation(const wxString& source, const wxString& destination)
{
    OperationFile* operation = new CutFile(getCutData(), source, destination);
    addOperationFile(operation);
}

/** @brief Appends a delete operation.
 *
 * @param source const wxString&
 * @return void
 *
 */
void DirFileManager::createDeleteOperation(const wxString& source)
{
    OperationFile* operation = new DeleteFile(getDeleteData(), source);
    addOperationFile(operation);
}


