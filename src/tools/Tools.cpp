/***************************************************************
 * Name:      Tools.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-01-30
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "Tools.h"
#include "Define.h"
#include <tools/system/System.h>

/** @brief Indicates if the string contains reserved characters.
 * @param str string to test
 * @return bool
 *
 */
bool tools::containsInvalidCharacter(const wxString& str)
{
    return str.Contains(system::System::getUnauthorizedCharacterFile());
}

/** @brief Returns a string according to the Id
 *
 * @param id const int
 * @return wxString&
 *
 */
wxString tools::getResource(const int id)
{
    wxString val;
    switch (id)
    {
        case ID_EXPLORER_PANEL_1_NAME:
            val = _("Navig gauche"); break;
        case ID_EXPLORER_PANEL_2_NAME:
            val = _("Navig droite"); break;
        case ID_EXPLORER_PANEL_1_DESCRIPTION:
            val = _("Navigation gauche : Fu(X) toujours en développement"); break;
        case ID_EXPLORER_PANEL_2_DESCRIPTION:
            val = _("Navigation droite : donc toujours plus loin !"); break;
        default:
            break;
    }
    return val;
}

