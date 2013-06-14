#ifndef IMAGEFICHIERMUSIQUE_H_INCLUDED
#define IMAGEFICHIERMUSIQUE_H_INCLUDED

#include <wx/wx.h>
#include <wx/dnd.h>
#include "ImagePochetteMusique.h"
#include "jaquetteClasses.h"

class DropFichierImagePochetteMusique : public wxFileDropTarget
{
    public:
        DropFichierImagePochetteMusique(ImagePochetteMusique *imageMusique);
        virtual ~DropFichierImagePochetteMusique();
        bool OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& filenames);

    protected:
        ImagePochetteMusique *m_imageMusique;
};

#endif // IMAGEFICHIERMUSIQUE_H_INCLUDED
