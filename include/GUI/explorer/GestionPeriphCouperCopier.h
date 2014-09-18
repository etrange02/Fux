#ifndef GESTIONPERIPHCOUPERCOPIER_H_INCLUDED
#define GESTIONPERIPHCOUPERCOPIER_H_INCLUDED

#include "../../Define.h"
#include <wx/wx.h>
#include <wx/dir.h>
#include <wx/filename.h>
//#include "../../music/Musique.h"
#include "../../music/MusicManager.h"
#include "../../tools/ThreadGestion.h"


class CouperCopierColler
{
    public:
        static CouperCopierColler* Get();
        void Delete();
        void SetArrayString(wxArrayString*, int, int, wxString chemin = wxEmptyString);
        void ModifEtatDonnee(bool reset = false);
        bool SetDestination(wxString, int);
        bool estCharge();
        int GetOrigine();

    protected:
        CouperCopierColler();
        ~CouperCopierColler();

    private:
        wxArrayString m_tableau;
        int m_action;
        int m_objetOrigine;
        wxString m_cheminOri;//Chemin du m3u
};

#endif // GESTIONPERIPHCOUPERCOPIER_H_INCLUDED
