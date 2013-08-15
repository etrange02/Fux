#ifndef FENETRE_H_INCLUDED
#define FENETRE_H_INCLUDED

#include <wx/wx.h>
#include <wx/app.h>
#include <wx/notebook.h>
#include <wx/filedlg.h>
#include <wx/spinctrl.h>
#include <wx/textfile.h>
#include <wx/bmpbuttn.h>
#include <wx/thread.h>
#include "../Parametre.h"
#include "../Timer.h"
#include "PreferenceSon.h"
#include "PreferenceCouleur.h"
#include "PreferenceDefaut.h"
#include "PlayList.h"
#include "GestionPeriph.h"
#include "../Reseau/TCPServeur.h"
#include "SliderSon.h"
#include "../FichierLog.h"
#include "../BDD/BDDThread.h"
#include "ArrayFenetreDetachable.h"
#include "BoutonFenetreDetachable.h"

class FuXFenetre: public wxFrame
{
  public:
    FuXFenetre(int argc = 0, wxChar** argv = NULL);
    virtual ~FuXFenetre();

    void ConstructionBarre();
    void ConstructionSizerGauche();
    void AffichePrincipal(wxCommandEvent &WXUNUSED(event));
    void AfficheDefaut(wxCommandEvent &WXUNUSED(event));
    void AffichePreference(wxCommandEvent &WXUNUSED(event));
    void AfficheEncodage(wxCommandEvent &WXUNUSED(event));
    void AfficheListeDeLecture(wxCommandEvent &WXUNUSED(event));
    void AfficheGestPeriph(wxCommandEvent &WXUNUSED(event));

    void Quitter(wxCommandEvent &event);
    void Stop(wxCommandEvent &WXUNUSED(event));
    void Lecture(wxCommandEvent &WXUNUSED(event));
    void BoutonLecture(wxCommandEvent &event);
    void BoutonChangeImage(wxCommandEvent &event);
    void Suivant(wxCommandEvent &WXUNUSED(event));
    void Precedent(wxCommandEvent &WXUNUSED(event));
    void Repete(wxCommandEvent &WXUNUSED(event));
    void Aleatoire(wxCommandEvent &WXUNUSED(event));
    void OuvrirChanson(wxCommandEvent &WXUNUSED(event));
    void OuvrirM3U(wxCommandEvent &WXUNUSED(event));
    void SupprimerListe(wxCommandEvent &WXUNUSED(event));
    void ChangementChanson(wxCommandEvent&);
    void MAJplaylist(wxCommandEvent &WXUNUSED(event));
    void SauvegardeListeLecture(wxCommandEvent&);
    void MenuAbout(wxCommandEvent &WXUNUSED(event));
    void MenuSiteWeb(wxCommandEvent &WXUNUSED(event));
    void MenuAide(wxCommandEvent &WXUNUSED(event));
    void AfficherPreferenceCouleur(wxCommandEvent &WXUNUSED(event));
    void AfficherPreferenceSon(wxCommandEvent &WXUNUSED(event));
    void AfficherPreferenceDefaut(wxCommandEvent &WXUNUSED(event));
    void EvtServeurAjout(wxCommandEvent&);
    void OnTitreChange(wxCommandEvent &WXUNUSED(event));
    void OnKeyDownRaccourci(wxKeyEvent&);
    void SeparationPanel(wxCommandEvent&);
    void ReunionPanel(wxCommandEvent&);
    void Initialisation();
    void CreerPages();
    void ChangeFenetre();

    void ModifSon(wxScrollEvent &WXUNUSED(event));
    void LecturePreference(bool);

  protected:
    wxBoxSizer *sizerPrincipalH, *sizerGaucheV, *sizerDroit, *sizerDroitPrincipal, *sizerDroitPreference, *sizerDroitExtracteur, *sizerDroitPlayist, *sizerDroitIPod;

    wxMenuBar *menuBarre;
    wxMenu *menuFichier, *menuAffichage, *menuPreferences, *menuExtraction, *menuAide, *menuControle;
    wxNotebook *m_notebookPreference;
    wxBitmapButton *m_boutonImageLP;
    wxBitmap *m_imageBouton;

    MusiqueGraph *m_musiqueGraph;
    TimerGraph m_TimerGraph;
    PreferenceSon *m_pageSon;
    PreferenceCouleur *m_pageCouleur;
    PreferenceDefaut *m_pageDefaut;
    PlayList *m_playList;
    bool *m_panelsAssocies;

    ArrayFenetreDetachable *m_fenetresDetachables;

    TCPServeur *m_serveur;

    int m_FenetreActuel, m_nouvelleFenetre;
    bool m_MAJliste;

    DECLARE_EVENT_TABLE()
};


#endif // AFFICHAGE_H_INCLUDED
