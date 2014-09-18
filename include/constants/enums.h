#ifndef ENUMS_H_INCLUDED
#define ENUMS_H_INCLUDED

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

#endif // ENUMS_H_INCLUDED