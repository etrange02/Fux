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
#include "../../settings/Parametre.h"
#include "../../tools/Timer.h"
#include "../settings/PreferenceSon.h"
#include "../settings/PreferenceCouleur.h"
#include "../settings/PreferenceDefaut.h"
#include "../musiclist/PlayList.h"
#include "../explorer/GestionPeriph.h"
#include "../../network/TCPServeur.h"
#include "./SliderSon.h"
#include "../../tools/FichierLog.h"
#include "../../db/BDDThread.h"
#include "../tools/ArrayFenetreDetachable.h"
#include "./BoutonFenetreDetachable.h"

class FuXFenetre: public wxFrame
{
  public:
    FuXFenetre(int argc = 0, wxChar** argv = NULL);
    virtual ~FuXFenetre();


    /// Event methods ///
    // button left panel event //
    void AffichePrincipal(wxCommandEvent &WXUNUSED(event));
    void AfficheDefaut(wxCommandEvent &WXUNUSED(event));
    void AffichePreference(wxCommandEvent &WXUNUSED(event));
    void AfficheEncodage(wxCommandEvent &WXUNUSED(event));
    void AfficheListeDeLecture(wxCommandEvent &WXUNUSED(event));
    void AfficheGestPeriph(wxCommandEvent &WXUNUSED(event));
    void AfficherPreferenceCouleur(wxCommandEvent &WXUNUSED(event));
    void AfficherPreferenceSon(wxCommandEvent &WXUNUSED(event));
    void AfficherPreferenceDefaut(wxCommandEvent &WXUNUSED(event));
    void SeparationPanel(wxCommandEvent&);
    void ReunionPanel(wxCommandEvent&);
    void EventUpdateMusicVolume(wxScrollEvent &WXUNUSED(event));
    // Bar menu event //
    void EventDeleteCurrentPlayingTitle(wxCommandEvent &WXUNUSED(event));
    void EventMusicStop(wxCommandEvent &WXUNUSED(event));
    void EventMenuBarPlay(wxCommandEvent &WXUNUSED(event));
    void EventMusicNext(wxCommandEvent &WXUNUSED(event));
    void EventMusicPrevious(wxCommandEvent &WXUNUSED(event));
    void EventMusicRandomize(wxCommandEvent &WXUNUSED(event));
    void EventMusicRepete(wxCommandEvent &WXUNUSED(event));
    void EventOpenDialogToPlayMusic(wxCommandEvent &WXUNUSED(event));
    void EventOpenDialogToSelectPlayListFile(wxCommandEvent &WXUNUSED(event));
    void EventPlayButtonPressed(wxCommandEvent &event);
    void EventQuit(wxCommandEvent &event);
    void EventSavePlayList(wxCommandEvent&);
    void EventUpdatePlayLists(wxCommandEvent &WXUNUSED(event));
    void MenuAbout(wxCommandEvent &WXUNUSED(event));
    void MenuSiteWeb(wxCommandEvent &WXUNUSED(event));
    void MenuAide(wxCommandEvent &WXUNUSED(event));
    // Internal management event //
    void EvtServeurAjout(wxCommandEvent&);
    void OnTitreChange(wxCommandEvent &WXUNUSED(event));
    void OnKeyDownRaccourci(wxKeyEvent&);
    void EventMusicChanged(wxCommandEvent&);
    void EventSwitchButtonImage(wxCommandEvent &event);
    void EventNoMusic(wxCommandEvent &WXUNUSED(event));


    /// Internal management methods ///
    void SwitchWindow();
    void readPreferences(bool loadDefaultMusic);
    void readPreferencesOldWay(bool loadDefaultMusic, wxTextFile& prefFile);
    void readPreferencesNewWay(bool loadDefaultMusic, const wxString& fileName);

    void drawPlayImageStatus();
    void drawPauseImageStatus();
    void playButtonPressed();
    void openDialogToPlayMusic();
    void openDialogToSelectPlayListFile();
    void deleteCurrentPlayingTitle();

  private :

    /// Initialization methods ///
    void panelCreation();
    void panelAssociation();
    void MenuBarCreation();
    void LeftSizerCreation();

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
