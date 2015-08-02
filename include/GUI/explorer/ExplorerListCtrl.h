#ifndef EXPLORERLISTCTRL_H
#define EXPLORERLISTCTRL_H

#include "Define.h"
#include <wx/wx.h>
#include <wx/filename.h>
#include <vector>
#include "gui/tools/DroppedMarkedLineListCtrl.h"

namespace gui
{
    namespace explorer
    {
        class ExplorerPanel;

        class ExplorerListCtrl : public DroppedMarkedLineListCtrl
        {
            public:
                ExplorerListCtrl(ExplorerPanel *parent, wxWindowID id);
                virtual ~ExplorerListCtrl();

                void addDir(const wxString& dir);
                void addFile(const wxString& file);
                void addInexistantFile(const wxString& file);
                void addLine(const wxString& name, const wxString& type);
                void addLine(wxString& name, wxString& type);

                void selectLine(const wxString& text);
                void selectLine(const long line);
                void deselectLines();

                std::vector<unsigned long> getSelectedLines();
                void removeSelectedLines();

            protected:
                void Create();
                int addItem(const wxString& name, const wxString& kind);
                int addItem(const wxString& name, const wxString& kind, const wxColor& foreground, const wxColor& background);

                virtual void updateLines();

            private:
                ExplorerPanel& m_explorerPanel;
        };
    }
}

#endif // EXPLORERLISTCTRL_H
