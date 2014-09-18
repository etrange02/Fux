#ifndef EVENTS_H_INCLUDED
#define EVENTS_H_INCLUDED

#define EVT_MUSIQUE_CHANGE(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_MUSIQUE_CHANGE, id, wxID_ANY, \
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),

#define EVT_MUSIQUE_MAJ(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_MUSIQUE_MAJ, id, wxID_ANY, \
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),

#define EVT_MUSIQUE_LECTURE(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_MUSIQUE_LECTURE, id, wxID_ANY, \
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),

#define EVT_MUSIQUE_GRAPH(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_MUSIQUE_GRAPH, id, wxID_ANY, \
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),

#define EVT_SERVEUR(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_SERVEUR, id, wxID_ANY, \
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),

#define EVT_VIDER_PANNEAU(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_VIDER_PANNEAU, id, wxID_ANY, \
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),

#define EVT_IMAGE_SELECTION(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_IMAGE_SELECTION, id, wxID_ANY, \
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),

/*#define EVT_LISTE_PERIPH_CLAVIER(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_LISTE_PERIPH_CLAVIER, id, wxID_ANY, \
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxKeyEventFunction, &fn ), \
    (wxObject *) NULL ),

#define EVT_LISTE_PERIPH_SOURIS(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_LISTE_PERIPH_SOURIS, id, wxID_ANY, \
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),*/

#define EVT_LISTE_RENEW(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_LISTE_RENEW, id, wxID_ANY, \
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),

#define EVT_LISTE_DETAILS(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_LISTE_DETAILS, id, wxID_ANY, \
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),

#define EVT_MUSIQUE_SUPPRESSION(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_MUSIQUE_SUPPRESSION, id, wxID_ANY, \
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),

#define EVT_BOUTON_FENETRE_DETACHABLE(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_BOUTON_FENETRE_DETACHABLE, id, wxID_ANY, \
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),

#define EVT_FERMER_FENETRE_DETACHABLE(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_FERMER_FENETRE_DETACHABLE, id, wxID_ANY, \
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),

#define EVT_PREFERENCE_MAJ_LISTE(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_PREFERENCE_MAJ_LISTE, id, wxID_ANY, \
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),

#define EVT_PREFERENCE_MAJ_M3U(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_PREFERENCE_MAJ_M3U, id, wxID_ANY, \
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),

/* #define EVT_BDDTHREAD_RESULTAT(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_BDDTHREAD_RESULTAT, id, wxID_ANY, \
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxBDDResultatEventFunction, &fn ), \
    (wxObject *) NULL ),
*/

#define EVT_FUX_MUSICLIST_LIST_UPDATE(id, fn)\
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_FUX_MUSICLIST_LIST_UPDATE, id, wxID_ANY,\
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),

#define EVT_FUX_MUSICPLAYER_CHANGE_TITLE(id, fn)\
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_FUX_MUSICPLAYER_CHANGE_TITLE, id, wxID_ANY,\
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),

#define EVT_FUX_MUSICMANAGER_NO_FILE(id, fn)\
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_FUX_MUSICMANAGER_NO_FILE, id, wxID_ANY,\
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),

#define EVT_FUX_MUSICPLAYER_UPDATE_GRAPH(id, fn)\
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_FUX_MUSICPLAYER_UPDATE_GRAPH, id, wxID_ANY,\
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),

#define EVT_FUX_MUSICPLAYER_CHANGE_STATUS(id, fn)\
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_FUX_MUSICPLAYER_CHANGE_STATUS, id, wxID_ANY,\
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),


#endif // EVENTS_H_INCLUDED