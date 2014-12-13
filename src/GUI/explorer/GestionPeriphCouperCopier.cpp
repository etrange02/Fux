/***************************************************************
 * Name:      GestionPeriphCouperCopier.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2010-12-14
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../../../include/gui/explorer/GestionPeriphCouperCopier.h"

/**
 * @class CouperCopierColler
 * @brief Mise en mémoire d'une opération de couper-copier-coller et gère les modifications.
 */

static CouperCopierColler *s_instanceCouperCopier = NULL;

/**
 * Constructeur protégé
 */
CouperCopierColler::CouperCopierColler()
{ m_action = -1; m_objetOrigine = VIDE;}

/**
 * Destructeur protégé
 */
CouperCopierColler::~CouperCopierColler()
{}

/**
 * Retourne une instance de la classe
 * @return l'instance
 */
CouperCopierColler* CouperCopierColler::Get()
{
    if (s_instanceCouperCopier == NULL)
        s_instanceCouperCopier = new CouperCopierColler();
    return s_instanceCouperCopier;
}

void CouperCopierColler::Delete()
{
    delete s_instanceCouperCopier;
    s_instanceCouperCopier = NULL;
}

/**
 * Met en mémoire un tableau de chaînes de caractères avec les paramètres propres à celui-ci
 * @param tableau un tableau de chaînes de caractères
 * @param action l'action à entreprendre : COUPER, COPIE, DEPLACE
 * @param objetOr le type associé à la liste : VIDE, M3U, PLAYLIST, DOSSIER
 * @param chemin le chemin de la liste
 */
void CouperCopierColler::SetArrayString(wxArrayString *tableau, int action, int objetOr, wxString chemin)
{
    if (m_tableau.GetCount() == 0)
        m_tableau.Empty();
    m_tableau = *tableau;
    m_action = action;
    m_objetOrigine = objetOr;
    m_cheminOri = chemin;
}

/**
 * Si l'action à effectuer est COUPER et que l'objet d'origine est un fichier, le contenu du tableau en mémoire est supprimé du fichier. Reset efface la mémoire.
 * @param reset si vrai, le tableau mis en mémoire est effacé
 */
void CouperCopierColler::ModifEtatDonnee(bool reset)
{
    if (m_action == COUPER)
    {
        if (m_objetOrigine == M3U)
        {
            wxTextFile fichier(m_cheminOri);
            if (!fichier.Open())
                return;

            size_t max = m_tableau.GetCount(), i = 0, j = 0;
            bool parcouru = true, cont = true;

            while (i<max && cont)
            {
                while (j<fichier.GetLineCount() && cont)
                {
                    if (fichier.GetLine(j).IsSameAs(m_tableau.Item(i)))
                    {
                        fichier.RemoveLine(j);
                        i++;
                        j--;
                        parcouru = false;
                        if (i >= max)
                            cont = false;
                    }
                    j++;
                }
                if (parcouru)
                { i++; parcouru = false;}
                else
                    parcouru = true;
                j = 0;
            }

            fichier.Write();
            fichier.Close();
            reset = true;
        }
        else if (m_objetOrigine == PLAYLIST)
        {
            MusicManager::get().deleteTitles(&m_tableau, true);
            //Musique::Get()->SupprimerNom();
            reset = true;
        }
    }
    if (reset)
    {
        m_tableau.Empty();
        m_action = -1;
        m_objetOrigine = VIDE;
    }
}

/**
 * Effectue les opérations de modification
 * @param destination le chemin de la destination
 * @param type le type de la destination : VIDE, M3U, PLAYLIST, DOSSIER
 * @return vrai si opération effectuée, faux sinon
 */
bool CouperCopierColler::SetDestination(wxString destination, int type)
{
    bool fait = false;
    if (type == VIDE)
        return fait;
    if (type == DOSSIER && m_objetOrigine == DOSSIER)
    {
        wxArrayString *tableau = new wxArrayString;
        *tableau = m_tableau;
        ThreadFichierFichier::Get()->AjoutDonnee(tableau, (m_action == COPIE) ? COPIE : DEPLACE, destination);
        if (!ThreadFichierFichier::Get()->GetEtat())
            ThreadFichierFichier::Get()->Run();
        if (m_action == COUPER)
            ModifEtatDonnee(true);
        fait = true;
    }
    else if (type == M3U)
    {
        if (!wxFileExists(destination))
            return false;

        wxTextFile fichier(destination);
        if (!fichier.Open())
            return false;

        size_t max = m_tableau.GetCount();
        for (size_t i=0; i<max; i++)
        {
            if (wxFileExists(m_tableau.Item(i)) && Parametre::Get()->islisable(m_tableau.Item(i).AfterLast('.').Lower()))
                fichier.AddLine(m_tableau.Item(i));
            else
                wxLogMessage(_("Fichier introuvable : ") + m_tableau.Item(i));
        }
        fichier.Write();
        fichier.Close();
        fait = true;
        ModifEtatDonnee();
    }
    else if (type == PLAYLIST)
    {
        size_t i = 0;
        while(i < m_tableau.GetCount())
        {
            if (Parametre::Get()->islisable(m_tableau.Item(i).AfterLast('.').Lower()))
                i++;
            else
                m_tableau.RemoveAt(i);
        }
        if (m_tableau.IsEmpty())
            return false;

        MusicManager::get().deleteTitles(&m_tableau, true);
        //Musique::Get()->Listage(&m_tableau, true);
        fait = true;
        ModifEtatDonnee();
    }

    return fait;
}

/**
 * Indique si des données sont en mémoire
 * @return vrai ou faux
 */
bool CouperCopierColler::estCharge()
{    return (m_tableau.GetCount() > 0);}

/**
 * Retourne le type de la liste d'origine
 * @return le type
 */
int CouperCopierColler::GetOrigine()
{    return m_objetOrigine;}



