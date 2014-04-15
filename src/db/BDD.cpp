/***************************************************************
 * Name:      BDD.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2011-11-29
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include "../../include/db/BDD.h"

/**
 * @class BDD
 * @brief Représente la base de données de Fu(X) (ou l'audiothèque)
 */

/********* Base de données ***********/
/*
chanson     (id INTEGER PRIMARY KEY AUTOINCREMENT, nom VARCHAR(255), adresse VARCHAR(255), annee CHAR(4), genre INTEGER)//dansabilité
artiste     (id INTEGER PRIMARY KEY AUTOINCREMENT, nom VARCHAR(75))
album       (id INTEGER PRIMARY KEY AUTOINCREMENT, nom VARCHAR(100), annee_parution CHAR(4))
utilisateur (id INTEGER PRIMARY KEY AUTOINCREMENT, nom VARCHAR(60))


produit     (id_chanson INTEGER REFERENCES chanson(id), id_artiste INTEGER REFERENCES artiste(id),          PRIMARY KEY(id_chanson, id_artiste))
publie      (id_artiste INTEGER REFERENCES artiste(id), id_album INTEGER REFERENCES album(id),              PRIMARY KEY(id_artiste, id_album))
contient    (id_chanson INTEGER REFERENCES chanson(id), id_album INTEGER REFERENCES album(id),              PRIMARY KEY(id_chanson, id_album))

listeperso  (id_utilisateur INTEGER REFERENCES utilisateur(id), id_chanson INTEGER REFERENCES chanson(id),  PRIMARY KEY(id_utilisateur, id_chanson))
remix       (id INTEGER REFERENCES chanson(id),                 id_original INTEGER REFERENCES chanson(id), PRIMARY KEY(id, id_original))
*/

/**
 * Constructeur, ne pas appeler
 * @see BDD::Get()
 */
BDD::BDD()
{
    wxSQLite3Database::InitializeSQLite();
    m_database = new wxSQLite3Database();
    m_database->Open(Parametre::Get()->getRepertoireParametre(_T("fux.db")));
    CreerTables();
}

BDD::~BDD()
{
    FichierLog::Get()->Ajouter(_T("BDD::~BDD"));
}

/**
 * Ferme la base de données
 */
void BDD::Close()
{
    m_database->Close();
    delete m_database;
    wxSQLite3Database::ShutdownSQLite();
}

/**
 * Crée les différentes tables si celles-ci n'existent pas dans la base de données.
 */
void BDD::CreerTables()
{
    if (!m_database->TableExists(_T("chanson")))
        m_database->ExecuteUpdate(_T("CREATE TABLE chanson(id INTEGER PRIMARY KEY AUTOINCREMENT, nom VARCHAR(255), adresse VARCHAR(255), annee CHAR(4), genre CHAR(30));"));//dansabilité
    if (!m_database->TableExists(_T("artiste")))
        m_database->ExecuteUpdate(_T("CREATE TABLE artiste(id INTEGER PRIMARY KEY AUTOINCREMENT, nom VARCHAR(75));"));
    if (!m_database->TableExists(_T("album")))
        m_database->ExecuteUpdate(_T("CREATE TABLE album(id INTEGER, id_artiste INTEGER REFERENCES artiste(id), nom VARCHAR(100), annee_parution CHAR(4), PRIMARY KEY(id, id_artiste));"));//AAAA-MM-JJ

    if (!m_database->TableExists(_T("produit")))
        m_database->ExecuteUpdate(_T("CREATE TABLE produit(id_chanson INTEGER REFERENCES chanson(id), id_artiste INTEGER REFERENCES artiste(id), PRIMARY KEY(id_chanson, id_artiste));"));
    //if (!m_database->TableExists("publie"))
    //    m_database->ExecuteUpdate("CREATE TABLE publie(id_artiste INTEGER REFERENCES artiste(id), id_album INTEGER REFERENCES album(id), PRIMARY KEY(id_artiste, id_album))");
    if (!m_database->TableExists(_T("contient")))
        m_database->ExecuteUpdate(_T("CREATE TABLE contient(id_chanson INTEGER REFERENCES chanson(id), id_album INTEGER REFERENCES album(id), PRIMARY KEY(id_chanson, id_album));"));//AAAA-MM-JJ

    if (!m_database->TableExists(_T("utilisateur")))
        m_database->ExecuteUpdate(_T("CREATE TABLE utilisateur(id INTEGER PRIMARY KEY AUTOINCREMENT, nom VARCHAR(60))"));
    if (!m_database->TableExists(_T("listeperso")))
        m_database->ExecuteUpdate(_T("CREATE TABLE listeperso(id_utilisateur INTEGER REFERENCES utilisateur(id), id_chanson INTEGER REFERENCES chanson(id), PRIMARY KEY(id_utilisateur, id_chanson));"));
    if (!m_database->TableExists(_T("remix")))
        m_database->ExecuteUpdate(_T("CREATE TABLE remix(id INTEGER REFERENCES chanson(id), id_original INTEGER REFERENCES chanson(id), PRIMARY KEY(id, id_original));"));
}

