/***************************************************************
 * Name:      OS_Win.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2011-01-25
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "../../include/tools/OS_Win.h"

#ifdef __WXMSW__
    #include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
    //#define _WIN32_IE  0x0400/////////////////////////////////////
    #include <windows.h>
    #include <shlobj.h>
    #include <shellapi.h>

/**
 * Crée un raccourci (.lnk) à l'endroit spécifier)
 * @param cheminRaccourci l'endroit où doit être placé le raccourci
 * @param cheminOrigine l'endroit que point le raccourci
 * @return true si succès
 */
bool CreationRaccourci(wxString cheminRaccourci, wxString cheminOrigine)
{
    bool resultat = false;
    CoInitialize(NULL);
    IShellLink* pIShellLink = NULL;
    if (SUCCEEDED(CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID *)&pIShellLink)))
    {
        IPersistFile* pIPersistFile = NULL;
        wxString description = _T("Raccourci fichier .") + cheminOrigine.AfterLast('.') + _T(" - Fu(X) 2.0");

        // Vérifier si le raccourci existe déjà:

        // Définir le chemin du raccourci et descrition:
        pIShellLink->SetPath(cheminOrigine.c_str());
        pIShellLink->SetDescription(description.c_str());

        //Sauvegarde le raccourci de façon durable
        if (SUCCEEDED(pIShellLink->QueryInterface(IID_IPersistFile, (LPVOID *)&pIPersistFile)))
        {
            // Convertir le chemin en UNICODE:
            WCHAR *chaine = new WCHAR[cheminRaccourci.Length()+2];

            MultiByteToWideChar(CP_ACP, 0, cheminRaccourci.mb_str(), -1, (LPWSTR)chaine, cheminRaccourci.Length()+1);
            // Créer le raccourci:
            resultat = pIPersistFile->Save(chaine, 1);

            delete[] chaine;
            // Libérer l'interface IPersistFile:
            pIPersistFile->Release();
        }
     }
     // Libérer l'interface IShellLink:
     pIShellLink->Release();
     // Fermer la librairie COM:
     CoUninitialize();
     return !resultat;
}
#else
    #include <unistd.h>


/**
 * Crée un raccourci (.lnk) à l'endroit spécifier)
 * @param cheminRaccourci l'endroit où doit être placé le raccourci
 * @param cheminOrigine l'endroit que point le raccourci
 * @return true si succès
 */
bool CreationRaccourci(wxString cheminRaccourci, wxString cheminOrigine)
{
    return !symlink(cheminOrigine.c_str(), cheminRaccourci.c_str());
}
#endif

