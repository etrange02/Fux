/***************************************************************
 * Name:      RechercheTraverser.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2010-05-06
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../include/RechercheTraverser.h"

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

//////////////////////////////////////////////////////////////////////
/**
 * @class TraverserCopieFichier
 * @brief Copie les fichiers se trouvant dans l'arborescence dep dans le répertoire dest. Les dossiers doivent exister !
 */

/**
 * Construteur
 * @param destination le répertoire de départ
 * @param origine le répertoire d'arrivée
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

/////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////
/**
 * @class TraverserDeplaceFichier
 * @brief Déplace le contenu d'un dossier origine dans un répertoire destination. Les dossiers vidés ne sont pas supprimés
 */

/**
 * Construteur
 * @param origine le dossier de départ
 * @param destination le dossier d'arrivée
 * @param tableau ce tableau est rempli par la classe. Il contient le nom des dossiers vidés. Ces dossiers ne sont pas supprimés
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

/////////////////////////////////////////////////////////////////////
/**
 * @class TraverserSupprimeFichier
 * @brief Supprime les fichiers se trouvant dans une arborescence
 */

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

/*TraverserSupprimeDossier::TraverserSupprimeDossier(wxString origine)
{    m_origine = origine;}

TraverserSupprimeDossier::~TraverserSupprimeDossier()
{   wxRmdir(m_origine);}

wxDirTraverseResult TraverserSupprimeDossier::OnFile(const wxString &filename)
{   return wxDIR_CONTINUE;}

wxDirTraverseResult TraverserSupprimeDossier::OnDir(const wxString &dirname)
{
    wxRmdir(dirname);
    wxLogMessage("SupprimeDossier:" +dirname);
    if (!ThreadFichierFichier::Get()->GetEtat())
        return wxDIR_STOP;
    else
        return wxDIR_CONTINUE;
}*/



