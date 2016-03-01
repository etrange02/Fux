/***************************************************************
 * Name:      FileValidator.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2016-02-01
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "FileValidator.h"

using namespace tools::validator;

FileValidator::FileValidator(wxString* valPtr) :
    wxTextValidator(wxFILTER_EXCLUDE_CHAR_LIST, valPtr)
{
    #ifdef __WXMSW__
    SetCharExcludes(_T("\\/:*?\"<>|")); // Windows
    #else
    SetCharExcludes(_T("/")); // Linux/Mac ?
    #endif
}

FileValidator::~FileValidator()
{
    //dtor
}

