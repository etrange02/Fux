#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include <wx/wx.h>
#include <wx/snglinst.h>
#include <wx/intl.h>
#include "application/Mediator.h"

class FuXFenetre;

class FuxApplication : public wxApp
{
    public:
        FuxApplication();
        virtual bool OnInit();
        virtual int OnExit();
        void EnvoiStringAutreInstance();
        void TraductionInternationale();
        void Fermer(wxCloseEvent& event);

    private:
        wxSingleInstanceChecker *m_checker;
        wxLocale m_local;
        FuXFenetre *m_window;
        Mediator m_mediator;

    DECLARE_EVENT_TABLE()
};

DECLARE_APP(FuxApplication);

#endif // APPLICATION_H_INCLUDED
