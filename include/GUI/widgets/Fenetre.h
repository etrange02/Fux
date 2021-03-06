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
#include "settings/Parametre.h"
#include "tools/Timer.h"
#include "settings/PreferenceSon.h"
#include "settings/PreferenceCouleur.h"
#include "settings/PreferenceDefaut.h"
#include "musiclist/PlayList.h"
#include "network/TCPServeur.h"
#include "SliderSon.h"
#include "tools/FichierLog.h"
#include "tools/ArrayFenetreDetachable.h"
#include "BoutonFenetreDetachable.h"

#include "application/Mediator.h"

namespace gui
{
    namespace explorer {
        class DriveManagersPanel;
    }
    namespace music {
        class MusiqueGraph;
    }
}

class Mediator;

class FuXFenetre: public wxFrame
{
    public:
        FuXFenetre(/*Mediator& mediator, */int argc = 0, wxChar** argv = NULL);
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
        void onEventUpdatePlaylistSearchDone(wxCommandEvent &WXUNUSED(event));
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

        void changePlayPauseImageStatus();
        void drawPlayImageStatus();
        void drawPauseImageStatus();
        void playButtonPressed();
        void openDialogToPlayMusic();
        void openDialogToSelectPlayListFile();
        void deleteCurrentPlayingTitle();

        void onUpdateLine(wxCommandEvent& event);
        void onDeleteLine(wxCommandEvent& event);
        void onDirFileDialogClose (wxCommandEvent& event);
        void onDirFileDialogRange (wxCommandEvent& event);
        void onDirFileDialogUpdate(wxCommandEvent& event);
        void onDirFileRecurseQuestion(wxCommandEvent& event);

    private :

        /// Initialization methods ///
        void panelCreation();
        void panelAssociation();
        void MenuBarCreation();
        void LeftSizerCreation();

      protected:
        wxBoxSizer* sizerPrincipalH;
        wxBoxSizer* sizerGaucheV;
        wxBoxSizer* sizerDroit;
        wxBoxSizer* sizerDroitPrincipal;
        wxBoxSizer* sizerDroitPreference;
        wxBoxSizer* sizerDroitExtracteur;
        wxBoxSizer* m_sizerDroitPlaylist;
        wxBoxSizer* m_sizerRightExplorer;

        wxMenuBar* menuBarre;
        wxMenu* menuFichier;
        wxMenu* menuAffichage;
        wxMenu* menuPreferences;
        wxMenu* menuExtraction;
        wxMenu* menuAide;
        wxMenu* menuControle;
        wxNotebook* m_notebookPreference;
        wxBitmapButton* m_boutonImageLP;
        wxBitmap* m_imageBouton;

    private:
        gui::music::MusiqueGraph *m_musiqueGraph;
        TimerGraph m_TimerGraph;
        PreferenceSon *m_pageSon;
        PreferenceCouleur *m_pageCouleur;
        PreferenceDefaut *m_pageDefaut;
        PlayList *m_playList;
        bool *m_panelsAssocies;

        ArrayFenetreDetachable *m_fenetresDetachables;

        TCPServeur *m_serveur;

        int m_FenetreActuel;
        int m_nouvelleFenetre;
        gui::explorer::DriveManagersPanel* m_driveManagersPanel;
        Mediator m_mediator;

        DECLARE_EVENT_TABLE()
};


#endif // AFFICHAGE_H_INCLUDED
