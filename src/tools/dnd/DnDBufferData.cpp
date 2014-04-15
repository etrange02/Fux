/***************************************************************
 * Name:      DnDBufferData.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2012-06-26
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../../../include/tools/dnd/DnDBufferData.h"

/**
 * @class DnDBufferData
 * @brief Traduit un DnDListeFichier en une chaîne compatible avec le buffer. Cette classe représente les éléments en déplacement
 */

/**
 * Constructeur
 * @param dndNom un tableau de chaînes
 */
DnDBufferData::DnDBufferData(DnDListeFichier* dndNom)
{
   if (dndNom)  // Si aucun objet donnée n'est fourni en créer un
      m_DndNomObjet = new DnDListeFichier(*dndNom);
   else
      m_DndNomObjet = 0;

   wxDataFormat transfileformat; // Positionner l'identifiant du format
   transfileformat.SetId(_T("DnDBufferData"));
   SetFormat(transfileformat);
}

/**
 * Destructeur
 */
DnDBufferData::~DnDBufferData()
{    delete m_DndNomObjet;}

/**
 * Calcul la taille que prendra le tampon après transformation du DnDListeFichier (tableau de chaînes) en une chaine
 */
size_t DnDBufferData::GetDataSize() const
{
   size_t ret = 0, count;

   if (m_DndNomObjet)  // Vérification de l'existance d'un objet donnée
   {  // Chemin et noms de fichiers séparés par \n
      count = m_DndNomObjet->GetCount();
      ret += count;  // On ajoute count caractère \n
      for (size_t i = 0; i < count; i++)
         ret += m_DndNomObjet->Item(i).Len();
   }
   else
      ret = 0;
   return ret;
}

/**
 * Transforme un DnDListeFichier (tableau de chaînes) en une chaîne
 * @param buf un tableau de type void qui sera remplie par la méthode
 * @return true si la conversion a pu se faire, faux sinon
 */
bool DnDBufferData::GetDataHere(void *buf) const
{
   if (m_DndNomObjet)  // Vérification de l'existance d'un objet donnée
   {
      wxString tmp;
      size_t count = m_DndNomObjet->GetCount();
      for (size_t i = 0; i < count; i++)  // les autres sont les noms de fichiers
         tmp += m_DndNomObjet->Item(i) + _T("\n");
      memcpy(buf, tmp.c_str(), tmp.Len());
      return true;
   }
   return false;
}

/**
 * Transforme un tableau de type void (buf) en DnDListeFichier (tableau de chaînes)
 * @param len la taille du buffer
 * @param buf le buffer
 * @return vrai si la conversion a pu se faire
 */
bool DnDBufferData::SetData(size_t len, const void* buf)
{
    if (len != 0)
    {
        wxString tmp1, tmp2;

        if (!m_DndNomObjet) // Créer un objet donnée si inexistant
            m_DndNomObjet = new DnDListeFichier;
        tmp1 = wxString((const wxChar*)buf, len);
        m_DndNomObjet->Clear();

        while (!tmp1.IsEmpty())
        {
            tmp2 = tmp1.BeforeFirst(_T('\n'));  // découpage du tampon à chaque \n
            tmp1 = tmp1.AfterFirst(_T('\n'));
            if (!tmp2.IsEmpty())
                m_DndNomObjet->AddFile(tmp2);   // Les autres sont les noms de fichiers
        }
    }
   return true;
}

/**
 * Retourne le tableau de chaînes associé
 * @return le tableau
 */
DnDListeFichier* DnDBufferData::GetTransFile()
{    return m_DndNomObjet;}

