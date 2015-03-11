/***************************************************************
 * Name:      ExplorerFactory.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-02-25
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "ExplorerFactory.h"
#include "DriveManagerState.h"
#include "DefaultDriveManagerState.h"
#include "DirDriveManagerState.h"
#include "FileDriveManagerState.h"
#include "PlaylistDriveManagerState.h"
#include "explorer/ExplorerManagerData.h"

using namespace explorer;

ExplorerFactory::ExplorerFactory()
{
    //ctor
}

ExplorerFactory::~ExplorerFactory()
{
    //dtor
}

DriveManagerState* ExplorerFactory::createDefaultDriveManagerState(ExplorerManagerData& data)
{
    return new DefaultDriveManagerState(data);
}

DriveManagerState* ExplorerFactory::createDirDriveManagerState(ExplorerManagerData& data)
{
    return new DirDriveManagerState(data);
}

DriveManagerState* ExplorerFactory::createFileDriveManagerState(ExplorerManagerData& data)
{
    return new FileDriveManagerState(data);
}

DriveManagerState* ExplorerFactory::createPlaylistDriveManagerState(ExplorerManagerData& data)
{
    return new PlaylistDriveManagerState(data);
}

