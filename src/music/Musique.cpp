/***************************************************************
 * Name:      Musique.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2009-08-04
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../../include/music/Musique.h"

/**
 * @class Musique
 * @brief Classe centrale de Fu(X). Elle gère la lecture ainsi que toutes les opérations liées.
 */

static Musique* s_instanceMusique = NULL;

const wxEventType wxEVT_MUSIQUE_CHANGE = wxNewEventType();
const wxEventType wxEVT_MUSIQUE_MAJ = wxNewEventType();
const wxEventType wxEVT_MUSIQUE_LECTURE = wxNewEventType();
const wxEventType wxEVT_MUSIQUE_GRAPH = wxNewEventType();


/**
 * Constructeur privé
 */
Musique::Musique()
{
    FMOD_System_Create(&m_system);
    //wxString cheminPluginAAC = wxStandardPaths::Get()->GetDataDir(); cheminPluginAAC << wxFileName::GetPathSeparator() << "codec_aac.dll";
    //FMOD_System_LoadPlugin(m_system, cheminPluginAAC.c_str(), &codec, /*FMOD_PLUGINTYPE_CODEC, */2600);
    //FMOD_System_SetOutputByPlugin(m_system, codec);

    FMOD_System_Init(m_system, 1, FMOD_INIT_NORMAL, NULL);//(void*)cheminPluginAAC.c_str());//
    m_sound = NULL;
    m_channel = NULL;

    m_stop = true;
    m_action = SUIVANT;
    m_musCharge = false;
    m_positionListe = -1;
    m_cheminComplet = wxEmptyString;
    m_nomChanson = wxEmptyString;

    m_duree.SetMSecondeTot(1);
    m_tpsActuel.SetMSecondeTot(0);
    m_volume = 1;

    m_aleatoire = false;
    m_isPlaying = false;
    srand(time(NULL));
}

/**
 * Récupère l'instance de la classe
 * @return l'instance
 */
Musique* Musique::Get()
{
    if (s_instanceMusique == NULL)
        s_instanceMusique = new Musique();
    return s_instanceMusique;
}

/**
 * Destructeur
 */
Musique::~Musique()
{
    if (m_musCharge)
        FMOD_Sound_Release(m_sound);
    //FMOD_System_UnloadPlugin(m_system, codec);
    FMOD_System_Release(m_system);

    #if DEBUG
    FichierLog::Get()->Ajouter(_T("Musique::~Musique - fin"));
    #endif
}

void Musique::Delete()
{
    delete s_instanceMusique;
    s_instanceMusique = NULL;
}

/**
 * Setter
 * @param parent la classe (= fenêtre) parente pour l'envoi d'évènement
 */
void Musique::SetParent(wxWindow *parent)
{
    m_parent = parent;
}

/**
 * Gère le chargement du titre à écouter. Informe le reste de l'application du changement grâce aux évènements
 * @param nomChanson le titre
 */
void Musique::Lecture(wxString nomChanson)
{
    m_musCharge = true;
    m_isPlaying = true;
    m_stop = false;

    FMOD_System_CreateStream(m_system, (char*) nomChanson.wc_str(), /*FMOD_LOOP_OFF | FMOD_2D | */FMOD_SOFTWARE | FMOD_UNICODE, 0, &m_sound);
    FMOD_System_PlaySound(m_system, FMOD_CHANNEL_FREE, m_sound, 0, &m_channel);
    FMOD_Channel_SetVolume(m_channel, m_volume);

    m_cheminComplet = nomChanson;
    DureeMS();

    m_nomChanson = m_cheminComplet.AfterLast(wxFileName::GetPathSeparator());
    wxString chaineT = m_cheminComplet.BeforeLast(wxFileName::GetPathSeparator());
    m_album = chaineT.AfterLast(wxFileName::GetPathSeparator());

    chaineT = chaineT.BeforeLast(wxFileName::GetPathSeparator());
    m_artiste = chaineT.AfterLast(wxFileName::GetPathSeparator());

    #if DEBUG
    FichierLog::Get()->Ajouter(wxT("Musique::Lecture - ") + m_nomChanson);
    #endif

    if (m_parent)
    {
        wxCommandEvent evt(wxEVT_MUSIQUE_CHANGE, wxID_ANY);
        evt.SetInt(1);
        m_parent->GetEventHandler()->AddPendingEvent(evt);
        wxCommandEvent evt2(wxEVT_MUSIQUE_GRAPH, wxID_ANY);
        m_parent->GetEventHandler()->AddPendingEvent(evt2);
    }
}

