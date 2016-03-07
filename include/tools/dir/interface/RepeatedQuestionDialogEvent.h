#ifndef REPEATEDQUESTIONDIALOGEVENT_H
#define REPEATEDQUESTIONDIALOGEVENT_H

#include <wx/wx.h>
#include "tools/dir/interface/RepeatedQuestionInterface.h"
#include "tools/dir/interface/Events.h"

extern const wxEventType wxEVT_TOOLS_DIR_FILE_ASK_REC_QUESTION;

/**
 * Name space of tools
 */
namespace tools
{
    namespace dir
    {
        class AskForRecursiveOperationData;

        class RepeatedQuestionDialogEvent : public RepeatedQuestionInterface
        {
            public:
                /** Default constructor */
                RepeatedQuestionDialogEvent(wxWindow& parent);
                /** Default destructor */
                virtual ~RepeatedQuestionDialogEvent();

                virtual void askQuestion(AskForRecursiveOperationData& data);

            protected:

            private:
                wxWindow& m_parent;
        };
    }
}

#endif // REPEATEDQUESTIONDIALOGEVENT_H
