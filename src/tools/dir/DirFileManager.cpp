/***************************************************************
 * Name:      DirFileManager.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-08-07
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/dir/DirFileManager.h"
#include "tools/dir/operations/CopyFile.h"
#include "tools/dir/operations/CutFile.h"
#include "tools/dir/operations/DeleteFile.h"
#include "tools/thread/ThreadProcess.h"
#include "tools/dir/interface/DirFileUserInterface.h"
#include "tools/dir/factory/DirFileCommunicationFactory.h"

using namespace tools::dir;

/** @brief Constructor.
 */
DirFileManager::DirFileManager(DirFileCommunicationFactory& factory) :
    SingleThreadManager(),
    m_factory(factory),
    m_interface(NULL),
    m_range(0),
    m_maxRange(0)
{
    m_interface = factory.createDirFileUser();
    start();
}

/** @brief Destructor.
 */
DirFileManager::~DirFileManager()
{
    kill();
    delete m_interface;
    delete &m_factory;
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
    addRunnable(operation);
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
    addRunnable(operation);
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
    addRunnable(operation);
}

/** @brief Runs/Unlocks the thread if possible.
 *
 * @return void
 *
 */
void DirFileManager::activateAWorker()
{
    wxMutexLocker locker(getMutex());
    if (/*m_operations.size() <= 1 && */m_maxRange <= 1)
    {
        tools::thread::ThreadProcess* tp = getAvailableWorker();
        if (NULL != tp)
        {
            tp->semaphorePost();
        }
    }
}

/** @brief
 *
 * @param tools::thread::Runnable&
 * @return void
 *
 */
void DirFileManager::doBeforeAddingWork(tools::thread::Runnable&)
{

}

/** @brief
 *
 * @param tools::thread::Runnable&
 * @return void
 *
 */
void DirFileManager::doAfterAddingWork(tools::thread::Runnable&)
{
    ++m_maxRange;
    m_interface->setRange(m_maxRange);
}

/** @brief
 *
 * @param work tools::thread::Runnable&
 * @param threadProcess tools::thread::ThreadProcess&
 * @return void
 *
 */
void DirFileManager::doBeforeProcessingWork(tools::thread::Runnable& work, tools::thread::ThreadProcess& threadProcess)
{
    OperationFile& op = static_cast<OperationFile&>(work);

    m_interface->update(m_range, op.operationName());
    ++m_range;
    op.setThread(&threadProcess);
    op.setFactory(&m_factory);
}

/** @brief
 *
 * @return void
 *
 */
void DirFileManager::doOnNoWork()
{
    m_interface->close();
    m_maxRange = 0;
    m_range = 0;
}

