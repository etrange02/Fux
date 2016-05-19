/***************************************************************
 * Name:      DataBaseManager.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2016-03-08
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/database/DataBaseManager.h"
#include "tools/database/DataBaseRequest.h"
#include <wx/wxsqlite3.h>
#include <algorithm>

using namespace tools::database;
/** Count instances of DataBaseManager to have only one initialization of SQLite. */
int DataBaseManager::m_initializingCounter = 0;

/** @brief Constructor.
 */
DataBaseManager::DataBaseManager() :
    tools::thread::SingleThreadManager(),
    m_database(NULL)
{
    if (m_initializingCounter == 0)
        wxSQLite3Database::InitializeSQLite();
    ++m_initializingCounter;
}

/** @brief Destructor.
 */
DataBaseManager::~DataBaseManager()
{
    setDatabase(NULL);
    --m_initializingCounter;
    if (m_initializingCounter == 0)
        wxSQLite3Database::ShutdownSQLite();
}

/** @brief Overload of addRunnable to make it easier.
 *
 * @param request DataBaseRequest*
 * @param priority int
 * @return void
 *
 */
void DataBaseManager::addDataBaseResquest(DataBaseRequest* request, int priority)
{
    addRunnable(request, priority);
}

/** @brief Overload of addRunnable to make it easier.
 *
 * @param request DataBaseRequest*
 * @return void
 *
 */
void DataBaseManager::addDataBaseResquest(DataBaseRequest* request)
{
    addRunnable(request);
}

/** @brief Indicates presence of statements.
 *
 * @return bool
 *
 */
bool DataBaseManager::hasStatements() const
{
    return !m_statements.empty();
}

/** @brief Indicates presence of the statement id.
 *
 * @param id int
 * @return bool
 *
 */
bool DataBaseManager::isContainingStatement(int id) const
{
    std::map<int, wxSQLite3Statement>::const_iterator iter = m_statements.find(id);
    return m_statements.end() != iter;
}

/** @brief Adds a statement. If id is already used, old statement is replaced.
 *
 * @param statement wxSQLite3Statement&
 * @param id int
 * @return void
 *
 */
void DataBaseManager::addStatement(int id, wxSQLite3Statement& statement)
{
    if (isContainingStatement(id))
    {
        std::map<int, wxSQLite3Statement>::iterator iter = m_statements.find(id);
        iter->second = statement;
    }
    else
        m_statements.insert(std::pair<int, wxSQLite3Statement>(id, statement));
}

/** @brief Gets a statement available with the database. Creates it if not referenced by the DB manager.
 *
 * @param uid int
 * @param requestForm const wxString&
 * @return sqlite3_stmt*
 *
 */
wxSQLite3Statement& DataBaseManager::initializeStatement(int uid, const wxString& requestForm)
{
    if (!isContainingStatement(uid))
    {
        wxSQLite3Statement stm = m_database->PrepareStatement(requestForm);
        addStatement(uid, stm);
    }

    wxSQLite3Statement& statement = getStatement(uid);
    return statement;
}

/** @brief Returns a statement id.
 *
 * @param id int
 * @return wxSQLite3Statement&
 *
 */
wxSQLite3Statement& DataBaseManager::getStatement(int id)
{
    std::map<int, wxSQLite3Statement>::iterator iter = m_statements.find(id);
    return iter->second;
}

/** @brief Deletes all statements generated for the DB.
 *
 * @return void
 *
 */
void DataBaseManager::destroyStatements()
{
    for (std::map<int, wxSQLite3Statement>::iterator iter = m_statements.begin(); iter != m_statements.end(); ++iter)
    {
        iter->second.Finalize();
    }
    m_statements.clear();
}

/** @brief Overload. Sets the manager to the request.
 *
 * @param work tools::thread::Runnable&
 * @return void
 *
 */
void DataBaseManager::doBeforeAddingWork(tools::thread::Runnable& work)
{
    DataBaseRequest& request = static_cast<DataBaseRequest&>(work);

    request.setDataBaseManager(*this);
}

/** @brief Indicates if the database connector has been created.
 *
 * @return bool
 *
 */
bool DataBaseManager::isDatabaseInitialized() const
{
    return NULL != m_database;
}

/** @brief Modifies the database connector to the new one. Can be used to close connection.
 *
 * @param database wxSQLite3Database*
 * @return void
 *
 */
void DataBaseManager::setDatabase(wxSQLite3Database* database)
{
    if (m_database)
    {
        destroyStatements();
        m_database->Close();
        delete m_database;
    }
    m_database = database;
}

/** @brief Returns a reference to the database connector.
 *
 * @return wxSQLite3Database&
 *
 */
wxSQLite3Database& DataBaseManager::getDatabase()
{
    return *m_database;
}

