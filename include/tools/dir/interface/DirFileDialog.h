#ifndef DIRFILEDIALOG_H
#define DIRFILEDIALOG_H

//(*Headers(DirFileDialog)
#include <wx/dialog.h>
class wxGauge;
class wxCheckBox;
class wxStaticText;
class wxBoxSizer;
class wxButton;
//*)
#include "tools/dir/interface/DirFileUserInterface.h"
#include "tools/dir/interface/RepeatedQuestionInterface.h"

/**
 * Name space of tools
 */
namespace tools
{
    namespace dir
    {
        class AskForRecursiveOperationData;

        class DirFileDialog : public wxDialog, public tools::dir::DirFileUserInterface, public tools::dir::RepeatedQuestionInterface
        {
            public:

                DirFileDialog(wxWindow* parent);
                virtual ~DirFileDialog();

                virtual void close();
                virtual void setRange(int range);
                virtual void update(int value);
                virtual void update(int value, const wxString& message);
                virtual void askQuestion(tools::dir::AskForRecursiveOperationData& data);

                //(*Declarations(DirFileDialog)
                wxButton* m_noButton;
                wxBoxSizer* m_questionSizer;
                wxStaticText* m_stateText;
                wxCheckBox* m_recurseCheckBox;
                wxButton* m_yesButton;
                wxStaticText* m_questionText;
                wxGauge* m_gauge;
                //*)

            protected:

                //(*Identifiers(DirFileDialog)
                static const long ID_STATICTEXT1;
                static const long ID_GAUGE1;
                static const long ID_STATICTEXT2;
                static const long ID_CHECKBOX1;
                static const long ID_BUTTON1;
                static const long ID_BUTTON2;
                //*)

            private:
                void respondToRecurse(bool overwrite);
                //(*Handlers(DirFileDialog)
                void onClickYesButton(wxCommandEvent& event);
                void onClickNoButton(wxCommandEvent& event);
                //*)

            private:
                AskForRecursiveOperationData* m_data;

                DECLARE_EVENT_TABLE()
        };
    }
}

#endif