/**
 * Ajoute une chanson avec ses différents paramètres dans la base de données
 * @param nom le nom de la chanson
 * @param adresse le chemin complet du dossier dans lequel se trouve la chanson
 * @param annee l'année de parution de la chanson
 * @param genre le genre de la chanson
 * @return vrai si l'ajout a été fait
 */
bool BDD::AjouterChanson(wxString nom, wxString adresse, wxString annee, wxString genre)
{
    bool res = false;
    try
    {
        wxSQLite3Transaction t(m_database);
        res = m_database->ExecuteUpdate(_T("INSERT INTO chanson VALUES(NULL, \"") + nom + _T("\", \"") + adresse + _T("\", \"") + annee + _T("\", \"") + genre + _T("\");"));
        t.Commit();
    }
    catch (...) {}
    return res;
}

/**
 * Ajoute une chanson avec ses différents paramètres dans la base de données
 * @param nomComplet le nom complet de la chanson
 * @param annee l'année de parution de la chanson
 * @param genre le genre de la chanson
 * @return vrai si l'ajout a été fait
 */
bool BDD::AjouterChanson(wxString nomComplet, wxString annee, wxString genre)
{
    return AjouterChanson(nomComplet.AfterLast(wxFileName::GetPathSeparator()), nomComplet.BeforeLast(wxFileName::GetPathSeparator()), annee, genre);
}

/**
 * Ajoute un artiste à la base de données
 * @param nom Le nom de l'artiste
 * @return vrai si l'ajout a été fait
 */
bool BDD::AjouterArtiste(wxString nom)
{
    return m_database->ExecuteUpdate(_T("INSERT INTO artiste VALUES(NULL, \"") + nom + _T("\");"));
}

/**
 * Ajoute un album à la base de données
 * @param nom Le nom de l'album
 * @param idArtiste L'identifiant de l'artiste à l'origine de l'album
 * @param idAlbum Si égale à 0, ajout d'un nouvel album. Sinon, permet de faire une association pour les collaborations
 * @return vrai si l'ajout a été fait
 */
bool BDD::AjouterAlbum(wxString nom, int idArtiste, int idAlbum) // idAlbum=-1
{
    if (idAlbum == -1)
        return m_database->ExecuteUpdate(_T("INSERT INTO album VALUES(NULL, ") + wxString::Format(_T("%d"), idArtiste) + _T(", \"") + nom + _T("\")"));
    else
        return m_database->ExecuteUpdate(_T("INSERT INTO album VALUES(") + wxString::Format(_T("%d"), idAlbum) + _T(", ") + wxString::Format(_T("%d"), idArtiste) + _T(", \"") + nom + _T("\")"));
}

/**
 * Associe une chanson à un artiste
 * @param idChanson l'identifiant de la chanson
 * @param idArtiste l'identifiant de l'artiste
 * @return vrai si l'ajout a été fait
 */
bool BDD::AjouterArtisteProduitChanson(int idChanson, int idArtiste)
{
    return m_database->ExecuteUpdate(wxString::Format(_T("INSERT INTO produit VALUES(%d, %d)"), idChanson, idArtiste));
}

/**
 * Associe une chanson à un album
 * @param idChanson l'identifiant de la chanson
 * @param idAlbum l'identifiant de l'album
 * @return vrai si l'ajout a été fait
 */
