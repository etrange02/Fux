/***************************************************************
 * Name:      Search.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2010-05-06
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "../../../include/tools/dir_traverser/Search.h"

/**
 * @class Search
 * @brief Parcours une arborescence et place dans un fichier texte tous les noms des fichiers rencontrés
 */

/**
 * Constructeur
 * @param fichier le fichier où copier les noms
 */
Search::Search(ISearchTraversable *searchTraversable): m_searchTraversable(searchTraversable)
{}

/**
 * Surcharge
 */
wxDirTraverseResult Search::OnFile(const wxString &filename)
{
    if (Parametre::Get()->islisable(filename))
        m_searchTraversable->addFileLine(filename);
    return wxDIR_CONTINUE;
}

/**
 * Surcharge
 */
wxDirTraverseResult Search::OnDir(const wxString &WXUNUSED(dirname))
{    return wxDIR_CONTINUE;}

