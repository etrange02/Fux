#ifndef PARAMETRE_H
#define PARAMETRE_H

#include "../Define.h"
#include "../gui/graph/MusiqueGraph.h"
#include "../music/Musique.h"
#include "../gui/widgets/SliderSon.h"
#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <wx/textfile.h>
#include <wx/filename.h>
#include <wx/xml/xml.h>
#include "Couleur.h"

class Parametre
{
    public:
        static Parametre* Get();

        wxString getCheminCouleur(wxString nom);
        wxString getCheminCouleur();
        wxString getCheminSon(wxString nom);
        wxString getCheminSon();
        bool getSousDossier();
        wxString getExtensionValideMusique();
        wxString getRepertoireDefaut();
        wxString getFiltre();
        wxString getRepertoireParametre();
        wxString getRepertoireParametre(wxString);
        wxString getRepertoireParametre(wxString, wxString);
        wxString getRepertoireParametre(wxString, wxString, wxString);
        wxString getRepertoireExecutable();
        wxString getRepertoireExecutableLib(wxString);
        bool isRepertoireInstallationDefaut();

        void setCheminCouleur(wxString);
        void setCheminSon(wxString);
        void setCouleurs(Couleur, Couleur, Couleur, Couleur, Couleur, Couleur, Couleur, bool);
        void setVolume(int, int);
        void setVolume(wxString, wxString);
        void setSousDossier(bool);
        void setRepertoireDefaut(wxString);
        bool isID3V2(const wxString&);
        bool islisable(const wxString&);
        void creerRepertoireParametre();
        void creerRepertoireParametre(wxString);

    protected:
        Parametre();
        ~Parametre();

        wxString m_cheminCouleur, m_cheminSon, m_extensionValide, m_repertoireDefaut, m_cheminRepertParam;
        bool m_doubleBarre, m_sousDossier, m_paramInstallation;
        Couleur m_fond, m_barre, m_police, m_haut, m_miSup, m_miInf, m_bas;
        wxArrayString m_extension, m_id3v2;

        //inclusion des sous dossiers, les extensions gérées, répertoire par défaut
};

#endif // PARAMETRE_H
