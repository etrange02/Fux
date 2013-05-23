#ifndef PREFERENCEDEFAUT_H_INCLUDED
#define PREFERENCEDEFAUT_H_INCLUDED

#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <wx/radiobox.h>
#include <wx/textfile.h>
#include <wx/scrolwin.h>
#include "Define.h"
#include "Musique.h"
#include "Parametre.h"

class PrefDefaut : public wxScrolledWindow
{
    public:
        PrefDefaut();
        PrefDefaut(wxWindow *Parent);
        virtual ~PrefDefaut();
        void Creer();
        int CreerListe(wxChoice *liste);
        int ListerContenuFichier(wxChoice *liste, int);
        void Defaut_Bouton_Enregistrer(wxCommandEvent &WXUNUSED(event));
        void Defaut_Bouton_Annuler(wxCommandEvent &WXUNUSED(event));
        void Defaut_Bouton_Recherche(wxCommandEvent &WXUNUSED(event));
        void Defaut_Bouton_DossierDefaut(wxCommandEvent &WXUNUSED(event));
        void Defaut_Bouton_MAJListe(wxCommandEvent &WXUNUSED(event));
        void Defaut_RadioMP3_M3U(wxCommandEvent &event);
        void Defaut_CheckBoxCouleur(wxCommandEvent &event);
        void Defaut_CheckBoxSon(wxCommandEvent &event);
        void Defaut_CheckBoxReprise(wxCommandEvent &event);
        void Defaut_CheckBoxTAG(wxCommandEvent &WXUNUSED(event));
        void OuvertureFichier();
        void Defaut_Bouton_Portable(wxCommandEvent &WXUNUSED(event));
        void Defaut_CheckBoxDefautBDR(wxCommandEvent &WXUNUSED(event));
        void Defaut_Bouton_CheminDefaut(wxCommandEvent &WXUNUSED(event));

        //wxString CheminOuvertureDefaut();

    protected:
        Musique *m_musique;

        wxSizer *m_sizer1V, *m_sizerUseQuo, *m_sizerAvancee;
        wxChoice *m_listeCouleur, *m_listeSon, *m_listeReprise;
        wxTextCtrl *m_boiteCheminChansonRep, *m_boiteCheminDefautRech;
        wxRadioBox *m_choix;
        wxButton *m_boutonEnregistrer, *m_boutonAnnuler, *m_boutonMAJListe, *m_boutonRecherche, *m_boutonCheminDefautRecherche, *m_boutonPortable;
        wxCheckBox *m_checkBox;

        int m_listeM3u_mp3;

    DECLARE_EVENT_TABLE()
};

#endif // PREFERENCEDEFAUT_H_INCLUDED
