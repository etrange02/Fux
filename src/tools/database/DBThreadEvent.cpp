/***************************************************************
 * Name:      DBThreadEvent.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2016-03-11
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "DBThreadEvent.h"
#include "DataBaseResponse.h"

wxDEFINE_EVENT(wxEVT_DB_THREAD, wxThreadEvent);

/** @brief Constructor.
 */
DBThreadEvent::DBThreadEvent(wxEventType eventType, int id) :
    wxThreadEvent(eventType, id),
    m_response(NULL)
{
}

/** @brief Copy constructor.
 *
 * @param other const DBThreadEvent&
 *
 */
DBThreadEvent::DBThreadEvent(const DBThreadEvent& other) :
    wxThreadEvent(other)
{
    m_response = other.m_response;
}

/** @brief Destructor.
 */
DBThreadEvent::~DBThreadEvent()
{
    delete m_response;
}

/** @brief Overloads.
 *
 * @return wxEvent*
 *
 */
wxEvent* DBThreadEvent::Clone() const
{
    return new DBThreadEvent(*this);
}

void DBThreadEvent::setResponse(tools::database::DataBaseResponse* response)
{
    m_response = response;
}

/** @brief Returns the response associated with
 *
 * @return tools::database::DataBaseResponse*
 *
 */
tools::database::DataBaseResponse* DBThreadEvent::getResponse() const
{
    return m_response;
}

