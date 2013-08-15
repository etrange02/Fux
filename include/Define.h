#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

#define DEBUG 1

#define REPERTOIRE _T("Fu(X)")
#define IPC_SERVICE _T("4242")
#define IPC_HOST _T("localhost")
#define IPC_TOPIC _T("FUXIPC")

#include <wx/wx.h>
//Définition de la barre de menu
////Fichier
#define ID_APP_BAR_QUITTER 1
#define ID_APP_BAR_OUVRIR 2
#define ID_APP_BAR_CHARGER_M3U 3
#define ID_APP_BAR_CHARGER_MATIN 7
////Edition
#define ID_APP_BAR_CREER_PLAYLIST 4
#define ID_APP_BAR_CREER_MATIN 5
////Affichage
/*#define ID_APP_BAR_AFFICHER_PANNEAU_LATERAL 7
#define ID_APP_BAR_PLEIN_ECRAN 8
#define ID_APP_BAR_MODULE_IPOD 9 //////////
#define ID_APP_BAR_PAPIER_PEINT 10 */////////
////Préférences
#define ID_APP_BAR_COULEUR_PREFERENCE 11
#define ID_APP_BAR_SON_PREFERENCE 12
#define ID_APP_BAR_DEFAUT_PREFERENCE 13
////Outils
#define ID_APP_BAR_EXTRACTION 14
#define ID_APP_BAR_MAJ_PLAYLIST 15
//// ?
#define ID_APP_BAR_AIDE 19
#define ID_APP_BAR_A_PROPOS 20
#define ID_APP_BAR_SITE_INTERNET 21
#define ID_APP_BAR_OBTENIR_EXTENSIONS 23
//// Controles
#define ID_APP_BAR_LECTURE 24
#define ID_APP_BAR_PAUSE 25
#define ID_APP_BAR_STOP 26
#define ID_APP_BAR_SUIVANT 27
#define ID_APP_BAR_PRECEDENT 28
#define ID_APP_BAR_REPETE 29
#define ID_APP_BAR_SUPPRIMER 30
#define ID_APP_BAR_ALEATOIRE 31

//Définition des boutons du menu de gauche
#define ID_APP_AFF_PRINCIPAL 100
#define ID_APP_AFF_PREFERENCE 101
#define ID_APP_AFF_EXTRACTEUR 102
#define ID_APP_AFF_PLAYIST 103
#define ID_APP_AFF_MODULE_IPOD 104
#define ID_APP_TIMER 105
#define ID_APP_AFF_BOUTON_PRECEDENT 107
#define ID_APP_AFF_BOUTON_LECTURE 108
#define ID_APP_AFF_BOUTON_SUIVANT 109
#define ID_APP_AFF_BOUTON_SUPPRIMER 110

#define ID_APP_SLIDER_SON 120

////Onglet Couleur
#define ID_PAGE_COULEUR 200
#define ID_APP_PREF_COULEUR_TREE 201
#define ID_APP_PREF_COULEUR_MENU_SUPPRIMER 202
#define ID_APP_PREF_COULEUR_MENU_RENOMMER 203
#define ID_APP_PREF_COULEUR_TEXT_NOM 204

//#define ID_APP_PREF_COULEUR_APPLIQUER 205
//#define ID_APP_PREF_COULEUR_SUPPRIMER 206
//#define ID_APP_PREF_COULEUR_ACTUEL 207
//#define ID_APP_PREF_COULEUR_BOITE 208
#define ID_APP_PREF_COULEUR_IMG_FOND 209
#define ID_APP_PREF_COULEUR_IMG_BARRE 210
#define ID_APP_PREF_COULEUR_IMG_GRAPH_HAUT 211
#define ID_APP_PREF_COULEUR_IMG_GRAPH_BAS 212
#define ID_APP_PREF_COULEUR_SLIDER_FOND 213
#define ID_APP_PREF_COULEUR_SLIDER_BARRE 214
#define ID_APP_PREF_COULEUR_BOX_HAUT 215
#define ID_APP_PREF_COULEUR_BOX_BAS 216
#define ID_APP_PREF_COULEUR_BOX_DOUBLE 217


