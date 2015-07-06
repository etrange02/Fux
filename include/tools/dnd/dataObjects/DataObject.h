#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <wx/wx.h>
#include <wx/dnd.h>
#include "tools/dnd/dataObjects/TransitiveData.h"

namespace dragAndDrop
{
    class DataObject : public wxDataObject
    {
        public:
            /** Constructor */
            DataObject();
            DataObject(TransitiveData* data);
            /** Default destructor */
            virtual ~DataObject();

            virtual wxDataFormat GetPreferredFormat(Direction WXUNUSED(dir)) const;
            virtual size_t GetFormatCount(Direction WXUNUSED(dir)) const;
            virtual void GetAllFormats(wxDataFormat* formats, Direction WXUNUSED(dir)) const;
            virtual size_t GetDataSize(const wxDataFormat& format) const;
            virtual bool GetDataHere(const wxDataFormat& format, void* pBuf) const;
            virtual bool SetData(const wxDataFormat& format, size_t WXUNUSED(len), const void* buf);

            TransitiveData* getData() const;

        protected:
            DataObject& operator=(const DataObject& rhs);
            void setData(TransitiveData* data);

        private:
            TransitiveData* m_data;
            wxDataFormat m_format;
    };
}

#endif // DATAOBJECT_H