bool BDD::AjouterAlbumContientChanson(int idChanson, int idAlbum)
{
    return m_database->ExecuteUpdate(wxString::Format(_T("INSERT INTO contient VALUES(%d, %d)"), idChanson, idAlbum));
}

/**
 * Ajoute un utilisateur à la base de données
 * @param nom Le nom de l'utilisateur
 * @return vrai si l'ajout a été fait
 */
bool BDD::AjouterUtilisateur(wxString nom)
{
    return m_database->ExecuteUpdate(_T("INSERT INTO utilisateur VALUES (NULL, \"") + nom + _T("\")"));
}

/**
 * Associe un titre à un utilisateur
 * @param idUtilisateur l'identifiant de l'utilisateur
 * @param idChanson l'identifiant de la chanson
 * @return vrai si l'ajout a été fait
 */
bool BDD::AjouterListePerso(int idUtilisateur, int idChanson)
{
    return m_database->ExecuteUpdate(wxString::Format(_T("INSERT INTO listeperso VALUES (%d, %d)"), idUtilisateur, idChanson));
}

/**
 * Associe deux chansons entre elles : la première est une reprise de la seconde
 * @param idRemix l'identifiant de la reprise
 * @param idOriginal l'identifiant de la chanson originelle
 * @return vrai si l'ajout a été fait
 */
bool BDD::AjouterRemixDe(int idRemix, int idOriginal)
{
    return m_database->ExecuteUpdate(wxString::Format(_T("INSERT INTO remix VALUES (%d, %d)"), idRemix, idOriginal));
}

/**
 * Modifie le nom d'une chanson
 * @param id l'identifiant de la chanson
 * @param nom le nom de la chanson
 * @return vrai si la modification a été faite
 */
bool BDD::ModifierChansonNom(int id, wxString nom)
{
    return m_database->ExecuteUpdate(_T("UPDATE chanson SET nom=\"") + nom + _T("\" WHERE id=") + wxString::Format(_T("%d"), id));
}

/**
 * Modifie l'année de parution d'une chanson
 * @param id l'identifiant de la chanson
 * @param annee l'année de parution
 * @return vrai si la modification a été faite
 */
bool BDD::ModifierChansonAnnee(int id, wxString annee)
{
    return m_database->ExecuteUpdate(_T("UPDATE chanson SET annee=\"") + annee + _T("\" WHERE id=") + wxString::Format(_T("%d"), id));
}

/**
 * Modifie le genre d'une chanson
 * @param id l'identifiant de la chanson
 * @param genre le genre de la chanson
 * @return vrai si la modification a été faite
 */
bool BDD::ModifierChansonGenre(int id, wxString genre)
{
    return m_database->ExecuteUpdate(_T("UPDATE chanson SET genre=\"") + genre + _T("\" WHERE id=") + wxString::Format(_T("%d"), id));
}
/**
 * Modifie le nom d'un artiste
 * @param id l'identifiant de l'artiste
 * @param nom le nom de l'artiste
 * @return vrai si la modification a été faite
 */

bool BDD::ModifierArtisteNom(int id, wxString nom)
{
    return m_database->ExecuteUpdate(_T("UPDATE artiste SET nom=\"") + nom + _T("\" WHERE id=") + wxString::Format(_T("%d"), id));
}

/**
 * Modifie le nom d'un album
 * @param id l'identifiant de l'album
 * @param nom le nom de l'album
 * @return vrai si la modification a été faite
 */
bool BDD::ModifierAlbumNom(int id, wxString nom)
{
    return m_database->ExecuteUpdate(_T("UPDATE album SET nom=\"") + nom + _T("\" WHERE id=") + wxString::Format(_T("%d"), id));
}

/**
 * Modifie l'année de parution d'un album
 * @param id l'identifiant de l'album
 * @param annee l'année de parution de l'album
 * @return vrai si la modification a été faite
 */
bool BDD::ModifierAlbumAnnee(int id, wxString annee)
{
    return m_database->ExecuteUpdate(_T("UPDATE album SET annee=\"") + annee + _T("\" WHERE id=") + wxString::Format(_T("%d"), id));
}

/**
 * Modifie le nom d'un utilisateur
 * @param id l'identifiant de l'utilisateur
 * @param nom le nom de l'utilisateur
 * @return vrai si la modification a été faite
 */
