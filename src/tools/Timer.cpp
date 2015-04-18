/***************************************************************
 * Name:      TimerGraph.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2009-08-12
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include <wx/wx.h>
#include <wx/app.h>
#include <wx/timer.h>
#include "tools/Timer.h"
#include "MusicManagerSwitcher.h"

using namespace ::music;

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
    if (MusicManagerSwitcher::get().getMusicPlayer().isEnding())
        MusicManagerSwitcher::get().playAMusic();
    if (MusiqueGraph::Get()->IsShownOnScreen())
        MusiqueGraph::Get()->OnIdle();
}


