/***************************************************************
 * Name:      ImageText.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2010-11-03
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "../../../include/gui/tools/ImageText.h"

/**
 * @class ImageText
 * @brief Transforme et affiche une chaîne de caractère dans une surface OpenGL
 */

/**
 * Constructeur
 */
ImageText::ImageText() :
    m_largeur(0),
    m_hauteur(0),
    m_largeurEcran(0)
{
    m_ID = new GLuint[1];
    glGenTextures(1, &m_ID[0]);
    m_img = new wxImage();
}

ImageText::ImageText(const ImageText& other)
{
    m_largeur = other.m_largeur;
    m_hauteur = other.m_hauteur;
    m_largeurEcran = other.m_largeurEcran;
    m_ID = new GLuint[1];
    m_ID[0] = other.m_ID[0];
    glGenTextures(1, &m_ID[0]);
    m_img = new wxImage();
    *m_img = *other.m_img;
}

/**
 * Destructeur
 */
ImageText::~ImageText()
{
    glDeleteTextures(1, m_ID);
    delete[] m_ID;
    delete m_img;
}

/**
 * Retourne l'identifiant de la texture
 * @return l'identifiant
 */
GLuint* ImageText::getID()
{    return m_ID;}

/**
 * Affiche la texture texte sur l'écran
 */
void ImageText::Affiche()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *m_ID);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex2f((m_largeurEcran-m_largeur)>>1, m_hauteur+2);

    glTexCoord2f(1, 1);
    glVertex2f((m_largeurEcran+m_largeur)>>1, m_hauteur+2);

    glTexCoord2f(1, 0);
    glVertex2f((m_largeurEcran+m_largeur)>>1, 2);

    glTexCoord2f(0, 0);
    glVertex2f((m_largeurEcran-m_largeur)>>1, 2);

    glEnd();
    glDisable(GL_TEXTURE_2D);
}

/**
 * Retourne la largeur de la texture
 * @return la largeur
 */
int ImageText::GetWidth()
{    return m_largeur;}

/**
 * Crée la texture texte à partir des paramètres fournis. largeur <= largeurEcran et largeur = 2<sup>n</sup>
 * @param nom le texte à afficher
 * @param largeur 2<sup>n</sup>
 * @param largeurEcran la largeur de l'écran
 * @param hauteur 2<sup>n</sup>
 */
void ImageText::Creer(wxString nom, int largeur, int largeurEcran, int hauteur)
{
    glBindTexture(GL_TEXTURE_2D, *m_ID);
    m_largeurEcran = largeurEcran;

	wxBitmap bitmap;
	largeur*=2;
    bitmap.Create(largeur, hauteur);
    wxMemoryDC Dc;
    Dc.SelectObject(bitmap);

    int largeurT = 0;
    Dc.GetTextExtent(nom, &largeurT, NULL);
    Dc.SetTextForeground(wxColour(255, 255, 255));
    Dc.DrawText(nom, (largeur-largeurT) >> 1, 0);
    Dc.SelectObject(wxNullBitmap);

	*m_img = bitmap.ConvertToImage();

	m_largeur = m_img->GetWidth();
	m_hauteur = m_img->GetHeight();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    GLubyte *bitmapData=m_img->GetData();
    GLubyte *imageData;

    //int bytesPerPixel = 4;//m_img->HasAlpha() ?  4 : 3;

    int imageSize = (m_largeur * m_hauteur) << 2;
    imageData=(GLubyte *)malloc(imageSize);

    int rev_val=m_hauteur-1;
    register int point, point2;

    for(int y=0; y<m_hauteur; y++)
    {
        for(int x=0; x<m_largeur; x++)
        {
            point = (x+y*m_largeur) << 2;
            point2 = ( x+(rev_val-y)*m_largeur)*3;

            imageData[point] = bitmapData[point2];

            imageData[point+1] = bitmapData[point2 + 1];

            imageData[point+2] = bitmapData[point2 + 2];

            imageData[point+3] =  (!bitmapData[point2] && !bitmapData[point2+1] && !bitmapData[point2+2]) ? 0 : 255;
        }//next
    }//next

    glTexImage2D(GL_TEXTURE_2D, 0, 4, m_largeur, m_hauteur, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    free(imageData);

	// set texture parameters as you wish
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // GL_LINEAR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // GL_LINEAR
}

/**
 * Affiche la texture temps sur l'écran
 * @param x l'abscisse du centre
 */
void ImageText::Affiche(int x)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *m_ID);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex2f(x-(m_largeur>>1), m_hauteur-6);

    glTexCoord2f(1, 1);
    glVertex2f(x+(m_largeur>>1), m_hauteur-6);

    glTexCoord2f(1, 0);
    glVertex2f(x+(m_largeur>>1), -6);

    glTexCoord2f(0, 0);
    glVertex2f(x-(m_largeur>>1), -6);

    glEnd();
    glDisable(GL_TEXTURE_2D);
}

/**
 * Crée une texture à partir des paramètres donnés
 * @param temps un temps
 * @param duree un autre temps
 */
void ImageText::Creer(wxString temps, wxString duree)
{
    glBindTexture(GL_TEXTURE_2D, *m_ID);

	wxBitmap bitmap;
    bitmap.Create(128, 64);
    wxMemoryDC Dc;
    Dc.SelectObject(bitmap);

    int largeur = 0;
    Dc.SetTextForeground(wxColour(255, 255, 255));

    Dc.GetTextExtent(temps, &largeur, NULL);
    Dc.DrawText(temps, (128-largeur) >> 1, 2);
    Dc.GetTextExtent(duree, &largeur, NULL);
    Dc.DrawText(duree, (128-largeur) >> 1, 21);

    Dc.SelectObject(wxNullBitmap);

	*m_img = bitmap.ConvertToImage();

	m_largeur=m_img->GetWidth();
	m_hauteur=m_img->GetHeight();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    GLubyte *bitmapData=m_img->GetData();
    GLubyte *imageData;

    int imageSize = (m_largeur * m_hauteur) << 2;
    imageData=(GLubyte *)malloc(imageSize);

    int rev_val=m_hauteur-1;
    register int point1, point2;

    for(int y=0; y<m_hauteur; y++)
    {
        for(int x=0; x<m_largeur; x++)
        {
            point1 = (x+y*m_largeur) << 2;
            point2 = ( x+(rev_val-y)*m_largeur)*3;

            imageData[point1] = bitmapData[point2];

            imageData[point1+1] = bitmapData[point2 + 1];

            imageData[point1+2] = bitmapData[point2 + 2];

            imageData[point1+3] =  (!bitmapData[point2] && !bitmapData[point2+1] && !bitmapData[point2+2]) ? 0 : 255;
        }//next
    }//next

    glTexImage2D(GL_TEXTURE_2D, 0, 4, m_largeur, m_hauteur, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    free(imageData);

	// set texture parameters as you wish
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // GL_LINEAR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // GL_LINEAR
}

/**
 * Affiche la texture à l'écran, elle est centré horizontalement
 * @param y l'ordonnée
 */
void ImageText::AfficheCentreHorizontal(int y)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *m_ID);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex2f((m_largeurEcran-m_largeur)>>1, m_hauteur+y);

    glTexCoord2f(1, 1);
    glVertex2f((m_largeurEcran+m_largeur)>>1, m_hauteur+y);

    glTexCoord2f(1, 0);
    glVertex2f((m_largeurEcran+m_largeur)>>1, y);

    glTexCoord2f(0, 0);
    glVertex2f((m_largeurEcran-m_largeur)>>1, y);

    glEnd();
    glDisable(GL_TEXTURE_2D);
}
