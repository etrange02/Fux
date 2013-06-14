/***************************************************************
 * Name:      TCPClient.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2010-06-01
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../../include/Reseau/TCPClient.h"

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

