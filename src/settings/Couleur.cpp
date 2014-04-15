/***************************************************************
 * Name:      Couleur.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2013-17-05
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../../include/settings/Couleur.h"

/**
 * @class Couleur
 * @brief Champs RVB
 */

/**
 * Constructeur
 */
Couleur::Couleur(unsigned int red, unsigned int green, unsigned int blue, bool boolValue)
{
    if (boolValue)
        SetBoolRGB(red, green, blue);
    else
        SetRGB(red, green, blue);
}

/**
 * Constructeur
 * @param chaine une chaine contenant le code de la couleur
 * @param boolValue Si vrai, chaine contient des 't' et des 'f' pour représenter les valeurs. Sinon, ce sont des entiers 0-255 séparé par des espaces ' '
 * @see Couleur::FromString
 */
Couleur::Couleur(wxString chaine, bool boolValue)
{
    FromString(chaine, boolValue);
}

/**
 * Constructeur
 * @param node un nœud XML
 * @see Couleur::FromXMLNode
 */
Couleur::Couleur(wxXmlNode *node)
{
    FromXMLNode(node);
}

/**
 * Destructeur
 */
Couleur::~Couleur()
{
}

/**
 * Lit un nœud XML
 * @param node
 */
void Couleur::FromXMLNode(wxXmlNode *node)
{
    if (node)
    {
        long val = 0;
        node->GetAttribute(_T("red"), wxEmptyString).ToLong(&val);
        SetRed(val);
        node->GetAttribute(_T("green"), wxEmptyString).ToLong(&val);
        SetGreen(val);
        node->GetAttribute(_T("blue"), wxEmptyString).ToLong(&val);
        SetBlue(val);
    }
    else
        SetRGB(0, 0, 0);
}

/**
 * Convertit une chaîne de caractères en structure Couleur (Couleur.R, Couleur.V, Couleur.B)
 * @param chaine une chaine contenant le code de la couleur
 * @param boolValue Si vrai, chaine contient des 't' et des 'f' pour représenter les valeurs. Sinon, ce sont des entiers 0-255 séparé par des espaces ' '
 */
void Couleur::FromString(wxString chaine, bool boolValue)
{
    wxString temp = chaine.AfterFirst(' '), tabCouleur[3];
    if (boolValue)
    {
        for (int i=0; i<3; i++)
        {
            tabCouleur[i] = temp.BeforeFirst(' ');
            temp = temp.AfterFirst(' ');
        }
        SetBoolRGB((tabCouleur[0] == _T("t")), (tabCouleur[1] == _T("t")), (tabCouleur[2] == _T("t")));
    }
    else
    {
        long val = 0;

        for (int i=0; i<3; i++)
        {
            tabCouleur[i] = temp.BeforeFirst(' ');
            temp = temp.AfterFirst(' ');
        }
        tabCouleur[0].ToLong(&val);
        SetRed(val);
        tabCouleur[1].ToLong(&val);
        SetGreen(val);
        tabCouleur[2].ToLong(&val);
        SetBlue(val);
    }
}

unsigned int Couleur::GetRed()
{
    return m_red;
}

bool Couleur::GetBoolRed()
{
    return m_red;
}

void Couleur::SetRed(unsigned int val)
{
    m_red = val;
}

unsigned int Couleur::GetBlue()
{
    return m_blue;
}

bool Couleur::GetBoolBlue()
{
    return m_blue;
}

void Couleur::SetBlue(unsigned int val)
{
    m_blue = val;
}

unsigned int Couleur::GetGreen()
{
    return m_green;
}

bool Couleur::GetBoolGreen()
{
    return m_green;
}

void Couleur::SetGreen(unsigned int val)
{
    m_green = val;
}

void Couleur::SetRGB(unsigned int red, unsigned int green, unsigned int blue)
{
    m_red = red;
    m_green = green;
    m_blue = blue;
}

void Couleur::SetBoolRGB(bool red, bool green, bool blue)
{
    m_red = (red) ? 255 : 0;
    m_green = (green) ? 255 : 0;
    m_blue = (blue) ? 255 : 0;
}

wxString Couleur::ToString(wxString mot)
{
    wxString res;
    res << mot << _T(" ") << m_red << _T(" ") << m_green << _T(" ") << m_blue;
    return res;
}

wxString Couleur::ToBoolString(wxString mot)
{
    wxString res;
    res << mot << _T(" ") << ((m_red)?_T("t"):_T("f")) << _T(" ") << ((m_green)?_T("t"):_T("f")) << _T(" ") << ((m_blue)?_T("t"):_T("f"));
    return res;
}

wxString Couleur::ToString()
{
    return ToString(wxEmptyString);
}

wxString Couleur::ToBoolString()
{
    return ToBoolString(wxEmptyString);
}

/*Couleur& Couleur::operator=(const Couleur& other)
{
    m_red = other.GetRed();
    m_green = other.GetGreen();
    m_blue = other.GetBlue();
    return *this;
}*/

/**
 * Renvoie les valeurs de la classe sous forme de nœud XML
 * @param parent le nœud parent
 * @param titre le nom du nœud
 * @return un nœud XML
 */
wxXmlNode* Couleur::ToXMLNode(wxXmlNode *parent, wxString titre)
{
    wxXmlNode *node = new wxXmlNode(parent, wxXML_ELEMENT_NODE, titre);
    node->AddAttribute(_T("red"), wxString::Format(_T("%u"), GetRed()));
    node->AddAttribute(_T("green"),wxString::Format(_T("%u"), GetGreen()));
    node->AddAttribute(_T("blue"), wxString::Format(_T("%u"), GetBlue()));
    return node;
}


