/***************************************************************
 * Name:      TraverserCopieDossier.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2010-05-06
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "../../../include/tools/dir_traverser/TraverserCopieDossier.h"

/**
 * @class TraverserCopieDossier
 * @brief Copie le contenu d'un dossier origine dans un répertoire destination. Les fichiers ne sont pas copiés.
 */

/**
 * Construteur
 * @param destination le dossier à copier
 * @param origine le répertoire de destination
 */
TraverserCopieDossier::TraverserCopieDossier(wxString destination, wxString origine)
{
    m_destination = destination;
    m_origine = origine;
    wxMkdir(destination);
}

/**
 * Surcharge
 */
wxDirTraverseResult TraverserCopieDossier::OnFile(const wxString &WXUNUSED(filename))
{   return wxDIR_CONTINUE;}

/**
 * Surcharge
 */
wxDirTraverseResult TraverserCopieDossier::OnDir(const wxString &dirname)
{
    wxString dest = dirname;
    dest.Replace(m_origine, m_destination, false);
    wxMkdir(dest);
    if (!ThreadFichierFichier::Get()->GetEtat())
        return wxDIR_STOP;
    else
        return wxDIR_CONTINUE;
}


