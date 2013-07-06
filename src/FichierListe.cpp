/***************************************************************
 * Name:      FichierListe.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2009-09-25
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../include/FichierListe.h"

/**
 * @class FichierListe
 * @brief Gére le support physique de la liste de lecture. La liste de lecture est enregistré dans un fichier sur le disque dur.
 *C'est ce fichier que le classe gère.
 */

static FichierListe *s_instanceFichierListe = NULL;

FichierListe* FichierListe::Get()
{
    if (s_instanceFichierListe == NULL)
        s_instanceFichierListe = new FichierListe;
    return s_instanceFichierListe;
}

/**
 * Constructeur privé
 */
FichierListe::FichierListe()
{    Init();}

FichierListe::~FichierListe()
{
    OnExit();
}

/**
 * Initialise les paramètres de FichierListe
 */
void FichierListe::Init()
{
    m_Liste = Parametre::Get()->getRepertoireParametre(_T("musique.liste"));
    wxRemoveFile(m_Liste);
    wxTextFile fichierListe(m_Liste);
    fichierListe.Create();
    fichierListe.Close();
    m_nombreFichier = 0;
}

void FichierListe::Delete()
{
    delete s_instanceFichierListe;
    s_instanceFichierListe = NULL;
}

/**
 * Supprime le fichier dans lequel est enregistré la liste de lecture
 */
void FichierListe::OnExit()
{    wxRemoveFile(m_Liste);}

/**
 * Rempli le fichier avec le contenu du dossier donné précédemment en paramètre
 * @see Parametre
 */
void FichierListe::ListageFichier()
{
    wxTextFile fichierListe(m_Liste);
    if (!fichierListe.Exists())
        fichierListe.Create();
    else
    {
        fichierListe.Open();
        fichierListe.Clear();
    }

    wxString repertoire = m_Chanson.BeforeLast(wxFileName::GetPathSeparator());
    wxDir dir(repertoire);


    if (!Parametre::Get()->getSousDossier())
    {
        wxString temp;
        bool cont = dir.GetFirst(&temp, wxEmptyString, wxDIR_FILES|wxDIR_DIRS);

        while (cont)
        {
            if (Parametre::Get()->islisable(temp.AfterLast('.').Lower()))
                fichierListe.AddLine(repertoire + wxFileName::GetPathSeparator() + temp);
            cont = dir.GetNext(&temp);
        }
    }
    else
    {
        Recherche trav(&fichierListe);
        dir.Traverse(trav, _T("*.*"), wxDIR_DIRS|wxDIR_FILES);//Parametre::Get()->getFiltre()
    }

    m_nombreFichier = fichierListe.GetLineCount();
    fichierListe.Write();
    fichierListe.Close();
}

/**
 * Ajoute au fichier chaine
 * @param chaine la chaine à ajouter
 */
void FichierListe::ListageFichier(wxString chaine)
{
    wxTextFile fichierListe(m_Liste);

    if (!fichierListe.Open())
        return;

    if (wxFileExists(chaine))
        fichierListe.AddLine(chaine);
    m_nombreFichier = fichierListe.GetLineCount();
    fichierListe.Write();
    fichierListe.Close();
}

/**
 * Ajoute au fichier le contenu du tableau donné en paramètre
 * @param chaine un pointeur sur le tableau à ajouter
 */
void FichierListe::ListageFichier(wxArrayString *chaine)
{
    if (chaine->IsEmpty())
        return;
    wxTextFile fichierListe(m_Liste);
    if (!fichierListe.Exists())
        m_nombreFichier = 0;
    else
        fichierListe.Open();

    for (unsigned int i=0; i<chaine->GetCount(); i++)
    {
        if (wxFileExists(chaine->Item(i)))
        {
            if (chaine->Item(i).AfterLast('.').Lower().IsSameAs(_T(".m3u")))
            {
                wxTextFile fichierM3U(chaine->Item(i));
                if (fichierM3U.Exists())
                    fichierM3U.Open();
                for (unsigned int j=1; j<fichierM3U.GetLineCount(); j++)
                    fichierListe.AddLine(fichierM3U.GetLine(j));
                fichierM3U.Close();
            }
            else
                fichierListe.AddLine(chaine->Item(i));
        }
        else if (Parametre::Get()->getSousDossier() && wxDirExists(chaine->Item(i)))
        {
            wxDir dir(chaine->Item(i));
            Recherche trav(&fichierListe);
            dir.Traverse(trav, _T("*.*"), wxDIR_DIRS|wxDIR_FILES);//Parametre::Get()->getFiltre()
        }
    }

    m_nombreFichier = fichierListe.GetLineCount();
    fichierListe.Write();
    fichierListe.Close();
}

/**
 * Copie le contenu d'un fichier dans la liste de lecture. Si celle-ci n'est pas vide, une fenêtre demande l'action à effectuer
 * @param NomFichierOrigine le nom du fichier à copier
 * @param Parent Un pointeur sur la fenêtre parente
 * @return vrai si réussi
 */
