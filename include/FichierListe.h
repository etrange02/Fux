#ifndef WXFICHIERLISTE_H_INCLUDED
#define WXFICHIERLISTE_H_INCLUDED

#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include <wx/textfile.h>
#include <wx/filename.h>
#include "Define.h"
#include "DirTraverser/Recherche.h"
#include "Parametre.h"
#include "ChansonNomPos.h"

class FichierListe
{
    public:
        static FichierListe *Get();
        void Delete();
        void OnExit();
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

    private:
        FichierListe();
        virtual ~FichierListe();

    protected:
        void Init();

        wxString m_Liste, m_Chanson;//chemin complet de la liste
        int m_nombreFichier;//Ne pas dépasser, nombre de lignes comptées
};

#endif // WXFICHIERLISTE_H_INCLUDED
