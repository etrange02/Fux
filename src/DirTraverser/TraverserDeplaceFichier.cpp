/***************************************************************
 * Name:      TraverserDeplaceFichier.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2010-05-06
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../../include/DirTraverser/TraverserDeplaceFichier.h"

/**
 * @class TraverserDeplaceFichier
 * @brief D�place le contenu d'un dossier origine dans un r�pertoire destination. Les dossiers vid�s ne sont pas supprim�s
 */

/**
 * Construteur
 * @param origine le dossier de d�part
 * @param destination le dossier d'arriv�e
 * @param tableau ce tableau est rempli par la classe. Il contient le nom des dossiers vid�s. Ces dossiers ne sont pas supprim�s
 */
TraverserDeplaceFichier::TraverserDeplaceFichier(wxString destination, wxString origine, wxArrayString &tableau): m_tableau(tableau)
{
    m_destination = destination;
    m_origine = origine;
    tableau.Add(m_origine);
}

/**
 * Surcharge
 */
wxDirTraverseResult TraverserDeplaceFichier::OnFile(const wxString &filename)
{
    wxString dest = filename;
    dest.Replace(m_origine, m_destination, false);
    wxRenameFile(filename, dest, false);
    if (!ThreadFichierFichier::Get()->GetEtat())
        return wxDIR_STOP;
    else
        return wxDIR_CONTINUE;
}

/**
 * Surcharge
 */
wxDirTraverseResult TraverserDeplaceFichier::OnDir(const wxString &dirname)
{
    m_tableau.Add(dirname);
    return wxDIR_CONTINUE;
}

