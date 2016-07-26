/***************************************************************
 * Name:      DirFileManager.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-08-07
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "Mediator.h"

Mediator::Mediator() :
    m_dirFileManager(NULL),
    m_dirFileDialog(NULL)
{
    //ctor
}

Mediator::~Mediator()
{
    delete m_dirFileManager;
}

void Mediator::setDirFileManager(tools::dir::DirFileManager* manager)
{
    delete m_dirFileManager;
    m_dirFileManager = manager;
}

tools::dir::DirFileManager& Mediator::getDirFileManager()
{
    return *m_dirFileManager;
}

tools::dir::DirFileDialog& Mediator::getDirFileDialog()
{
    return m_dirFileDialog;
}

explorer::ExplorerDriveManagers& Mediator::getExplorerDriveManagers()
{
    return m_explorerDriveManagers;
}

tools::database::DataBaseManager& Mediator::getDatabase()
{
    return m_database;
}

