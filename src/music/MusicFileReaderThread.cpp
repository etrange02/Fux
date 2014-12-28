/***************************************************************
 * Name:      MusicFileReaderThread.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2014-12-27
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "MusicFileReaderThread.h"


/** @brief Constructor
 * Constructor
 * @param musicFileReader Delegate the work to
 *
 */
MusicFileReaderThread::MusicFileReaderThread(MusicFileReader* musicFileReader) :
    m_musicFileReader(musicFileReader)
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
}


