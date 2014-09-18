#ifndef PREFERENCEDEFAUT_H_INCLUDED
#define PREFERENCEDEFAUT_H_INCLUDED

#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <wx/radiobox.h>
#include <wx/textfile.h>
#include <wx/scrolwin.h>
#include <wx/xml/xml.h>
#include "../../Define.h"
//#include "../../music/Musique.h"
#include "../../music/MusicManager.h"
#include "../../settings/Parametre.h"
#include "PreferenceCouleur.h"
#include "PreferenceSon.h"
#include "../dialogs/DialogEnregistreM3U.h"

class PreferenceDefaut : public wxScrolledWindow
{
    public:
        PreferenceDefaut(wxWindow *Parent, wxWindowID Id);
        PreferenceDefaut(wxWindow *Parent, wxWindowID Id, PreferenceCouleur *pageCouleur, PreferenceSon *pageSon);
        virtual ~PreferenceDefaut();
        void Creer(wxWindow *Parent, wxWindowID Id);
        int CreerListe(wxChoice *liste);
        void Defaut_Bouton_Recherche(wxCommandEvent &WXUNUSED(event));
        void Defaut_Bouton_DossierDefaut(wxCommandEvent &WXUNUSED(event));
        void Evt_MAJListe(wxCommandEvent &WXUNUSED(event));
        void Defaut_RadioMP3_M3U(wxCommandEvent &event);
        void Defaut_CheckBoxCouleur(wxCommandEvent &event);
        void Defaut_CheckBoxSon(wxCommandEvent &event);
        void Defaut_CheckBoxReprise(wxCommandEvent &event);
        void Defaut_CheckBoxTAG(wxCommandEvent &WXUNUSED(event));
        void OuvertureFichier();
        void Defaut_Bouton_Portable(wxCommandEvent &WXUNUSED(event));
        void Defaut_CheckBoxDefautBDR(wxCommandEvent &WXUNUSED(event));
        void Defaut_Bouton_CheminDefaut(wxCommandEvent &WXUNUSED(event));
        void MAJListe(bool save = true);
        void SetPreferencePage(PreferenceCouleur *pageCouleur, PreferenceSon *pageSon);
        bool AutoSave();
        void AutoSave(wxCommandEvent &WXUNUSED(event));

        //wxString CheminOuvertureDefaut();

    protected:
        wxSizer *m_sizer1V, *m_sizerUseQuo, *m_sizerAvancee;
        wxChoice *m_listeCouleur, *m_listeSon, *m_listeReprise;
        wxTextCtrl *m_boiteCheminChansonRep, *m_boiteCheminDefautRech;
        wxRadioBox *m_choix;
        wxButton *m_boutonRecherche, *m_boutonCheminDefautRecherche, *m_boutonPortable;
        wxCheckBox *m_checkBox;

        PreferenceCouleur* m_pageCouleur;
        PreferenceSon *m_pageSon;

        //int m_listeM3u_mp3;

    DECLARE_EVENT_TABLE()
};

#endif // PREFERENCEDEFAUT_H_INCLUDED
