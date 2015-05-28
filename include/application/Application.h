#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include <wx/wx.h>
#include <wx/snglinst.h>
#include <wx/intl.h>
#include "gui/widgets/Fenetre.h"
#include "tools/FichierLog.h"
#include "network/TCPClient.h"
#include "network/TCPConnexionEchangeInstanceLocalHost.h"

class wxFuXApp : public wxApp
{
    public:
        virtual bool OnInit();
        virtual int OnExit();
        void EnvoiStringAutreInstance();
        void TraductionInternationale();
        void Fermer(wxCloseEvent& event);

    private:
        wxSingleInstanceChecker *m_checker;
        wxLocale m_local;
        FuXFenetre *m_fenetre;

    DECLARE_EVENT_TABLE()
};

DECLARE_APP(wxFuXApp);

#endif // APPLICATION_H_INCLUDED
