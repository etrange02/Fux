/***************************************************************
 * Name:      BDDThreadEvent.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2012-07-28
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../../include/db/BDDThreadEvent.h"

IMPLEMENT_DYNAMIC_CLASS(BDDThreadEvent, wxEvent)
DEFINE_EVENT_TYPE(wxEVT_BDDTHREAD_RESULTAT)

BDDThreadEvent::BDDThreadEvent(wxWindow* win)
{
	SetEventType(wxEVT_BDDTHREAD_RESULTAT);
	SetEventObject(win);
	m_array = NULL;
}

BDDThreadEvent::~BDDThreadEvent()
{
    if (m_array)
    {
        m_array->Clear();
        delete m_array;
    }
}

wxArrayString* BDDThreadEvent::GetArrayString()
{
    return m_array;
}

void BDDThreadEvent::SetArrayString(wxArrayString *arrayS)
{
    m_array = arrayS;
}

