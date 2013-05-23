/***************************************************************
 * Name:      FenetreDetachable.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2012-01-23
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../include/FenetreDetachable.h"

/**
 * @class FenetreDetachable
 * @brief Fenêtre qui peut accueillir un panel. On obtient un "panel flottant"
 */

const wxEventType wxEVT_FERMER_FENETRE_DETACHABLE = wxNewEventType();

BEGIN_EVENT_TABLE(FenetreDetachable, wxFrame)
    EVT_CLOSE(FenetreDetachable::Fermer)
    EVT_MUSIQUE_SUPPRESSION(wxID_ANY, FenetreDetachable::RenvoieEvent)
END_EVENT_TABLE()

/**
 * Constructeur
 */
FenetreDetachable::FenetreDetachable(wxWindow* parent, wxWindow* page, wxSizer* sizer, int type, int idBouton, wxString titre) : wxFrame(NULL, -1, titre)
{
    m_page = page;
    m_page->Reparent(this);
    m_parent = parent;
    m_type = type;
    m_idBouton = idBouton;

    m_sizer = sizer;
    m_sizer->Show(true);
    SetSizer(m_sizer);
    m_sizer->SetSizeHints(this);
    SetIcon(wxIcon(Parametre::Get()->getRepertoireExecutableLib(_T("play.ico")), wxBITMAP_TYPE_ICO));
}

/**
 * Destructeur
 */
FenetreDetachable::~FenetreDetachable()
{
    Destroy();
}

/**
 * Retourne le panel associé
 * @return l'instance du panel associé
 */
wxSizer* FenetreDetachable::GetSizer()
{ return m_sizer; }

/**
 * Assoce un panel
 * @param sizer la panel à associer
 */
void FenetreDetachable::SetSizer(wxSizer* sizer)
{ m_sizer = sizer; }

/**
 * Retourne le type de la fenêtre, correspond à la classe. UTILE ?????
 */
int FenetreDetachable::GetType()
{    return m_type;}

/**
 * Retourne l'identifiant du bouton qui a causé la création de cette fenêtre
 */
int FenetreDetachable::GetIdBouton()
{    return m_idBouton;}

/**
 * Évènement - Déclenché lors d'un clic sur la croix. Envoie un message pour informer de la tentative de suppression. Le but est de récupérer les éléments internes. Le évènement envoyé contient en entier le type du panel
 * @param event
 */
void FenetreDetachable::Fermer(wxCloseEvent &WXUNUSED(event))
{
    wxCommandEvent evt(wxEVT_FERMER_FENETRE_DETACHABLE, GetId());
    evt.SetInt(m_type);
    m_parent->GetEventHandler()->AddPendingEvent(evt);
}

/**
 * Permet de remettre le panel dans son état d'origine. Renvoie le sizer contenant le panel
 * @return un pointeur vers le sizer de la fenêtre
 */
wxSizer* FenetreDetachable::RetourNormale()
{
    m_page->Reparent(m_parent);
    return m_sizer;
}

void FenetreDetachable::RenvoieEvent(wxCommandEvent &event)
{
    m_parent->GetEventHandler()->AddPendingEvent(event);
}

