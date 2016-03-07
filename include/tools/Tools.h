#ifndef TOOLS_H
#define TOOLS_H

#include "wx/wx.h"

/**
 * Name space of tools
 */
namespace tools
{
    bool containsInvalidCharacter(const wxString& str);
    wxString getResource(const int id);
}

#endif // TOOLS_H