////Onglet Son
#define ID_PAGE_SON 300
#define ID_APP_PREF_SON_TREE 301
#define ID_APP_PREF_SON_MENU_SUPPRIMER 302
#define ID_APP_PREF_SON_MENU_RENOMMER 303
#define ID_APP_PREF_SON_TEXT_NOM 304
#define ID_APP_PREF_SON_TEXT_VOLUME 305
#define ID_APP_PREF_SON_TEXT_VOLUME_PC 306
//#define ID_APP_PREF_SON_ACTUEL 308
//#define ID_APP_PREF_SON_BOITE 307

////Onglet Defaut
#define ID_PAGE_DEFAUT 400
#define ID_APP_PREF_DEFAUT_LISTE_SON 401
#define ID_APP_PREF_DEFAUT_LISTE_COULEUR 402
#define ID_APP_PREF_DEFAUT_LISTE_M3U 403
#define ID_APP_PREF_DEFAUT_RECHERCHE 406
#define ID_APP_PREF_DEFAUT_BOX_COULEUR 407
#define ID_APP_PREF_DEFAUT_BOX_SON 408
#define ID_APP_PREF_DEFAUT_PORTABLE 409
#define ID_APP_PREF_DEFAUT_BOX_REPRISE 410
#define ID_APP_PREF_DEFAUT_CHOIX 411
#define ID_APP_PREF_DEFAUT_BOX_RECHERCHE 412
#define ID_APP_PREF_DEFAUT_CHEMIN_RECHERCHE_DEFAUT 413
#define ID_APP_PREF_DEFAUT_BOX_TAG 414
#define ID_APP_PREF_DEFAUT_BOX_DEFAUT_BDR 415

//Liste de lecture
#define ID_PAGE_PLAYLIST_LISTE 500
#define ID_PAGE_PLAYLIST_BOUTON_ENREGISTRE_M3U 501
#define ID_PAGE_PLAYLIST_BOUTON_APPLIQUER 502
#define ID_PAGE_PLAYLIST_BOUTON_ANNULER 503
#define ID_PAGE_PLAYLIST_PANNEAUREPLIABLE 504
#define ID_PAGE_PLAYLIST_POCHETTE 505
#define ID_PAGE_PLAYLIST_MENU_LECTURE 506
#define ID_PAGE_PLAYLIST_MENU_PAUSE 507
#define ID_PAGE_PLAYLIST_MENU_SUPPRIMER 508
#define ID_PAGE_PLAYLIST_MENU_COUPER 509
#define ID_PAGE_PLAYLIST_MENU_COLLER 510
#define ID_PAGE_PLAYLIST_MENU_DETAILS 511
#define ID_PAGE_PLAYLIST_CHAMPS_RECHERCHE_LOCALE 512
#define POCHETTE_COTE 90

#define ID_PAGE_PLAYLIST_DETAILS_POCHETTE 520

