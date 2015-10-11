#ifndef DIRFILEDIALOGEVENT_H
#define DIRFILEDIALOGEVENT_H

#include "DirFileUserInterface.h"
#include <wx/wx.h>
#include "tools/dir/Events.h"


extern const wxEventType wxEVT_TOOLS_DIR_FILE_CLOSE;
extern const wxEventType wxEVT_TOOLS_DIR_FILE_RANGE;
extern const wxEventType wxEVT_TOOLS_DIR_FILE_UPDATE;

namespace tools
{
    namespace dir
    {
        class DirFileDialogEvent : public DirFileUserInterface
        {
            public:
                /** Default constructor */
                DirFileDialogEvent();
                DirFileDialogEvent(wxWindow* dialog);
                /** Default destructor */
                virtual ~DirFileDialogEvent();

                void setDialog(wxWindow* dialog);

                virtual void close();
                virtual void setRange(int range);
                virtual void update(int value);
                virtual void update(int value, const wxString& message);

            protected:
            private:
                wxWindow* m_dialog;
                wxLongLong m_lastUpdate;
        };
    }
}

#endif // DIRFILEDIALOGEVENT_H
