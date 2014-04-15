/***************************************************************
 * Name:      TimerGraph.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2009-08-12
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include <wx/wx.h>
#include <wx/app.h>
#include <wx/timer.h>
#include "../../include/tools/Timer.h"

/**
 * @class TimerGraph
 * @brief Timer gérant la mise à jour du graphe et le passage d'une chanson à l'autre
 */

/**
 * Constructeur
 */
TimerGraph::TimerGraph()
{}

/**
 * Destructeur
 */
TimerGraph::~TimerGraph()
{}

/**
 * Réécriture. Méthode appelé à chaque exécution du thread.
 */
void TimerGraph::Notify()
{
    if (Musique::Get()->VerifTemps())
        Musique::Get()->ChangementChanson();
    if (MusiqueGraph::Get()->IsShownOnScreen())
        MusiqueGraph::Get()->OnIdle();
}


