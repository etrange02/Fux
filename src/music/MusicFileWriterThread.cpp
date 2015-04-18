/***************************************************************
 * Name:      MusicFileWriterThread.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-01-23
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "MusicFileWriterThread.h"

using namespace ::music;

const wxEventType wxEVT_FUX_MUSICFILE_WRITER_THREAD = wxNewEventType();

MusicFileWriterThread::MusicFileWriterThread(MusicFileWriter* musicFileWriter, wxWindow* parent) :
    m_musicFileWriter(musicFileWriter),
    m_parent(parent)
{
    //ctor
}

MusicFileWriterThread::~MusicFileWriterThread()
{
    delete m_musicFileWriter;
}

void MusicFileWriterThread::process()
{
    if (NULL == m_musicFileWriter)
        return;

    m_musicFileWriter->process();
    sendUpdatedLineEvent();
}

void MusicFileWriterThread::sendUpdatedLineEvent()
{
    if (NULL == m_parent)
        return;

    wxCommandEvent evt(wxEVT_FUX_MUSICFILE_WRITER_THREAD);
    evt.SetClientData(m_musicFileWriter->getMusic());
    wxQueueEvent(m_parent, evt.Clone());
}

