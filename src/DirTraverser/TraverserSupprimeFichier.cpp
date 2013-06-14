/***************************************************************
 * Name:      TraverserSupprimeFichier.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2010-05-06
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../../include/DirTraverser/TraverserSupprimeFichier.h"

/**
 * @class TraverserSupprimeFichier
 * @brief Supprime les fichiers se trouvant dans une arborescence
 */

/**
 * Construteur
 * @param origine le r�pertoire o� doit �tre supprim� les fichiers
 * @param tableau ce tableau est rempli par la classe. Il contient le nom des dossiers vid�s. Ces dossiers ne sont pas supprim�s
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
