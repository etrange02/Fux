#ifndef FINDPATHMENUELEMENT_H
#define FINDPATHMENUELEMENT_H

#include <wx/wx.h>

namespace explorer {
    class MenuElement;
    class MenuElementData;
}

class findPathMenuElement
{
    public:
        /** Default constructor */
        findPathMenuElement(const wxString& path);
        /** Default destructor */
        virtual ~findPathMenuElement();
        bool operator()(const ::explorer::MenuElement& element);
        bool operator()(const ::explorer::MenuElementData& element);

    protected:
    private:
        wxString m_path;
};

#endif // FINDPATHMENUELEMENT_H
