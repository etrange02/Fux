/***************************************************************
 * Name:      SliderSon.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2011-09-01
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
 #include "../../include/GUI/SliderSon.h"

/**
 * @class SliderSon
 * @brief Contrôleur du volume sonore de la musique
 */

static SliderSon* s_instanceSliderSon = NULL;

/**
 * Constructeur
 * @param parent Fenêtre parente (pour les évènements)
 */
SliderSon::SliderSon()
{}

/**
 * Destructeur
 */
SliderSon::~SliderSon()
{}

/**
 * Retourne l'instance de la classe
 * @return l'instance
 */
SliderSon* SliderSon::Get()
{
    if (s_instanceSliderSon == NULL)
        s_instanceSliderSon = new SliderSon();
    return s_instanceSliderSon;
}

/**
 * Augmente la valeur de la barre et en informe le système. Le volume augmente
 * @see SonDown
 */
void SliderSon::SonUp()
{
    int volume = GetValue() + 7;
    SetValue( (volume > 100) ? 100 : volume );
    wxCommandEvent evt(wxEVT_SCROLL_TOP, GetId());
    GetParent()->GetEventHandler()->AddPendingEvent(evt);
}

/**
 * Diminue la valeur de la barre et en informe le système. Le volume baisse
 * @see SonUp
 */
void SliderSon::SonDown()
{
    int volume = GetValue() - 7;
    SetValue( (volume < 0)?0:volume );
    wxCommandEvent evt(wxEVT_SCROLL_TOP, GetId());
    GetParent()->GetEventHandler()->AddPendingEvent(evt);
}




