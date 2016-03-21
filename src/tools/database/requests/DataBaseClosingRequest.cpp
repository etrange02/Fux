/***************************************************************
 * Name:      DataBaseClosingRequest.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2016-03-16
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "DataBaseClosingRequest.h"
#include "DataBaseManager.h"
#include <wx/wxsqlite3.h>

using namespace tools::database;

/** @brief Constructor.
 */
DataBaseClosingRequest::DataBaseClosingRequest() :
    DataBaseRequest()
{
    setPriority(100);
}

/** @brief Destructor.
 */
DataBaseClosingRequest::~DataBaseClosingRequest()
{
    //dtor
}

/** @brief Overload.
 *
 * @param dataBaseManager DataBaseManager&
 * @return DataBaseResponse*
 *
 */
tools::database::DataBaseResponse* DataBaseClosingRequest::execute(tools::database::DataBaseManager& dataBaseManager)
{
    dataBaseManager.setDatabase(NULL);

    return NULL;
}
