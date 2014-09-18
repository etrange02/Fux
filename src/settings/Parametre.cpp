/***************************************************************
 * Name:      Parametre.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2011-06-01
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../../include/settings/Parametre.h"

/**
 * @class Parametre
 * @brief La classe Paramètre contient toutes les informations sur l'emplacement des différents fichiers et dossiers nécessaires à l'exécution de Fu(X).
 */

static Parametre* instanceParametre = NULL;

/**
 * Constructeur
 */
Parametre::Parametre()
{
    m_fond.SetRGB(0, 0, 0);
    m_barre.SetRGB(0, 0, 255);
    m_police.SetRGB(255, 0, 255);
    m_haut.SetRGB(255, 0, 0);
    m_miSup.SetRGB(0, 255, 0);
    m_miInf.SetRGB(0, 0, 0);
    m_bas.SetRGB(0, 0, 0);
    m_doubleBarre = false;

    m_cheminCouleur = _T("");
    m_cheminSon = _T("");
    //"Fichiers audio (*.mp3;*.wav;*.aac;*.m4a;*.mp4;*.ogg)|*.mp3;*.wav;*.aac;*.m4a;*.mp4;*.ogg"
     /*|| temp.EndsWith(".m4a"))*/ //||temp.EndsWith(".wav") || temp.EndsWith(".aac") ||/ || temp.EndsWith(".ogg")
    m_extension.Add(_T("mp3"));
    m_extension.Add(_T("wma"));
    m_extension.Add(_T("wav"));
    m_extension.Add(_T("ogg"));
    m_id3v2.Add(_T("mp3"));
    m_id3v2.Add(_T("wma"));
    m_id3v2.Add(_T("ogg"));
    m_extensionValide = _T("Fichiers audio (*.mp3;*.wma;*.wav;*.ogg)|*.mp3;*.wma;*.wav;*.ogg");/*;*.m4a;*.wav;*.aac;;*.ogg|*.wav;*.aac;*.m4a;*.ogg*/ /*|Fichiers wav (*.wav)|*.wav"*/
    //m_extensionValide = _T("Fichiers audio (*.mp3)|*.mp3;(*.wma)|*.wma;(*.wav)|*.wav;(*.ogg)|*.ogg");/*;*.m4a;*.wav;*.aac;;*.ogg|*.wav;*.aac;*.m4a;*.ogg*/ /*|Fichiers wav (*.wav)|*.wav"*/
    m_repertoireDefaut = wxStandardPaths::Get().GetDocumentsDir();
    m_sousDossier = false;

    m_cheminRepertParam = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + REPERTOIRE;
    if (wxDir::Exists(m_cheminRepertParam))//installation classique
    {
        m_paramInstallation = true;
    }
    else if (wxDir::Exists(wxStandardPaths::Get().GetDataDir() + wxFileName::GetPathSeparator() + _T("Play_list_M3U")))//portable
    {
        m_cheminRepertParam = wxStandardPaths::Get().GetDataDir();
        m_paramInstallation = false;
    }
    else//Les dossiers devront être créés ici
    {
        m_paramInstallation = true;
        creerRepertoireParametre();// L'appel se fait dans FuXFenetre
    }
    //wxLogMessage(m_cheminRepertParam);
    setCheminCouleur(m_cheminRepertParam);
    setCheminSon(m_cheminRepertParam);
}

Parametre::~Parametre()
{
    #if DEBUG
    FichierLog::Get()->Ajouter(_T("Parametre::~Parametre()"));
    #endif
}

/**
 * Retourne l'instance de la classe Parametre
 * @return l'instance
 */
Parametre* Parametre::Get()
{
    if (!instanceParametre)
        instanceParametre = new Parametre;
    return instanceParametre;
}

/**
 * Modifie l'adresse du fichier à utiliser pour les couleurs du graph
 * @param chemin l'adresse du fichier
 */
void Parametre::setCheminCouleur(wxString chemin)
{
    m_cheminCouleur = chemin;
    m_cheminCouleur << wxFileName::GetPathSeparator() << _T("Preference") << wxFileName::GetPathSeparator() << _T("Couleur");
}

/**
 * Modifie l'adresse du fichier à utiliser pour les volumes de l'application
 * @param chemin l'adresse du fichier
 */
void Parametre::setCheminSon(wxString chemin)
{
    m_cheminSon = chemin;
    m_cheminSon << wxFileName::GetPathSeparator() << _T("Preference") << wxFileName::GetPathSeparator() << _T("Son");
}

/**
 * Retourne le chemin complet du dossier contenant les paramètres du graphe
 * @return le chemin
 */
wxString Parametre::getCheminCouleur()
{    return m_cheminCouleur;}


/**
 * Retourne le chemin complet du fichier se trouvant dans le dossier Preference/Couleur
 * @param nom le nom d'un fichier
 * @return le chemin du fichier
 */
wxString Parametre::getCheminCouleur(wxString nom)
{    return m_cheminCouleur + wxFileName::GetPathSeparator() + nom;}

/**
 * Retourne le chemin complet du dossier contenant les paramètres du son
 * @return le chemin
 */