/**
 * Suspend ou relance la lecture
 * @param etat si vrai, met la lecture sur pause sinon la relance
 */
void Musique::SetPause(bool etat)
{
    FMOD_Channel_SetPaused(m_channel, etat);
    FMOD_BOOL result;
    FMOD_Channel_GetPaused(m_channel, &result);
    m_isPlaying = !result;
    if (m_parent)
    {
        wxCommandEvent evt(wxEVT_MUSIQUE_LECTURE, wxID_ANY);
        evt.SetInt((result) ? 1 : 0);
        m_parent->GetEventHandler()->AddPendingEvent(evt);
    }
}

/**
 * Indique si l'écoute est en pause ou non. Pause ne veut pas dire stoppé
 * @return vrai si en pause
 */
bool Musique::GetPause()
{
    FMOD_BOOL result;
    FMOD_Channel_GetPaused(m_channel, &result);

    return result;
}

/**
 * Stop la lecture
 */
void Musique::SetStop()
{
    FMOD_Channel_Stop(m_channel);
    m_stop = true;
    m_isPlaying = false;
}

/**
 * Définie la façon dont le prochain titre sera à lire. N'est utilisé que lorsque la chanson actuelle est finie.
 * @param action l'action à faire : SUIVANT, PRECEDENT, IDENTIQUE
 */
void Musique::SetAction(e_ChangeChanson action)
{    m_action = action;}

/**
 * Effectus le changement de chanson en fonction de la valeur contenu dans action
 * @param action
 * @return vrai si réussite
 * @see Musique::SetAction(e_ChangeChanson)
 */
bool Musique::ChangementChanson(e_ChangeChanson action)
{
    if (FichierListe::Get()->GetNombreFichier() == 0)
    {
        /*m_nomChanson = wxEmptyString;
        m_cheminComplet = wxEmptyString;
        wxCommandEvent evt(wxEVT_MUSIQUE_CHANGE, GetId());
        evt.SetInt(0);
        GetParent()->GetEventHandler()->AddPendingEvent(evt);*/
        ModifListeVide();
        return false;
    }

    m_positionListe = FichierListe::Get()->GetPositionListe(m_cheminComplet, m_positionListe);

    if (action == PRECEDENT)
    {
        if (!m_aleatoire)
        {
            m_positionListe--;
            if (m_positionListe <0)
                m_positionListe = FichierListe::Get()->GetNombreFichier() -1;
        }
        else
            m_positionListe = rand() % FichierListe::Get()->GetNombreFichier();
    }
    else if (action == SUIVANT)
    {
        if(!m_aleatoire)
        {
            if (m_positionListe == -1)
                m_positionListe = 0;
            else
                m_positionListe++;

            if (m_positionListe >= FichierListe::Get()->GetNombreFichier())
                m_positionListe = 0;
        }
        else
            m_positionListe = rand() % FichierListe::Get()->GetNombreFichier();
    }
    else if (action == IDENTIQUE)
    {}
    else
        return false;

    m_cheminComplet = FichierListe::Get()->GetNomPosition(m_positionListe);

    if (!wxFileExists(m_cheminComplet))
        return false;

    SetStop();
    FMOD_Sound_Release(m_sound);

    #if DEBUG
    FichierLog::Get()->Ajouter(_T("Musique:ChangementChanson"));
    #endif
    Lecture(m_cheminComplet);

    return true;
}

