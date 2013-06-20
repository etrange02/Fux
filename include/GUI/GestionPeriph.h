#ifndef GESTIONPERIPH_H_INCLUDED
#define GESTIONPERIPH_H_INCLUDED

#include "../Define.h"
#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include <wx/listctrl.h>
#include <wx/filename.h>
#include <wx/imaglist.h>
#include <wx/gauge.h>
#include <wx/event.h>
#include <wx/dynarray.h>
#include <wx/mimetype.h>
#include <wx/textfile.h>
#include <wx/progdlg.h>
#include "../ThreadGestion.h"
#include "../OS_Win.h"
#include "GestionPeriphMoitiePage.h"
#include "GestionPeriphElementLecteurRacineFichier.h"

class PageGestionPeriph;

WX_DEFINE_ARRAY(ElementLecteurRacineFichier*, ArrayOfElementLecteurRacineFichier);

class GestPeriph : public wxPanel
{
    public :
        static GestPeriph* Get();
        void Delete();
        void Creer(wxWindow *Parent);

        void AfficheMenu_MesDoc(wxCommandEvent &WXUNUSED(event));
        void AfficheMenu_Periph(wxCommandEvent &WXUNUSED(event));
        void AfficheMenu_Autre(wxCommandEvent &WXUNUSED(event));

        ElementLecteurRacineFichier* Insertion(ArrayOfElementLecteurRacineFichier*, wxString, wxString);
        ElementLecteurRacineFichier* Insertion(ArrayOfElementLecteurRacineFichier*, wxString, int);
        void ListePeripherique();
        void ListeM3U();
        void DetruireListes();


        void AffListeMesDoc(wxCommandEvent&);
        void AffListeRepertoireLect(wxCommandEvent&);
        void AffListePlaylist(wxCommandEvent&);
        void AffListeM3U(wxCommandEvent&);
        void Copier(wxCommandEvent &WXUNUSED(event));
        void Supprimer(wxCommandEvent &WXUNUSED(event));
        void DeplaceG(wxCommandEvent &WXUNUSED(event));
        void DeplaceD(wxCommandEvent &WXUNUSED(event));
        void FocusD(wxChildFocusEvent &WXUNUSED(event));
        void FocusG(wxChildFocusEvent &WXUNUSED(event));
        void ComparaisonStatutEvt(wxCommandEvent &WXUNUSED(event));
        void ComparaisonStatut();
        void MAJPlaylist();

    protected:
        GestPeriph();
        ~GestPeriph();

    private :
        wxSizer *m_sizer1V, *m_sizerBoutonRacc, *m_sizer2G, *m_sizer2GridG, *m_sizer2GridD, *m_sizerBoutonModif;
        wxButton *m_boutonMesDoc, *m_boutonPeriph, *m_boutonAutre, *m_boutonModif;
        PageGestionPeriph *m_listeG, *m_listeD;
        wxMenu *m_menuMesDoc, *m_menuPeriph, *m_menuAutre, *m_menuM3U;
        ArrayOfElementLecteurRacineFichier *m_listeLecteur, *m_listePlaylist;
        int m_tableauFocus;

    DECLARE_EVENT_TABLE()
};

#endif // GESTIONPERIPH_H_INCLUDED
