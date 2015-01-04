/***************************************************************
 * Name:      MusicFileReaderThread.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2014-12-27
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "MusicFileReaderThread.h"

const wxEventType wxEVT_FUX_MUSICFILE_READER_THREAD = wxNewEventType();

/** @brief Constructor
 * Constructor
 * @param musicFileReader Delegate the work to
 *
 */
MusicFileReaderThread::MusicFileReaderThread(MusicFileReader* musicFileReader, wxWindow* parent, int position) :
    m_musicFileReader(musicFileReader),
    m_parent(parent),
    m_position(position)
{
}

/** @brief Destructor
 */
MusicFileReaderThread::~MusicFileReaderThread()
{
    if (NULL != m_musicFileReader)
        delete m_musicFileReader;
}

/** @brief Process the work
 * Process the work
 * @return void
 *
 */
void MusicFileReaderThread::process()
{
    if (NULL == m_musicFileReader)
        return;

    m_musicFileReader->process();
    sendUpdatedLineEvent();
}

/** @brief Informs data has been updated for a Music located at a specific position
 *
 * @return void
 *
 */
void MusicFileReaderThread::sendUpdatedLineEvent()
{
    if (NULL == m_parent)
        return;

    wxCommandEvent evt(wxEVT_FUX_MUSICFILE_READER_THREAD);
    evt.SetInt(m_position);
    wxQueueEvent(m_parent, evt.Clone());
}


