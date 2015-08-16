#ifndef IMAGETEXT_H
#define IMAGETEXT_H

#include "wx/wx.h"
#include "wx/image.h"
#include <GL/gl.h>

class ImageText
{
    public:
        ImageText();
        ImageText(const ImageText& other);
        ~ImageText();

        GLuint* getID();
        int GetWidth();
        void Creer(wxString titre, int largeur, int largeurEcran, int hauteur = 16);
        void Affiche();
        void Creer(wxString, wxString);
        void Affiche(int x);

        void AfficheCentreHorizontal(int y);

    protected:
        GLuint *m_ID;
        int m_largeur;
        int m_hauteur;
        int m_largeurEcran;
        wxImage *m_img;
};

#endif // IMAGETEXT_H
