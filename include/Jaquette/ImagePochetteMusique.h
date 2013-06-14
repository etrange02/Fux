#ifndef IMAGEPOCHETTEMUSIQUE_H
#define IMAGEPOCHETTEMUSIQUE_H

#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include "../Define.h"
#include "DropFichierImagePochetteMusique.h"
#include "jaquetteClasses.h"

extern const wxEventType wxEVT_IMAGE_SELECTION;

class ImagePochetteMusique : public wxStaticBitmap
{
    public:
        ImagePochetteMusique(wxWindow*, wxWindowID, wxBitmap, bool);
        ~ImagePochetteMusique();
        bool AfficheImage(bool);
        wxImage GetImage();
        void SetImage(wxImage);
        void EvtSouris(wxMouseEvent&);
        void LectureImageEvent(wxString);
        bool IsModified();

    private:
        bool m_modif, m_avertirParent;
        wxImage m_image;

    DECLARE_EVENT_TABLE()
};

#endif // IMAGEPOCHETTEMUSIQUE_H
