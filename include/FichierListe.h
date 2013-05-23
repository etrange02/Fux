#ifndef WXFICHIERLISTE_H_INCLUDED
#define WXFICHIERLISTE_H_INCLUDED

#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include <wx/textfile.h>
#include <wx/filename.h>
#include "Define.h"
#include "RechercheTraverser.h"
#include "Parametre.h"

class wxFichierListe
{
    public:
        wxFichierListe();
        void Init();
        void Fermeture();
        int GetPositionListe(wxString, int position = -1);
        int GetNombreFichier();
        wxString GetNomPosition(int);
        wxString GetCheminListe();
        void ListageFichier();
        void ListageFichier(wxArrayString*);
        void ListageFichier(wxString);
        void EffacerNom(ChansonNomPos);
        void EffacerNom(wxArrayString*);
        bool PlacerLigneInt(wxArrayString*, long, bool supprime = true);
        void PlacerLigneString(wxArrayString *ligne, long);

        void SetDossierRecherche(wxString);
        void EchangeNom(wxString, wxString);
        bool CopieFichierTOListe(wxString, wxWindow*);

    protected:
        wxString m_Liste, m_Chanson;//chemin complet de la liste
        int m_nombreFichier;//Ne pas dépasser, nombre de lignes comptées
};

#endif // WXFICHIERLISTE_H_INCLUDED
