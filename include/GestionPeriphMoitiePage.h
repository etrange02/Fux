#ifndef GESTIONPERIPHMOITIEPAGE_H_INCLUDED
#define GESTIONPERIPHMOITIEPAGE_H_INCLUDED

#include "Define.h"
#include <wx/wx.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include "GestionPeriphTableau.h"
#include "ThreadGestion.h"
#include "DialogueFenetreExt.h"
#include "GestionPeriphCouperCopier.h"
#include "OS_Win.h"

class PageGestionPeriph : public wxPanel
{
    public :
        PageGestionPeriph(wxWindow*, wxWindowID);
        virtual ~PageGestionPeriph();
        void SetPageParallele(PageGestionPeriph*);
        void SetFichierDossier(wxString, int, bool activeLigne = false);
        int GetEtat();
        wxString GetChemin();

        void OuvrirDossierSuivant(wxCommandEvent &WXUNUSED(event));
        void OuvrirDossierPrecedent(wxCommandEvent &WXUNUSED(event));
        void OuvrirDossierPrec();
        void RechargerE(wxCommandEvent &WXUNUSED(event));

        void Recharger();
        void Suppression();
        void Copie();
        void Deplace();

        wxArrayString* GetFichierLigneSelection();
        wxArrayString* GetFichierLigneSelectionInt();
        wxArrayString* GetDossierLigneSelection();

        void OnKey(wxKeyEvent&);
        void OnMenu(wxCommandEvent&);

        void MenuCreerDossier();
        void MenuCreerM3U();
        void MenuSuprimer();
        void MenuRenommer();
        void MenuCouper();
        void MenuCopier();
        void MenuColler();
        void MenuLire();
        void MenuRaccourci();

        void Glisser(wxCommandEvent &WXUNUSED(event));
        void GlisserTraitement(wxArrayString*, long);
        bool isDragging();
        void PlacerLigneInt(wxArrayString*, long, bool);
        void PlacerLigneString(wxArrayString*, long);

    private :
        void AjoutDansFichierLigne(wxArrayString*);//Appel uniquement extérieur
        void DeplaceDansFichierLigne();
        void CopieDansFichier();

        void CopieDossierDansFichier();

        void CopieDansDossier();
        void DeplaceDansDossier();
        bool SuppressionDansFichierLigneM3u();
        bool SuppressionDansFichierLignePlaylist();
        void SuppressionDansDossier();

        void ArrayIntToString(wxArrayString*, wxString);

        PageGestionPeriph *m_pageParallele;
        ListeGestionPeriph *m_liste;
        wxString m_chemin, m_navigDef, m_texteDef;
        wxStaticBoxSizer *m_sizer1V;
        wxSizer *m_sizer1H, *m_sizer2H;
        wxTextCtrl *m_text;
        wxButton *m_boutonRecharge, *m_boutonPrecedent;
        wxCheckBox *m_checkBoxCache, *m_checkBoxFiltre;
        bool m_dragging;

    DECLARE_EVENT_TABLE()
};

#endif // GESTIONPERIPHMOITIEPAGE_H_INCLUDED