bool BDD::ModifierUtilisateurNom(int id, wxString nom)
{
    return m_database->ExecuteUpdate(_T("UPDATE utilisateur SET nom=\"") + nom + _T("\" WHERE id=") + wxString::Format(_T("%d"), id));
}

/**
 * Supprime une chanson
 * @param id l'identifiant de la chanson
 * @return vrai si la modification a été faite
 */
bool BDD::SupprimerChanson(int id)
{
    m_database->ExecuteUpdate(wxString::Format(_T("DELETE FROM produit WHERE id_chanson=%d"), id));
    m_database->ExecuteUpdate(wxString::Format(_T("DELETE FROM contient WHERE id_chanson=%d"), id));
    m_database->ExecuteUpdate(wxString::Format(_T("DELETE FROM listeperso WHERE id_chanson=%d"), id));
    m_database->ExecuteUpdate(wxString::Format(_T("DELETE FROM remix WHERE id=%d"), id));
    m_database->ExecuteUpdate(wxString::Format(_T("DELETE FROM remix WHERE id_original=%d"), id));
    return m_database->ExecuteUpdate(wxString::Format(_T("DELETE FROM chanson WHERE id=%d"), id));
}

/**
 * Supprime une chanson
 * @param nomComplet le nom complet de la chanson
 * @return vrai si la modification a été faite
 */
bool BDD::SupprimerChanson(wxString nomComplet)
{
    return SupprimerChanson(GetChansonIDs(nomComplet, true)->Item(0));
}

/**
 * Supprime un album
 * @param id l'identifiant de l'album
 * @return vrai si la modification a été faite
 */
bool BDD::SupprimerAlbum(int id)
{
    m_database->ExecuteUpdate(wxString::Format(_T("DELETE FROM contient WHERE id_album=%d"), id));
    return m_database->ExecuteUpdate(wxString::Format(_T("DELETE FROM album WHERE id=%d"), id));
}

/**
 * Supprime un artiste
 * @param id l'identifiant de l'artiste
 * @return vrai si la modification a été faite
 */
bool BDD::SupprimerArtiste(int id)
{
    m_database->ExecuteUpdate(wxString::Format(_T("DELETE FROM contient WHERE id_artiste=%d"), id));
    return m_database->ExecuteUpdate(wxString::Format(_T("DELETE FROM artiste WHERE id=%d"), id));
}

/**
 * Supprime un artiste
 * @param nom le nom de l'artiste
 * @return vrai si la modification a été faite
 */
bool BDD::SupprimerArtiste(wxString nom)
{
    return SupprimerArtiste(GetArtisteIDs(nom)->Item(0));
}

/**
 * Supprime un utilisateur
 * @param id l'identifiant de l'utilisateur
 * @return vrai si la modification a été faite
 */
bool BDD::SupprimerUtilisateur(int id)
{
    m_database->ExecuteUpdate(wxString::Format(_T("DELETE FROM listeperso WHERE id_utilisateur=%d"), id));
    return m_database->ExecuteUpdate(wxString::Format(_T("DELETE FROM utilisateur WHERE id=%d"), id));
}

/**
 * Supprime un utilisateur
 * @param nom le nom de l'utilisateur
 * @return vrai si la modification a été faite
 */
bool BDD::SupprimerUtilisateur(wxString nom)
{
    return SupprimerUtilisateur(GetUtilisateurID(nom));
}

/**
 * Supprime une association chanson-artiste
 * @param idChanson l'identifiant de la chanson
 * @param idArtiste l'identifiant de l'artiste
 * @return vrai si la modification a été faite
 */
bool BDD::SupprimerProduit(int idChanson, int idArtiste)
{
    return m_database->ExecuteUpdate(wxString::Format(_T("DELETE FROM produit WHERE id_chanson=%d AND id_artiste=%d"), idChanson, idArtiste));
}

/**
 * Supprime une association chanson-album
 * @param idChanson l'identifiant de la chanson
 * @param idAlbum l'identifiant de l'album
 * @return vrai si la modification a été faite
 */
