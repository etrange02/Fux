/***************************************************************
 * Name:      DataBaseOpeningRequest_01.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2016-03-16
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "DataBaseOpeningRequest_01.h"
#include <wx/wxsqlite3.h>
#include "DataBase_MetaData.h"
#include "tools/database/DataBaseMetaData.h"

using namespace database;

/** @brief Constructor.
 *
 * @param filename const wxString&
 *
 */
DataBaseOpeningRequest_01::DataBaseOpeningRequest_01(const wxString& filename) :
    tools::database::DataBaseOpeningRequest(filename)
{
    //ctor
}

/** @brief Destructor.
 */
DataBaseOpeningRequest_01::~DataBaseOpeningRequest_01()
{
    //dtor
}

/** @brief Overload. Update the DB to version 1.
 *
 * @param database wxSQLite3Database&
 * @param currentVersion int
 * @return int
 *
 */
int DataBaseOpeningRequest_01::updateTables(wxSQLite3Database& database, int currentVersion)
{
    const int targetVersion = 1;
    if (currentVersion >= targetVersion)
        return targetVersion;

    tools::database::DataBaseOpeningRequest::updateTables(database, currentVersion);

    // Logical data
    if (!database.TableExists(TABLE_ARTIST))
        database.ExecuteUpdate("CREATE TABLE " TABLE_ARTIST "("
                                COLUMN_ARTIST_ID " INTEGER PRIMARY KEY AUTOINCREMENT,"
                                COLUMN_ARTIST_GID " VARCHAR(128),"
                                COLUMN_ARTIST_NAME " VARCHAR(256) NOT NULL DEFAULT ''," // NOT NULL
                                COLUMN_ARTIST_SORT_NAME " VARCHAR(256) NOT NULL DEFAULT '');");

    if (!database.TableExists(TABLE_ARTIST_CREDIT))
        database.ExecuteUpdate("CREATE TABLE " TABLE_ARTIST_CREDIT "("
                                COLUMN_ARTIST_CREDIT_ID " INTEGER PRIMARY KEY AUTOINCREMENT,"
                                COLUMN_ARTIST_CREDIT_NAME " VARCHAR(256) NOT NULL DEFAULT '',"
                                COLUMN_ARTIST_CREDIT_ARTIST_COUNT " INTEGER NOT NULL DEFAULT 1 CHECK(" COLUMN_ARTIST_CREDIT_ARTIST_COUNT ">=0));"); // INTEGER

    if (!database.TableExists(TABLE_ARTIST_CREDIT_NAME))
        database.ExecuteUpdate("CREATE TABLE " TABLE_ARTIST_CREDIT_NAME "("
                                COLUMN_ARTIST_CREDIT_NAME_ARTIST_CREDIT " INTEGER REFERENCES " TABLE_ARTIST_CREDIT "(" COLUMN_ARTIST_CREDIT_ID "),"
                                COLUMN_ARTIST_CREDIT_NAME_ARTIST_ID " INTEGER REFERENCES " TABLE_ARTIST "(" COLUMN_ARTIST_ID "),"
                                COLUMN_ARTIST_CREDIT_NAME_POSITION " INTEGER NOT NULL DEFAULT 1 CHECK (" COLUMN_ARTIST_CREDIT_NAME_POSITION " >=1)," // INTEGER
                                "PRIMARY KEY(" COLUMN_ARTIST_CREDIT_NAME_ARTIST_CREDIT "," COLUMN_ARTIST_CREDIT_NAME_POSITION "));");

    if (!database.TableExists(TABLE_LANGUAGE))
        database.ExecuteUpdate("CREATE TABLE " TABLE_LANGUAGE "("
                                COLUMN_LANGUAGE_ID " INTEGER PRIMARY KEY AUTOINCREMENT,"
                                COLUMN_LANGUAGE_NAME " VARCHAR(256) NOT NULL DEFAULT '');");

    if (!database.TableExists(TABLE_WORK))
        database.ExecuteUpdate("CREATE TABLE " TABLE_WORK "("
                                COLUMN_WORK_ID " INTEGER PRIMARY KEY AUTOINCREMENT,"
                                COLUMN_WORK_GID " VARCHAR(128),"
                                COLUMN_WORK_NAME " VARCHAR(256) NOT NULL DEFAULT '');");

    if (!database.TableExists(TABLE_RECORDING))
        database.ExecuteUpdate("CREATE TABLE " TABLE_RECORDING "("
                                COLUMN_RECORDING_ID " INTEGER PRIMARY KEY AUTOINCREMENT,"
                                COLUMN_RECORDING_ARTIST_CREDIT_ID " INTEGER REFERENCES " TABLE_ARTIST_CREDIT "(" COLUMN_ARTIST_CREDIT_ID "),"
                                COLUMN_RECORDING_WORK_ID " INTEGER REFERENCES " TABLE_WORK "(" COLUMN_WORK_ID "),"
                                COLUMN_RECORDING_GID " VARCHAR(128),"
                                COLUMN_RECORDING_NAME " VARCHAR(256) NOT NULL DEFAULT '',"
                                COLUMN_RECORDING_YEAR " INTEGER NOT NULL DEFAULT -1,"// CHECK (" COLUMN_RELEASE_DATE_YEAR " >=-1),"
                                COLUMN_RECORDING_ADDING_DATE " TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP);");

    if (!database.TableExists(TABLE_RECORDING_LANGUAGE))
        database.ExecuteUpdate("CREATE TABLE " TABLE_RECORDING_LANGUAGE "("
                                COLUMN_RECORDING_LANGUAGE_LANGUAGE_ID " INTEGER REFERENCES " TABLE_LANGUAGE "(" COLUMN_LANGUAGE_ID "),"
                                COLUMN_RECORDING_LANGUAGE_RECORDING_ID " INTEGER REFERENCES " TABLE_RECORDING "(" COLUMN_RECORDING_ID "),"
                                "PRIMARY KEY(" COLUMN_RECORDING_LANGUAGE_LANGUAGE_ID ", " COLUMN_RECORDING_LANGUAGE_RECORDING_ID "));");

// 2385
    if (!database.TableExists(TABLE_RELEASE))
        database.ExecuteUpdate("CREATE TABLE " TABLE_RELEASE "("
                                COLUMN_RELEASE_ID " INTEGER PRIMARY KEY AUTOINCREMENT,"
                                COLUMN_RELEASE_ARTIST_CREDIT_ID " INTEGER REFERENCES " TABLE_ARTIST_CREDIT "(" COLUMN_ARTIST_CREDIT_ID "),"
                                COLUMN_RELEASE_GID " VARCHAR(128),"
                                COLUMN_RELEASE_NAME " VARCHAR(256) NOT NULL DEFAULT '',"
                                COLUMN_RELEASE_DATE_YEAR " INTEGER NOT NULL DEFAULT -1 CHECK (" COLUMN_RELEASE_DATE_YEAR " >=-1));");// INTEGER

    if (!database.TableExists(TABLE_RELEASE_TYPE))
        database.ExecuteUpdate("CREATE TABLE " TABLE_RELEASE_TYPE "("
                                COLUMN_RELEASE_TYPE_ID " INTEGER PRIMARY KEY AUTOINCREMENT,"
                                COLUMN_RELEASE_TYPE_NAME " VARCHAR(256) NOT NULL DEFAULT '');");

    if (!database.TableExists(TABLE_JOIN_RELEASE_TYPE))
        database.ExecuteUpdate("CREATE TABLE " TABLE_JOIN_RELEASE_TYPE "("
                                COLUMN_JOIN_RELEASE_TYPE_RELEASE_ID " INTEGER REFERENCES " TABLE_RELEASE "(" COLUMN_RELEASE_ID "),"
                                COLUMN_JOIN_RELEASE_TYPE_TYPE_ID " INTEGER REFERENCES " TABLE_RELEASE_TYPE "(" COLUMN_RELEASE_TYPE_ID "),"
                                "PRIMARY KEY(" COLUMN_JOIN_RELEASE_TYPE_RELEASE_ID ", " COLUMN_JOIN_RELEASE_TYPE_TYPE_ID "));");

    if (!database.TableExists(TABLE_TRACK))
        database.ExecuteUpdate("CREATE TABLE " TABLE_TRACK "("
                                COLUMN_TRACK_ID " INTEGER PRIMARY KEY AUTOINCREMENT,"
                                COLUMN_TRACK_RECORDING_ID " INTEGER REFERENCES " TABLE_RECORDING "(" COLUMN_RECORDING_ID "),"
                                COLUMN_TRACK_RELEASE_ID " INTEGER REFERENCES " TABLE_RELEASE "(" COLUMN_RELEASE_ID "),"
                                COLUMN_TRACK_GID " VARCHAR(128),"
                                COLUMN_TRACK_POSITION " INTEGER,"
                                COLUMN_TRACK_NUMBER " INTEGER NOT NULL DEFAULT 0 CHECK (" COLUMN_TRACK_NUMBER " >=0));");

    // Physical data

    if (!database.TableExists(TABLE_COMPUTER))
        database.ExecuteUpdate("CREATE TABLE " TABLE_COMPUTER "("
                                COLUMN_COMPUTER_ID " INTEGER PRIMARY KEY AUTOINCREMENT,"
                                COLUMN_COMPUTER_NAME " VARCHAR(256) NOT NULL,"
                                COLUMN_COMPUTER_LAST_KNOWN_IP_ADDRESS " VARCHAR(40) NOT NULL,"
                                COLUMN_COMPUTER_LAST_UPDATE " DATETIME);");

    if (!database.TableExists(TABLE_PHYSICAL_RECORDING))
        database.ExecuteUpdate("CREATE TABLE " TABLE_PHYSICAL_RECORDING "("
                                COLUMN_PHYSICAL_RECORDING_ID " INTEGER PRIMARY KEY AUTOINCREMENT,"
                                COLUMN_PHYSICAL_RECORDING_RECORD_ID " INTEGER,"
                                COLUMN_PHYSICAL_RECORDING_COMPUTER_ID " INTEGER REFERENCES " TABLE_COMPUTER "(" COLUMN_COMPUTER_ID ") NOT NULL,"
                                COLUMN_PHYSICAL_RECORDING_FILENAME "  VARCHAR(512) NOT NULL);");

    if (!database.TableExists(TABLE_PHYSICAL_RECORDING_DELETED))
        database.ExecuteUpdate("CREATE TABLE " TABLE_PHYSICAL_RECORDING_DELETED "("
                                COLUMN_PHYSICAL_RECORDING_DELETED_ID " INTEGER PRIMARY KEY AUTOINCREMENT,"
                                COLUMN_PHYSICAL_RECORDING_DELETED_GID " VARCHAR(128) NOT NULL DEFAULT '',"
                                COLUMN_PHYSICAL_RECORDING_DELETED_FILENAME " VARCHAR(512) NOT NULL,"
                                COLUMN_PHYSICAL_RECORDING_DELETED_DATE " DATETIME);");

    if (!database.TableExists(TABLE_PHYSICAL_RECORDING_RENAMED))
        database.ExecuteUpdate("CREATE TABLE " TABLE_PHYSICAL_RECORDING_RENAMED "("
                                COLUMN_PHYSICAL_RECORDING_RENAMED_ID " INTEGER PRIMARY KEY AUTOINCREMENT,"
                                COLUMN_PHYSICAL_RECORDING_RENAMED_GID " VARCHAR(128) NOT NULL DEFAULT '',"
                                COLUMN_PHYSICAL_RECORDING_RENAMED_OLD_FILENAME " VARCHAR(512),"
                                COLUMN_PHYSICAL_RECORDING_RENAMED_NEW_FILENAME " VARCHAR(512) NOT NULL,"
                                COLUMN_PHYSICAL_RECORDING_RENAMED_DATE " DATETIME);");

    // Database management
    int lines = database.ExecuteScalar("SELECT COUNT(*) FROM " TABLE_META_DATA " WHERE " COLUMN_DATA_KEY " = '" COLUMN_DATA_KEY_LOCALHOST_ID "';");
    if (lines == 0)
    {
        wxString str1 = wxGetFullHostName();
        wxString str2 = wxGetHostName();
        database.ExecuteUpdate("INSERT INTO " TABLE_META_DATA " VALUES ('" COLUMN_DATA_KEY_LOCALHOST_ID "','1')");
        database.ExecuteUpdate("INSERT INTO " TABLE_COMPUTER "(" COLUMN_COMPUTER_NAME ", " COLUMN_COMPUTER_LAST_KNOWN_IP_ADDRESS ", " COLUMN_COMPUTER_LAST_UPDATE ") VALUES ('', 'localhost', datetime('now'))");
    }

    return targetVersion;
}

