/***************************************************************
 * Name:      ImageFichierMusique.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2010-09-01
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/

#include "../../include/Jaquette/DropFichierImagePochetteMusique.h"

/**
 * @class DropFichierImagePochetteMusique
 * @brief Permet un Drag&Drop de fichier venant de l'extérieur sur ImagePochetteMusique
 */

/**
 * Constructeur
 * @param imageMusique l'objet associé
 */
DropFichierImagePochetteMusique::DropFichierImagePochetteMusique(ImagePochetteMusique *imageMusique)
{    m_imageMusique = imageMusique;}

/**
 * Destructeur
 */
DropFichierImagePochetteMusique::~DropFichierImagePochetteMusique()
{}

/**
 * Appelé lors d'un Drag&Drop sur l'élément associé
 * @param x l'abscisse du point de relâchement
 * @param y l'ordonnée du point de relâchement
 * @param filenames un tableau contenant des noms à essayer
 * @return vrai si une image a pu être trouvée, faux sinon
 */
bool DropFichierImagePochetteMusique::OnDropFiles(wxCoord WXUNUSED(x), wxCoord WXUNUSED(y), const wxArrayString& filenames)
{
    size_t max = filenames.GetCount(), i = 0;
    bool continuer = true;
    #if DEBUG
    wxLogMessage(filenames.Item(i));
    #endif

    while (i<max && continuer)
    {
        if (filenames.Item(i).Lower().EndsWith(_T(".jpg")) || filenames.Item(i).Lower().EndsWith(_T(".bmp")))
        {
            m_imageMusique->LectureImageEvent(filenames.Item(i));
            continuer = false;
        }
        i++;
    }
    return !continuer;
}


