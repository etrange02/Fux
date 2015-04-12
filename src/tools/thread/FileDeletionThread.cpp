/***************************************************************
 * Name:      FileDeletionThread.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2014-12-27
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "FileDeletionThread.h"
#include <wx/filename.h>
#include <algorithm>

using namespace tools::thread;

/** @brief
 *
 * @param files const wxArrayString&
 *
 */
FileDeletionThread::FileDeletionThread(const wxArrayString& files) :
    m_files(files)
{
    //ctor
}

/** @brief
 */
FileDeletionThread::~FileDeletionThread()
{
    //dtor
}

/** @brief Process the work
 * Process the work
 * @return void
 *
 */
void FileDeletionThread::process()
{
    for (wxArrayString::iterator iter = m_files.begin(); iter != m_files.end(); ++iter)
        wxFileName::Rmdir(*iter, wxPATH_RMDIR_RECURSIVE);
//    sendUpdatedLineEvent();
}

