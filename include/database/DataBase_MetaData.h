#ifndef DATABASE_METADATA_H_INCLUDED
#define DATABASE_METADATA_H_INCLUDED

//#define TCOL(x) "\"" + x + "\""

#define DataBaseName "fux.db"

#define TABLE_ARTIST_CREDIT "artist_credit"
#define COLUMN_ARTIST_CREDIT_ID "id"
#define COLUMN_ARTIST_CREDIT_NAME "name"
#define COLUMN_ARTIST_CREDIT_ARTIST_COUNT "artist_count"

#define TABLE_GENDER "gender"
#define COLUMN_GENDER_ID "id"
#define COLUMN_GENDER_NAME "name"

#define TABLE_ARTIST_TYPE "artist_type"
#define COLUMN_ARTIST_TYPE_ID "id"
#define COLUMN_ARTIST_TYPE_NAME "name"

#define TABLE_ARTIST "artist"
#define COLUMN_ARTIST_ID "id"
#define COLUMN_ARTIST_GID "gid"
#define COLUMN_ARTIST_NAME "name"
#define COLUMN_ARTIST_SORT_NAME "sort_name"
#define COLUMN_ARTIST_TYPE "type"
#define COLUMN_ARTIST_GENDER "gender"

#define TABLE_ARTIST_CREDIT_NAME "artist_credit_name"
#define COLUMN_ARTIST_CREDIT_NAME_ARTIST_CREDIT "artist_credit"
#define COLUMN_ARTIST_CREDIT_NAME_POSITION "position"
#define COLUMN_ARTIST_CREDIT_NAME_ARTIST "artist"
#define COLUMN_ARTIST_CREDIT_NAME_NAME "name"

#define TABLE_RECORDING "recording"
#define COLUMN_RECORDING_ID "id"
#define COLUMN_RECORDING_GID "gid"
#define COLUMN_RECORDING_ARTIST_CREDIT "artist_credit"
#define COLUMN_RECORDING_NAME "name"
#define COLUMN_RECORDING_FILENAME "filename"

#define TABLE_HOSTNAME "hostname"
#define COLUMN_HOSTNAME_ID "id"
#define COLUMN_HOSTNAME_NAME "name"
#define COLUMN_HOSTNAME_LAST_KNOWN_IP_ADDRESS "last_known_ip_address"

#define TABLE_RECORDING_ON_LAN "recording_on_lan"
#define COLUMN_RECORDING_ON_LAN_RECORDING "recording_gid"
#define COLUMN_RECORDING_ON_LAN_HOSTNAME "hostname"
#define COLUMN_RECORDING_ON_LAN_FILENAME "filename"

#define TABLE_WORK_TYPE "work_type"
#define COLUMN_WORK_TYPE_ID "id"
#define COLUMN_WORK_TYPE_NAME "name"

#define TABLE_WORK "work"
#define COLUMN_WORK_ID "id"
#define COLUMN_WORK_GID "gid"
#define COLUMN_WORK_TYPE "type"
#define COLUMN_WORK_NAME "name"

#define TABLE_LANGUAGE "language"
#define COLUMN_LANGUAGE_ID "id"
#define COLUMN_LANGUAGE_NAME "name"

#define TABLE_MEDIUM_FORMAT "medium_format"
#define COLUMN_MEDIUM_FORMAT_ID "id"
#define COLUMN_MEDIUM_FORMAT_NAME "name"

#define TABLE_MEDIUM "medium"
#define COLUMN_MEDIUM_ID "id"
#define COLUMN_MEDIUM_RELEASE "release"
#define COLUMN_MEDIUM_POSITION "position"
#define COLUMN_MEDIUM_NAME "name"
#define COLUMN_MEDIUM_TRACK_COUNT "track_count"
#define COLUMN_MEDIUM_FORMAT "format"

#define TABLE_TRACK "track"
#define COLUMN_TRACK_ID "id"
#define COLUMN_TRACK_GID "gid"
#define COLUMN_TRACK_RECORDING "recording"
#define COLUMN_TRACK_MEDIUM "medium"
#define COLUMN_TRACK_POSITION "position"
#define COLUMN_TRACK_NUMBER "number"
#define COLUMN_TRACK_NAME "name"
#define COLUMN_TRACK_ARTIST_CREDIT "artist_credit"

#define TABLE_RELEASE "release"
#define COLUMN_RELEASE_ID "id"
#define COLUMN_RELEASE_GID "gid"
#define COLUMN_RELEASE_RELEASE_GROUP "release_group"
#define COLUMN_RELEASE_ARTIST_CREDIT "artist_credit"
#define COLUMN_RELEASE_DATE_YEAR "date_year"

#define TABLE_RELEASE_GROUP "release_group"
#define COLUMN_RELEASE_GROUP_ID "id"
#define COLUMN_RELEASE_GROUP_GID "gid"
#define COLUMN_RELEASE_GROUP_NAME "name"
#define COLUMN_RELEASE_GROUP_ARTIST_CREDIT "artist_credit"
#define COLUMN_RELEASE_GROUP_TYPE "type"

#define TABLE_RELEASE_GROUP_PRIMARY_TYPE "release_group_primary_type"
#define COLUMN_RELEASE_GROUP_PRIMARY_TYPE_ID "id"
#define COLUMN_RELEASE_GROUP_PRIMARY_TYPE_TYPE "type"

#define TABLE_RELEASE_GROUP_SECONDARY_TYPE "release_group_secondary_type"
#define COLUMN_RELEASE_GROUP_SECONDARY_TYPE_ID "id"
#define COLUMN_RELEASE_GROUP_SECONDARY_TYPE_TYPE "type"

#define TABLE_RELEASE_GROUP_SECONDARY_TYPE_JOIN "release_group_secondary_type_join"
#define COLUMN_RELEASE_GROUP_SECONDARY_TYPE_JOIN_RELEASE_GROUP "release_group"
#define COLUMN_RELEASE_GROUP_SECONDARY_TYPE_JOIN_SECONDARY_TYPE "secondary_type"

#endif // DATABASEMETADATA_H_INCLUDED
