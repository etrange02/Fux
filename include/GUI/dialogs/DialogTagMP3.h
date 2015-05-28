#ifndef DIALOGTAGMP3_H
#define DIALOGTAGMP3_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include "../../Define.h"
#include "../widgets/ImagePochetteMusique.h"
#include "DialogTagMP3Info.h"
#include "Music.h"

class DialogTagMP3 : public wxDialog
{
    public:
        DialogTagMP3(wxWindow *parent, const wxWindowID id, const music::Music& music);
        ~DialogTagMP3();
        bool isModified();
        wxString getComment() const;
        ImagePochetteMusique* getImage();
        music::Music* getResult();

    private:
        void initialize();

    private:
        DialogTagMP3Info *m_pageInfo;
        ImagePochetteMusique *m_image;
        wxNotebook *m_notebook;
        wxTextCtrl *m_comment;
        music::Music* m_music;
};

#endif // DIALOGTAGMP3_H
