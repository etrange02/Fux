#ifndef TRANSITIVEDATATARGET_H
#define TRANSITIVEDATATARGET_H

#include <wx/wx.h>
#include <wx/dnd.h>

namespace dragAndDrop
{
    class TransitiveDataTarget : public wxDropTarget
    {
        public:
            /** Default constructor */
            TransitiveDataTarget();
            /** Default destructor */
            virtual ~TransitiveDataTarget();
            virtual wxDragResult OnDragOver(wxCoord, wxCoord, wxDragResult);
            virtual wxDragResult OnData(wxCoord, wxCoord, wxDragResult);

        protected:
        private:
    };
}

#endif // TRANSITIVEDATATARGET_H
