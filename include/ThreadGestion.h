#ifndef THREADGESTION_H_INCLUDED
#define THREADGESTION_H_INCLUDED

#include <wx/wx.h>
#include <wx/thread.h>
#include <wx/dynarray.h>
#include "Define.h"
#include "DirTraverser/TraverserCopieDossier.h"
#include "DirTraverser/TraverserCopieFichier.h"
#include "DirTraverser/TraverserDeplaceFichier.h"
#include "DirTraverser/TraverserSupprimeFichier.h"
#include "ElementThreadFichier.h"
#include "FichierLog.h"

WX_DEFINE_ARRAY(ElementThreadFichier*, ArrayOfElementThreadFichier);

class ThreadFichierFichier : public wxThread
{
    public:
        void AjoutDonnee(wxArrayString*, int, wxString dest = wxEmptyString);
        static ThreadFichierFichier* Get();
        bool GetEtat();
        void SetStop();
        void ViderListe();

    private:
        ThreadFichierFichier();
        virtual ~ThreadFichierFichier();
        virtual void* Entry();
        void DossierSuppression(wxArrayString&);//Deplace inutile !!
        void DossierCopie(wxString, wxString);
        void FichierSuppression(wxString);
        void FichierCopie(wxString, wxString);
        void FichierDeplace(wxString, wxString);

        bool m_estActif, m_continue;
        //ListeThreadFichier m_liste;
        ArrayOfElementThreadFichier *m_liste;
};

#endif // THREADGESTION_H_INCLUDED
