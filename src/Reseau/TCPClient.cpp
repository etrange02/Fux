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
* @brief Repr�sente le client. �change local de cha�nes de caract�res vers le serveur.
*/

/**
 * Constructeur
 */
TCPClient::TCPClient() : wxClient()
{}

/**
 * Demande la cr�ation d'une connexion
 * @return l'instance de la connexion
 */
wxConnectionBase* TCPClient::OnMakeConnection()
{    return new TCPConnexionEchangeInstanceLocalHost;}

