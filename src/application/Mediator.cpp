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
    m_dirFileManager(m_dirFileDialogEvent)
{
    //ctor
}

Mediator::~Mediator()
{
    //dtor
}

tools::dir::DirFileManager& Mediator::getDirFileManager()
{
    return m_dirFileManager;
}

tools::dir::DirFileDialogEvent& Mediator::getDirFileDialogEvent()
{
    return m_dirFileDialogEvent;
}

tools::dir::DirFileDialog& Mediator::getDirFileDialog()
{
    return m_dirFileDialog;
}

explorer::ExplorerDriveManagers& Mediator::getExplorerDriveManagers()
{
    return m_explorerDriveManagers;
}

