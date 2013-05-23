#ifndef FICHIERLOG_H
#define FICHIERLOG_H

#include <wx/wx.h>
#include <wx/file.h>
#include "Parametre.h"

class FichierLog
{
    public:
        FichierLog();
        ~FichierLog();
        static FichierLog* Get();

        void Ajouter(wxString);
        void Ajouter(const wxChar* ch1);
        void Ajouter(const wxChar* ch1, wxString ch2);

    protected:
    private:
        wxFile *m_fichier; //!< Member variable "m_fichier"
};

#endif // FICHIERLOG_H