// Exploration
//#define ID_PAGE_PERIHERIQUE_LISTE 600
#define ID_PAGE_PERIHERIQUE_BOUTON_MESDOC 601
#define ID_PAGE_PERIHERIQUE_MENU_MESDOC_GAUCHE 602
#define ID_PAGE_PERIHERIQUE_MENU_MESDOC_DROITE 603
#define ID_PAGE_PERIHERIQUE_BOUTON_PERIPH 604
//#define ID_PAGE_PERIHERIQUE_MENU_PERIPH_EJECTER 607
#define ID_PAGE_PERIHERIQUE_BOUTON_AUTRE 608
#define ID_PAGE_PERIHERIQUE_MENU_PLAYLIST_GAUCHE 611
#define ID_PAGE_PERIHERIQUE_MENU_PLAYLIST_DROITE 612
#define ID_PAGE_PERIHERIQUE_BOUTON_PRECEDENT_G 613
#define ID_PAGE_PERIHERIQUE_BOUTON_PRECEDENT_D 614
#define ID_PAGE_PERIHERIQUE_BOUTON_RECHARGE_G 615
#define ID_PAGE_PERIHERIQUE_BOUTON_RECHARGE_D 616
#define ID_PAGE_PERIHERIQUE_BOUTON_DEPLACE_POURG 617
#define ID_PAGE_PERIHERIQUE_BOUTON_DEPLACE_POURD 618
#define ID_PAGE_PERIHERIQUE_BOUTON_COPIE 619
#define ID_PAGE_PERIHERIQUE_BOUTON_SUPPRIMER 620
#define ID_PAGE_PERIHERIQUE_CHECKBOX_CACHE_G 621
#define ID_PAGE_PERIHERIQUE_CHECKBOX_CACHE_D 622
#define ID_PAGE_PERIHERIQUE_LISTE_G 623
#define ID_PAGE_PERIHERIQUE_LISTE_D 624
#define ID_PAGE_PERIHERIQUE_MENU_CREER_DOSSIER 625
#define ID_PAGE_PERIHERIQUE_MENU_CREER_M3U 626
#define ID_PAGE_PERIHERIQUE_MENU_COPIER 627
#define ID_PAGE_PERIHERIQUE_MENU_COLLER 628
#define ID_PAGE_PERIHERIQUE_MENU_COUPER 629
#define ID_PAGE_PERIHERIQUE_MENU_RACCOURCI 630
#define ID_PAGE_PERIHERIQUE_MENU_RENOMMER 631
#define ID_PAGE_PERIHERIQUE_MENU_SUPPRIMER 632
#define ID_PAGE_PERIHERIQUE_MENU_TOUT_SELECTIONNER 633
#define ID_PAGE_PERIHERIQUE_MENU_LIRE 634
#define ID_PAGE_PERIHERIQUE_GAUCHE 645
#define ID_PAGE_PERIHERIQUE_DROITE 646
#define ID_PAGE_PERIHERIQUE_TEXTE_G 647
#define ID_PAGE_PERIHERIQUE_TEXTE_D 648

#define ID_DIALOGUE_SAUVEGARDE_M3U 700
#define ID_DIALOGUE_FENETRE_MENU_AFFBARRE 701
#define ID_DIALOGUE_FENETRE_MENU_QUITTER 702


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

enum e_ChangeChanson
{SUIVANT, PRECEDENT, IDENTIQUE};
enum
{PRINCIPAL = 0, LISTELECTURE = 1, GESTIONPERIPH = 2, PREFERENCE = 3, ENCODAGE = 4};
enum
{NOUVEAU = 0, MODIFIER = 1};
enum e_Couleur
{ROUGE = 0, VERT = 1, BLEU = 2, ALPHA = 3};
enum e_GraphPosition
{FOND = 0, BARRE = 1, HAUT_SUP = 2, BAS_INF = 3};
enum e_BoxPreferenceDefaut
{COULEUR = 0, SON = 1, REPRISE = 2, SOUSDOSSIER = 3, TAG = 4, DEFAUT = 5};
enum
{MP3 = 0, M3U = 1};
enum
{GAUCHE = 0, DROITE = 1};
enum
{VIDE = 0, DOSSIER = 2, PLAYLIST = 3};//M3U = 1
enum
{COPIE = 0, COUPER = 1, DEPLACE = 2, SUPPRIME = 4};
enum
{PREC = 0, LECT = 1, PAUS = 2, SUIV = 3, SUPPR = 4};

enum e_BDDRequete
{
    BDD_SUPPRIMER = 25,
    BDD_MODIFIER = 26,
    BDD_AJOUTER_UTILISATEUR = 49,
    BDD_AJOUTER_CHANSON_ALBUM_ARTISTE = 50,
    BDD_AJOUTER_ALBUM_ARTISTE = 51,
    BDD_AJOUTER_CHANSON_ARTISTE = 52,
    BDD_AJOUTER_CHANSON_ALBUM = 53,
    BDD_AJOUTER_ALBUM = 75,
    BDD_AJOUTER_ARTISTE = 76,
    BDD_AJOUTER_CHANSON = 77,
    BDD_RECHERCHER = 99,
    BDD_GET = 100
};

#endif // DEFINE_H_INCLUDED
