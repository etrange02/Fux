/***************************************************************
 * Name:      ComInterProcess.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2010-06-01
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../include/ComInterProcess.h"


const wxEventType wxEVT_SERVEUR = wxNewEventType();
/**
 * @class TCPConnexionEchangeInstanceLocalHost
 * @brief Représente la connexion client/serveur. Échange local de chaînes de caractères.
 */
 /**
 * @class TCPClient
 * @brief Représente le client. Échange local de chaînes de caractères vers le serveur.
 */
 /**
 * @class TCPServeur
 * @brief Représente le serveur. Échange local de chaînes de caractères en provenance du client.
 */

/////////////////////////////////////////////////
/**
 * Constructeur
 * @param parent fenêtre parente (Serveur uniquement)
 * @param id identifiant de la connexion (Serveur uniquement)
 */
TCPConnexionEchangeInstanceLocalHost::TCPConnexionEchangeInstanceLocalHost(wxWindow *parent, int id) : wxConnection()
{
    m_parent = parent;
    m_id = id;
}

/**
 * Côté client - Demande l'exécution de data donnée en paramètre.
 * @param data Ligne à exécuter
 * @return vrai si réussite, faux sinon.
 */
bool TCPConnexionEchangeInstanceLocalHost::Execute(const wxString data)
{    return wxConnection::Execute(data);}

/**
 * Côté serveur - Demande l'exécution de données
 * @param topic
 * @param data
 * @param size
 * @param format
 * @return vrai si réussite, faux sinon
 */
bool TCPConnexionEchangeInstanceLocalHost::OnExecute(const wxString& topic, wxChar *data, int WXUNUSED(size), wxIPCFormat WXUNUSED(format))//que contient topic ?
{
    if (topic == IPC_TOPIC)
        m_tableau.Add(wxString(data));
    return true;
}

/**
 * Côté serveur - Demande d'interruption de la connexion. La suppression de la classe est manuelle
 * @return vrai
 */
bool TCPConnexionEchangeInstanceLocalHost::OnDisconnect()
{
    if(m_parent!=NULL)
    {
        wxCommandEvent evt(wxEVT_SERVEUR, m_parent->GetId());
        evt.SetInt(m_id);
        m_parent->GetEventHandler()->AddPendingEvent(evt);
    }
    return true;
}

/**
 * Retourne l'identifiant de la connexion. Utilise seulement du côté serveur
 * @return l'identifiant
 */
int TCPConnexionEchangeInstanceLocalHost::GetId()
{
    return m_id;
}

/**
 * Retourne le tableau construit à partir de l'échange d'information entre le client et le serveur. Utilise seulement du côté serveur
 * @return le tableau
 */
wxArrayString* TCPConnexionEchangeInstanceLocalHost::GetTableau()
{
    return &m_tableau;
}

///////////////////////////////////////////////
/**
 * Constructeur
 */
TCPClient::TCPClient() : wxClient()
{}

/**
 * Demande la création d'une connexion
 * @return l'instance de la connexion
 */
wxConnectionBase* TCPClient::OnMakeConnection()
{    return new TCPConnexionEchangeInstanceLocalHost;}


///////////////////////////////////////////////
/**
 * Constructeur
 * @param parent Nécessaire à l'envoi d'évènements
 */
TCPServeur::TCPServeur(wxWindow *parent) : wxServer()
{    m_parent = parent; m_connexions = new ArrayOfConnexion(); m_compte = 0;}

/**
 * Destructeur
 */
TCPServeur::~TCPServeur()
{
    if (!m_connexions->IsEmpty())
        m_connexions->Clear();
}

/**
 * Serveur - Crée et retourne une connexion si celle-ci est valide
 * @param topic le "type" de connexion
 * @return une instance de la connexion
 */
wxConnectionBase* TCPServeur::OnAcceptConnection(const wxString &topic)
{
    if (topic == IPC_TOPIC)
    {
        TCPConnexionEchangeInstanceLocalHost* c = new TCPConnexionEchangeInstanceLocalHost(m_parent, m_compte++);
        m_connexions->Add(c);
        return c;
    }
    else
    {
        wxLogMessage(_("Connexion non autorisée"));
        return NULL;
    }
}

/**
 * Serveur - Supprime la connexion dont l'identifiant est id
 * @param id l'identifiant de la connexion à supprimer
 */
void TCPServeur::Deconnecter(int id)
{
    size_t i = 0;
    while (i < m_connexions->GetCount())
    {
        if (m_connexions->Item(i)->GetId() == id)
        {
            m_connexions->Remove(m_connexions->Item(i));
            i = m_connexions->GetCount();
        }
        i++;
    }
}

/**
 * Serveur - Retourne le tableau construit par la connexion n°id
 * @param id l'identifiant de la connexion
 * @return le tableau de caractères
 */
wxArrayString* TCPServeur::GetConnexionTableau(int id)
{
    size_t i = 0;
    while (i < m_connexions->GetCount())
    {
        if (m_connexions->Item(i)->GetId() == id)
             return m_connexions->Item(i)->GetTableau();
        i++;
    }
    return NULL;
}


