#ifndef BDDREQUETE_H
#define BDDREQUETE_H

#include <wx/wx.h>
#include "../Define.h"

class BDDRequete
{
    public:
        BDDRequete(wxWindow *parent);
        virtual ~BDDRequete();

        //void AjouterChanson(wxString nom, wxString adresse, wxString annee, int genre);
        void AjouterChanson(wxString nomComplet, wxString annee, wxString genre);
        void AjouterArtiste(wxString nomArtiste);
        void AjouterAlbum(wxString nom, int idArtiste, int idAlbum = 0);
        void AjouterAlbum(wxString nom, wxString nomArtiste, int idAlbum = 0);
        //void AjouterArtisteProduitChanson(int idChanson, int idArtiste);
        //void AjouterAlbumContientChanson(int idChanson, int idAlbum);
        void AjouterUtilisateur(wxString nom);
        /*void AjouterListePerso(int idUtilisateur, int idChanson);
        void AjouterRemixDe(int idRemix, int idOriginal);
        void ModifierChansonNom(int id, wxString nom);
        void ModifierChansonAnnee(int id, wxString annee);
        void ModifierChansonGenre(int id, int genre);
        void ModifierArtisteNom(int id, wxString nom);
        void ModifierAlbumNom(int id, wxString nom);
        void ModifierAlbumAnnee(int id, wxString annee);
        void ModifierUtilisateurNom(int id, wxString nom);
        void SupprimerChanson(int id);
        void SupprimerChanson(wxString nomComplet);
        void SupprimerAlbum(int id);
        void SupprimerArtiste(int id);
        void SupprimerArtiste(wxString nom);
        void SupprimerUtilisateur(int id);
        void SupprimerUtilisateur(wxString nom);
        void SupprimerProduit(int idChanson, int idArtiste);
        void SupprimerContient(int idChanson, int idAlbum);
        void SupprimerListePerso(int idUtilisateur);
        void SupprimerListePerso(int idUtilisateur, int idChanson);
        void SupprimerRemix(int idRemix, int idOriginal);
        void GetChansonNom(int id);
        void GetChansonAdresse(int id);
        void GetChansonAnnee(int id);
        void GetChansonGenre(int id);
        void GetChansonIDs(wxString nom, bool complet = false);
        void GetArtisteNom(int id);
        void GetArtisteIDs(wxString nom);
        void GetAlbumNom(int id);
        void GetAlbumAnnee(int id);
        void GetAlbumArtiste(int id);
        void GetAlbumIDs(wxString nom, wxString annee, bool nomParam = true);
        void GetAlbumIDs(int idArtiste);
        void GetUtilisateurNom(int id);
        void GetUtilisateurID(wxString nom);
        void GetProduitChanson(int idArtiste);
        void GetProduitArtiste(int idChanson);
        void GetContientChanson(int idAlbum);
        void GetContientAlbum(int idChanson);
        void GetListePersoChanson(int idUtilisateur);
        void GetListePersoUtilisateur(int idChanson);
        void GetRemixOriginal(int idReprise);
        void GetRemixReprise(int idOriginal);
        void RechercherChansonByNom(wxString nomChanson);
        void RechercherChansonByAlbum(wxString nomAlbum);
        void RechercherChansonByArtiste(wxString nomArtiste);*/

        int GetPriorite();
        wxString& GetNomUtilisateur();
        wxString& GetNomChanson();
        wxString& GetNomChanson2();
        wxString& GetNomAlbum();
        wxString& GetNomArtiste();
        wxArrayString* GetNomsArtistes();
        wxString& GetAnneeAlbum();
        wxString& GetAnneeChanson();
        wxString& GetGenre();
        int GetIdArtiste();
        int GetIdAlbum();
        wxWindow* GetParent();

        bool HasManyArtistes();

    protected:
        int GetTypeRequete();

        wxWindow *m_parent;
        wxString m_nomChanson, m_nomChanson2, m_nomArtiste, m_nomAlbum, m_nomUtilisateur, m_chansonAnnee, m_albumAnnee, m_genre;
        int m_idChanson, m_idChanson2, m_idArtiste, m_idAlbum, m_idUtilisateur;
        int m_typeRequete;
};

class ComparaisonRequete
{
    public:
        ComparaisonRequete(){}
        bool operator()(BDDRequete* a, BDDRequete* b) const
        {
            return (a->GetPriorite() < b->GetPriorite());
        }
};

#endif // BDDREQUETE_H
