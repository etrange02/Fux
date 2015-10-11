#ifndef DIRFILEDIALOG_H
#define DIRFILEDIALOG_H

#include "DirFileUserInterface.h"
#include <wx/wx.h>
#include <wx/progdlg.h>


namespace tools
{
    namespace dir
    {
        class DirFileDialog : public DirFileUserInterface
        {
            public:
                /** Default constructor */
                DirFileDialog();
                /** Default destructor */
                virtual ~DirFileDialog();

                //virtual void show();
                virtual void close();
                virtual void setRange(int range);
                virtual void update(int value);
                virtual void update(int value, const wxString& message);

            protected:
            private:
                wxGenericProgressDialog* m_dialog;
        };
    }
}

#endif // DIRFILEDIALOG_H