wxString Parametre::getCheminSon()
{    return m_cheminSon;}

/**
 * Retourne le chemin complet du fichier se trouvant dans le dossier Preference/Son
 * @param nom le nom d'un fichier
 * @return le chemin du fichier
 */
wxString Parametre::getCheminSon(wxString nom)
{    return m_cheminSon + wxFileName::GetPathSeparator() + nom;}

/**
 * Modifie les couleurs du graphe
 * @param fond la couleur du fond
 * @param barre la couleur de la barre de défilement
 * @param police la couleur des écrits
 * @param haut la couleur de l'extrémité supérieur du graphe
 * @param miSup la couleur de la moitié supérieur du graphe
 * @param miInf la couleur de la moitié inférieur du graphe
 * @param bas la couleur de la partie intérieur du graphe
 * @param doubleBarre symétrie horizontale si vrai
 */
void Parametre::setCouleurs(Couleur fond, Couleur barre, Couleur police, Couleur haut, Couleur miSup, Couleur miInf, Couleur bas, bool doubleBarre)
{
    /*m_fond = fond; m_barre = barre; m_police = police;
    m_haut = haut; m_miSup = miSup;
    m_miInf = miInf; m_bas = bas;
    m_doubleBarre = doubleBarre;*/

    MusiqueGraph::Get()->AffecteCouleurs(fond, barre, police, haut, miSup, doubleBarre, miInf, bas);
}

/**
 * Modifie le volume de plusieurs classes (Musique et SliderSon)
 * @param volume
 * @param volumePC
 */
void Parametre::setVolume(wxString volume, wxString volumePC)
{
    long vol = 0, volPC = 0;
    volume.ToLong(&vol);
    volumePC.ToLong(&volPC);
    setVolume(vol, volPC);
}

/**
 * Modifie le volume de plusieurs classes (Musique et SliderSon)
 * @param volume
 * @param volumePC
 */
void Parametre::setVolume(int volume, int volumePC)
{
    MusicManager::get()->getMusicPlayer()->setVolume(volume);
    SliderSon::Get()->SetValue(volume);
}

/**
 * Indique si l'on doit lister les sous dossiers d'un répertoire lors d'une recherche
 * @return vrai si les sous-dossiers doivent être pris en compte
 */
bool Parametre::getSousDossier()
{    return m_sousDossier;}

/**
 * Affecte ou non les opérations de recherche dans les sous-répertoires
 * @param sousDossier
 */
void Parametre::setSousDossier(bool sousDossier)
{    m_sousDossier = sousDossier;}

/**
 * Retourne une chaine contenant les extensions lisible par les classes. Elle sert à créer le filtre des fenêtres de recherche
 * @return le filtre
 */
wxString Parametre::getExtensionValideMusique()
{    return m_extensionValide;}

/**
 * Retourne le chemin complet du répertoire qui doit être ouvert lors d'une recherche
 * @return le chemin
 */
wxString Parametre::getRepertoireDefaut()
{    return m_repertoireDefaut;}

/**
 * Modifie le chemin du répertoire qui doit être ouvert lors d'une recherche
 * @param chemin le répertoire par défaut à ouvrir
 */
void Parametre::setRepertoireDefaut(wxString chemin)
{    m_repertoireDefaut = chemin;}

/**
 * Indique si l'extension envoyée est au format id3v2
 * @param ext l'extension à tester
 * @return vrai si l'extension permet l'ID3v2
 */
bool Parametre::isID3V2(const wxString &ext)
{
    unsigned int i = 0;
    while (i<m_id3v2.Count())
    {
        if (m_id3v2.Item(i).IsSameAs(ext))
            return true;
        else
            i++;
    }
    return false;
}

/**
 * Indique si Fu(X) peut lire et gérer l'extension. La chaîne envoyée doit être en minuscule et ne pas contenir de '.'
 * @param ext l'extension qui doit être testé.
 * @return vrai si la lecture est possible
 */
bool Parametre::islisable(const wxString &ext)
{
    unsigned int i = 0;
    while (i<m_extension.Count())
    {
        if (m_extension.Item(i).IsSameAs(ext, false))
            return true;
        else
            i++;
    }
    return false;
}

/**
 * Retourne une chaine utilisable pour filtrer les fichiers par extension.
 * @return le filtre
 */
wxString Parametre::getFiltre()
{
    wxString filtre = _T("*.") + m_extension.Item(0);
    for (unsigned int i = 1; i<m_extension.Count(); i++)
        filtre.Append(_T(";*.") + m_extension.Item(i));
    return filtre;
}

/**
 * Retourne l'adresse qui contient tous les fichiers et paramètres nécessaires à Fu(X)
 * @return l'adresse du répertoire
 */
wxString Parametre::getRepertoireParametre()
{    return m_cheminRepertParam;}

/**
 * Retourne l'adresse de l'élément donné en paramètre se trouvant dans le dossier des paramètres de Fu(X)
 * @param element le nom du fichier/dossier
 * @return l'adresse du fichier
 */
