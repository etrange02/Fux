#ifndef FINDPATHMENUELEMENT_H
#define FINDPATHMENUELEMENT_H

#include <wx/wx.h>

class MenuElement;
class MenuElementData;

class findPathMenuElement
{
    public:
        /** Default constructor */
        findPathMenuElement(const wxString& path);
        /** Default destructor */
        virtual ~findPathMenuElement();
        bool operator()(const MenuElement& element);
        bool operator()(const MenuElementData& element);

    protected:
    private:
        wxString m_path;
};

#endif // FINDPATHMENUELEMENT_H
