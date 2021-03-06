/***************************************************************
 * Name:      ElementThreadFichier.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2012-01-31
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
 #include "../../include/tools/ElementThreadFichier.h"

/**
 * @class ElementThreadFichier
 * @brief Représente un élément physique (fichier ou dossier) et l'action qu'il doit subir
 */

/**
 * Constructeur
 * @param nom le nom complet de l'élément
 * @param action l'action à entreprendre (COPIE, DEPLACE, SUPPRIME)
 * @param destination le répertoire de destination où doit d'effectuer l'action
 */
ElementThreadFichier::ElementThreadFichier(wxString nom, int action, wxString destination) :
    m_nom(nom),
    m_destination(destination),
    m_action(action)
{
}

/**
 * Destructeur
 */
ElementThreadFichier::~ElementThreadFichier()
{}

/**
 * Retourne le nom de complet l'élément
 * @return le nom de l'élément
 */
wxString& ElementThreadFichier::GetNom()
{
    return m_nom;
}

/**
 * Retourne l'action à faire
 * @return l'action à entreprendre
 */
int ElementThreadFichier::GetAction()
{
    return m_action;
}

/**
 * Compare si l'action à effectuer est celle donné en paramètre
 * @param action le type d'action à comparer
 * @return vrai si égalité, faux sinon
 */
bool ElementThreadFichier::IsAction(int action)
{
    return (m_action == action);
}

/**
 * Renvoi le répertoire de destination de l'élément. Il peut être nul.
 * @return le répertoire de destination
 */
wxString& ElementThreadFichier::GetDestination()
{
    return m_destination;
}
