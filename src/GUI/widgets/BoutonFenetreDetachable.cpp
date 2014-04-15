/***************************************************************
 * Name:      BoutonFenetreDetachable.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2012-01-24
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../../../include/gui/widgets/BoutonFenetreDetachable.h"

/**
 * @class BoutonFenetreDetachable
 * @brief Bouton envoyant un message lors d'un glissé-sortant sur celui-ci
 */

const wxEventType wxEVT_BOUTON_FENETRE_DETACHABLE = wxNewEventType();

BEGIN_EVENT_TABLE(BoutonFenetreDetachable, wxButton)
    EVT_MOTION(BoutonFenetreDetachable::SeparationPanel)
END_EVENT_TABLE()

/**
 * Constructeur
 * @param parent la fenêtre parente
 * @param id un identifiant
 * @param label un texte
 * @param size une taille
 * @param type le type de panel associé au bouton, ie celui qui doit être affiché lors d'un clique dessus
 */
BoutonFenetreDetachable::BoutonFenetreDetachable(wxWindow *parent, wxWindowID id, const wxString &label, const wxSize &size, int type) : wxButton(parent, id, label, wxDefaultPosition, size)
{   m_type = type;}

/**
 * Destructeur
 */
BoutonFenetreDetachable::~BoutonFenetreDetachable()
{}

/**
 * Évènement - Provoque l'envoi un message lors d'un glissé-sortant du bouton
 * @param event
 */
void BoutonFenetreDetachable::SeparationPanel(wxMouseEvent &event)
{
    if (event.Dragging())
    {
        wxPoint positionSouris = event.GetPosition();
        if (positionSouris.x < 0 || positionSouris.x > GetSize().GetX() ||  positionSouris.y < 0 || positionSouris.y > GetSize().GetY())
            EnvoieMessageDrag();
    }
}

/**
 * Envoie un message de type wxEVT_BOUTON_FENETRE_DETACHABLE à la fenêtre parente. L'évènement contient le type du panel associé
 */
void BoutonFenetreDetachable::EnvoieMessageDrag()
{
    wxCommandEvent evt(wxEVT_BOUTON_FENETRE_DETACHABLE, GetId());
    evt.SetInt(m_type);
    GetParent()->GetEventHandler()->AddPendingEvent(evt);
}