bool BDD::SupprimerContient(int idChanson, int idAlbum)
{
    return m_database->ExecuteUpdate(wxString::Format(_T("DELETE FROM contient WHERE id_chanson=%d AND id_album=%d"), idChanson, idAlbum));
}

/**
 * Supprime toutes les associations entre des chansons et un utilisateur
 * @param idUtilisateur l'identifiant de l'utilisateur
 * @return vrai si la modification a été faite
 */
bool BDD::SupprimerListePerso(int idUtilisateur)
{
    return m_database->ExecuteUpdate(wxString::Format(_T("DELETE FROM listeperso WHERE id_utilisateur=%d"), idUtilisateur));
}

/**
 * Supprime une association entre une chanson et un utilisateur
 * @param idUtilisateur l'identifiant de l'utilisateur
 * @param idChanson l'identifiant de la chanson
 * @return vrai si la modification a été faite
 */
bool BDD::SupprimerListePerso(int idUtilisateur, int idChanson)
{
    return m_database->ExecuteUpdate(wxString::Format(_T("DELETE FROM listeperso WHERE id_utilisateur=%d AND id_chanson=%d"), idUtilisateur, idChanson));
}

/**
 * Supprime une association de reprise entre deux chansons
 * @param idRemix l'identifiant de la reprise
 * @param idOriginal l'identifiant de la chanson originelle
 * @return vrai si la modification a été faite
 */
bool BDD::SupprimerRemix(int idRemix, int idOriginal)
{
    return m_database->ExecuteUpdate(wxString::Format(_T("DELETE FROM remix WHERE id=%d AND id_original=%d"), idRemix, idOriginal));
}

/**
 * Renvoie le nom d'une chanson
 * @param id l'identifiant de la chanson
 * @return le nom de la chanson
 */
wxString BDD::GetChansonNom(int id)
{
    return m_database->ExecuteQuery(wxString::Format(_T("SELECT nom FROM chanson WHETE id=%d"), id)).GetString(0);
}

/**
 * Renvoie le nom complet du dossier dans lequel se trouve la chanson
 * @param id l'identifiant de la chanson
 * @return le nom complet du dossier
 */
wxString BDD::GetChansonAdresse(int id)
{
    return m_database->ExecuteQuery(wxString::Format(_T("SELECT adresse FROM chanson WHETE id=%d"), id)).GetString(0);
}

/**
 * Renvoie l'année de parution d'une chanson
 * @param id l'identifiant de la chanson
 * @return l'année de parution de la chanson
 */
wxString BDD::GetChansonAnnee(int id)
{
    return m_database->ExecuteQuery(wxString::Format(_T("SELECT annee FROM chanson WHETE id=%d"), id)).GetString(0);
}

/**
 * Renvoie le genre d'une chanson
 * @param id l'identifiant de la chanson
 * @return le genre de la chanson
 */
wxString BDD::GetChansonGenre(int id)
{
    return m_database->ExecuteQuery(wxString::Format(_T("SELECT genre FROM chanson WHETE id=%d"), id)).GetString(0);
}

/**
 * Renvoie les identifiants des chansons à partir de leurs noms
 * @param nom le nom de la chanson
 * @param complet si faux, on considère le nom court de la chanson, et si vrai on considère le nom complet
 * @return les identifiants des chansons
 * @see RechercherChansonByNom
 */
wxArrayInt* BDD::GetChansonIDs(wxString nom, bool complet) // complet = false
{
    /*wxArrayInt* arrayInt = new wxArrayInt();
    //while (res.NextRow())
        //arrayInt->Add(res.GetInt(0));
    wxSQLite3ResultSet res = m_database->ExecuteQuery(wxT("SELECT * FROM chanson WHERE nom=\"" + nom + "\""));
    while (res.NextRow())
        arrayInt->Add(res.GetInt(0));
    res.Finalize();
    //arrayInt->Clear();
    //delete arrayInt;
    return arrayInt;*/
    if (complet)
        return ResultSetToArrayInt(m_database->ExecuteQuery(_T("SELECT id FROM chanson WHERE nom=\"") + nom.AfterLast(wxFileName::GetPathSeparator()) + _T("\" AND adresse=\"") + nom.BeforeLast(wxFileName::GetPathSeparator()) + _T("\"")));
    else
        return ResultSetToArrayInt(m_database->ExecuteQuery(_T("SELECT id FROM chanson WHERE nom=\"") + nom + _T("\"")));
}

