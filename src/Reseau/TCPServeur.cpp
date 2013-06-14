/***************************************************************
 * Name:      TCPServeur.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2010-06-01
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../../include/Reseau/TCPServeur.h"

/**
* @class TCPServeur
* @brief Représente le serveur. Échange local de chaînes de caractères en provenance du client.
*/

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


