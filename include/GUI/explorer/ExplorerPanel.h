#ifndef EXPLORERPANEL_H
#define EXPLORERPANEL_H

#include "../../Define.h"
#include <wx/wx.h>
#include <wx/statline.h>

#include "ExplorerListCtrl.h"
//#include "../../explorer/ExplorerManager.h" // Must be deactivated to compile, self-inclusion

class ExplorerManager;

class ExplorerPanel : public wxPanel
{
    public:
        /** Default constructor */
        ExplorerPanel(wxWindow* parent, wxWindowID id, wxWindowID idExplorerList, wxWindowID idPreviousButton, wxWindowID idRefreshButton, wxWindowID idTextField, wxWindowID idCheckBox, wxString& managerName, wxString& managerDescription);
        /** Default destructor */
        virtual ~ExplorerPanel();

        void SetExplorerManager(ExplorerManager* explorerManager);

    protected:
        void Create(wxWindow* parent, wxWindowID id, wxWindowID idExplorerList, wxWindowID idPreviousButton, wxWindowID idRefreshButton, wxWindowID idTextField, wxWindowID idCheckBox, wxString& managerName, wxString& managerDescription);

    private:
        ExplorerListCtrl *m_explorerList;
        ExplorerManager *m_explorerManager;

        wxStaticBoxSizer *m_sizer1V;
        wxSizer *m_sizer1H, *m_sizer2H;
        wxTextCtrl *m_pathTextCtrl;
        wxButton *m_refreshButton, *m_previousButton;
        wxCheckBox *m_hiddenFilesCheckBox, *m_filterCheckBox;
        wxString m_managerName, m_managerDescription;
};

#endif // EXPLORERPANEL_H
