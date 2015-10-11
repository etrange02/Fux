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
#include "tools/thread/ThreadProcess.h"
#include "DirFileUserInterface.h"

using namespace tools::dir;

/** @brief Constructor.
 */
DirFileManager::DirFileManager(DirFileUserInterface& userInterface) :
    m_interface(userInterface),
    m_thread(this),
    m_range(-1),
    m_maxRange(0)
{
}

/** @brief Destructor.
 */
DirFileManager::~DirFileManager()
{
    kill();
}

/** @brief Thread starting
 *
 * @return void
 *
 */
void DirFileManager::start()
{
    #ifndef DEBUG
    m_thread.Create();
    m_thread.Run();
    #endif
}

/** @brief Thread destruction.
 *
 * @return void
 *
 */
void DirFileManager::kill()
{
    if (!m_thread.IsAlive())
        return;

    #ifndef DEBUG
    wxMutexLocker locker(m_mutex);
    m_thread.semaphorePost();
    m_thread.Delete();
    #endif
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
    #if DEBUG
    operation->process();
    #else // DEBUG
    m_operations.push(operation);
    processOperation();
    #endif // DEBUG
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

void DirFileManager::processOperation()
{
    ++m_maxRange;
    m_interface.setRange(m_maxRange);
    runThread();
}

void DirFileManager::runThread()
{
    wxMutexLocker locker(m_mutex);
    m_thread.semaphorePost();
}

void DirFileManager::currentWorkFinished(tools::thread::ThreadProcess& threadProcess)
{
    wxMutexLocker locker(m_mutex);
    if (m_operations.empty())
    {
        ++m_range;
        m_interface.close();
        m_maxRange = 0;
        m_range = -1;
        return;
    }
    ++m_range;
    OperationFile* op = m_operations.pop_front();
    if (op)
        m_interface.update(m_range, op->operationName());
    threadProcess.setWork(op);
    threadProcess.semaphorePost();
}


