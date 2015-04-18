#ifndef MENUELEMENT_H
#define MENUELEMENT_H

#include <wx/wx.h>
#include "MenuElementData.h"

/**
 * Explorer name space.
 */
namespace explorer
{
    class MenuElement
    {
        public:
            /** Default constructor */
            MenuElement(MenuElementData& data);
            /** Default destructor */
            virtual ~MenuElement();

            void setLeftID(int id);
            void setRightID(int id);
            void setLabel(const wxString& label);
            void setPath(const wxString& path);
            void setUsed();
            void setUnused();
            void setMenuItem(wxMenuItem* menuItem);

            int getRightID() const;
            int getLeftID() const;
            const wxString& getLabel() const;
            const wxString& getPath() const;
            bool isUsed() const;
            wxMenu* getMenu() const;
            wxMenuItem* getMenuItem() const;

            wxMenu* generateMenu();

        protected:
        private:
            int m_rightID;
            int m_leftID;
            bool m_used;
            wxMenu* m_menu;
            wxMenuItem* m_menuItem;
            MenuElementData m_data;
    };
}

#endif // MENUELEMENT_H