/**
 * Renvoie le nom d'un artiste
 * @param id l'identifiant de l'artiste
 * @return le nom de l'artiste
 */
wxString BDD::GetArtisteNom(int id)
{
    return m_database->ExecuteQuery(wxString::Format(_T("SELECT nom FROM artiste WHETE id=%d"), id)).GetString(0);
}

/**
 * Renvoie les identifiants des artistes en fonction de leur nom
 * @param nom le nom de l'artiste
 * @return les identifiants des artistes
 */
wxArrayInt* BDD::GetArtisteIDs(wxString nom)
{
    return ResultSetToArrayInt(m_database->ExecuteQuery(_T("SELECT id FROM artiste WHERE nom=\"") + nom + _T("\"")));
}

/**
 * Renvoie le nom d'un album
 * @param id l'identifiant de l'album
 * @return le nom de l'album
 */
wxString BDD::GetAlbumNom(int id)
{
    return m_database->ExecuteQuery(wxString::Format(_T("SELECT nom FROM album WHETE id=%d"), id)).GetString(0);
}

/**
 * Renvoie l'année de parution d'un album
 * @param id l'identifiant de l'album
 * @return l'année de parution
 */
wxString BDD::GetAlbumAnnee(int id)
{
    return m_database->ExecuteQuery(wxString::Format(_T("SELECT annee FROM album WHETE id=%d"), id)).GetString(0);
}

/**
 * Renvoie la liste des artistes ayant participé à l'élaboration d'un album
 * @param id l'identifiant de l'album
 * @return les albums produit par l'artiste
 */
wxArrayString* BDD::GetAlbumArtiste(int id)
{
    wxSQLite3ResultSet res = m_database->ExecuteQuery(wxString::Format(_T("SELECT nom FROM artiste WHERE id=(SELECT id_artiste FROM album WHERE id=%d)"), id));

    wxArrayString* arrayString = new wxArrayString();
    while (res.NextRow())
        arrayString->Add(res.GetString(0));
    return arrayString;
}

/**
 * Renvoie les albums selon deux critères possibles : le nom ou l'année de parution
 * @param nom le nom de l'album
 * @param annee l'année de parution
 * @param nomParam si vrai, seul le nom est pris en compte sinon seul l'année est considérée
 * @return les identifiants des albums
 */
wxArrayInt* BDD::GetAlbumIDs(wxString nom, wxString annee, bool nomParam)
{
    if (nomParam)
        return ResultSetToArrayInt(m_database->ExecuteQuery(_T("SELECT id FROM album WHERE nom=\"") + nom + _T("\"")));
    else
        return ResultSetToArrayInt(m_database->ExecuteQuery(_T("SELECT id FROM album WHERE annee=\"") + annee + _T("\"")));
}

/**
 * Renvoie la liste des albums d'un artiste
 * @param idArtiste l'identifiant de l'artiste
 * @return les albums produit par l'artiste
 */
wxArrayInt* BDD::GetAlbumIDs(int idArtiste)
{
    return ResultSetToArrayInt(m_database->ExecuteQuery(wxString::Format(_T("SELECT id FROM album WHERE id_artiste=%d"), idArtiste)));
}

int BDD::GetAlbumID(wxString nom, int idArtiste)
{
    wxArrayInt *arr = ResultSetToArrayInt(m_database->ExecuteQuery(wxString::Format(_T("SELECT id FROM album WHERE id_artiste=%d AND nom=\""), idArtiste) + nom + _T("\"")));
    int ret = (arr->IsEmpty()) ? -1 : arr->Item(0);
    arr->Clear();
    delete arr;
    return ret;
}

/**
 * Renvoie le nom d'un utilisateur en fonction de son identifiant
 * @param id l'identifiant de l'utilisateur
 * @return les albums produit par l'utilisateur
 */
wxString BDD::GetUtilisateurNom(int id)
{
    return m_database->ExecuteQuery(wxString::Format(_T("SELECT nom FROM utilisateur WHETE id=%d"), id)).GetString(0);
}