/**
 * Changement de titre "automatique"
 * @return vrai si réussite
 * @see Musique::ChangementChanson(e_ChangeChanson)
 */
bool Musique::ChangementChanson()
{
    return Musique::ChangementChanson(m_action);
}

/**
 * Change le titre avec les arguments qui lui sont envoyés. Cette méthode est utilisée par ListeLecture et GestionPeriphMoitiePage.
 *Si la position vaut -1, le titre lu sera la première occurrence de chaine. Sinon, la recherche est faite à partir de la position peu importe le contenu de chaine.
 * @param position la position du titre dans la liste (ou dans le fichier musique.liste)
 * @param chaine l'adresse du titre
 * @return vrai si réussite
 */
bool Musique::ChangementChanson(long position, wxString chaine)
{
    if (FichierListe::Get()->GetNombreFichier() == 0)
    {
        ModifListeVide();
        return false;
    }

    if (position != -1)
        chaine = FichierListe::Get()->GetNomPosition(position);
    else
        position = FichierListe::Get()->GetPositionListe(chaine, -1);
    if (chaine.IsEmpty())// || !wxFileExists(chaine))
        return false;

    m_cheminComplet = chaine;
    m_positionListe = position;
    return ChangementChanson(IDENTIQUE);
    /*SetStop();
    FMOD_Sound_Release(m_sound);
    Lecture(chaine);
    m_positionListe = position;

    return true;*/
}

/**
 * Provoque le remplissage de la liste de lecture. Elle est utilisée lorsque le fichier est vide. Le contenu du fichier correspond donc au contenu du dossier contenant le titre envoyé en lecture
 */
void Musique::Listage()
{
    FichierListe::Get()->SetDossierRecherche(m_cheminComplet);
    FichierListe::Get()->ListageFichier();
    m_positionListe = FichierListe::Get()->GetPositionListe(m_cheminComplet);
}

/**
 * Provoque l'ajout de chaine à la liste de lecture
 * chaine un tableau de wxString contenant des adresses
 * maj si vrai, informe l'application du changement (pas toujours nécessaire)
 */
void Musique::Listage(wxArrayString *chaine, bool maj)
{
    FichierListe::Get()->ListageFichier(chaine);
    Recharger(maj);
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("Musique::Listage - tableau"));
    #endif
}

/**
 * Modifie la liste de lecture en déplaçant un ensemble de titres à la position pos dans la liste
 * @param chaine contient les positions des titres à déplacer
 * @param pos la ligne où doivent se retrouver les titres
 * @param maj si une mise à jour des tableaux est nécessaires
 * @param supprime doit valoir vrai
 */
void Musique::PlacerLigneInt(wxArrayString* chaine, long pos, bool maj, bool supprime)
{
    FichierListe::Get()->PlacerLigneInt(chaine, pos, supprime);
    Recharger(maj, true);
}

/**
 * Modifie la liste de lecture en ajoutant un ensemble de titres à la position pos dans la liste
 * @param chaine contient les noms des titres
 * @param pos la ligne où doivent être placée les titres
 * @param maj si une mise à jour des tableaux est nécessaires
 */
void Musique::PlacerLigneString(wxArrayString* chaine, long pos, bool maj)
{
    FichierListe::Get()->PlacerLigneString(chaine, pos);
    Recharger(maj, true);
}


/**
 * Provoque l'ajout de chaine à la liste de lecture
 * chaine l'adresse du titre à ajouter
 */
 void Musique::Listage(wxString chaine)
{
    if (Parametre::Get()->islisable(chaine.AfterLast('.').Lower()))
    {
        FichierListe::Get()->ListageFichier(chaine);
        if (!m_musCharge)
            Lecture(chaine);//ChangementChanson(0, "");
    }
}

