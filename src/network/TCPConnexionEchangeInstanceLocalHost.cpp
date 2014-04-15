/***************************************************************
 * Name:      TCPConnexionEchangeInstanceLocalHost.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2010-06-01
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../../include/network/TCPConnexionEchangeInstanceLocalHost.h"

const wxEventType wxEVT_SERVEUR = wxNewEventType();

/**
* @class TCPConnexionEchangeInstanceLocalHost
* @brief Représente la connexion client/serveur. Échange local de chaînes de caractères.
*/

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