/**
 * Renvoie l'identifiant d'un utilisateur en fonction de son nom
 * @param nom le nom de l'utilisateur
 * @return l'identifiant
 */
int BDD::GetUtilisateurID(wxString nom)
{
    return m_database->ExecuteScalar(_T("SELECT id FROM utilisateur WHETE nom=\"") + nom + _T("\""));
}

/**
 * Renvoie la liste des chansons produites par un artiste
 * @param idArtiste l'identifiant de l'artiste
 * @return les chansons produites par l'artiste
 * @see RechercherChansonByArtiste
 */
wxArrayInt* BDD::GetProduitChanson(int idArtiste)
{
    return ResultSetToArrayInt(m_database->ExecuteQuery(wxString::Format(_T("SELECT id_chanson FROM produit WHERE id_artiste=%d"), idArtiste)));
}

/**
 * Renvoie la liste des artistes ayant participé à une chanson
 * @param idChanson l'identifiant de la chanson
 * @return les artistes ayant collaborés
 */
wxArrayInt* BDD::GetProduitArtiste(int idChanson)
{
    return ResultSetToArrayInt(m_database->ExecuteQuery(wxString::Format(_T("SELECT id_artiste FROM produit WHERE id_chanson=%d"), idChanson)));
}

/**
 * Renvoie la liste des chansons associées à un album
 * @param idAlbum l'identifiant de l'album
 * @return les chansons contenues dans l'album
 */
wxArrayInt* BDD::GetContientChanson(int idAlbum)
{
    return ResultSetToArrayInt(m_database->ExecuteQuery(wxString::Format(_T("SELECT id_chanson FROM contient WHERE id_album=%d"), idAlbum)));
}

/**
 * Renvoie la liste des albums contenant une chanson
 * @param idChanson l'identifiant de la chanson
 * @return les albums parus avec cette chanson
 * @see RechercherChansonByAlbum
 */
wxArrayInt* BDD::GetContientAlbum(int idChanson)
{
    return ResultSetToArrayInt(m_database->ExecuteQuery(wxString::Format(_T("SELECT id_album FROM contient WHERE id_chanson=%d"), idChanson)));
}

/**
 * Renvoie la liste des chansons appartenant à la liste de lecture d'un utilisateur
 * @param idUtilisateur l'identifiant de l'utilisateur
 * @return la liste des chansons
 */
wxArrayInt* BDD::GetListePersoChanson(int idUtilisateur)
{
    return ResultSetToArrayInt(m_database->ExecuteQuery(wxString::Format(_T("SELECT id_chanson FROM listeperso WHERE id_utilisateur=%d"), idUtilisateur)));
}

/**
 * Renvoie la liste des utilisateurs ayant associés une chanson à leurs listes de lecture
 * @param idChanson l'identifiant de la chanson
 * @return les utilisateurs
 */
wxArrayInt* BDD::GetListePersoUtilisateur(int idChanson)
{
    return ResultSetToArrayInt(m_database->ExecuteQuery(wxString::Format(_T("SELECT id_utilisateur FROM listeperso WHERE id_chanson=%d"), idChanson)));
}

/**
 * Renvoie la liste des chansons ayant servi à ce remix
 * @param idReprise l'identifiant de la chanson remixée
 * @return les chansons originelles
 */
wxArrayInt* BDD::GetRemixOriginal(int idReprise)
{
    return ResultSetToArrayInt(m_database->ExecuteQuery(wxString::Format(_T("SELECT id_original FROM remix WHERE id=%d"), idReprise)));
}

/**
 * Renvoie la liste des chansons basé sur cette chanson
 * @param idOriginal l'identifiant de la chanson originale
 * @return les chansons remixées
 */
wxArrayInt* BDD::GetRemixReprise(int idOriginal)
{
    return ResultSetToArrayInt(m_database->ExecuteQuery(wxString::Format(_T("SELECT id FROM remix WHERE id_original=%d"), idOriginal)));
}

/**
 * Renvoie les identifiants des chansons à partir de leurs noms
 * @param nomChanson le nom de la chanson (pas nécessairement complet
 * @return les identifiants des chansons
 * @see GetChansonIDs
 */
