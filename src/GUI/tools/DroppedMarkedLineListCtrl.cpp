/***************************************************************
 * Name:      DroppedMarkedLineListCtrl.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-08-01
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "DroppedMarkedLineListCtrl.h"
#include <wx/dcbuffer.h>
#include "tools/dnd/targets/TransitiveDataTarget.h"

BEGIN_EVENT_TABLE(DroppedMarkedLineListCtrl, wxListCtrl)
    EVT_KEY_DOWN        (DroppedMarkedLineListCtrl::OnKeyboardEvent)
    EVT_PAINT           (DroppedMarkedLineListCtrl::OnPaint)
END_EVENT_TABLE()

DroppedMarkedLineListCtrl::DroppedMarkedLineListCtrl(wxWindow *parent, wxWindowID id, const wxPoint& point, const wxSize& size, const long style) :
    wxListCtrl(parent, id, point, size, style)
{
    //SetBackgroundStyle(wxBG_STYLE_PAINT);
}

DroppedMarkedLineListCtrl::~DroppedMarkedLineListCtrl()
{
    //dtor
}

void DroppedMarkedLineListCtrl::OnKeyboardEvent(wxKeyEvent& event)
{
    if (event.GetKeyCode() == 'A' && event.ControlDown())
        selectAll();
    else if ((event.GetKeyCode() == 'R' && event.ControlDown()) || event.GetKeyCode() == WXK_F5)
        updateLines();
    else
        event.Skip();
}

void DroppedMarkedLineListCtrl::OnPaint(wxPaintEvent& event)
{
    wxListCtrl::OnPaint(event);

    if (NULL == GetDropTarget())
        return;

    dragAndDrop::TransitiveDataTarget& dropTarget = static_cast<dragAndDrop::TransitiveDataTarget&>(*GetDropTarget());

    if (!dropTarget.isSignificantDroppedLine())
        return;

    long position = dropTarget.getOverDroppedLine();

    const bool isOverEnd = position >= GetItemCount();
    wxRect rectangle;
    if (isOverEnd)
        GetItemRect(GetItemCount()-1, rectangle);
    else
        GetItemRect(position, rectangle);

    const int y = (position >= GetItemCount()) ? rectangle.GetBottom()-1 : rectangle.GetTop();
    const int xOffset = 4;
    rectangle.x     += xOffset;
    rectangle.width -= xOffset;

    wxPaintDC bufferedDC(this);
    renderLine(bufferedDC, rectangle.x, y, rectangle.width, 2);
    if (!isOverEnd)
        renderTriangle(bufferedDC, rectangle.x, y, rectangle.width);
}

void DroppedMarkedLineListCtrl::renderLine(wxDC& dc, const int x, const int y, const int width, const int height)
{
    wxPen pen(wxColour(255, 97, 255));
    dc.SetPen(pen);

    wxRect rectangle(x, y, width, height);
    dc.DrawRectangle(rectangle);
}

void DroppedMarkedLineListCtrl::renderTriangle(wxDC& dc, const int x, const int y, const int width)
{
    wxPen pen(wxColour(255, 97, 255));
    wxBrush brush(wxColour(255, 97, 255));
    dc.SetPen(pen);
    dc.SetBrush(brush);

    wxPoint triangle[3];
    triangle[0].x = x  ; triangle[0].y = y+6;
    triangle[1].x = x+8; triangle[1].y = y;
    triangle[2].x = x  ; triangle[2].y = y-6;
    dc.DrawPolygon(3, triangle, 0, 0, wxWINDING_RULE);
}

long DroppedMarkedLineListCtrl::convertCoordToPosition(wxCoord y)
{
    long itemCount = GetItemCount();

    if (itemCount == 0)
        return 0;

    long position = 0;
    long min = GetTopItem();
    bool found = false;
    wxPoint point;
    //position du dernier item visible
    if (itemCount < GetCountPerPage() || itemCount >= (GetCountPerPage() + min))//Le dernier item est visible
    {
        wxRect rect;
        GetItemRect(itemCount-1, rect);//emplacement physique du dernier item
        if (rect.GetY() + rect.GetHeight() < y)//le relâchement de la souris est après le dernier item
            return itemCount;
        position = GetItemCount();
    }
    else
        position = min + GetCountPerPage();

    while (itemCount > 0 && position >= min && position > 0 && !found)//Recherche la position par rapport au bord supérieur de la case
    {
        --position;
        GetItemPosition(position, point);
        found = (y > point.y);
        --itemCount;
    }
    return position;
}

void DroppedMarkedLineListCtrl::updateUI()
{
    Refresh(false);
    Update();
}

void DroppedMarkedLineListCtrl::selectAll()
{
    SetItemState(-1, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
}

