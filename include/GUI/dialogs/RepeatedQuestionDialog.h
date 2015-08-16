#ifndef REPEATEDQUESTIONDIALOG_H
#define REPEATEDQUESTIONDIALOG_H

#include <wx/wx.h>

namespace gui
{
    class RepeatedQuestionDialog : public wxDialog
    {
        public:
            /** Default constructor */
            RepeatedQuestionDialog(wxWindow* parent, const wxWindowID id, const wxString& message, const wxString& caption);
            /** Default destructor */
            virtual ~RepeatedQuestionDialog();

            bool isRecursiveChecked() const;
            void onRecursiveCheckBox(wxCommandEvent& event);

        private:
            void initialize();

        private:
            const wxString& m_message;
            bool m_isRecursiveChecked;
    };
}

#endif // REPEATEDQUESTIONDIALOG_H