/**
 * Provoque l'ajout à la liste de lecture du contenu du fichier donné en paramètre. Ce fichier doit être au format .m3u !
 * @param chemin l'adresse du fichier
 */
void Musique::CopieFichier(wxString chemin)
{
    if (FichierListe::Get()->CopieFichierTOListe(chemin, m_parent))// il faut relancer la musique si la liste est totalement nouvelle
    {
        int i = 0;
        while (i < FichierListe::Get()->GetNombreFichier() && !ChangementChanson(i, _T("")))
            i++;
        if (i == FichierListe::Get()->GetNombreFichier() && m_musCharge && (!m_stop || m_isPlaying))
        {
            #ifdef DEBUG
            FichierLog::Get()->Ajouter(_("Musique::CopieFichier - arrêt"));
            #endif
            SetStop();
            FMOD_Sound_Release(m_sound);
            m_sound = NULL;
            m_nomChanson = wxEmptyString;
            m_cheminComplet = wxEmptyString;
            m_positionListe = -1;
            if (m_parent)
            {
                wxCommandEvent evt2(wxEVT_MUSIQUE_GRAPH, wxID_ANY);
                m_parent->GetEventHandler()->AddPendingEvent(evt2);
            }
            //m_musCharge = false;
        }
    }
}

/**
 * Modifie (en interne) le contenu de m_duree : traduit le temps en ms de la chanson en minutes et secondes
 */
void Musique::DureeMS()
{
    unsigned int temps;
    FMOD_Sound_GetLength(m_sound, &temps, FMOD_TIMEUNIT_MS);

    m_duree.SetMSecondeTot(temps);
}

/**
 * Modifie (en interne) le contenu de m_tpsActuel : traduit le temps en ms de la chanson en minutes et secondes
 */
void Musique::TpsActuelMS()
{
    unsigned int position;
    FMOD_Channel_GetPosition(m_channel, &position, FMOD_TIMEUNIT_MS);

    m_tpsActuel.SetMSecondeTot(position);
}

/**
 * Indique si l'on arrive à la fin du titre
 * @return vrai si fin du titre
 */
bool Musique::VerifTemps()
{
    if (m_musCharge)
        TpsActuelMS();
    else
        return false;

    if (m_tpsActuel.GetMSecondeTot() >= m_duree.GetMSecondeTot() - 200)
        return true;
    else
        return false;
}

/**
 * Retourne la durée en ms de la chanson
 * @return la durée
 */
int Musique::GetDureeMS()
{    return m_duree.GetMSecondeTot();}

/**
 * Retourne le temps écoulé en ms de la chanson
* @return le temps écoulé
 */
int Musique::GetTpsActuel()
{    return m_tpsActuel.GetMSecondeTot();}

/**
 * Retourne la structure contenant les informations sur la durée du titre
 * @return la durée
 */
Duree Musique::GetDUREEDuree()
{    return m_duree;}

/**
 * Retourne la structure contenant les informations sur le temps écoulé du titre
 * @return le temps écoulé
 */
Duree Musique::GetDUREETpsActuel()
{    return m_tpsActuel;}

/**
 * Déplace le curseur de lecture
 * @param temps la position en ms
 */
void Musique::SetPositionMS(int temps)
{    FMOD_Channel_SetPosition(m_channel, temps, FMOD_TIMEUNIT_MS);}

/**
 * Indique si des titres ont été placés dans la liste de lecture
 * @return vrai si la liste n'est pas vide
 */
bool Musique::IsContainingMus()
{    return m_musCharge;}

/**
 * Indique si le mode de lecture est "répétition"
 * @return vrai si répétition du titre
 */
bool Musique::GetRepete()
{
    return (m_action == IDENTIQUE);
}

/**
 * Modifie l'action à effectuer lors de la fin du titre en fonction de etat. Si état est vrai, le titre sera lu en boucle sinon, un autre titre sera lu
 * @param etat
 */
