#ifndef EXPLORERLISTCTRL_H
#define EXPLORERLISTCTRL_H

#include "Define.h"
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/filename.h>
#include <vector>

namespace gui
{
    namespace explorer
    {
        class ExplorerListCtrl : public wxListCtrl
        {
            public:
                ExplorerListCtrl(wxWindow *parent, wxWindowID id);
                virtual ~ExplorerListCtrl();

                void addDir(const wxString& dir);
                void addFile(const wxString& file);
                void addInexistantFile(const wxString& file);
                void addLine(const wxString& name, const wxString& type);
                void addLine(wxString& name, wxString& type);

                void selectLine(const wxString& text);
                void selectLine(const long line);

                std::vector<unsigned long> getSelectedLines();
                void removeSelectedLines();

            protected:
                void Create();
                int addItem(const wxString& name, const wxString& kind);
                int addItem(const wxString& name, const wxString& kind, const wxColor& foreground, const wxColor& background);
            private:
        };
    }
}

#endif // EXPLORERLISTCTRL_H
