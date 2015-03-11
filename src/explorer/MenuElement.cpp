#include "MenuElement.h"

MenuElement::MenuElement(MenuElementData& data) :
    m_rightID(0),
    m_leftID(0),
    m_used(false),
    m_menu(NULL),
    m_menuItem(NULL),
    m_data(data)
{
}

MenuElement::~MenuElement()
{
    //dtor
}

void MenuElement::setLeftID(int id)
{
    m_leftID = id;
}

void MenuElement::setRightID(int id)
{
    m_rightID = id;
}

void MenuElement::setLabel(const wxString& label)
{
    m_data.setLabel(label);
}

void MenuElement::setPath(const wxString& path)
{
    m_data.setPath(path);
}

void MenuElement::setUsed()
{
    m_used = true;
}

void MenuElement::setUnused()
{
    m_used = false;
}

void MenuElement::setMenuItem(wxMenuItem* menuItem)
{
    m_menuItem = menuItem;
}

int MenuElement::getRightID() const
{
    return m_rightID;
}

int MenuElement::getLeftID() const
{
    return m_leftID;
}

const wxString& MenuElement::getLabel() const
{
    return m_data.getLabel();
}

const wxString& MenuElement::getPath() const
{
    return m_data.getPath();
}

bool MenuElement::isUsed() const
{
    return m_used;
}

wxMenu* MenuElement::getMenu() const
{
    return m_menu;
}

wxMenuItem* MenuElement::getMenuItem() const
{
    return m_menuItem;
}

wxMenu* MenuElement::generateMenu()
{
    m_menu = new wxMenu;
    m_menu->Append(m_leftID,  _("Gauche"));
    m_menu->Append(m_rightID, _("Droite"));

    return m_menu;
}


