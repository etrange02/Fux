/***************************************************************
 * Name:      DataBaseResponse.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2016-03-08
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "DataBaseResponse.h"

using namespace tools::database;

/** @brief Default constructor.
 */
DataBaseResponse::DataBaseResponse() :
    m_isOK(false)
{
}

/** @brief Constructor.
 *
 * @param ok bool
 *
 */
DataBaseResponse::DataBaseResponse(bool ok) :
    m_isOK(ok)
{
}

/** @brief Constructor
 *
 * @param ok bool
 * @param message const wxString&
 *
 */
DataBaseResponse::DataBaseResponse(bool ok, const wxString& message) :
    m_isOK(ok),
    m_errorMessage(message)
{
}

/** @brief Destructor
 */
DataBaseResponse::~DataBaseResponse()
{
}

/** @brief Makes a deep copy of this instance. Must be called in overload of clone().
 * Be careful with shared memory between instances, in particular with wxString.
 * @param dest DataBaseResponse&
 * @return void
 *
 */
//void DataBaseResponse::copyTo(DataBaseResponse& dest) const
//{
//    dest.m_isOK = this->m_isOK;
//    dest.m_errorMessage = m_errorMessage.c_str(); // Deep copy
//}

/** @brief Indicates if the response associated to the request is in a good state.
 *
 * @return bool
 *
 */
bool DataBaseResponse::isOK() const
{
    return m_isOK;
}

/** @brief Modifies the status.
 *
 * @param ok bool
 * @return void
 *
 */
void DataBaseResponse::setOK(bool ok)
{
    m_isOK = ok;
}

/** @brief Kind of the response.
 *
 * @return virtual int
 *
 */
int DataBaseResponse::getKind() const
{
    return -1;
}

/** @brief Returns the error message.
 *
 * @return wxString&
 *
 */
const wxString& DataBaseResponse::getErrorMessage() const
{
    return m_errorMessage;
}

/** @brief Modifies the error message.
 *
 * @param message const wxString&
 * @return void
 *
 */
void DataBaseResponse::setErrorMessage(const wxString& message)
{
    m_errorMessage = message;
}

