#ifndef IMAGEPOCHETTEMUSIQUE_H
#define IMAGEPOCHETTEMUSIQUE_H

#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include "../../Define.h"
#include "../tools/DropFichierImagePochetteMusique.h"
#include "../tools/jaquetteClasses.h"

extern const wxEventType wxEVT_IMAGE_SELECTION;

class ImagePochetteMusique : public wxStaticBitmap
{
    public:
        ImagePochetteMusique(wxWindow* parent, wxWindowID id, const int width, const int height, bool warnParent);
        ~ImagePochetteMusique();
        bool AfficheImage(bool);
        wxImage& GetImage();
        void SetImage(wxImage&);
        void EvtSouris(wxMouseEvent&);
        void LectureImageEvent(wxString);
        bool IsModified();

    private:
        bool m_modif;
        bool m_warnParent;
        int m_width;
        int m_height;
        wxImage m_image;
        wxBitmap m_defaultBitmap;

    DECLARE_EVENT_TABLE()
};

#endif // IMAGEPOCHETTEMUSIQUE_H
