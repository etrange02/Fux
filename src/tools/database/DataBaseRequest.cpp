/***************************************************************
 * Name:      DataBaseRequest.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2016-03-08
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/database/DataBaseRequest.h"
#include "tools/database/DataBaseManager.h"
#include "DBThreadEvent.h"
#include <sqlite3.h>

using namespace tools::database;

/** @brief Constructor.
 */
DataBaseRequest::DataBaseRequest() :
    tools::thread::Runnable(),
    m_dataBaseManager(NULL)
{
    setPriority(100);
}

/** @brief Destructor.
 */
DataBaseRequest::~DataBaseRequest()
{
}

/** @brief Modifies the database manager.
 *
 * @param dataBaseManager DataBaseManager&
 * @return void
 *
 */
void DataBaseRequest::setDataBaseManager(DataBaseManager& dataBaseManager)
{
    m_dataBaseManager = &dataBaseManager;
}

/** @brief Gets the database manager.
 *
 * @return DataBaseManager*
 *
 */
DataBaseManager* DataBaseRequest::getDataBaseManager()
{
    return m_dataBaseManager;
}

/** @brief Overloads. Call the execute method to have a result.
 *
 * @return void
 *
 */
void DataBaseRequest::process()
{
    if (NULL == getDataBaseManager())
        return; // throw ?

    initializeStatements();
    DataBaseResponse* response = execute(*getDataBaseManager());
    sendEvent(getEventType(), getEventId(), response);
}

/** @brief Initialize all statements needed by the request. Can be overloaded.
 * Example: wxSQLite3Statement* m_statement = &getDataBaseManager()->initializeStatement(uid, SQLRequest)
 * @return void
 * @see DataBaseManager::initializeStatement
 */
void DataBaseRequest::initializeStatements()
{
}

/** @brief Gets the type of the last event sent, at process ending.
 *
 * @return wxEventType
 *
 */
wxEventType DataBaseRequest::getEventType()
{
    return wxEVT_DB_THREAD;
}

/** @brief Returns the id of the event destination. wxID_ANY by default.
 *
 * @return int
 *
 */
int DataBaseRequest::getEventId()
{
    return wxID_ANY;
}

/** @brief Sends an event to a frame.
 *
 * @param response DataBaseResponse*
 * @return void
 *
 */
void DataBaseRequest::sendEvent(wxEventType commandType, int id, DataBaseResponse* response)
{
    if (NULL == response)
        return;

    DBThreadEvent evt(commandType, id);
    evt.setResponse(response);
    wxTheApp->QueueEvent(evt.Clone());
}

