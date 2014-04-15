#ifndef FICHIERLOG_H
#define FICHIERLOG_H

#include <wx/wx.h>
#include <wx/file.h>
#include "../settings/Parametre.h"

class FichierLog
{
    public:
        static FichierLog* Get();
        void Delete();

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
