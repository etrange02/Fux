/***************************************************************
 * Name:      AskForRecursiveOperationData.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-10-21
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/dir/AskForRecursiveOperationData.h"
#include "tools/thread/ThreadProcess.h"

using namespace tools::dir;

/** @brief Constructor.
 */
AskForRecursiveOperationData::AskForRecursiveOperationData(tools::thread::ThreadProcess* thread, const wxString& message) :
    m_message         (message),
    m_threadProcess   (thread),
    m_isRecursive     (false),
    m_canBeOverWritten(false)
{
    //ctor
}

/** @brief Destructor.
 */
AskForRecursiveOperationData::~AskForRecursiveOperationData()
{
    //dtor
}

/** @brief Copy constructor.
 *
 * @param other const AskForRecursiveOperationData&
 *
 */
AskForRecursiveOperationData::AskForRecursiveOperationData(const AskForRecursiveOperationData& other) :
    m_message         (other.m_message         ),
    m_threadProcess   (other.m_threadProcess   ),
    m_isRecursive     (other.m_isRecursive     ),
    m_canBeOverWritten(other.m_canBeOverWritten)
{
    //copy ctor
}

/** @brief
 *
 * @return bool
 *
 */
bool AskForRecursiveOperationData::isRecursive()
{
    return m_isRecursive;
}

/** @brief
 *
 * @param isRecursive bool
 * @return void
 *
 */
void AskForRecursiveOperationData::setRecursive(bool isRecursive)
{
    m_isRecursive = isRecursive;
}

/** @brief
 *
 * @return bool
 *
 */
bool AskForRecursiveOperationData::canBeOverWritten()
{
    return m_canBeOverWritten;
}

/** @brief
 *
 * @param overWrite bool
 * @return void
 *
 */
void AskForRecursiveOperationData::setOverWrite(bool overWrite)
{
    m_canBeOverWritten = overWrite;
}

/** @brief Make the thread running.
 *
 * @return void
 *
 */
void AskForRecursiveOperationData::postThread()
{
    if (m_threadProcess)
        m_threadProcess->semaphorePost();
}

/** @brief Make the thread waiting.
 *
 * @return void
 *
 */
void AskForRecursiveOperationData::waitThread()
{
    if (m_threadProcess)
        m_threadProcess->semaphoreWait();
}

/** @brief Returns the message to display.
 *
 * @return const wxString&
 *
 */
const wxString& AskForRecursiveOperationData::getMessage() const
{
    return m_message;
}

