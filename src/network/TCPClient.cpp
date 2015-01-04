/***************************************************************
 * Name:      TCPClient.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2010-06-01
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "../../include/network/TCPClient.h"

/**
* @class TCPClient
* @brief Représente le client. Échange local de chaînes de caractères vers le serveur.
*/

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

