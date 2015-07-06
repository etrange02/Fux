/***************************************************************
 * Name:      DataObject.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-07-03
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/dnd/dataObjects/DataObject.h"

using namespace dragAndDrop;

/** @brief Constructor.
 */
DataObject::DataObject() :
    wxDataObject(),
    m_data(NULL),
    m_format(_T("FuXDataObject"))
{
}

/** @brief Constructor.
 *
 * @param data TransitiveData*
 *
 */
DataObject::DataObject(TransitiveData* data) :
    wxDataObject(),
    m_data(data),
    m_format(_T("FuXDataObject"))
{
}

/** @brief Destructor.
 */
DataObject::~DataObject()
{
}

/** @brief Overloads.
 *
 * @param WXUNUSED(dir Direction
 * @return wxDataFormat
 *
 */
wxDataFormat DataObject::GetPreferredFormat(Direction WXUNUSED(dir)) const
{
    return m_format;
}

/** @brief Overloads.
 *
 * @param WXUNUSED(dir Direction
 * @return size_t
 *
 */
size_t DataObject::GetFormatCount(Direction WXUNUSED(dir)) const
{
    return 1;
}

/** @brief Overloads.
 *
 * @param formats wxDataFormat*
 * @param WXUNUSED(dir Direction
 * @return void
 *
 */
void DataObject::GetAllFormats(wxDataFormat* formats, Direction WXUNUSED(dir)) const
{
    formats[0] = m_format;
}

/** @brief Overloads.
 *
 * @param format const wxDataFormat&
 * @return size_t
 *
 */
size_t DataObject::GetDataSize(const wxDataFormat& format) const
{
    if (format == m_format)
        return sizeof(DataObject);
    return 0;
}

/** @brief Overloads.
 *
 * @param format const wxDataFormat&
 * @param pBuf void*
 * @return bool
 *
 */
bool DataObject::GetDataHere(const wxDataFormat& format, void* pBuf) const
{
    if (format == m_format)
    {
        *((DataObject*) pBuf) = *this;
        return true;
    }
    return false;
}

/** @brief Overloads.
 *
 * @param format const wxDataFormat&
 * @param WXUNUSED(len size_t
 * @return bool
 *
 */
bool DataObject::SetData(const wxDataFormat& format, size_t WXUNUSED(len), const void* buf)
{
    if (format == m_format)
    {
        DataObject* data = (DataObject*) buf;
        *this = *data;
        return true;
    }
    return false;
}

/** @brief Copy operator.
 *
 * @param rhs const DataObject&
 * @return DataObject&
 *
 */
DataObject& DataObject::operator=(const DataObject& rhs)
{
    if (this != &rhs)
    {
        setData(rhs.getData());
    }
    return *this;
}

/** @brief Returns the TransitiveData.
 *
 * @return TransitiveData*
 *
 */
TransitiveData* DataObject::getData() const
{
    return m_data;
}

/** @brief Modifies the TransitiveData.
 *
 * @param data TransitiveData*
 * @return void
 *
 */
void DataObject::setData(TransitiveData* data)
{
    m_data = data;
}



