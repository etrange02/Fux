#ifndef TRANSITIVEDATATARGET_H
#define TRANSITIVEDATATARGET_H

#include <wx/wx.h>
#include <wx/dnd.h>
#include "gui/tools/DroppedMarkedLineListCtrl.h"
#include "tools/dnd/dataObjects/TransitiveData.h"

namespace dragAndDrop
{
    class TransitiveDataTarget : public wxDropTarget
    {
        public:
            /** Default constructor */
            TransitiveDataTarget(DroppedMarkedLineListCtrl& source);
            /** Default destructor */
            virtual ~TransitiveDataTarget();
            virtual wxDragResult OnDragOver(wxCoord, wxCoord, wxDragResult);
            virtual wxDragResult OnData(wxCoord, wxCoord, wxDragResult);

            void setNoSignificantDroppedLine();
            bool isSignificantDroppedLine() const;
            long getOverDroppedLine() const;

            virtual bool OnDrop(wxCoord x, wxCoord y);
            virtual void OnLeave();

        protected:
            virtual bool isSameKind() const = 0;
            virtual void doCut(wxCoord y);
            void doCopy(wxCoord y);
            void doPaste(wxCoord y);

            virtual void doCopyProcessing(const wxArrayString& data, const long position) = 0;
            virtual void doCutProcessing(TransitiveData& transitiveData, const long position) = 0;

        private:

        protected:
            DroppedMarkedLineListCtrl& m_source;
            TransitiveData* m_data;

        private:
            bool m_isSignificantLine;
            long m_overDroppedLine;
    };
}

#endif // TRANSITIVEDATATARGET_H