void Musique::SetRepete(bool etat)
{
    m_action = (etat) ? IDENTIQUE : SUIVANT;
}

/**
 * Indique si l'on est en mode "Aléatoire"
 * @return vrai si aléatoire
 */
bool Musique::GetAleatoire()
{   return m_aleatoire;}

/**
 * Indique si un titre est en lecture (ni pause ni stop)
 * @return vrai si lecture (écoute)
 */
bool Musique::GetLecture()
{   return m_isPlaying;}

/**
 * Active ou désactive la lecture aléatoire
 * @param aleatoire si vrai, active l'aléatoire
 */
void Musique::SetAleatoire(bool aleatoire)
{   m_aleatoire = aleatoire;}

/**
 * Retourne le nom de la chanson "physique". Ex : chanson.mp3
 * @return le nom
 */
wxString Musique::GetNomChanson()
{    return m_nomChanson;}

/**
 * Retourne le nom comlet de la chanson en cours de lecture
 * @return le nom complet
 */
wxString Musique::GetNomComplet()
{
    return m_cheminComplet;
}

/**
 * Retourne le nom de l'album selon la structure de fichier artiste/album/titre.
 * @return le nom
 */
wxString Musique::GetAlbum()
{    return m_album;}

/**
 * Retourne le nom de l'album selon la structure de fichier artiste/album/titre.
 * @return le nom
 */
wxString Musique::GetArtiste()
{    return m_artiste;}

/**
 * Retourne le nom et la position du titre en cours de lecture
 * @return la position et le nom
 */
ChansonNomPos Musique::GetNomPos()
{
    m_positionListe = FichierListe::Get()->GetPositionListe(m_cheminComplet, m_positionListe);//FichierListe::Get().GetPositionListe(m_cheminComplet, m_positionListe));
    ChansonNomPos titre(m_nomChanson, m_positionListe);
    return titre;
}

/**
 * Efface de la liste le titre en cours de lecture
 * @return le nom et la position du titre effacé
 */
ChansonNomPos Musique::SupprimerNom()
{
    if(FichierListe::Get()->GetNombreFichier() == 0)
        return ChansonNomPos();
    ChansonNomPos Asuppr(m_cheminComplet, m_positionListe);

    if(FichierListe::Get()->GetNombreFichier() > 1)
        ChangementChanson(SUIVANT);
    else
        ModifListeVide();

    FichierListe::Get()->EffacerNom(Asuppr);
    m_positionListe--;
    return Asuppr;
}

/**
 * Efface de la liste le titre se trouvant à la position position.
 * @param position la position du titre à effacer
 */
void Musique::SupprimerNom(int position)//wxString chaine)
{
    ChansonNomPos titre(FichierListe::Get()->GetNomPosition(position), position);

    if (m_cheminComplet.IsSameAs(titre.GetNom()) && titre.GetNom().Length() != 0 && titre.GetPos() == m_positionListe)//titre actuellement en cours de lecture
    {
        if(FichierListe::Get()->GetNombreFichier() > 1)
            ChangementChanson(SUIVANT);
        else
            ModifListeVide();
        FichierListe::Get()->EffacerNom(titre);
        m_positionListe--;
        #if DEBUG
        FichierLog::Get()->Ajouter(_T("Musique::SupprimerNom - (titre actuel) ") + wxString::Format(_T("%d"), titre.GetPos()) + _T(" - ") + titre.GetNom());
        #endif
    }
    else
    {
        FichierListe::Get()->EffacerNom(titre);
        if (m_positionListe > titre.GetPos())
            m_positionListe--;
        #if DEBUG
        FichierLog::Get()->Ajouter(_T("Musique::SupprimerNom - ") + wxString::Format(_T("%d"), titre.GetPos()) + _T(" - ") + titre.GetNom());
        #endif
    }
}

