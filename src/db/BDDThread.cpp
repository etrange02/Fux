/***************************************************************
 * Name:      BDDThread.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2012-07-19
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "../../include/db/BDDThread.h"

/**
 * @class BDDThread
 * @brief Thread gérant la base de données
 */

static BDDThread* s_instanceBDDThread = NULL;
static wxMutex *s_mutexGestionGlobale = new wxMutex;

/**
 * Constructeur
 */
BDDThread::BDDThread() : wxThread()
{
    m_bdd = NULL;
    m_continuer = true;

    if (Create() == wxTHREAD_NO_ERROR)
    {
        if (Run() != wxTHREAD_NO_ERROR)
            delete this;
    }
    else
        delete this;
}

/**
 * Destructeur
 */
BDDThread::~BDDThread()
{
    if (m_bdd)
        m_bdd->Close();
}

/**
 * Singleton. Renvoie l'instance de BDDThread
 * @return une instance unique
 */
BDDThread* BDDThread::Get()
{
    if (!s_instanceBDDThread)
        s_instanceBDDThread = new BDDThread();
    return s_instanceBDDThread;
}

/**
 * Surcharge. Traitement en parallèle
 */
void* BDDThread::Entry()
{
    m_bdd = new BDD();
    int idChanson = -1, idArtiste = -1, idAlbum = -1;
    unsigned int i = 0;//urgent = 0,
    //size_t pos = 0, i = 0;
    BDDRequete *requete;
    wxArrayInt *arr = NULL;
    wxArrayString *arrString = NULL;

    while (m_continuer && !TestDestroy())
    {
        while (m_vecteurBDDRequete.size() == 0)
            Sleep(100);

        // Parcours du vecteur afin de prendre la requête la plus urgente (notamment les recherches sur les ajouts)
        /*urgent = 0;
        pos = 0;
        i = 0;
        while (urgent < 100 && i < m_vecteurBDDRequete.size())
        {
            if (urgent < m_vecteurBDDRequete[i]->GetPriorite())
            {
                pos = i;
                urgent = m_vecteurBDDRequete[i]->GetPriorite();
            }
            i++;
        }

        requete = m_vecteurBDDRequete.at(i);*/
        i++;
        //    wxLogMessage("oui " + i);

        //wxMutexLocker lock(*s_mutexGestionGlobale);
        //s_mutexGestionGlobale->Lock();
        requete = m_vecteurBDDRequete.top();

        idChanson = -1;
        idArtiste = -1;
        idAlbum = -1;

        switch (requete->GetPriorite())
        {
            /*case BDD_SUPPRIMER:
                break;
            case BDD_MODIFIER:
                break;*/
            /*case BDD_AJOUTER_UTILISATEUR:
                if (m_bdd->GetUtilisateurID(requete->GetNomUtilisateur()) == -1)
                    m_bdd->AjouterUtilisateur(requete->GetNomUtilisateur());
                break;*/
            case BDD_AJOUTER_CHANSON_ALBUM_ARTISTE:
                arr = m_bdd->GetChansonIDs(requete->GetNomChanson(), true);
                if (arr->IsEmpty())
                {
                    m_bdd->AjouterChanson(requete->GetNomChanson(), requete->GetAnneeChanson(), requete->GetGenre());
                    delete arr;
                    arr = m_bdd->GetChansonIDs(requete->GetNomChanson(), true);
                }
                idChanson = (arr->IsEmpty()) ? -1 : arr->Item(0);
                delete arr;
                arr = NULL;

                if (requete->GetIdArtiste() != -1)
                    idArtiste = requete->GetIdArtiste();
                else
                {
                    arr = m_bdd->GetArtisteIDs(requete->GetNomArtiste());
                    if (!arr->IsEmpty())// && arr->size() == 1
                        idArtiste = arr->Item(0);
                    delete arr;
                    arr = NULL;
                }
                /*if (!m_bdd->ExisteAlbum(requete->GetNomAlbum(), idArtiste))
                    m_bdd->AjouterAlbum(requete->GetNomAlbum(), idArtiste, requete->GetIdAlbum());

                idAlbum = m_bdd->GetAlbumID(requete->GetNomAlbum(), idArtiste);

                if (!m_bdd->ExisteContient(idChanson, idAlbum))
                    m_bdd->AjouterAlbumContientChanson(idChanson, idAlbum);

                if (!m_bdd->ExisteProduit(idChanson, idArtiste))
                    m_bdd->AjouterArtisteProduitChanson(idChanson, idArtiste);*/

                // Ajout de l'artiste
                if (requete->GetIdArtiste() != -1)
                {
                    idArtiste = requete->GetIdArtiste();
                    if (idArtiste != -1 && idChanson != -1 && !m_bdd->ExisteProduit(idChanson, idArtiste))//
                        m_bdd->AjouterArtisteProduitChanson(idChanson, idArtiste);
                    if (idArtiste != -1 && !m_bdd->ExisteAlbum(requete->GetNomAlbum(), idArtiste))
                        m_bdd->AjouterAlbum(requete->GetNomAlbum(), idArtiste, requete->GetIdAlbum());
                    idAlbum = m_bdd->GetAlbumID(requete->GetNomAlbum(), idArtiste);
                    if (idAlbum != -1 && idChanson != -1 && !m_bdd->ExisteContient(idChanson, idAlbum))
                        m_bdd->AjouterAlbumContientChanson(idChanson, idAlbum);
                }
                else
                {
                    arrString = requete->GetNomsArtistes();
                    if (arrString != NULL)
                    {
                        for (i = 0; i<arrString->Count(); i++)
                        {
                            arr = m_bdd->GetArtisteIDs(arrString->Item(i));
                            if (arr->IsEmpty())
                                m_bdd->AjouterArtiste(arrString->Item(i));
                            delete arr;
                            arr = m_bdd->GetArtisteIDs(arrString->Item(i));

                            idArtiste = (arr->IsEmpty()) ? -1 : arr->Item(0);
                            delete arr;
                            arr = NULL;

                            if (idArtiste != -1 && idChanson != -1 && !m_bdd->ExisteProduit(idChanson, idArtiste))//
                                m_bdd->AjouterArtisteProduitChanson(idChanson, idArtiste);
                        }

                        arr = m_bdd->GetArtisteIDs(arrString->Item(0));

                        idArtiste = (arr->IsEmpty()) ? -1 : arr->Item(0);
                        delete arr;
                        arr = NULL;
                        if (idArtiste != -1 && !m_bdd->ExisteAlbum(requete->GetNomAlbum(), idArtiste))
                            m_bdd->AjouterAlbum(requete->GetNomAlbum(), idArtiste, idAlbum);

                        idAlbum = m_bdd->GetAlbumID(requete->GetNomAlbum(), idArtiste);

                        if (idAlbum != -1)
                            for (i = 1; i<arrString->Count(); i++)
                            {
                                arr = m_bdd->GetArtisteIDs(arrString->Item(i));
                                idArtiste = (arr->IsEmpty()) ? -1 : arr->Item(i);
                                delete arr;
                                arr = NULL;
                                if (idArtiste != -1 && !m_bdd->ExisteAlbum(requete->GetNomAlbum(), idArtiste))
                                    m_bdd->AjouterAlbum(requete->GetNomAlbum(), idArtiste, idAlbum);
                            }

                        if (idChanson != -1 && idAlbum != -1 && !m_bdd->ExisteContient(idChanson, idAlbum))
                            m_bdd->AjouterAlbumContientChanson(idChanson, idAlbum);

                        delete arrString;
                    }
                }
                break;
            /*case BDD_AJOUTER_ALBUM_ARTISTE:
                if (m_bdd->GetArtisteIDs(requete->GetNomArtiste())->IsEmpty())
                    m_bdd->AjouterArtiste(requete->GetNomArtiste());
                arr = m_bdd->GetArtisteIDs(requete->GetNomArtiste());
                idArtiste = (arr->IsEmpty()) ? -1 : arr->Item(0);

                if (idArtiste != -1 && !m_bdd->ExisteAlbum(requete->GetNomAlbum(), idArtiste))
                    m_bdd->AjouterAlbum(requete->GetNomAlbum(), idArtiste, requete->GetIdAlbum());
                break;*/
            case BDD_AJOUTER_CHANSON_ARTISTE:
                arr = m_bdd->GetChansonIDs(requete->GetNomChanson(), true);
                if (arr->IsEmpty())
                {
                    m_bdd->AjouterChanson(requete->GetNomChanson(), requete->GetAnneeChanson(), requete->GetGenre());
                    delete arr;
                    arr = m_bdd->GetChansonIDs(requete->GetNomChanson(), true);
                }
                idChanson = (arr->IsEmpty()) ? -1 : arr->Item(0);
                delete arr;
                arr = NULL;

                // Ajout de l'artiste
                if (requete->GetIdArtiste() != -1)
                {
                    idArtiste = requete->GetIdArtiste();
                    if (idArtiste != -1 && idChanson != -1 && !m_bdd->ExisteProduit(idChanson, idArtiste))//
                        m_bdd->AjouterArtisteProduitChanson(idChanson, idArtiste);
                }
                else
                {
                    arrString = requete->GetNomsArtistes();
                    if (arrString != NULL)
                    {
                        for (i = 0; i<arrString->Count(); i++)
                        {
                            arr = m_bdd->GetArtisteIDs(arrString->Item(i));
                            if (arr->IsEmpty())
                                m_bdd->AjouterArtiste(arrString->Item(i));
                            delete arr;
                            arr = m_bdd->GetArtisteIDs(arrString->Item(i));

                            idArtiste = (arr->IsEmpty()) ? -1 : arr->Item(0);
                            delete arr;
                            arr = NULL;

                            if (idArtiste != -1 && idChanson != -1 && !m_bdd->ExisteProduit(idChanson, idArtiste))//
                                m_bdd->AjouterArtisteProduitChanson(idChanson, idArtiste);
                        }
                        delete arrString;
                    }
                }
                break;
            /*case BDD_AJOUTER_CHANSON_ALBUM:
            case BDD_AJOUTER_CHANSON_ALBUM_ARTISTE:
                // Ajout de la chanson
                arr = m_bdd->GetChansonIDs(requete->GetNomChanson(), true);
                if (arr->IsEmpty())
                {
                    m_bdd->AjouterChanson(requete->GetNomChanson(), requete->GetAnneeChanson(), requete->GetGenre());
                    delete arr;
                    arr = m_bdd->GetChansonIDs(requete->GetNomChanson(), true);
                }
                idChanson = (arr->IsEmpty()) ? -1 : arr->Item(0);
                delete arr;
                arr = NULL;

                // Ajout de l'artiste
                if (requete->GetIdArtiste() != -1)
                    idArtiste = requete->GetIdArtiste();
                else
                {
                    arr = m_bdd->GetArtisteIDs(requete->GetNomArtiste());
                    if (arr->IsEmpty())
                    {
                        m_bdd->AjouterArtiste(requete->GetNomArtiste());
                        delete arr;
                        arr = m_bdd->GetArtisteIDs(requete->GetNomArtiste());
                    }
                    if (!arr->IsEmpty())// && arr->size() == 1
                        idArtiste = arr->Item(0);
                    delete arr;
                    arr = NULL;
                }
                // Ajout de l'album
                if (idArtiste != -1 && !m_bdd->ExisteAlbum(requete->GetNomAlbum(), idArtiste))
                    m_bdd->AjouterAlbum(requete->GetNomAlbum(), idArtiste, requete->GetIdAlbum());

                idAlbum = m_bdd->GetAlbumID(requete->GetNomAlbum(), idArtiste);

                // Ajout des autres paramètres
                if (idAlbum != -1 && idChanson != -1 && !m_bdd->ExisteContient(idChanson, idAlbum))
                    m_bdd->AjouterAlbumContientChanson(idChanson, idAlbum);

                if (idArtiste != -1 && idChanson != -1 && !m_bdd->ExisteProduit(idChanson, idArtiste))
                    m_bdd->AjouterArtisteProduitChanson(idChanson, idArtiste);
                break;*/
            /*case BDD_AJOUTER_ALBUM:
                if (requete->GetIdArtiste() != -1)
                    m_bdd->AjouterAlbum(requete->GetNomAlbum(), requete->GetIdArtiste(), requete->GetIdAlbum());
                else
                {
                    arrString = requete->GetNomsArtistes();
                    if (arrString != NULL)
                    {
                        for (i = 0; i<arrString->Count(); i++)
                        {
                            arr = m_bdd->GetArtisteIDs(arrString->Item(i));
                            if (arr->IsEmpty())
                                m_bdd->AjouterArtiste(arrString->Item(i));
                            delete arr;
                            arr = m_bdd->GetArtisteIDs(requete->GetNomArtiste());

                            if (!arr->IsEmpty())// && arr->size() == 1
                                m_bdd->AjouterAlbum(requete->GetNomAlbum(), arr->Item(0), requete->GetIdAlbum());
                        }
                        delete arrString;
                    }
                }
                break;*/
            case BDD_AJOUTER_ARTISTE:
                arrString = requete->GetNomsArtistes();
                if (arrString != NULL)
                {
                    for (i = 0; i<arrString->Count(); i++)
                    {
                        arr = m_bdd->GetArtisteIDs(arrString->Item(i));
                        if (arr->IsEmpty())
                            m_bdd->AjouterArtiste(arrString->Item(i));
                    }
                    delete arrString;
                }
                break;
            case BDD_AJOUTER_CHANSON:
                arr = m_bdd->GetChansonIDs(requete->GetNomChanson().AfterLast(wxFileName::GetPathSeparator()), false);
                if (arr->IsEmpty())
                    m_bdd->AjouterChanson(requete->GetNomChanson(), requete->GetAnneeChanson(), requete->GetGenre());
                break;
            /*case BDD_RECHERCHER:
                break;
            case BDD_GET:
                break;*/
            default:
                break;
        }

        if (arr != NULL)
        {
            arr->Clear();
            delete arr;
            arr = NULL;
        }
        // Effacer l'élément ici
        m_vecteurBDDRequete.pop();
        //s_mutexGestionGlobale->Unlock();

        //m_continuer = false;
    }
    m_bdd->Close();
    return (ExitCode) 0;
}

void BDDThread::AjouterRequete(BDDRequete *bddRequete)
{
    //s_mutexGestionGlobale->Lock();
    m_vecteurBDDRequete.push(bddRequete);
    //wxLogMessage("" + m_vecteurBDDRequete.size());
    //s_mutexGestionGlobale->Unlock();
}

void BDDThread::SendEvent(BDDRequete* requete, bool WXUNUSED(etat), wxArrayString* arrayS)
{
    BDDThreadEvent event;
    event.SetArrayString(arrayS);
    requete->GetParent()->GetEventHandler()->AddPendingEvent(event);
}

void BDDThread::Stop()
{
    m_continuer = false;
}


