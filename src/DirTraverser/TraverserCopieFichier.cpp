/***************************************************************
 * Name:      TraverserCopieFichier.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2010-05-06
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
 #include "../../include/DirTraverser/TraverserCopieFichier.h"

/**
 * @class TraverserCopieFichier
 * @brief Copie les fichiers se trouvant dans l'arborescence dep dans le r�pertoire dest. Les dossiers doivent exister !
 */

/**
 * Construteur
 * @param destination le r�pertoire de d�part
 * @param origine le r�pertoire d'arriv�e
 */
TraverserCopieFichier::TraverserCopieFichier(wxString destination, wxString origine)
{
    m_destination = destination;
    m_origine = origine;
}

/**
 * Surcharge
 */
wxDirTraverseResult TraverserCopieFichier::OnFile(const wxString &filename)
{
    wxString dest = filename;
    dest.Replace(m_origine, m_destination, false);
    wxCopyFile(filename, dest, false);
    if (!ThreadFichierFichier::Get()->GetEtat())
        return wxDIR_STOP;
    else
        return wxDIR_CONTINUE;
}

/**
 * Surcharge
 */
wxDirTraverseResult TraverserCopieFichier::OnDir(const wxString &WXUNUSED(dirname))
{   return wxDIR_CONTINUE;}
