/***************************************************************
 * Name:      ArrayFenetreDetachable.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2012-01-24
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "../../../include/gui/tools/ArrayFenetreDetachable.h"

/**
 * @class ArrayFenetreDetachable
 * @brief Array contenant des FenetreDetachable
 */

/**
 * Constructeur
 */
ArrayFenetreDetachable::ArrayFenetreDetachable()
{}

/**
 * Destructeur
 */
ArrayFenetreDetachable::~ArrayFenetreDetachable()
{
    Vider();
}

/**
 * Supprime tous les éléments présents dans l'array
 */
void ArrayFenetreDetachable::Vider()
{
    for (size_t i = 0; i< GetCount(); i++)
        Item(i)->Destroy();
}

/**
 * Crée une fenêtre avec les éléments donnés en paramètres puis ajoute celle-ci dans l'array
 * @param parent l'ancien parent du panel
 * @param page le panel devant changer de parent
 * @param sizer le sizer contenant le panel
 * @param type correspond au type du panel
 * @param idBouton l'identifiant du bouton étant à l'origine de cette fenêtre
 * @param titre le titre de la fenêtre
 */
void ArrayFenetreDetachable::Add(wxWindow* parent, wxWindow* page, wxSizer* sizer, int type, int idBouton, wxString titre)
{
    FenetreDetachable *f = new FenetreDetachable(parent, page, sizer, type, idBouton, titre);
    f->Show();
    ArrayOfFenetreDetachable::Add(f);
}

/**
 * Indique si une fenêtre a été créée à partir de l'identifiant d'un bouton
 * @param idBouton l'identifiant du bouton
 * @return vrai si la fenêtre existe, faux sinon
 */
bool ArrayFenetreDetachable::IsInsideBouton(int idBouton)
{
    bool result = false;
    size_t i = 0;
    while (!result && i < GetCount())
    {
        if (Item(i)->GetIdBouton() == idBouton)
            result = true;
        i++;
    }
    return result;
}

/**
 * Indique si une fenêtre a été créée à partir du type de panel contenu
 * @param type le type de panel associé
 * @return vrai si la fenêtre existe, faux sinon
 */
bool ArrayFenetreDetachable::IsInsideType(int type)
{
    bool result = false;
    size_t i = 0;
    while (!result && i < GetCount())
    {
        if (Item(i)->GetType() == type)
            result = true;
        i++;
    }
    return result;
}

/**
 * Retourne la FenetreDetachable correspondant à l'idBouton
 * @param idBouton l'identifiant du bouton à l'origine de la fenêtre
 * @return un pointeur sur la fenêtre
 */
FenetreDetachable* ArrayFenetreDetachable::GetFenetreByIdBouton(int idBouton)
{
    if (IsInsideBouton(idBouton))
    {
        size_t i = 0;
        while (i < GetCount())
        {
            if (Item(i)->GetIdBouton() == idBouton)
                return Item(i);
            i++;
        }
        return NULL;
    }
    else
        return NULL;
}

/**
 * Retourne la FenetreDetachable correspondant au type
 * @param type le type du panel contenu dans la fenêtre
 * @return un pointeur sur la fenêtre
 */
FenetreDetachable* ArrayFenetreDetachable::GetFenetreByType(int type)
{
    if (IsInsideType(type))
    {
        size_t i = 0;
        while (i < GetCount())
        {
            if (Item(i)->GetType() == type)
                return Item(i);
            i++;
        }
        return NULL;
    }
    else
        return NULL;
}

