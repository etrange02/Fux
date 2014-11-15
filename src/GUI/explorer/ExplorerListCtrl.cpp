#include "../../../include/gui/explorer/ExplorerListCtrl.h"

/**
 * Constructor
 */
ExplorerListCtrl::ExplorerListCtrl(wxWindow *parent, wxWindowID id)
{
    Create(parent, id);
}

/**
 * Destructor
 */
ExplorerListCtrl::~ExplorerListCtrl()
{
    //dtor
}

void ExplorerListCtrl::Create(wxWindow* parent, wxWindowID id)
{
    wxListCtrl::Create(parent, id, wxDefaultPosition, wxDefaultSize, wxLC_REPORT |  wxLC_HRULES | wxLC_VRULES);
    InsertColumn(0, _("Nom"), wxLIST_FORMAT_CENTER, 400);
    InsertColumn(1, _("Type"), wxLIST_FORMAT_CENTER, 60);
}

void ExplorerListCtrl::addDir(wxString& dir)
{
    int pos = GetItemCount();
    pos = InsertItem(pos, dir);
    SetItem(pos, 1, _T("Dossier"));
    SetItemBackgroundColour(pos, wxColor(236, 150, 243));
    SetItemTextColour(pos, wxColor(255, 253, 151));
}

void ExplorerListCtrl::addFile(wxString& file)
{
    int pos = GetItemCount();
    int j = file.Find(wxFileName::GetPathSeparator(), true);
    pos = InsertItem(pos, file.Right(file.Length()-j-1));
    SetItem(pos, 1, file.AfterLast('.'));
}

void ExplorerListCtrl::addInexistantFile(wxString& file)
{
    int pos = GetItemCount();
    pos = InsertItem(pos, file);
    SetItem(pos, 1, _("Fichier inexistant"));
    SetItemTextColour(pos, wxColor(255, 255, 255));
    SetItemBackgroundColour(pos, wxColor(255, 0, 0));
}

void ExplorerListCtrl::addLine(wxString& name, wxString& type)
{
    int pos = GetItemCount();
    pos = InsertItem(pos, name);
    SetItem(pos, 1, type);
}


