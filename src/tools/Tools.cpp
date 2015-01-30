/***************************************************************
 * Name:      Tools.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-01-30
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "Tools.h"

/** @brief Indicates if the string contains reserved characters.
 * The invalid characters is based on Windows file system. It is on this
 * I found more constraints.
 * @param str string to test
 * @return bool
 *
 */
bool containsInvalidCharacter(const wxString& str)
{
    str.Contains("/\\:*?\"<>|");
}

