/***************************************************************
 * Name:      Music.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2014-04-16
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
 #include "music/IMusic.h"

 using namespace ::music;

 /**
 * @class IMusic
 * @brief Interface of a Music with some implemented methods.
 */

/** @brief Gets the duration under dd:dd format
 * Gets the duration under dd:dd format. 0 inserted if necessary
 * @return a dd:dd string
 *
 */
wxString IMusic::GetStringDuration()
{
    wxString str;
    str << GetDuration()/60 << _T(":");
    if (GetDuration()%60 < 10)
        str << _T("0") << GetDuration()%60;
    else
        str << GetDuration()%60;
    return str;
}

/** @brief Gets the year under string format
 *
 * @return the year under string format
 *
 */
wxString IMusic::GetStringYear()
{
    wxString str = wxString::Format(_("%d"), GetYear());
    return str;
}

bool IMusic::IsMatching(const wxString& word)
{
    return !(
                      wxNOT_FOUND == GetFileName()      .Lower().Find(word)
                 &&   wxNOT_FOUND == GetArtists()       .Lower().Find(word)
                 &&   wxNOT_FOUND == GetAlbum()         .Lower().Find(word)
                 &&   wxNOT_FOUND == GetTitle()         .Lower().Find(word)
                 &&   wxNOT_FOUND == GetGenres()        .Lower().Find(word)
                 &&   wxNOT_FOUND == GetStringDuration().Lower().Find(word)
                 &&   wxNOT_FOUND == GetStringYear()    .Lower().Find(word)
             );
}

