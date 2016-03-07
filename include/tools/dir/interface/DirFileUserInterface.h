#ifndef DIRFILEUSERINTERFACE_H
#define DIRFILEUSERINTERFACE_H

#include <wx/wx.h>


/**
 * Name space of tools
 */
namespace tools
{
    namespace dir
    {
        class DirFileUserInterface
        {
            public:
                /** Default destructor */
                virtual ~DirFileUserInterface() {}
                //virtual void show() = 0;
                virtual void close() = 0;
                virtual void setRange(int range) = 0;
                virtual void update(int value) = 0;
                virtual void update(int value, const wxString& message) = 0;

            protected:
                /** Default constructor */
                DirFileUserInterface() {}
                DirFileUserInterface(const DirFileUserInterface&) {}

            private:
        };
    }
}

#endif // DIRFILEUSERINTERFACE_H
