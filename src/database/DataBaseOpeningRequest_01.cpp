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
    tools::database::DataBaseOpeningRequest::updateTables(database, currentVersion);

    const int targetVersion = 1;
    if (currentVersion >= targetVersion)
        return targetVersion;

    if (!database.TableExists(TABLE_ARTIST_CREDIT))
        database.ExecuteUpdate("CREATE TABLE " TABLE_ARTIST_CREDIT "("
                                COLUMN_ARTIST_CREDIT_ID " INTEGER PRIMARY KEY AUTOINCREMENT,"
                                COLUMN_ARTIST_CREDIT_NAME " TEXT NOT NULL DEFAULT '',"
                                COLUMN_ARTIST_CREDIT_ARTIST_COUNT " INTEGER NOT NULL DEFAULT 0 CHECK(" COLUMN_ARTIST_CREDIT_ARTIST_COUNT ">=0));"); // INTEGER

    if (!database.TableExists(TABLE_GENDER))
        database.ExecuteUpdate("CREATE TABLE " TABLE_GENDER "("
                                COLUMN_GENDER_ID " INTEGER PRIMARY KEY AUTOINCREMENT,"
                                COLUMN_GENDER_NAME " TEXT NOT NULL DEFAULT '');");

    if (!database.TableExists(TABLE_ARTIST_TYPE))
        database.ExecuteUpdate("CREATE TABLE " TABLE_ARTIST_TYPE "("
                                COLUMN_ARTIST_TYPE_ID " INTEGER PRIMARY KEY AUTOINCREMENT,"
                                COLUMN_ARTIST_TYPE_NAME " TEXT NOT NULL DEFAULT '');");

    if (!database.TableExists(TABLE_ARTIST))
        database.ExecuteUpdate("CREATE TABLE " TABLE_ARTIST "("
                                COLUMN_ARTIST_ID " INTEGER PRIMARY KEY AUTOINCREMENT,"
                                COLUMN_ARTIST_GID " TEXT,"
                                COLUMN_ARTIST_NAME " TEXT NOT NULL DEFAULT ''," // NOT NULL
                                COLUMN_ARTIST_SORT_NAME " TEXT NOT NULL DEFAULT '',"
                                COLUMN_ARTIST_TYPE " INTEGER REFERENCES " TABLE_ARTIST_TYPE "(" COLUMN_ARTIST_TYPE_ID "),"
                                COLUMN_ARTIST_GENDER " INTEGER REFERENCES " TABLE_GENDER "(" COLUMN_GENDER_ID "));");

    if (!database.TableExists(TABLE_ARTIST_CREDIT_NAME))
        database.ExecuteUpdate("CREATE TABLE " TABLE_ARTIST_CREDIT_NAME "("
                                COLUMN_ARTIST_CREDIT_NAME_ARTIST_CREDIT " INTEGER REFERENCES " TABLE_ARTIST_CREDIT "(" COLUMN_ARTIST_CREDIT_ID "),"
                                COLUMN_ARTIST_CREDIT_NAME_POSITION " INTEGER NOT NULL," // INTEGER
                                COLUMN_ARTIST_CREDIT_NAME_ARTIST " INTEGER REFERENCES " TABLE_ARTIST "(" COLUMN_ARTIST_ID "),"
                                COLUMN_ARTIST_CREDIT_NAME_NAME " TEXT NOT NULL DEFAULT '',"
                                "PRIMARY KEY(" COLUMN_ARTIST_CREDIT_NAME_ARTIST_CREDIT "," COLUMN_ARTIST_CREDIT_NAME_POSITION "));");

    if (!database.TableExists(TABLE_RECORDING))
        database.ExecuteUpdate("CREATE TABLE " TABLE_RECORDING "("
                                COLUMN_RECORDING_ID " INTEGER PRIMARY KEY AUTOINCREMENT,"
                                COLUMN_RECORDING_GID " INTEGER,"
                                COLUMN_RECORDING_ARTIST_CREDIT " INTEGER REFERENCES " TABLE_ARTIST_CREDIT "(" COLUMN_ARTIST_CREDIT_ID "),"
                                COLUMN_RECORDING_NAME " TEXT NOT NULL DEFAULT '',"
                                COLUMN_RECORDING_FILENAME " TEXT NOT NULL DEFAULT '');");

    if (!database.TableExists(TABLE_HOSTNAME))
        database.ExecuteUpdate("CREATE TABLE " TABLE_HOSTNAME "("
                                COLUMN_HOSTNAME_ID " INTEGER PRIMARY KEY AUTOINCREMENT,"
                                COLUMN_HOSTNAME_NAME " TEXT NOT NULL DEFAULT '',"
                                COLUMN_HOSTNAME_LAST_KNOWN_IP_ADDRESS " TEXT NOT NULL DEFAULT '');");

    if (!database.TableExists(TABLE_RECORDING_ON_LAN))
        database.ExecuteUpdate("CREATE TABLE " TABLE_RECORDING_ON_LAN "("
                                COLUMN_RECORDING_ON_LAN_RECORDING " INTEGER REFERENCES " TABLE_RECORDING "(" COLUMN_RECORDING_GID "),"
                                COLUMN_RECORDING_ON_LAN_HOSTNAME " INTEGER REFERENCES " TABLE_HOSTNAME "(" COLUMN_HOSTNAME_ID "),"
                                COLUMN_RECORDING_ON_LAN_FILENAME " TEXT NOT NULL DEFAULT '',"
                                "PRIMARY KEY(" COLUMN_RECORDING_ON_LAN_RECORDING "," COLUMN_RECORDING_ON_LAN_HOSTNAME "));");

    if (!database.TableExists(TABLE_WORK_TYPE))
        database.ExecuteUpdate("CREATE TABLE " TABLE_WORK_TYPE "("
                                COLUMN_WORK_TYPE_ID " INTEGER PRIMARY KEY AUTOINCREMENT,"
                                COLUMN_WORK_TYPE_NAME " TEXT NOT NULL DEFAULT '');");
    // 2852
    if (!database.TableExists(TABLE_WORK))
        database.ExecuteUpdate("CREATE TABLE " TABLE_WORK "("
                                COLUMN_WORK_ID " INTEGER PRIMARY KEY AUTOINCREMENT,"
                                COLUMN_WORK_GID " TEXT,"
                                COLUMN_WORK_TYPE " INTEGER REFERENCES " TABLE_WORK_TYPE "(" COLUMN_WORK_TYPE_ID "),"
                                COLUMN_WORK_NAME " TEXT NOT NULL DEFAULT '');");
    // 1911
    if (!database.TableExists(TABLE_LANGUAGE))
        database.ExecuteUpdate("CREATE TABLE " TABLE_LANGUAGE "("
                                COLUMN_LANGUAGE_ID " INTEGER PRIMARY KEY AUTOINCREMENT,"
                                COLUMN_LANGUAGE_NAME " TEXT NOT NULL DEFAULT '');");

    if (!database.TableExists(TABLE_MEDIUM_FORMAT))
        database.ExecuteUpdate("CREATE TABLE " TABLE_MEDIUM_FORMAT "("
                                COLUMN_MEDIUM_FORMAT_ID " INTEGER PRIMARY KEY AUTOINCREMENT,"
                                COLUMN_MEDIUM_FORMAT_NAME " TEXT NOT NULL DEFAULT '');");
    // 2385
    if (!database.TableExists(TABLE_RELEASE))
        database.ExecuteUpdate("CREATE TABLE " TABLE_RELEASE "("
                                COLUMN_RELEASE_ID " INTEGER PRIMARY KEY AUTOINCREMENT,"
                                COLUMN_RELEASE_GID " TEXT,"
                                COLUMN_RELEASE_RELEASE_GROUP " INTEGER REFERENCES " TABLE_RECORDING "(" COLUMN_RECORDING_ID "),"
                                COLUMN_RELEASE_ARTIST_CREDIT " INTEGER REFERENCES " TABLE_ARTIST_CREDIT "(" COLUMN_ARTIST_CREDIT_ID "),"
                                COLUMN_RELEASE_DATE_YEAR " INTEGER NOT NULL DEFAULT -1 CHECK (" COLUMN_RELEASE_DATE_YEAR " >=-1));");// INTEGER

    if (!database.TableExists(TABLE_MEDIUM))
        database.ExecuteUpdate("CREATE TABLE " TABLE_MEDIUM "("
                                COLUMN_MEDIUM_ID " INTEGER PRIMARY KEY AUTOINCREMENT,"
                                COLUMN_MEDIUM_RELEASE " INTEGER REFERENCES " TABLE_RELEASE "(" COLUMN_RELEASE_ID "),"
                                COLUMN_MEDIUM_POSITION " INTEGER,"
                                COLUMN_MEDIUM_NAME " TEXT NOT NULL DEFAULT '',"
                                COLUMN_MEDIUM_TRACK_COUNT " INTEGER,"
                                COLUMN_MEDIUM_FORMAT " INTEGER REFERENCES " TABLE_MEDIUM_FORMAT "(" COLUMN_MEDIUM_FORMAT_ID "));");
    // 2794
    if (!database.TableExists(TABLE_TRACK))
        database.ExecuteUpdate("CREATE TABLE " TABLE_TRACK "("
                                COLUMN_TRACK_ID " INTEGER PRIMARY KEY AUTOINCREMENT,"
                                COLUMN_TRACK_GID " TEXT,"
                                COLUMN_TRACK_RECORDING " INTEGER REFERENCES " TABLE_RECORDING "(" COLUMN_RECORDING_ID "),"
                                COLUMN_TRACK_MEDIUM " INTEGER REFERENCES " TABLE_MEDIUM "(" COLUMN_MEDIUM_ID "),"
                                COLUMN_TRACK_POSITION " INTEGER,"
                                COLUMN_TRACK_NUMBER " INTEGER,"
                                COLUMN_TRACK_NAME " TEXT NOT NULL DEFAULT '',"
                                COLUMN_TRACK_ARTIST_CREDIT " INTEGER REFERENCES " TABLE_ARTIST_CREDIT "(" COLUMN_ARTIST_CREDIT_ID "));");
    // 2636
    if (!database.TableExists(TABLE_RELEASE_GROUP_PRIMARY_TYPE))
        database.ExecuteUpdate("CREATE TABLE " TABLE_RELEASE_GROUP_PRIMARY_TYPE "("
                                COLUMN_RELEASE_GROUP_PRIMARY_TYPE_ID " INTEGER PRIMARY KEY AUTOINCREMENT,"
                                COLUMN_RELEASE_GROUP_PRIMARY_TYPE_TYPE " TEXT NOT NULL DEFAULT '');");
    // 2540
    if (!database.TableExists(TABLE_RELEASE_GROUP))
        database.ExecuteUpdate("CREATE TABLE " TABLE_RELEASE_GROUP "("
                                COLUMN_RELEASE_GROUP_ID " INTEGER PRIMARY KEY AUTOINCREMENT,"
                                COLUMN_RELEASE_GROUP_GID " INTEGER,"
                                COLUMN_RELEASE_GROUP_NAME " TEXT NOT NULL DEFAULT '',"
                                COLUMN_RELEASE_GROUP_ARTIST_CREDIT " INTEGER REFERENCES " TABLE_ARTIST_CREDIT "(" COLUMN_ARTIST_CREDIT_ID "),"
                                COLUMN_RELEASE_GROUP_TYPE " INTEGER REFERENCES " TABLE_RELEASE_GROUP_PRIMARY_TYPE "(" COLUMN_RELEASE_GROUP_PRIMARY_TYPE_ID "));");
    // 2644
    if (!database.TableExists(TABLE_RELEASE_GROUP_SECONDARY_TYPE))
        database.ExecuteUpdate("CREATE TABLE " TABLE_RELEASE_GROUP_SECONDARY_TYPE "("
                                COLUMN_RELEASE_GROUP_SECONDARY_TYPE_ID " INTEGER PRIMARY KEY AUTOINCREMENT,"
                                COLUMN_RELEASE_GROUP_SECONDARY_TYPE_TYPE " TEXT NOT NULL DEFAULT '');");
    // 2652
    if (!database.TableExists(TABLE_RELEASE_GROUP_SECONDARY_TYPE_JOIN))
        database.ExecuteUpdate("CREATE TABLE " TABLE_RELEASE_GROUP_SECONDARY_TYPE_JOIN "("
                                COLUMN_RELEASE_GROUP_SECONDARY_TYPE_JOIN_RELEASE_GROUP " INTEGER REFERENCES " TABLE_RELEASE_GROUP "(" COLUMN_RELEASE_GROUP_ID "),"
                                COLUMN_RELEASE_GROUP_SECONDARY_TYPE_JOIN_SECONDARY_TYPE " INTEGER REFERENCES " TABLE_RELEASE_GROUP_SECONDARY_TYPE "(" COLUMN_RELEASE_GROUP_SECONDARY_TYPE_ID "),"
                                "PRIMARY KEY(" COLUMN_RELEASE_GROUP_SECONDARY_TYPE_JOIN_RELEASE_GROUP ", " COLUMN_RELEASE_GROUP_SECONDARY_TYPE_JOIN_SECONDARY_TYPE "));");

    return targetVersion;
}

