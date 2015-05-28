/***************************************************************
 * Name:      ExplorerListCtrl.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2014-11-19
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "ExplorerListCtrl.h"

using namespace gui::explorer;

/**
 * Constructor
 */
ExplorerListCtrl::ExplorerListCtrl(wxWindow *parent, wxWindowID id) :
    wxListCtrl(parent, id, wxDefaultPosition, wxDefaultSize, wxLC_REPORT |  wxLC_HRULES | wxLC_VRULES)
{
    Create();
}

/**
 * Destructor
 */
ExplorerListCtrl::~ExplorerListCtrl()
{
    //dtor
}

void ExplorerListCtrl::Create()
{
    InsertColumn(0, _("Nom"), wxLIST_FORMAT_CENTER, 400);
    InsertColumn(1, _("Type"), wxLIST_FORMAT_CENTER, 60);
    SetMinSize(wxSize(10, 10)); //< Allows the listctrl to be resized as little as we want
}

void ExplorerListCtrl::addDir(const wxString& dir)
{
    addItem(dir, _T("Dossier"), /*wxColor(236, 150, 243)*/wxColor(255, 255, 0), wxColor(130, 0, 236));
}

void ExplorerListCtrl::addFile(const wxString& file)
{
    addItem(file.AfterLast(wxFileName::GetPathSeparator()).BeforeLast('.'), file.AfterLast('.'));
}

void ExplorerListCtrl::addInexistantFile(const wxString& file)
{
    addItem(file, _("Fichier inexistant"), wxColor(255, 255, 255), wxColor(255, 0, 0));
}

void ExplorerListCtrl::addLine(const wxString& name, const wxString& type)
{
    addItem(name, type);
}

void ExplorerListCtrl::addLine(wxString& name, wxString& type)
{
    addItem(name, type);
}

int ExplorerListCtrl::addItem(const wxString& name, const wxString& kind)
{
    int pos = GetItemCount();
    pos = InsertItem(pos, name);
    SetItem(pos, 1, kind);
    return pos;
}

int ExplorerListCtrl::addItem(const wxString& name, const wxString& kind, const wxColor& foreground, const wxColor& background)
{
    int pos = addItem(name, kind);
    SetItemTextColour(pos, foreground);
    SetItemBackgroundColour(pos, background);
    return pos;
}

void ExplorerListCtrl::selectLine(const wxString& text)
{
    long lineToSelect = FindItem(-1, text);
    selectLine(lineToSelect);
}

void ExplorerListCtrl::selectLine(const long line)
{
    if (line < 0 || line >= GetItemCount())
        return;
    SetItemState(line, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED);
    EnsureVisible(line);
}

void ExplorerListCtrl::selectAll()
{
    SetItemState(-1, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
}

std::vector<unsigned long> ExplorerListCtrl::getSelectedLines()
{
    std::vector<unsigned long> selectedItemsPosition;
    long index = GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

    while (index != -1)
    {
        selectedItemsPosition.push_back(index);
        index = GetNextItem(index, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    }
    return selectedItemsPosition;
}

void ExplorerListCtrl::removeSelectedLines()
{
    long index = GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

    while (index != -1)
    {
        DeleteItem(index);
        index = GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    }
}

void ExplorerListCtrl::deselectLines()
{
    while (GetSelectedItemCount() > 0)
        SetItemState(GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED), 0, wxLIST_STATE_SELECTED);
}

