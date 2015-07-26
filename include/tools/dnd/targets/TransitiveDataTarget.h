#ifndef TRANSITIVEDATATARGET_H
#define TRANSITIVEDATATARGET_H

#include <wx/wx.h>
#include <wx/dnd.h>
#include <wx/listctrl.h>
#include "tools/dnd/dataObjects/TransitiveData.h"

namespace dragAndDrop
{
    class TransitiveDataTarget : public wxDropTarget
    {
        public:
            /** Default constructor */
            TransitiveDataTarget(const wxListCtrl& source);
            /** Default destructor */
            virtual ~TransitiveDataTarget();
            virtual wxDragResult OnDragOver(wxCoord, wxCoord, wxDragResult);
            virtual wxDragResult OnData(wxCoord, wxCoord, wxDragResult);

        protected:
            virtual bool isSameKind() const = 0;
            virtual void doCut(wxCoord y); // = 0
            void doCopy(wxCoord y);
            void doPaste(wxCoord y);

            long convertCoordToPosition(wxCoord y);
            virtual void doCopyProcessing(const wxArrayString& data, const long position) = 0;

        private:

        protected:
            const wxListCtrl& m_source;
            TransitiveData* m_data;
    };
}

#endif // TRANSITIVEDATATARGET_H
