/***************************************************************
 * Name:      SliderSon.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2011-09-01
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
 #include "../include/SliderSon.h"

/**
 * @class SliderSon
 * @brief Contrôleur du volume sonore de la musique
 */

static SliderSon* instanceSliderSon = NULL;

/**
 * Constructeur
 * @param parent Fenêtre parente (pour les évènements)
 */
SliderSon::SliderSon(wxWindow *Parent) : wxSlider(Parent, ID_APP_SLIDER_SON, 100, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL)
{    instanceSliderSon = this;}

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
{    return instanceSliderSon;}

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