/**
 * Efface de la liste les titre se trouvant dans tableau. Si le titre en écoute se trouve dans cette liste, un titre ne se trouvant pas dans celle-ci est lu
 * @param tableau les titres à effacer
 * @param maj vrai si une mise à jour des tableaux est à faire
 */
void Musique::SupprimerNom(wxArrayString *tableau, bool maj)
{
    unsigned int i = 0, taille = tableau->GetCount(), pos = 0;
    m_positionListe = FichierListe::Get()->GetPositionListe(m_cheminComplet, m_positionListe);
    bool change = false;

    while (i<taille && change == false)
    {
        if (m_cheminComplet.IsSameAs(tableau->Item(i)))
        {
            change = true;
            pos = m_positionListe - i;
        }
        i++;
    }

    FichierListe::Get()->EffacerNom(tableau);

    if (change)
    {
        if (FichierListe::Get()->GetNombreFichier() > 1)
        {
            if (m_positionListe >= FichierListe::Get()->GetNombreFichier())
                    m_positionListe = 0;
            else
                m_positionListe = pos;
            ChangementChanson(m_positionListe, FichierListe::Get()->GetNomPosition(m_positionListe));
        }
        else
            ModifListeVide();
    }
        Recharger(maj, false);
}

/**
 * Retourne le volume
 * @return le volume
 */
float Musique::GetVolume()
{
    float volume;
    FMOD_Channel_GetVolume(m_channel, &volume);
    return volume;
}

/**
 * Modifie le volume
 * @param volume le niveau sonore à appliquer
 */
void Musique::SetVolume(int volume)
{
    float vol = volume *0.01;
    m_volume = vol;
    FMOD_Channel_SetVolume(m_channel, m_volume);
}

/**
 * Retourne une chaine contenant les informations dur la durée su titre au format mm:ss
 * @return la chaine
 */
wxString Musique::GetDureeFormatMinSec()
{
    wxString chaine;
    chaine << m_duree.GetMinute() << _T(":") << m_duree.GetSeconde();
    return chaine;
}

/**
 * Retourne l'instance de la classe wxFichierListe. A utiliser le moins possible !
 * @return l'instance
 */
/*wxFichierListe* Musique::GetFichier()
{    return FichierListe::Get();}*/

/**
 * Remplit le tableau spectre avec les valeurs du spectre du titre
 * @param spectre un tableau de taille largeur
 * @param largeur la taille du tableau
 */
void Musique::RemplirSpectre(float spectre[], int largeur)
{   FMOD_System_GetSpectrum(m_system, spectre, largeur, 0, FMOD_DSP_FFT_WINDOW_RECT);}

/**
 * Modifie les attributs de la classe pour prendre en compte le fait que la liste de lecture soit vide. Elle n'effectue aucun test.
 */
void Musique::ModifListeVide()
{
    SetStop();
    FMOD_Sound_Release(m_sound);
    if (m_parent)
    {
        wxCommandEvent evt(wxEVT_MUSIQUE_CHANGE, wxID_ANY);
        evt.SetInt(0);
        m_parent->GetEventHandler()->AddPendingEvent(evt);
    }
    m_musCharge = false;
    m_nomChanson = wxEmptyString;
    m_cheminComplet = wxEmptyString;
}

/**
 * Agit de façon globale sur l'application en fonction des paramètres
 * @param maj si vrai, provoque la mise à jour des tableaux
 * @param lect si vrai, provoque la lecture d'un titre
 */
void Musique::Recharger(bool maj, bool lect)
{
    if (maj && m_parent)
    {
        wxCommandEvent evt(wxEVT_MUSIQUE_MAJ, wxID_ANY);
        m_parent->GetEventHandler()->AddPendingEvent(evt);
    }
    if (lect && !m_musCharge)
    {
        if (!m_aleatoire)
            ChangementChanson(0, wxT(""));
        else
            ChangementChanson();
    }
}


