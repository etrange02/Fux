/***************************************************************
 * Name:      Recherche.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2010-05-06
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../../include/DirTraverser/Recherche.h"

/**
 * @class Recherche
 * @brief Parcours une arborescence et place dans un fichier texte tous les noms des fichiers rencontrés
 */

/**
 * Constructeur
 * @param fichier le fichier où copier les noms
 */
Recherche::Recherche(wxTextFile *fichier): m_fichier(fichier)
{}

/**
 * Surcharge
 */
wxDirTraverseResult Recherche::OnFile(const wxString &filename)
{
    if (Parametre::Get()->islisable(filename.AfterLast('.').Lower()))
        m_fichier->AddLine(filename);
    return wxDIR_CONTINUE;
}

/**
 * Surcharge
 */
wxDirTraverseResult Recherche::OnDir(const wxString &WXUNUSED(dirname))
{    return wxDIR_CONTINUE;}

