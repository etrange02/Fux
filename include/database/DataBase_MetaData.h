#ifndef DATABASE_METADATA_H_INCLUDED
#define DATABASE_METADATA_H_INCLUDED

//#define TCOL(x) "\"" + x + "\""

/// Logical data
#define TABLE_ARTIST "artist"
#define COLUMN_ARTIST_ID "id"
#define COLUMN_ARTIST_GID "gid"
#define COLUMN_ARTIST_NAME "name"
#define COLUMN_ARTIST_SORT_NAME "sort_name"

#define TABLE_ARTIST_CREDIT "artist_credit"
#define COLUMN_ARTIST_CREDIT_ID "id"
#define COLUMN_ARTIST_CREDIT_NAME "name"
#define COLUMN_ARTIST_CREDIT_ARTIST_COUNT "artist_count"

#define TABLE_ARTIST_CREDIT_NAME "artist_credit_name"
#define COLUMN_ARTIST_CREDIT_NAME_ARTIST_ID "id_artist"
#define COLUMN_ARTIST_CREDIT_NAME_ARTIST_CREDIT "id_artist_credit"
#define COLUMN_ARTIST_CREDIT_NAME_POSITION "position"

#define TABLE_LANGUAGE "language"
#define COLUMN_LANGUAGE_ID "id"
#define COLUMN_LANGUAGE_NAME "name"

#define TABLE_WORK "work"
#define COLUMN_WORK_ID "id"
#define COLUMN_WORK_GID "gid"
#define COLUMN_WORK_NAME "name"

#define TABLE_RECORDING "recording"
#define COLUMN_RECORDING_ID "id"
#define COLUMN_RECORDING_ARTIST_CREDIT_ID "id_artist_credit"
#define COLUMN_RECORDING_WORK_ID "id_work"
#define COLUMN_RECORDING_GID "gid"
#define COLUMN_RECORDING_NAME "name"
#define COLUMN_RECORDING_YEAR "year"
#define COLUMN_RECORDING_ADDING_DATE "adding_date"

#define TABLE_RECORDING_LANGUAGE "recording_language"
#define COLUMN_RECORDING_LANGUAGE_LANGUAGE_ID "id_language"
#define COLUMN_RECORDING_LANGUAGE_RECORDING_ID "id_recording"

#define TABLE_RELEASE "release"
#define COLUMN_RELEASE_ID "id"
#define COLUMN_RELEASE_ARTIST_CREDIT_ID "id_artist_credit"
#define COLUMN_RELEASE_GID "gid"
#define COLUMN_RELEASE_NAME "name"
#define COLUMN_RELEASE_DATE_YEAR "date_year"

#define TABLE_RELEASE_TYPE "type"
#define COLUMN_RELEASE_TYPE_ID "id"
#define COLUMN_RELEASE_TYPE_NAME "name"

#define TABLE_JOIN_RELEASE_TYPE "release_type_join"
#define COLUMN_JOIN_RELEASE_TYPE_RELEASE_ID "id_release"
#define COLUMN_JOIN_RELEASE_TYPE_TYPE_ID "id_type"

#define TABLE_TRACK "track"
#define COLUMN_TRACK_ID "id"
#define COLUMN_TRACK_RECORDING_ID "id_recording"
#define COLUMN_TRACK_RELEASE_ID "id_release"
#define COLUMN_TRACK_GID "gid"
#define COLUMN_TRACK_NAME "name"
#define COLUMN_TRACK_POSITION "position"
#define COLUMN_TRACK_NUMBER "number"

/// Physical data
#define TABLE_COMPUTER "computer"
#define COLUMN_COMPUTER_ID "id"
#define COLUMN_COMPUTER_NAME "name"
#define COLUMN_COMPUTER_LAST_KNOWN_IP_ADDRESS "last_known_ip_address"
#define COLUMN_COMPUTER_LAST_UPDATE "last_update"

#define TABLE_PHYSICAL_RECORDING "physical_recording"
#define COLUMN_PHYSICAL_RECORDING_ID "id"
#define COLUMN_PHYSICAL_RECORDING_RECORD_ID "id_recording"
#define COLUMN_PHYSICAL_RECORDING_COMPUTER_ID "id_computer"
#define COLUMN_PHYSICAL_RECORDING_FILENAME "filename"

// Used to determine the local host ID. No column needed in TABLE_HOSTNAME
#define COLUMN_DATA_KEY_LOCALHOST_ID "id_localhost"

// To update other instances (on other platforms)
#define TABLE_PHYSICAL_RECORDING_DELETED "physical_recording_deleted"
#define COLUMN_PHYSICAL_RECORDING_DELETED_ID "id"
#define COLUMN_PHYSICAL_RECORDING_DELETED_GID "recording_gid"
#define COLUMN_PHYSICAL_RECORDING_DELETED_FILENAME "filename"
#define COLUMN_PHYSICAL_RECORDING_DELETED_DATE "creation_date"

#define TABLE_PHYSICAL_RECORDING_RENAMED "physical_recording_renamed"
#define COLUMN_PHYSICAL_RECORDING_RENAMED_ID "id"
#define COLUMN_PHYSICAL_RECORDING_RENAMED_GID "recording_id"
#define COLUMN_PHYSICAL_RECORDING_RENAMED_OLD_FILENAME "old_filename"
#define COLUMN_PHYSICAL_RECORDING_RENAMED_NEW_FILENAME "new_filename"
#define COLUMN_PHYSICAL_RECORDING_RENAMED_DATE "creation_date"

#endif // DATABASEMETADATA_H_INCLUDED
