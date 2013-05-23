#ifndef IMAGEFICHIERMUSIQUE_H_INCLUDED
#define IMAGEFICHIERMUSIQUE_H_INCLUDED

#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include <wx/dnd.h>
#include "Define.h"

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
