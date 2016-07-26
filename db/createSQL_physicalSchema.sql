--==============================================================
-- Date de création :  21/07/2016 01:29:14
--==============================================================

--==============================================================
-- Table : COMPUTER
--==============================================================
create table COMPUTER (
ID                   INTEGER              not null,
NAME                 VARCHAR(256)         not null,
IP_ADDRESS           VARCHAR(40)          not null,
LAST_UPDATE          DATE,
primary key (ID)
);

--==============================================================
-- Table : PHYSICAL_RECORDING
--==============================================================
create table PHYSICAL_RECORDING (
ID                   INTEGER              not null,
ID_RECORDING         INTEGER,
COMPUTER_ID          INTEGER,
FILENAME             VARCHAR(512),
primary key (ID),
foreign key (COMPUTER_ID)
      references COMPUTER (ID)
);

--==============================================================
-- Table : PHYSICAL_RECORDING_DELETED
--==============================================================
create table PHYSICAL_RECORDING_DELETED (
RECORDING_GID        VARCHAR(512)         not null,
FILENAME             VARCHAR(512)         not null,
CREATION_DATE        DATE                 not null
);

--==============================================================
-- Table : PHYSICAL_RECORDING_RENAMED
--==============================================================
create table PHYSICAL_RECORDING_RENAMED (
RECORDING_ID         VARCHAR(512)         not null,
OLD_FILENAME         VARCHAR(512),
NEW_FILENAME         VARCHAR(512)         not null,
CREATION_DATE        DATE                 not null
);

