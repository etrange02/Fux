// *** ADDED BY HEADER FIXUP ***
#include <string>
// *** END ***
#ifndef FICHIERLOG_H
#define FICHIERLOG_H

#include <wx/wx.h>
#include <wx/file.h>
#include "settings/Parametre.h"

#if DEBUG
#define LogFileAppend(string) FichierLog::Get()->Ajouter(string)
#else
#define LogFileAppend(string)
#endif // DEBUG

class FichierLog
{
    public:
        static FichierLog* Get();
        static void Delete();

        void Ajouter(wxString);
        void Ajouter(const wxChar* ch1);
        void Ajouter(const wxChar* ch1, wxString ch2);

    protected:
        FichierLog();
        ~FichierLog();
    private:
        wxFile *m_fichier; //!< Member variable "m_fichier"
};

#endif // FICHIERLOG_H