bool FichierListe::CopieFichierTOListe(wxString NomFichierOrigine, wxWindow *WXUNUSED(Parent))
{
    bool copie = true, reprise = false;

    wxTextFile fichierListe(m_Liste);
    if (!fichierListe.Exists())
        fichierListe.Create();
    else
        fichierListe.Open();

    if (fichierListe.IsOpened() && fichierListe.GetLineCount() >0)//FichierListe.IsOpened()
    {
        wxArrayString choix;
        choix.Add(_("Ajouter le contenu du fichier à la liste de lecture"));
        choix.Add(_("Remplacer la liste de lecture par le contenu du fichier"));
        choix.Add(_("Ne rien faire"));
        wxSingleChoiceDialog actionPlay(NULL, _("La liste de lecture n'est pas vierge !\nQue souhaitez-vous faire ?"), _("Action requise, problème liste de lecture"), choix);

        if (actionPlay.ShowModal() == wxID_OK)
        {
            if (actionPlay.GetSelection() == 1)
            {
                fichierListe.Clear();
                fichierListe.Write();
                m_nombreFichier = 0;
                reprise = true;
            }
            else if (actionPlay.GetSelection() == 2)
                copie = false;
        }
        else
            copie = false;
    }

    if (copie)
    {
        wxTextFile fichierACopie(NomFichierOrigine);
        fichierACopie.Open();

        if (!fichierListe.IsOpened() || !fichierACopie.IsOpened())
            return false;

        if (fichierListe.GetLineCount() == 0)
            reprise = true;

        for (unsigned int i = 1; i < fichierACopie.GetLineCount(); i++)
            fichierListe.AddLine(fichierACopie.GetLine(i));

        fichierACopie.Close();
    }
    m_nombreFichier = fichierListe.GetLineCount();
    fichierListe.Write();
    fichierListe.Close();
    return reprise;
}

/**
 * Retourne l'adresse du fichier utilisé pour faire la liste de lecture
 * @return l'adresse
 */
wxString FichierListe::GetCheminListe()
{    return m_Liste;}

/**
 * Retourne le texte (chemin) présent à la ligne spécifiée
 * @param position le numéro de la ligne
 * @return la chaine correspondante
 */
wxString FichierListe::GetNomPosition(int position)
{
    wxTextFile fichierListe(m_Liste);
    if (!fichierListe.Open())
        return _T("");

    wxString chaine;
    if (fichierListe.GetLineCount())
        chaine = fichierListe.GetLine(position);
    fichierListe.Close();
    return chaine;
}

/**
 * Recherche dans le fichier si la combinaison le numéro de ligne de chaineT. position spécifie à partir de quel endroit rechercher. Si position vaut -1,
 *la recherche se fait depuis le début du fichier. La recherche est effectuée en premier en sens descendant puis en sens montant à partir de position
 * @param chaineT la chaine à rechercher
 * @param position l'endroit à partir duquel doit être fait la recherche
 * @return -1 si erreur ou inexistant. Sinon le numéro de ligne
 */
int FichierListe::GetPositionListe(wxString chaineT, int position)
{
    wxTextFile fichierListe(m_Liste);
    if (!fichierListe.Open())
       return -1;

    if (chaineT.IsEmpty())
        return -1;

    if (position != -1 && position < (int)fichierListe.GetLineCount() && fichierListe.GetLine(position).IsSameAs(chaineT))
    {
        fichierListe.Close();
        return position;
    }

    if (position == (int)fichierListe.GetLineCount())
        position--;

    unsigned int i = (position == -1) ? 0 : position;
    bool continuer = true;

    while (i < fichierListe.GetLineCount() && continuer)
    {
        if (fichierListe.GetLine(i).IsSameAs(chaineT))// || extrait.First(chaineT) != wxNOT_FOUND)
        {
            continuer = false;
            i--;
        }
        i++;
    }

    if (continuer)
    {
        i = position;
        while (i > 0 && continuer)
        {
            if (fichierListe.GetLine(i).IsSameAs(chaineT))// || extrait.First(chaineT) != wxNOT_FOUND)
            {
                continuer = false;
                i++;
            }
            i--;
        }
        //continuer = false;
    }

    return continuer ? -1 : i;
}

/**
 * Retourne le nombre de lignes du fichier. ie le nombre de titre mis en mémoire
 * @return le nombre de fichier
 */
int FichierListe::GetNombreFichier()////////////////
{
    wxTextFile fichierListe(m_Liste);
    fichierListe.Open();
    m_nombreFichier = fichierListe.GetLineCount();
    fichierListe.Close();
    return m_nombreFichier;
}

/**
 * Affecte le chemin de la chanson. C'est à partir de cette adresse que ce fait la plupart des opérations
 * @param chanson une adresse complète
 */
void FichierListe::SetDossierRecherche(wxString chanson)
{    m_Chanson = chanson;}

/**
 * Retire de la liste le contenu de titre(Nom, Position). Le nom est important, la position est vivement conseillée
 * @param titre "l'élément" à retirer
 */
