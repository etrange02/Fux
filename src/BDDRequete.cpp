/***************************************************************
 * Name:      BDDRequete.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2012-07-27
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../include/BDDRequete.h"

BDDRequete::BDDRequete(wxWindow *parent)
{
    m_parent = parent;
    m_typeRequete = 0;
    m_idArtiste = -1;
    m_idChanson = -1;
    m_idChanson2 = -1;
    m_idAlbum = -1;
    m_idUtilisateur = -1;
}

BDDRequete::~BDDRequete()
{}

int BDDRequete::GetTypeRequete()
{
    if (m_nomChanson.IsEmpty())
    {
        if (m_nomAlbum.IsEmpty())
            return (m_nomArtiste.IsEmpty()) ? 0 : BDD_AJOUTER_ARTISTE;
        else
            return (m_nomArtiste.IsEmpty()) ? BDD_AJOUTER_ALBUM : BDD_AJOUTER_ALBUM_ARTISTE;
    }
    else
    {
        if (m_nomAlbum.IsEmpty())
            return (m_nomArtiste.IsEmpty()) ? BDD_AJOUTER_CHANSON : BDD_AJOUTER_CHANSON_ARTISTE;
        else
            return (m_nomArtiste.IsEmpty()) ? BDD_AJOUTER_CHANSON_ALBUM : BDD_AJOUTER_CHANSON_ALBUM_ARTISTE;
    }
}

int BDDRequete::GetPriorite()
{
    return (int) m_typeRequete;
}

void BDDRequete::AjouterChanson(wxString nomComplet, wxString annee, wxString genre)
{
    m_nomChanson = nomComplet;
    m_chansonAnnee = annee;
    m_genre = genre;
    m_typeRequete = GetTypeRequete();
}
void BDDRequete::AjouterArtiste(wxString nomArtiste)
{
    m_nomArtiste = nomArtiste;
    m_typeRequete = GetTypeRequete();
}

void BDDRequete::AjouterAlbum(wxString nom, int idArtiste, int idAlbum)//collaborations
{
    m_nomAlbum = nom;
    m_idAlbum = idAlbum;
    m_idArtiste = idArtiste;
    m_typeRequete = GetTypeRequete();
}

void BDDRequete::AjouterAlbum(wxString nom, wxString nomArtiste, int idAlbum)//collaborations
{
    m_nomAlbum = nom;
    m_idAlbum = idAlbum;
    m_nomArtiste = nomArtiste;
    m_typeRequete = GetTypeRequete();
}

//void BDDRequete::AjouterArtisteProduitChanson(int idChanson, int idArtiste);
//void BDDRequete::AjouterAlbumContientChanson(int idChanson, int idAlbum);

void BDDRequete::AjouterUtilisateur(wxString nom)
{
    m_nomUtilisateur = nom;
    m_typeRequete = BDD_AJOUTER_UTILISATEUR;
}
/*void BDDRequete::AjouterListePerso(int idUtilisateur, int idChanson);
void BDDRequete::AjouterRemixDe(int idRemix, int idOriginal);
void BDDRequete::ModifierChansonNom(int id, wxString nom);
void BDDRequete::ModifierChansonAnnee(int id, wxString annee);
void BDDRequete::ModifierChansonGenre(int id, int genre);
void BDDRequete::ModifierArtisteNom(int id, wxString nom);
void BDDRequete::ModifierAlbumNom(int id, wxString nom);
void BDDRequete::ModifierAlbumAnnee(int id, wxString annee);
void BDDRequete::ModifierUtilisateurNom(int id, wxString nom);
void BDDRequete::SupprimerChanson(int id);
void BDDRequete::SupprimerChanson(wxString nomComplet);
void BDDRequete::SupprimerAlbum(int id);
void BDDRequete::SupprimerArtiste(int id);
void BDDRequete::SupprimerArtiste(wxString nom);
void BDDRequete::SupprimerUtilisateur(int id);
void BDDRequete::SupprimerUtilisateur(wxString nom);
void BDDRequete::SupprimerProduit(int idChanson, int idArtiste);
void BDDRequete::SupprimerContient(int idChanson, int idAlbum);
void BDDRequete::SupprimerListePerso(int idUtilisateur);
void BDDRequete::SupprimerListePerso(int idUtilisateur, int idChanson);
void BDDRequete::SupprimerRemix(int idRemix, int idOriginal);
void BDDRequete::GetChansonNom(int id);
void BDDRequete::GetChansonAdresse(int id);
void BDDRequete::GetChansonAnnee(int id);
void BDDRequete::GetChansonGenre(int id);
void BDDRequete::GetChansonIDs(wxString nom, bool complet = false);
void BDDRequete::GetArtisteNom(int id);
void BDDRequete::GetArtisteIDs(wxString nom);
void BDDRequete::GetAlbumNom(int id);
void BDDRequete::GetAlbumAnnee(int id);
void BDDRequete::GetAlbumArtiste(int id);
void BDDRequete::GetAlbumIDs(wxString nom, wxString annee, bool nomParam = true);
void BDDRequete::GetAlbumIDs(int idArtiste);
void BDDRequete::GetUtilisateurNom(int id);
void BDDRequete::GetUtilisateurID(wxString nom);
void BDDRequete::GetProduitChanson(int idArtiste);
void BDDRequete::GetProduitArtiste(int idChanson);
void BDDRequete::GetContientChanson(int idAlbum);
void BDDRequete::GetContientAlbum(int idChanson);
void BDDRequete::GetListePersoChanson(int idUtilisateur);
void BDDRequete::GetListePersoUtilisateur(int idChanson);
void BDDRequete::GetRemixOriginal(int idReprise);
void BDDRequete::GetRemixReprise(int idOriginal);
void BDDRequete::RechercherChansonByNom(wxString nomChanson);
void BDDRequete::RechercherChansonByAlbum(wxString nomAlbum);
void BDDRequete::RechercherChansonByArtiste(wxString nomArtiste);*/

wxString& BDDRequete::GetNomUtilisateur()
{
    return m_nomUtilisateur;
}

wxString& BDDRequete::GetNomChanson()
{
    return m_nomChanson;
}

wxString& BDDRequete::GetNomChanson2()
{
    return m_nomChanson2;
}

wxString& BDDRequete::GetNomAlbum()
{
    return m_nomAlbum;
}

wxString& BDDRequete::GetNomArtiste()
{
    return m_nomArtiste;
}

wxString& BDDRequete::GetAnneeAlbum()
{
    return m_albumAnnee;
}

wxString& BDDRequete::GetAnneeChanson()
{
    return m_chansonAnnee;
}

wxString& BDDRequete::GetGenre()
{
    return m_genre;
}

int BDDRequete::GetIdArtiste()
{
    return m_idArtiste;
}
int BDDRequete::GetIdAlbum()
{
    return m_idAlbum;
}

wxWindow* BDDRequete::GetParent()
{
    return m_parent;
}

/* Feat. ft*/
wxArrayString* BDDRequete::GetNomsArtistes()
{
    if (m_nomArtiste.IsEmpty())
        return NULL;
    wxArrayString *arr = new wxArrayString;
    int nbrSeparateur = m_nomArtiste.Freq(';');
    wxString nom = m_nomArtiste;

    for (int i = 0; i<=nbrSeparateur; i++)
    {
        arr->Add(nom.BeforeFirst(';').Trim(true));
        nom = nom.AfterFirst(';');
        nom.Trim(false);
    }

    return arr;
}

bool BDDRequete::HasManyArtistes()
{
    return (m_nomArtiste.Freq(';'));
}



