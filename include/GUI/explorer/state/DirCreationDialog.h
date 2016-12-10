#ifndef DIRCREATIONDIALOG_H
#define DIRCREATIONDIALOG_H

//(*Headers(DirCreationDialog)
#include <wx/dialog.h>
class wxStdDialogButtonSizer;
class wxTextCtrl;
class wxRadioButton;
class wxStaticText;
class wxBoxSizer;
class wxButton;
class wxGridSizer;
//*)

class DirCreationDialog: public wxDialog
{
	public:

		DirCreationDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~DirCreationDialog();

    public:
        wxString getFullPath() const;
        bool isShowInSameExplorer() const;
        bool isShowInOtherExplorer() const;
        bool isNoShowInExplorer() const;
        bool isDataOK() const;

        void setDirPath(const wxString& dirPath);
        void setDirName(const wxString& dirName);

	private:

		//(*Declarations(DirCreationDialog)
		wxRadioButton* m_otherExplorer;
		wxTextCtrl* m_dirNameCtrl;
		wxRadioButton* m_noExplorer;
		wxTextCtrl* m_dirPath;
		wxButton* m_dirSelectionButton;
		wxRadioButton* m_sameExplorer;
		//*)

	public:

		//(*Identifiers(DirCreationDialog)
		static const long ID_DIR_CREATION_DIALOG_DIR_PATH;
		static const long ID_DIR_CREATION_DIALOG_OPEN_BUTTON;
		static const long ID_DIR_CREATION_DIALOG_DIR_NAME;
		static const long ID_DIR_CREATION_DIALOG_RADIOBUTTON_LEFT_EXPLORER;
		static const long ID_DIR_CREATION_DIALOG_RADIOBUTTON_RIGHT_EXPLORER;
		static const long ID_DIR_CREATION_DIALOG_RADIOBUTTON_NO_EXPLORER;
		//*)

	private:

		//(*Handlers(DirCreationDialog)
		void onClickDirSelectionButton(wxCommandEvent& event);
		void OnsameExplorerSelect(wxCommandEvent& event);
		//*)

    private:
        wxString m_dirName;
		DECLARE_EVENT_TABLE()
};

#endif
