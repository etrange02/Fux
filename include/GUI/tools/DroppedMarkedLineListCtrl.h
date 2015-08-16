#ifndef DROPPEDMARKEDLINELISTCTRL_H
#define DROPPEDMARKEDLINELISTCTRL_H

#include <wx/wx.h>
#include <wx/listctrl.h>

class DroppedMarkedLineListCtrl : public wxListCtrl
{
    public:
        /** Default constructor */
        DroppedMarkedLineListCtrl(wxWindow *parent, wxWindowID id, const wxPoint& point, const wxSize& size, const long style);
        /** Default destructor */
        virtual ~DroppedMarkedLineListCtrl();

        virtual void OnPaint(wxPaintEvent& event);
        virtual void OnKeyboardEvent(wxKeyEvent& event);
        virtual void OnErasedBackground(wxEraseEvent& event);

        long convertCoordToPosition(wxCoord y);
        void updateUI();
        void selectAll();
        virtual void updateLines() = 0;

    protected:
    private:
        void paint(wxPaintEvent& event);
        void renderTriangle(wxDC& dc, const int x, const int y, const int width);
        void renderLine(wxDC& dc, const int x, const int y, const int width, const int height);
        DECLARE_EVENT_TABLE()
};

#endif // DROPPEDMARKEDLINELISTCTRL_H