wxArrayInt* BDD::RechercherChansonByNom(wxString nomChanson)
{
    return ResultSetToArrayInt(m_database->ExecuteQuery(_T("SELECT id FROM chanson WHERE nom LIKE %") + nomChanson + _T("%")));
}

/**
 * Renvoie la liste des chansons se trouvant dans l'album nom
 * @param nomAlbum le nom de l'album (pas nécessairement complet)
 * @return les albums parus avec cette chanson
 * @see GetContientAlbum
 */
wxArrayInt* BDD::RechercherChansonByAlbum(wxString nomAlbum)
{
    return ResultSetToArrayInt(m_database->ExecuteQuery(_T("SELECT id_chanson FROM contient WHERE id_album=(SELECT id FROM album WHERE nom LIKE %") + nomAlbum + _T("%)")));
}

/**
 * Renvoie la liste des chansons produites par un artiste
 * @param nomArtiste le nom de l'artiste (pas nécessairement complet
 * @return les chansons produites par l'artiste
 * @see GetProduitChanson
 */
wxArrayInt* BDD::RechercherChansonByArtiste(wxString nomArtiste)
{
    return ResultSetToArrayInt(m_database->ExecuteQuery(_T("SELECT id_chanson FROM produit WHERE id_artiste=(SELECT id FROM artiste WHERE nom LIKE %") + nomArtiste + _T("%)")));
}

/**
 * Transforme le résultat d'une requête dans une base de données SQLite3 en vecteur d'entiers
 * @param res le résultat de la requête
 * @return le vecteur d'entiers
 */
wxArrayInt* BDD::ResultSetToArrayInt(wxSQLite3ResultSet res)
{
    wxArrayInt* arrayInt = new wxArrayInt();
    while (res.NextRow())
        arrayInt->Add(res.GetInt(0));
    res.Finalize();
    //arrayInt->Clear();
    //delete arrayInt;
    return arrayInt;
}

/**
 * Indique si un tuple existe dans la table PRODUIT.
 * @param idChanson l'identifiant de la chanson
 * @param idArtiste l'identifiant de l'artiste
 * @return vrai si le tuple existe
 */
bool BDD::ExisteProduit(int idChanson, int idArtiste)
{
    return m_database->ExecuteScalar(wxString::Format(_T("SELECT COUNT(*) FROM produit WHERE id_artiste=%d AND id_chanson=%d"), idArtiste, idChanson));
}

bool BDD::ExisteAlbum(wxString nomAlbum, int idArtiste)
{
    return m_database->ExecuteScalar(wxString::Format(_T("SELECT COUNT(*) FROM album WHERE id_artiste=%d AND nom=\""), idArtiste) + nomAlbum + _T("\""));
}

bool BDD::ExisteContient(int idChanson, int idAlbum)
{
    return m_database->ExecuteScalar(wxString::Format(_T("SELECT COUNT(*) FROM contient WHERE id_chanson=%d AND id_album=%d"), idChanson, idAlbum));
}

/********* Base de données ***********/
/*
chanson     (id INTEGER PRIMARY KEY AUTOINCREMENT, nom VARCHAR(255), adresse VARCHAR(255), annee CHAR(4), genre INTEGER)//dansabilité
artiste     (id INTEGER PRIMARY KEY AUTOINCREMENT, nom VARCHAR(75))
album       (id INTEGER PRIMARY KEY AUTOINCREMENT, id_artiste INTEGER REFERENCES artiste(id), nom VARCHAR(100), annee_parution CHAR(4))
utilisateur (id INTEGER PRIMARY KEY AUTOINCREMENT, nom VARCHAR(60))

produit     (id_chanson INTEGER REFERENCES chanson(id), id_artiste INTEGER REFERENCES artiste(id),          PRIMARY KEY(id_chanson, id_artiste))
contient    (id_chanson INTEGER REFERENCES chanson(id), id_album INTEGER REFERENCES album(id),              PRIMARY KEY(id_chanson, id_album))

listeperso  (id_utilisateur INTEGER REFERENCES utilisateur(id), id_chanson INTEGER REFERENCES chanson(id),  PRIMARY KEY(id_utilisateur, id_chanson))
remix       (id INTEGER REFERENCES chanson(id),                 id_original INTEGER REFERENCES chanson(id), PRIMARY KEY(id, id_original))
*/
