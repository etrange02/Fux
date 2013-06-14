/***************************************************************
 * Name:      DnDListeFichier.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2012-06-26
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../../include/DnD/DnDListeFichier.h"


/**
 * @class DnDListeFichier
 * @brief Représente un tableau servant aux opérations de Drag & Drop (Glisser et Déposer)
 */

/**
 * Constructeur
 */
DnDListeFichier::DnDListeFichier()
{}

/**
 * Destructeur
 */
DnDListeFichier::~DnDListeFichier()
{    m_Nom.Clear();}

/**
 * Ajoute une chaîne au tableau
 * @param nom un nom complet
 */
void DnDListeFichier::AddFile(const wxString &nom)
{
    if (!nom.IsEmpty())
        m_Nom.Add(nom);
}

/**
 * Fait pointer le tableau vers tab
 * @param tab un pointeur sur un tableau
 */
void DnDListeFichier::AddStringArray(const wxArrayString* tab)
{
    if (!tab->empty())
        m_Nom = *tab;
}

/**
 * Retourne la chaîne placé en position nIndex
 * @param nIndex la position de la chaîne
 * @return la chaîne
 */
wxString& DnDListeFichier::Item(size_t nIndex)
{    return m_Nom.Item(nIndex);}

/**
 * Retourne la taille du tableau
 * @return la taille
 */
size_t DnDListeFichier::GetCount()
{    return m_Nom.GetCount();}

/**
 * Efface le tableau
 */
void DnDListeFichier::Clear()
{    m_Nom.Clear();}

/**
 * Retourne un pointeur sur le tableau
 * @return un pointeur de tableau
 */
wxArrayString* DnDListeFichier::arrayString()
{    return &m_Nom;}
