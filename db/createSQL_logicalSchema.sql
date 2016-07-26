--==============================================================
-- Date de création :  20/07/2016 00:07:34
--==============================================================

--==============================================================
-- Table : ARTIST
--==============================================================
create table ARTIST (
ID                   INTEGER              not null,
SORT_NAME            VARCHAR(256),
NAME                 VARCHAR(256),
GID                  VARCHAR(128),
primary key (ID)
);

--==============================================================
-- Table : ARTIST_CREDIT
--==============================================================
create table ARTIST_CREDIT (
ID                   INTEGER              not null,
NAME                 VARCHAR(256)         not null,
COUNT                INTEGER,
primary key (ID)
);

--==============================================================
-- Table : ARTIST_CREDIT_NAME
--==============================================================
create table ARTIST_CREDIT_NAME (
ARTIST_ID            INTEGER              not null,
ARTIST_CREDIT_ID     INTEGER              not null,
POSITION             INTEGER,
primary key (ARTIST_ID, ARTIST_CREDIT_ID),
foreign key (ARTIST_ID)
      references ARTIST (ID),
foreign key (ARTIST_CREDIT_ID)
      references ARTIST_CREDIT (ID)
);

--==============================================================
-- Table : LANGUAGE
--==============================================================
create table LANGUAGE (
ID                   INTEGER              not null,
NAME                 VARCHAR(256)         not null,
primary key (ID)
);

--==============================================================
-- Table : WORK
--==============================================================
create table WORK (
ID                   INTEGER              not null,
GID                  VARCHAR(128)         not null,
NAME                 VARCHAR(256),
primary key (ID)
);

--==============================================================
-- Table : RECORDING
--==============================================================
create table RECORDING (
ID                   INTEGER              not null,
WORK_ID              INTEGER,
ARTIST_CREDIT_ID     INTEGER,
NAME                 VARCHAR(256)         not null,
GID                  VARCHAR(128),
YEAR                 INTEGER,
ADDING_DATE          DATE                 not null,
primary key (ID),
foreign key (ARTIST_CREDIT_ID)
      references ARTIST_CREDIT (ID),
foreign key (WORK_ID)
      references WORK (ID)
);

--==============================================================
-- Table : RECORDING_LANGUAGE
--==============================================================
create table RECORDING_LANGUAGE (
LANGUAGE_ID          INTEGER              not null,
RECORDING_ID         INTEGER              not null,
primary key (LANGUAGE_ID, RECORDING_ID),
foreign key (LANGUAGE_ID)
      references LANGUAGE (ID),
foreign key (RECORDING_ID)
      references RECORDING (ID)
);

--==============================================================
-- Table : RELEASE
--==============================================================
create table RELEASE (
ID                   INTEGER              not null,
ARTIST_CREDIT_ID     INTEGER              not null,
GID                  VARCHAR(128),
NAME                 VARCHAR(256),
YEAR                 INTEGER,
primary key (ID),
foreign key (ARTIST_CREDIT_ID)
      references ARTIST_CREDIT (ID)
);

--==============================================================
-- Table : TYPE
--==============================================================
create table TYPE (
ID                   INTEGER              not null,
NAME                 VARCHAR(256)         not null,
primary key (ID)
);

--==============================================================
-- Table : RELEASE_TYPE
--==============================================================
create table RELEASE_TYPE (
RELEASE_ID           INTEGER              not null,
TYPE_ID              INTEGER              not null,
primary key (RELEASE_ID, TYPE_ID),
foreign key (RELEASE_ID)
      references RELEASE (ID),
foreign key (TYPE_ID)
      references TYPE (ID)
);

--==============================================================
-- Table : TRACK
--==============================================================
create table TRACK (
ID                   INTEGER              not null,
RECORDING_ID         INTEGER              not null,
RELEASE_ID           INTEGER,
GID                  VARCHAR(128),
POSITION             INTEGER,
NUMBER               INTEGER              not null,
primary key (ID),
foreign key (RECORDING_ID)
      references RECORDING (ID),
foreign key (RELEASE_ID)
      references RELEASE (ID)
);
