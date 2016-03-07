#ifndef DIRFILEDIALOGEVENT_H
#define DIRFILEDIALOGEVENT_H

#include <wx/wx.h>
#include "tools/dir/interface/DirFileUserInterface.h"
#include "tools/dir/interface/Events.h"


extern const wxEventType wxEVT_TOOLS_DIR_FILE_CLOSE;
extern const wxEventType wxEVT_TOOLS_DIR_FILE_RANGE;
extern const wxEventType wxEVT_TOOLS_DIR_FILE_UPDATE;

/**
 * Name space of tools
 */
namespace tools
{
    namespace dir
    {
        class DirFileDialogEvent : public DirFileUserInterface
        {
            public:
                /** Default constructor */
                DirFileDialogEvent(wxWindow& dialog);
                /** Default destructor */
                virtual ~DirFileDialogEvent();

                virtual void close();
                virtual void setRange(int range);
                virtual void update(int value);
                virtual void update(int value, const wxString& message);

            protected:
            private:
                wxWindow& m_dialog;
                wxLongLong m_lastUpdate;
        };
    }
}

#endif // DIRFILEDIALOGEVENT_H
