#ifndef BDD_H_INCLUDED
#define BDD_H_INCLUDED

#include <wx/wx.h>
#include <wx/dynarray.h>
#include <wx/wxsqlite3.h>
#include "settings/Parametre.h"
#include "tools/FichierLog.h"
//#include "wxsqlite3.h"

/*
Pour compiler, il faut placer les entêtes de wxsqlite3 dans le dossier d'installation de wxWidgets.
Un simple copier-colle de include dans include suffit !
*/

class BDD
{
    public:
        BDD();
        ~BDD();
        void Close();
        void CreerTables();


        bool AjouterChanson(wxString nom, wxString adresse, wxString annee, wxString genre);
        bool AjouterChanson(wxString nomComplet, wxString annee, wxString genre);
        bool AjouterArtiste(wxString nom);
        bool AjouterAlbum(wxString nom, int idArtiste, int idAlbum = -1);
        bool AjouterArtisteProduitChanson(int idChanson, int idArtiste);
        bool AjouterAlbumContientChanson(int idChanson, int idAlbum);
        bool AjouterUtilisateur(wxString nom);
        bool AjouterListePerso(int idUtilisateur, int idChanson);
        bool AjouterRemixDe(int idRemix, int idOriginal);

        bool ModifierChansonNom(int id, wxString nom);
        bool ModifierChansonAnnee(int id, wxString annee);
        bool ModifierChansonGenre(int id, wxString genre);
        bool ModifierArtisteNom(int id, wxString nom);
        bool ModifierAlbumNom(int id, wxString nom);
        bool ModifierAlbumAnnee(int id, wxString annee);
        bool ModifierUtilisateurNom(int id, wxString nom);

        bool SupprimerChanson(int id);
        bool SupprimerChanson(wxString nomComplet);
        bool SupprimerAlbum(int id);
        bool SupprimerArtiste(int id);
        bool SupprimerArtiste(wxString nom);
        bool SupprimerUtilisateur(int id);
        bool SupprimerUtilisateur(wxString nom);
        bool SupprimerProduit(int idChanson, int idArtiste);
        bool SupprimerContient(int idChanson, int idAlbum);
        bool SupprimerListePerso(int idUtilisateur);
        bool SupprimerListePerso(int idUtilisateur, int idChanson);
        bool SupprimerRemix(int idRemix, int idOriginal);

        wxString GetChansonNom(int id);
        wxString GetChansonAdresse(int id);
        wxString GetChansonAnnee(int id);
        wxString GetChansonGenre(int id);
        wxArrayInt* GetChansonIDs(wxString nom, bool complet = false); // = false

        wxString GetArtisteNom(int id);
        wxArrayInt* GetArtisteIDs(wxString nom);

        wxString GetAlbumNom(int id);
        wxString GetAlbumAnnee(int id);
        wxArrayString* GetAlbumArtiste(int id);
        wxArrayInt* GetAlbumIDs(wxString nom, wxString annee, bool nomParam = true);
        //wxArrayInt* GetAlbumIDs(wxString annee);
        wxArrayInt* GetAlbumIDs(int idArtiste);
        int GetAlbumID(wxString nom, int idArtiste);

        wxString GetUtilisateurNom(int id);
        int GetUtilisateurID(wxString nom);
        wxArrayInt* GetProduitChanson(int idArtiste);
        wxArrayInt* GetProduitArtiste(int idChanson);

        wxArrayInt* GetContientChanson(int idAlbum);
        wxArrayInt* GetContientAlbum(int idChanson);

        wxArrayInt* GetListePersoChanson(int idUtilisateur);
        wxArrayInt* GetListePersoUtilisateur(int idChanson);

        wxArrayInt* GetRemixOriginal(int idReprise);
        wxArrayInt* GetRemixReprise(int idOriginal);

        wxArrayInt* ResultSetToArrayInt(wxSQLite3ResultSet res);

        wxArrayInt* RechercherChansonByNom(wxString nomChanson);
        wxArrayInt* RechercherChansonByAlbum(wxString nomAlbum);
        wxArrayInt* RechercherChansonByArtiste(wxString nomArtiste);

        bool ExisteProduit(int idChanson, int idArtiste);
        bool ExisteAlbum(wxString nomAlbum, int idArtiste);
        bool ExisteContient(int idChanson, int idAlbum);

    protected:
        wxSQLite3Database *m_database;
};

#endif // BDD_H_INCLUDED