void FichierListe::EffacerNom(ChansonNomPos titre)
{
    int ligneASuppr;
    if (titre.GetPos() != -1)
        ligneASuppr = titre.GetPos();
    else
        ligneASuppr = GetPositionListe(titre.GetNom());

    wxTextFile fichierListe(m_Liste);
    if (!fichierListe.Open())
        return;
    if (fichierListe.GetLineCount() > 0)
        fichierListe.RemoveLine(ligneASuppr);
    m_nombreFichier = fichierListe.GetLineCount();
    fichierListe.Write();
    fichierListe.Close();
}

/**
 * Retire du fichier les titres présents dans le tableau
 * @param tableau le pointeur sur le tableau
 */
void FichierListe::EffacerNom(wxArrayString *tableau)
{
    wxTextFile fichierListe(m_Liste);
    if (!fichierListe.Open())
        return;

    size_t i = 0, maxTab = tableau->GetCount(), j = 0;
    bool parcouru = true, cont = true;

    while (j < maxTab && cont)
    {
        while (i < fichierListe.GetLineCount() && cont)
        {
            if (fichierListe.GetLine(i).IsSameAs(tableau->Item(j)))
            {
                fichierListe.RemoveLine(i);
                j++;
                i--;
                parcouru = false;
                if (j >= maxTab)
                    cont = false;
            }
            i++;
        }
        if (parcouru)
        { parcouru = false; i++;}
        else
            parcouru = true;
        i = 0;
    }

    m_nombreFichier = fichierListe.GetLineCount();
    fichierListe.Write();
    fichierListe.Close();
}

/**
 * Echange la position des deux chaines données en paramètre
 * @param nom1 la première chaine
 * @param nom2 la deuxième chaîne
 */
void FichierListe::EchangeNom(wxString nom1, wxString nom2)////////////////Revu
{
    wxTextFile fichierListe(m_Liste);
    if (!fichierListe.Open())
        return;

    int ligneASuppr = GetPositionListe(nom1);
    fichierListe.RemoveLine(ligneASuppr);
    fichierListe.InsertLine(nom2, ligneASuppr);
    m_nombreFichier = fichierListe.GetLineCount();
    fichierListe.Write();
    fichierListe.Close();
}

/**
 * Si <b>supprime</b> vaut vrai, déplace les lignes dont le numéro se trouve dans le tableau <b>ligne</b> à la position <b>position<b/>.
 *Si <b>supprime</b> vaut faux, crée une copie des lignes dont le numéro se trouve dans le tableau <b>ligne</b> à la position <b>position<b/>.
 * @param ligne un pointeur sur le tableau contenant <b>le numéro</b> des lignes
 * @param position
 * @param supprime si vrai, l'ancienne position
 * @return vrai si le déplacement a été fait sans erreurs
 * @see FichierListe::PlacerLigneString
 */
bool FichierListe::PlacerLigneInt(wxArrayString *ligne, long position, bool supprime)
{
    wxTextFile fichierListe(m_Liste);
    if (!fichierListe.Open())
        return false;

    int j = 0, k = 0;
    long val;
    bool deplace = true;
    wxArrayString chaine;
    chaine.Alloc(ligne->GetCount());

    if (position < 0)
        position = 0;
    else if (position > long(fichierListe.GetLineCount()+1))
        position = fichierListe.GetLineCount()+1;

    for (unsigned int i=0; i<ligne->GetCount(); i++)
    {
        ligne->Item(i).ToLong(&val);
        chaine.Add(fichierListe.GetLine(val));
        if (val == position)
            deplace = false;
    }
    if (deplace)
    {
        for (unsigned int i=0; i<ligne->GetCount(); i++)
        {
            ligne->Item(i).ToLong(&val);
            if (val > position)//Remonte
            {
                if (supprime)
                    fichierListe.RemoveLine(val);
                fichierListe.InsertLine(chaine.Item(i), position+j);
                j++;
            }
            else if (val < position)//Descend
            {
                if (supprime)
                    fichierListe.RemoveLine(val-k);
                fichierListe.InsertLine(chaine.Item(i), position-1);///////
                k++;
            }
        }
    }
    m_nombreFichier = fichierListe.GetLineCount();
    fichierListe.Write();
    fichierListe.Close();
    return deplace;
}

/**
 * Place les chaines contenues dans le tableau ligne à la position pos
 * @param ligne un pointeur de tableau contenant du texte
 * @param pos
 * @see FichierListe::PlacerLigneInt
 */
void FichierListe::PlacerLigneString(wxArrayString *ligne, long pos)
{
    wxTextFile fichierListe(m_Liste);
    if (!fichierListe.Open())
        return;

    long insertion = pos;
    bool deplace = true;

    if (insertion < 0)
        insertion = 0;
    else if (insertion > long(fichierListe.GetLineCount()+1))
        insertion = fichierListe.GetLineCount()+1;

    if (deplace)
    {
        for (unsigned int i=0; i<ligne->GetCount(); i++)
        {
            if (Parametre::Get()->islisable(ligne->Item(i).AfterLast('.').Lower()))
            {
                fichierListe.InsertLine(ligne->Item(i), insertion);
                insertion++;
            }
        }
    }
    m_nombreFichier = fichierListe.GetLineCount();
    fichierListe.Write();
    fichierListe.Close();
}


