#ifndef GESTIONPERIPHELEMENTLECTEURRACINEFICHIER_H_INCLUDED
#define GESTIONPERIPHELEMENTLECTEURRACINEFICHIER_H_INCLUDED

#include <wx/wx.h>

class ElementLecteurRacineFichier
{
    public:
        ElementLecteurRacineFichier();
        void SetNomAffiche(wxString);
        void SetChemin(wxString);
        void SetIdGauche(int);
        void SetIdDroite(int);
        void SetUtilise(bool);
        void SetMenuItem(wxMenuItem*);

        wxString GetNomAffiche();
        wxString GetChemin();
        int GetIdGauche();
        int GetIdDroite();
        bool GetUtilise();
        wxMenuItem* GetMenuItem();
        wxMenu* GetMenu();

        void CreerMenu();
        void PasUtilise();

    protected:
        wxString m_nomAffiche, m_chemin;
        int m_idGauche, m_idDroite;
        wxMenu *m_menu;
        wxMenuItem *m_menuItem;
        bool m_utilise;
};

#endif // GESTIONPERIPHELEMENTLECTEURRACINEFICHIER_H_INCLUDED
