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
    m_factory(factory),
    m_interface(NULL),
    m_thread(this),
    m_range(0),
    m_maxRange(0)
{
    m_interface = factory.createDirFileUser();
}

/** @brief Destructor.
 */
DirFileManager::~DirFileManager()
{
    kill();
    delete m_interface;
    delete &m_factory;
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

/** @brief Launches thread and sends events.
 *
 * @return void
 *
 */
void DirFileManager::processOperation()
{
    ++m_maxRange;
    m_interface->setRange(m_maxRange);
    runThread();
}

/** @brief Runs/Unlocks the thread if possible.
 *
 * @return void
 *
 */
void DirFileManager::runThread()
{
    wxMutexLocker locker(m_mutex);
    if (/*m_operations.size() <= 1 && */m_maxRange <= 1)
        m_thread.semaphorePost();
}

/** @brief Overloads. Called by thread to get another task.
 *
 * @param threadProcess tools::thread::ThreadProcess&
 * @return void
 *
 */
void DirFileManager::currentWorkFinished(tools::thread::ThreadProcess& threadProcess)
{
    wxMutexLocker locker(m_mutex);
    if (m_operations.empty())
    {
        m_interface->close();
        m_maxRange = 0;
        m_range = 0;
        return;
    }
    OperationFile* op = m_operations.pop_front();
    if (op)
    {
        m_interface->update(m_range, op->operationName());
        ++m_range;
        op->setThread(&threadProcess);
        op->setFactory(&m_factory);
    }
    threadProcess.setWork(op);
    threadProcess.semaphorePost();
}


