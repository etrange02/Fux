/***************************************************************
 * Name:      Parametre.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2011-10-20
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
 #include "../include/FichierLog.h"

/**
 * @class FichierLog
 * @brief Gère le fichier log de l'application
 */

static FichierLog* instanceFichierLog = NULL;

/**
 * Constructeur
 */
FichierLog::FichierLog()
{
    m_fichier = new wxFile(Parametre::Get()->getRepertoireParametre(_T("fichier.log")), wxFile::write);
}

/**
 * Destructeur
 */
FichierLog::~FichierLog()
{
    m_fichier->Close();
}

/**
 * Retourne un pointeur sur l'instance FichierLog
 * @return l'instance
 */
FichierLog* FichierLog::Get()
{
    if (instanceFichierLog == NULL)
        instanceFichierLog = new FichierLog();
    return instanceFichierLog;
}

/**
 * Ajoute une ligne au fichier
 */
void FichierLog::Ajouter(wxString chaine)
{
    m_fichier->Write(chaine + _T("\r\n"));
}

/**
 * Ajoute une ligne au fichier
 */
void FichierLog::Ajouter(const wxChar* ch1, wxString ch2)
{
    m_fichier->Write(ch1);
    m_fichier->Write(ch2 + _T("\r\n"));
}

/**
 * Ajoute une ligne au fichier
 */
void FichierLog::Ajouter(const wxChar* ch1)
{
    m_fichier->Write(ch1);
    m_fichier->Write(_T("\r\n"));
}

