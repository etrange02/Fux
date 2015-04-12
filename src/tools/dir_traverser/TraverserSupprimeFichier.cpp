/***************************************************************
 * Name:      TraverserSupprimeFichier.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2010-05-06
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "../../../include/tools/dir_traverser/TraverserSupprimeFichier.h"

/**
 * @class TraverserSupprimeFichier
 * @brief Supprime les fichiers se trouvant dans une arborescence
 */

 /// DELETE WITH GIT ////

/**
 * Construteur
 * @param origine le répertoire où doit être supprimé les fichiers
 * @param tableau ce tableau est rempli par la classe. Il contient le nom des dossiers vidés. Ces dossiers ne sont pas supprimés
 */
TraverserSupprimeFichier::TraverserSupprimeFichier(wxString origine, wxArrayString &tableau): m_tableau(tableau)
{
    m_origine = origine;
    tableau.Add(m_origine);
}

/**
 * Surcharge
 */
wxDirTraverseResult TraverserSupprimeFichier::OnFile(const wxString &filename)
{
    wxRemoveFile(filename);
    if (!ThreadFichierFichier::Get()->GetEtat())
        return wxDIR_STOP;
    else
        return wxDIR_CONTINUE;
}

/**
 * Surcharge
 */
wxDirTraverseResult TraverserSupprimeFichier::OnDir(const wxString &dirname)
{
    m_tableau.Add(dirname);
    return wxDIR_CONTINUE;
}
