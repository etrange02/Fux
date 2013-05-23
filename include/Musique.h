#ifndef MUSIQUE_H_INCLUDED
#define MUSIQUE_H_INCLUDED

#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <ctime>
#include <FMODex/fmod.hpp>
#include "Define.h"
#include "FichierListe.h"
#include "FichierLog.h"

class wxFichierListe;

extern const wxEventType wxEVT_MUSIQUE_CHANGE;
extern const wxEventType wxEVT_MUSIQUE_MAJ;
extern const wxEventType wxEVT_MUSIQUE_LECTURE;//pause et lecture
extern const wxEventType wxEVT_MUSIQUE_GRAPH;

class Musique
{
    public:
        Musique(wxWindow*);
        virtual ~Musique();
        static Musique* Get();

        int GetDureeMS();
        int GetTpsActuel();
        DUREE GetDUREEDuree();
        DUREE GetDUREETpsActuel();
        void SetPositionMS(int);
        bool IsContainingMus();
        bool GetPause();
        bool GetRepete();
        bool GetAleatoire();
        bool GetLecture();
        float GetVolume();
        wxString GetAlbum();
        wxString GetArtiste();
        wxString GetNomChanson();
        wxString GetPlaylist();
        wxString GetDureeFormatMinSec();
        ChansonNomPos GetNomPos();

        void SetAction(e_ChangeChanson);
        void SetPause(bool);
        void SetRepete(bool);
        void SetAleatoire(bool);
        void SetStop();
        ChansonNomPos SupprimerNom();
        void SupprimerNom(int);
        void SupprimerNom(wxArrayString*, bool maj = false);
        void SetVolume(int);

        bool ChangementChanson(e_ChangeChanson);
        bool ChangementChanson(long, wxString chaine = wxEmptyString);
        bool ChangementChanson();
        bool VerifTemps();
        void PlacerLigneInt(wxArrayString*, long, bool maj = true, bool supprime = true);
        void PlacerLigneString(wxArrayString* chaine, long pos, bool maj = true);
        void Lecture(wxString);
        void DureeMS();
        void TpsActuelMS();
        void Listage();
        void Listage(wxArrayString*, bool maj = false);
        void Listage(wxString);
        void CopieFichier(wxString);
        void RemplirSpectre(float[], int);
        void ModifListeVide();
        void Recharger(bool maj = true, bool lect = true);

        wxFichierListe* GetFichier();

    protected:
        wxWindow *m_parent;
        FMOD_SYSTEM *m_system;
        FMOD_SOUND *m_sound;
        FMOD_CHANNEL *m_channel;
        //FMOD_CODEC_DESCRIPTION m_infoCodec;
        float *m_volumeSysteme, m_volume;
        int m_positionListe;
        e_ChangeChanson m_action;//puissance de 2, 64 à 8192
        bool m_stop, m_aleatoire, m_musCharge, m_isPlaying;
        wxString m_nomChanson, m_cheminComplet, m_album, m_artiste;
        DUREE m_duree, m_tpsActuel;
        wxFichierListe *m_liste;
};

#endif // MUSIQUE_H_INCLUDED
