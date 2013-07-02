/***************************************************************
 * Name:      ThreadGestion.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2010-05-07
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../include/ThreadGestion.h"

/**
 * @class ThreadFichierFichier
 * @brief Thread faisant de la gestion de dossiers et fichiers
 */

static ThreadFichierFichier* s_instanceThreadFichier = NULL;

/**
 * Constructeur
 */
ThreadFichierFichier::ThreadFichierFichier() : wxThread(wxTHREAD_JOINABLE)
{
    m_estActif = false;
    m_continue = false;
    m_liste = new ArrayOfElementThreadFichier;
    Create();
}

/**
 * Destructeur
 */
ThreadFichierFichier::~ThreadFichierFichier()
{
    ViderListe();
    delete m_liste;
    FichierLog::Get()->Ajouter(_T("ThreadFichierFichier::~ThreadFichierFichier"));
}

/**
 * Ajoute à la liste de traitement les combinaisons d'éléments données en paramètre
 * @param tableau un array contenant des chemins complets
 * @param action l'action à effectuer (copie, déplacement, suppression)
 * @param dest le répertoire de destination si besoin
 */
void ThreadFichierFichier::AjoutDonnee(wxArrayString *tableau, int action, wxString dest)
{
    size_t max = tableau->GetCount();

    for (size_t i=0; i<max; i++)
        m_liste->Add(new ElementThreadFichier(tableau->Item(i), action, dest));
    delete tableau;
    /*if (IsPaused())
        Resume();*/
}

/**
 * Retourne l'instance de la classe
 * @return l'instance
 */
ThreadFichierFichier* ThreadFichierFichier::Get()
{
    if (!s_instanceThreadFichier)
        s_instanceThreadFichier = new ThreadFichierFichier;
    return s_instanceThreadFichier;
}

/**
 * Retourne l'état du thread
 * @return l'état
 */
bool ThreadFichierFichier::GetEtat()
{    return m_estActif;}

/**
 * Stop le thread
 */
void ThreadFichierFichier::SetStop()
{    m_continue = false;}

/**
 * Efface la liste des modifications non effectuées
 */
void ThreadFichierFichier::ViderListe()
{
    m_liste->Clear();
}

/**
 * Lance le traitement des dossiers et fichiers
 */
void* ThreadFichierFichier::Entry()
{
    m_estActif = true;
    m_continue = true;
    ElementThreadFichier *element = NULL;
    wxString chemin;

    while (m_continue && !TestDestroy())
    {
        if (m_liste->IsEmpty())
            Sleep(500);
        else
        {
            element = m_liste->Item(0);

            if (element->IsAction(COPIE))
            {
                chemin = element->GetDestination() + wxFileName::GetPathSeparator() + element->GetNom().AfterLast(wxFileName::GetPathSeparator());

                if (wxFileExists(element->GetNom()))
                    wxCopyFile(element->GetNom(), chemin, false);
                else if (wxDirExists(element->GetNom()))
                {
                    DossierCopie(element->GetNom(), chemin);
                    FichierCopie(element->GetNom(), chemin);
                }
            }
            else if (element->IsAction(DEPLACE))
            {
                chemin = element->GetDestination() + wxFileName::GetPathSeparator() + element->GetNom().AfterLast(wxFileName::GetPathSeparator());

                if (wxFileExists(element->GetNom()))
                    wxRenameFile(element->GetNom(), chemin, false);
                else if (wxDirExists(element->GetNom()))
                {
                    DossierCopie(element->GetNom(), chemin);
                    FichierDeplace(element->GetNom(), chemin);
                }
            }
            else if (element->IsAction(SUPPRIME))
            {
                if (wxFileExists(element->GetNom()))
                    wxRemoveFile(element->GetNom());
                else if (wxDirExists(element->GetNom()))
                    FichierSuppression(element->GetNom());
            }

            element->~ElementThreadFichier();
            m_liste->Remove(element);
        }
    }
    m_estActif = false;
    m_continue = false;
    return NULL;
}

/**
 * Supprime une arborescence de dossier. Le premier dossier est la racine. Les dossiers ne doivent contenir aucun fichier !
 * @param dossier un array de nom de dossier dont le premier est la racine
 * @see FichierSuppression
 */
void ThreadFichierFichier::DossierSuppression(wxArrayString &dossier)
{
    size_t i = dossier.GetCount();
    while(i>0)
    {
        wxRmdir(dossier[i-1]);
        i--;
    }
    dossier.Empty();
}

/**
 * Copie le contenu du dossier dep dans le répertoire dest. Les fichiers ne sont pas copiés.
 * @param dep le dossier à copier
 * @param dest le répertoire de destination
 * @see FichierCopie
 */
void ThreadFichierFichier::DossierCopie(wxString dep, wxString dest)
{
    wxDir dir(dep);
    TraverserCopieDossier traverser(dest, dep);
    dir.Traverse(traverser);
}

/**
 * Supprime le répertoire chemin ainsi que les fichiers et dossiers se trouvant à l'intérieur
 * @param chemin le répertoire à supprimer
 */
void ThreadFichierFichier::FichierSuppression(wxString chemin)
{
    wxArrayString tableau;
    wxDir dir(chemin);
    TraverserSupprimeFichier traverser(chemin, tableau);
    dir.Traverse(traverser);
    DossierSuppression(tableau);
}

/**
 * Copie les fichiers se trouvant dans l'arborescence dep dans le répertoire dest. Les dossiers doivent exister !
 * @param dep le répertoire de départ
 * @param dest le répertoire d'arrivée
 */
void ThreadFichierFichier::FichierCopie(wxString dep, wxString dest)
{
    wxDir dir(dep);
    TraverserCopieFichier traverser(dest, dep);
    dir.Traverse(traverser);
}

/**
 * Déplace le contenu de dep dans le répertoire dest
 * @param dep le dossier de départ
 * @param dest le dossier d'arrivée
 */
void ThreadFichierFichier::FichierDeplace(wxString dep, wxString dest)
{
    wxArrayString tableau;
    wxDir dir(dep);
    TraverserDeplaceFichier traverser(dest, dep, tableau);
    dir.Traverse(traverser);
    DossierSuppression(tableau);
}

