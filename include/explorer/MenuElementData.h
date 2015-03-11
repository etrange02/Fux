#ifndef MENUELEMENTDATA_H
#define MENUELEMENTDATA_H

#include <wx/wx.h>

class MenuElementData
{
    public:
        /** Default constructor */
        MenuElementData();
        MenuElementData(const MenuElementData& other);
        /** Default destructor */
        virtual ~MenuElementData();
        MenuElementData& operator=(const MenuElementData& other);

        void setLabel(const wxString& label);
        void setPath(const wxString& path);
        const wxString& getLabel() const;
        const wxString& getPath() const;

    protected:

    private:
        wxString m_label;
        wxString m_path;
};

#endif // MENUELEMENTDATA_H
