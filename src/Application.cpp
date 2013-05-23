/***************************************************************
 * Name:      Application.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2009-07-25
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "../include/Application.h"

/**
 * @class wxFuXApp
 * @brief Classe application du programme, "contient la fonction main"
 */

BEGIN_EVENT_TABLE(wxFuXApp, wxApp)
    EVT_END_SESSION(wxFuXApp::Fermer)
END_EVENT_TABLE()

/**
 * Surcharge. Appelé au lancement de l'application
 * @return Vrai si succès.
 */
bool wxFuXApp::OnInit()
{
    // Gestion de la langue
    //TraductionInternationale();

    m_checker = new wxSingleInstanceChecker(_T("Fu(X)") + wxGetUserId());
    if (m_checker->IsAnotherRunning())
    {
        if (argc >= 2)
            EnvoiStringAutreInstance();
        else
            wxLogError(_("Fu(X) est déjà ouvert, procédure d'ouverture annulée"));//"Another program instance is already running, aborting."));

        delete m_checker; // OnExit() won't be called if we return false
        m_checker = NULL;

        return false;
    }
    else
    {
        //Parametre::Get();
        #if DEBUG
        FichierLog::Get()->Ajouter(_T("Démarrage de l'application, paramètre : ") + wxString(argc >= 2 ? argv[1] : _T("NULL")));
        #endif
        m_fenetre = new FuXFenetre(argc, argv);
        m_fenetre->Show(true);

        return true;
    }
}

/**
 * Surcharge. Appelé à la fermeture de l'application
 * @return 0 si aucun problème
 */
int wxFuXApp::OnExit()
{
    delete m_checker;
    //Parametre::Get()->~Parametre();
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("Fin de l'application"));
    FichierLog::Get()->~FichierLog();
    #endif
    return 0;
}

/**
 * Envoi à une autre instance du programme les chaînes données en argument
 */
void wxFuXApp::EnvoiStringAutreInstance()
{
    TCPClient *client = new TCPClient();
    TCPConnexionEchangeInstanceLocalHost *connexion = (TCPConnexionEchangeInstanceLocalHost*) client->MakeConnection(IPC_HOST, IPC_SERVICE, IPC_TOPIC);
    wxFileName chaine;

    if (connexion)
    {
        for (int i = 1; i<argc; i++)
        {
            chaine = argv[i];
            chaine.Normalize(wxPATH_NORM_SHORTCUT);
            if (Parametre::Get()->islisable(chaine.GetFullPath().AfterLast('.').Lower()))
            {
                if (!connexion->Execute(chaine.GetFullPath()))
                {
                    wxLogMessage(_T("Erreur lors de l'envoie du titre à l'application principale : \n") + chaine.GetFullPath());
                }
            }
            else
                wxLogMessage(_T("L'extension ") + chaine.GetExt() + _T(" n'est pas prise en compte"));
        }
        connexion->Disconnect();
        delete connexion;
    }
    else
        wxLogMessage(_T("Impossible d'envoyer le titre à l'application principale\n") + chaine.GetFullPath());
    delete client;
}

/**
 * Traduction automatique de l'application dans une langue étrangère
 */
void wxFuXApp::TraductionInternationale()
{
    // Ajout des préfixes possibles de chemins d'accès aux catalogues
    wxLocale::AddCatalogLookupPathPrefix(wxT("."));
    wxLocale::AddCatalogLookupPathPrefix(wxT(".."));
    wxLocale::AddCatalogLookupPathPrefix(_T("locale"));
    // Mise en place de la langue par défaut du système
    m_local.Init(wxLANGUAGE_DEFAULT);
    {
        wxLogNull noLog; // Supprime les erreurs si les catalogues n'existent pas
        // Catalogue de l'application
        m_local.AddCatalog(_T("Fu(X)"));
        // Catalogue de wxWidgets
        m_local.AddCatalog(_T("wxstd"));
    }
}

/**
 * Appelé en cas de fermeture de session, arrêt du programme avant de se faire tuer !
 */
void wxFuXApp::Fermer(wxCloseEvent &WXUNUSED(event))
{
    m_fenetre->Close(true);
}

IMPLEMENT_APP(wxFuXApp);
