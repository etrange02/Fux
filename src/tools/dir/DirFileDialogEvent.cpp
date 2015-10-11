/***************************************************************
 * Name:      DirFileDialogEvent.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-09-28
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "DirFileDialogEvent.h"
#include <wx/time.h>

#define TOOLS_DIR_FILE_DELTA_UPDATE 500

using namespace tools::dir;

const wxEventType wxEVT_TOOLS_DIR_FILE_CLOSE  = wxNewEventType();
const wxEventType wxEVT_TOOLS_DIR_FILE_RANGE  = wxNewEventType();
const wxEventType wxEVT_TOOLS_DIR_FILE_UPDATE = wxNewEventType();

DirFileDialogEvent::DirFileDialogEvent() :
    DirFileUserInterface(),
    m_dialog(NULL)
{
}

DirFileDialogEvent::DirFileDialogEvent(wxWindow* dialog) :
    DirFileUserInterface(),
    m_dialog(dialog)
{
}

DirFileDialogEvent::~DirFileDialogEvent()
{
}

void DirFileDialogEvent::setDialog(wxWindow* dialog)
{
    if (NULL == dialog)
        return;
    m_dialog = dialog;
}

void DirFileDialogEvent::close()
{
    if (NULL == m_dialog)
        return;

    wxCommandEvent evt(wxEVT_TOOLS_DIR_FILE_CLOSE);
    wxQueueEvent(m_dialog, evt.Clone());
}

void DirFileDialogEvent::setRange(int range)
{
    if (NULL == m_dialog)
        return;

    wxCommandEvent evt(wxEVT_TOOLS_DIR_FILE_RANGE);
    evt.SetInt(range);
    wxQueueEvent(m_dialog, evt.Clone());
}

void DirFileDialogEvent::update(int value)
{
    update(value, "");
}

void DirFileDialogEvent::update(int value, const wxString& message)
{
    if (NULL == m_dialog)
        return;

    wxLongLong now = wxGetUTCTimeMillis();
    if (now > m_lastUpdate + TOOLS_DIR_FILE_DELTA_UPDATE)
    {
        m_lastUpdate = now;
        wxCommandEvent evt(wxEVT_TOOLS_DIR_FILE_UPDATE);
        evt.SetInt(value);
        evt.SetString(message);
        wxQueueEvent(m_dialog, evt.Clone());
    }
}

