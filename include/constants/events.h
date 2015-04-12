#ifndef EVENTS_H_INCLUDED
#define EVENTS_H_INCLUDED

/* Include a new event kind in source files :
   Header:
        extern const wxEventType wxMY_EVENT;
        // Indicates that event is defined in another file.
        // Useful to avoid multiple declarations
   Source:
        const wxEventType wxMY_EVENT = wxNewEventType();
 */

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

#define EVT_FUX_MUSICLIST_LIST_UPDATE(fn)\
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_FUX_MUSICLIST_LIST_UPDATE, wxID_ANY, wxID_ANY,\
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),

#define EVT_FUX_MUSICLIST_LIST_LINE_DELETED(fn)\
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_FUX_MUSICLIST_LIST_LINE_DELETED, wxID_ANY, wxID_ANY,\
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),

#define EVT_FUX_MUSICPLAYER_CHANGE_TITLE(fn)\
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_FUX_MUSICPLAYER_CHANGE_TITLE, wxID_ANY, wxID_ANY,\
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),

#define EVT_FUX_MUSICPLAYER_UPDATE_GRAPH(fn)\
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_FUX_MUSICPLAYER_UPDATE_GRAPH, wxID_ANY, wxID_ANY,\
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),

#define EVT_FUX_MUSICPLAYER_CHANGE_STATUS(fn)\
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_FUX_MUSICPLAYER_CHANGE_STATUS, wxID_ANY, wxID_ANY,\
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),

#define EVT_FUX_MUSICMANAGER_NO_FILE(fn)\
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_FUX_MUSICMANAGER_NO_FILE, wxID_ANY, wxID_ANY,\
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),

#define EVT_FUX_MUSICMANAGER_SEARCH_DONE(fn)\
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_FUX_MUSICMANAGER_SEARCH_DONE, wxID_ANY, wxID_ANY,\
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),

#define EVT_FUX_MUSICFILE_READER_THREAD(fn)\
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_FUX_MUSICFILE_READER_THREAD, wxID_ANY, wxID_ANY,\
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),

#define EVT_FUX_MUSICFILE_WRITER_THREAD(fn)\
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_FUX_MUSICFILE_WRITER_THREAD, wxID_ANY, wxID_ANY,\
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),

#define EVT_FUX_EXPLORERLISTCTRL_FOCUS(fn)\
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_FUX_EXPLORERLISTCTRL_FOCUS, wxID_ANY, wxID_ANY,\
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),

#endif // EVENTS_H_INCLUDED
