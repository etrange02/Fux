/***************************************************************
 * Name:      GestionPeriphElementLecteurRacineFichier.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2012-01-20
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "../../../include/gui/explorer/GestionPeriphElementLecteurRacineFichier.h"

/**
 * @class ElementLecteurRacineFichier
 * @brief Élément d'un sous menu représentant soit un lecteur (sous Windows) ou la racine (sous UNIX) soit un fichier .m3u soit la liste de lecture.
 */

/**
 * Constructeur
 */
ElementLecteurRacineFichier::ElementLecteurRacineFichier()
{
    m_idGauche = 0;
    m_idDroite = 0;
    m_menu = NULL;
    m_menuItem = NULL;
    m_utilise = false;
}

/**
 * Modifie le nom à afficher
 * @param nom le nom de l'élément
 */
void ElementLecteurRacineFichier::SetNomAffiche(wxString nom)
{
    m_nomAffiche = nom;
}

/**
 * Modifie le nom complet de l'élément
 * @param chemin le nom complet de l'élément
 */
void ElementLecteurRacineFichier::SetChemin(wxString chemin)
{
    m_chemin = chemin;
}

/**
 * Modifie l'identifiant associé au sous-menu "Gauche"
 * @param id l'identifiant gauche
 */
void ElementLecteurRacineFichier::SetIdGauche(int id)
{
    m_idGauche = id;
}

/**
 * Modifie l'identifiant associé au sous-menu "Droite"
 * @param id l'identifiant droit
 */
void ElementLecteurRacineFichier::SetIdDroite(int id)
{
    m_idDroite = id;
}

/**
 * Modifie l'utilisation de l'instance
 * @param utilise vrai si utilisé
 */
void ElementLecteurRacineFichier::SetUtilise(bool utilise)
{
    m_utilise = utilise;
}

/**
 * Associe un l'élément résultant de l'ajout du menu dans un autre
 * @param menuItem le sous-menu représentant l'instance
 */
void ElementLecteurRacineFichier::SetMenuItem(wxMenuItem* menuItem)
{
    m_menuItem = menuItem;
}

/***Getters ***/
/**
 * Retourne le nom affiché
 * @return le nom
 */
wxString ElementLecteurRacineFichier::GetNomAffiche()
{
    return m_nomAffiche;
}

/**
 * Retourne le chemin associé
 * @return le chemin
 */
wxString ElementLecteurRacineFichier::GetChemin()
{
    return m_chemin;
}

/**
 * Retourne l'identifiant associé au sous-menu "Gauche"
 * @return l'identifiant gauche
 */
int ElementLecteurRacineFichier::GetIdGauche()
{
    return m_idGauche;
}

/**
 * Retourne l'identifiant associé au sous-menu "Droite"
 * @return l'identifiant droit
 */
int ElementLecteurRacineFichier::GetIdDroite()
{
    return m_idDroite;
}

/**
 * Indique si l'instance est utilisée
 * @return vrai si utilisé, faux sinon
 */
bool ElementLecteurRacineFichier::GetUtilise()
{
    return m_utilise;
}

/**
 * Retourne l'élément résultant de l'ajout du menu dans un autre
 * @return le wxMenuItem
 */
wxMenuItem* ElementLecteurRacineFichier::GetMenuItem()
{
    return m_menuItem;
}

/**
 * Retourne le menu construit à partir de l'instance
 * @return le menu
 */
wxMenu* ElementLecteurRacineFichier::GetMenu()
{
    return m_menu;
}

/**
 * Efface l'élément résultant de l'ajout du menu dans un autre et met l'instance en non-utilisé
 */
void ElementLecteurRacineFichier::PasUtilise()
{
    SetUtilise(false);
    m_menuItem = NULL;
}

/**
 * Crée un menu à partir des paramètres déjà donnés
 */
void ElementLecteurRacineFichier::CreerMenu()
{
    m_menu = new wxMenu;
    m_menu->Append(m_idGauche, _("Gauche"));
    m_menu->Append(m_idDroite, _("Droite"));
}

