/***************************************************************
 * Name:      DataBaseOpeningRequest.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2016-03-12
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "DataBaseOpeningRequest.h"
#include "DataBaseManager.h"
#include <wx/wxsqlite3.h>
#include "DataBaseMetaData.h"

using namespace tools::database;

/** @brief Constructor.
 */
DataBaseOpeningRequest::DataBaseOpeningRequest(const wxString& filename) :
    DataBaseRequest(),
    m_filename(filename)
{
}

/** @brief Destructor
 */
DataBaseOpeningRequest::~DataBaseOpeningRequest()
{
}

/** @brief
 *
 * @return void
 *
 */
void DataBaseOpeningRequest::initializeStatements()
{

}

/** @brief Overload.
 *
 * @param dataBaseManager DataBaseManager&
 * @return DataBaseResponse*
 *
 */
tools::database::DataBaseResponse* DataBaseOpeningRequest::execute(tools::database::DataBaseManager& dataBaseManager)
{
    bool fileExists = wxFileExists(m_filename);
    wxSQLite3Database& database = dataBaseManager.getDatabase();
    database.Open(m_filename); // Creates the file if necessary.

    int version = -1;
    if (database.TableExists(TABLE_DATA))
    {
        wxSQLite3ResultSet result = database.ExecuteQuery("SELECT " COLUMN_DATA_VALUE " FROM " TABLE_DATA " WHERE " COLUMN_DATA_KEY "='" DataBaseVersion "';");
        version = result.GetInt(0, -1);
    }
    else
    {
        if (fileExists)
        {
            database.Close();
            wxRemoveFile(m_filename);
            database.Open(m_filename);
        }
    }

    int newVersion = updateTables(database, version);
    if (newVersion > version)
    {
        wxString request;
        request << "UPDATE " TABLE_DATA " SET " COLUMN_DATA_VALUE "='";
        request << newVersion;
        request << "' WHERE " COLUMN_DATA_KEY "='" DataBaseVersion "'";
        database.ExecuteUpdate(request);
    }

    return NULL;
}

/** @brief Updates tables (Create, Update, Delete) and return the new version of the database.
 * Overload this method to modify the DB or to migrate data. Do not forget to call old versions.
 * Creates a 'data' table which contains the DB version number. Can be used to store key-value data.
 * @param database wxSQLite3Database&
 * @param currentVersion the current version of the base
 * @return the new version of the base
 *
 */
int DataBaseOpeningRequest::updateTables(wxSQLite3Database& database, int currentVersion)
{
    const int targetVersion = 0;
    if (currentVersion >= targetVersion)
        return targetVersion;

    if (!database.TableExists(TABLE_DATA))
        database.ExecuteUpdate("CREATE TABLE " TABLE_DATA "("
                                COLUMN_DATA_KEY " VARCHAR(100),"
                                COLUMN_DATA_VALUE " VARCHAR(100));");

    // We create the row to modify it later.
    database.ExecuteUpdate("INSERT INTO " TABLE_DATA " VALUES ('" DataBaseVersion "','0')");

    return targetVersion;
}