wxString Parametre::getRepertoireParametre(wxString element)
{    return m_cheminRepertParam + wxFileName::GetPathSeparator() + element;}

/**
 * Retourne l'adresse de l'élément donné en paramètre se trouvant dans le dossier des paramètres de Fu(X)
 * @param dir le nom du sous-répertoire
 * @param element le nom du fichier/dossier
 * @return l'adresse du fichier
 */
wxString Parametre::getRepertoireParametre(wxString dir, wxString element)
{    return m_cheminRepertParam + wxFileName::GetPathSeparator() + dir + wxFileName::GetPathSeparator() + element;}

/**
 * Retourne l'adresse de l'élément donné en paramètre se trouvant dans le dossier des paramètres de Fu(X)
 * @param dir1 le nom du premier sous-répertoire
 * @param dir2 le nom du deuxième sous-répertoire
 * @param element le nom du fichier/dossier
 * @return l'adresse du fichier
 */
wxString Parametre::getRepertoireParametre(wxString dir1, wxString dir2, wxString element)
{    return m_cheminRepertParam + wxFileName::GetPathSeparator() + dir1 + wxFileName::GetPathSeparator() + dir2 + wxFileName::GetPathSeparator() + element;}

/**
 * Indique si le répertoire contenant les fichiers nécessaires à Fu(X) est celui créé au moment de l'installation. C'est à dire 'C:/Users/username/AppData/Roaming/Fu(X)'
 * @return vrai si installation classique
 */
bool Parametre::isRepertoireInstallationDefaut()
{    return m_paramInstallation;}

/**
 * Créé la structure des fichiers de Fu(X) si celle-ce est inexistante. Elle utilise le répertoire par défaut.
 */
void Parametre::creerRepertoireParametre()
{
    creerRepertoireParametre(m_cheminRepertParam);
}

/**
 * Créé la structure des fichiers de Fu(X) si celle-ce est inexistante à l'adresse donnée.
 * @param chemin le répertoire où la structure doit être créée.
 */
void Parametre::creerRepertoireParametre(wxString chemin)
{
    wxString repertoire;

    //Test répertoire générale
    repertoire = chemin;
    if(!wxFileName::DirExists(repertoire))
        wxFileName::Mkdir(repertoire);

    //Test sous-Rep Pref
    repertoire = chemin + wxFileName::GetPathSeparator() + _T("Preference");
    if(!wxFileName::DirExists(repertoire))
        wxFileName::Mkdir(repertoire);

    //Test sous-Rep Pref/couleur
    repertoire = chemin + wxFileName::GetPathSeparator() + _T("Preference") + wxFileName::GetPathSeparator() + _T("Couleur");
    if(!wxFileName::DirExists(repertoire))
        wxFileName::Mkdir(repertoire);

    //Test sous-Rep Pref/son
    repertoire = chemin + wxFileName::GetPathSeparator() + _T("Preference") + wxFileName::GetPathSeparator() + _T("Son");
    if(!wxFileName::DirExists(repertoire))
        wxFileName::Mkdir(repertoire);

    //Test sous-Rep Playlist
    repertoire = chemin + wxFileName::GetPathSeparator() + _T("Play_list_M3U");
    if(!wxFileName::DirExists(repertoire))
        wxFileName::Mkdir(repertoire);

    //Test fichier conf
    repertoire = chemin + wxFileName::GetPathSeparator() + _T("Fu(X).conf");
    if(!wxFileName::FileExists(repertoire))
    {
        wxXmlNode *rootNode = new wxXmlNode(wxXML_ELEMENT_NODE, _("default"));
        new wxXmlNode(rootNode, wxXML_TEXT_NODE, _(""));
        wxXmlDocument doc;
        doc.SetRoot(rootNode);
        doc.Save(repertoire);

        /*wxTextFile fichier(repertoire);
        if (fichier.Create())
        {
            fichier.AddLine(_T("#EXTCONF_1"));
            fichier.AddLine(_T("Couleur= NON"));
            fichier.AddLine(_T("Son= NON"));
            fichier.AddLine(_T("Reprise= NON"));
            fichier.AddLine(_T("Chemin= NON"));
            fichier.AddLine(_T("SousDossier= NON"));

            fichier.Write();
            fichier.Close();
        }*/
    }
}

/**
 * Retourne l'adresse du répertoire dans lequel se trouve l'exécutable
 * @return l'adresse du répertoire
 */
wxString Parametre::getRepertoireExecutable()
{
    return wxStandardPaths::Get().GetDataDir();
}

/** @brief Je ne sais pas ce qu'est brief
 * Retourne l'adresse du fichier donné en paramètre. Ce fichier doit se trouver dans le dossier lib du répertoire de l'exécutable
 * @param element le nom du fichier avec l'extension
 * @return l'adresse complète
 */
wxString Parametre::getRepertoireExecutableLib(wxString element)
{
    return wxStandardPaths::Get().GetDataDir() + wxFileName::GetPathSeparator() + _T("lib") + wxFileName::GetPathSeparator() + element;
}

bool Parametre::isContainerFile(const wxString& extension)
{
    return extension.IsSameAs(_T("m3u"), false);
}

