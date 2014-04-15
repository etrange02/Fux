#ifndef BDDTHREAD_H
#define BDDTHREAD_H

#include <wx/wx.h>
#include <wx/Thread.h>
#include <queue>
#include "BDD.h"
#include "BDDRequete.h"
#include "BDDThreadEvent.h"

class BDDThread : public wxThread
{
    public:
        static BDDThread* Get();
        virtual ~BDDThread();

        void AjouterRequete(BDDRequete *bddRequete);
        void Stop();

    protected:
        BDDThread();
        ExitCode Entry();
        void SendEvent(BDDRequete* requete, bool etat, wxArrayString* arrayS);

        //std::vector<BDDRequete*> m_vecteurBDDRequete;
        std::priority_queue<BDDRequete*, std::vector<BDDRequete*>, ComparaisonRequete> m_vecteurBDDRequete;

        BDD* m_bdd;
        bool m_continuer;
};

#endif // BDDTHREAD_H
