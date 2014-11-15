#ifndef EXPLORERLISTCTRL_H
#define EXPLORERLISTCTRL_H

#include "../../Define.h"
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/filename.h>


class ExplorerListCtrl : public wxListCtrl
{
    public:
        ExplorerListCtrl(wxWindow *parent, wxWindowID id);
        virtual ~ExplorerListCtrl();

        void addDir(wxString& dir);
        void addFile(wxString& file);
        void addInexistantFile(wxString& file);
        void addLine(wxString& name, wxString& type);

    protected:
        void Create(wxWindow *parent, wxWindowID id);
    private:
};

#endif // EXPLORERLISTCTRL_H
