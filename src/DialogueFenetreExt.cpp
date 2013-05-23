/***************************************************************
 * Name:      DialogueFenetreExt.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2010-05-29
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../include/DialogueFenetreExt.h"

/**
 * @class DialogEnregistreM3U
 * @brief Ouvre une boîte de dialogue permettant de choisir le nom du fichiers .m3u à créer et éventuellement le raccourci.
 */
BEGIN_EVENT_TABLE(DialogEnregistreM3U, wxDialog)
    EVT_BUTTON(ID_DIALOGUE_SAUVEGARDE_M3U, DialogEnregistreM3U::OuvrirDossier)
END_EVENT_TABLE()

/**
 * Constructeur
 * @param parent la fenêtre parente
 * @param id l'identifiant de l'instance
 * @param racc le répertoire où doit être créé un raccourci
 */
 DialogEnregistreM3U::DialogEnregistreM3U(wxWindow *parent, wxWindowID id, wxString racc) : wxDialog(parent, id, _("Création de playlist (fichier .m3u)"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER)
{
    m_chemin = wxEmptyString; m_raccourci = racc;
    m_rep = Parametre::Get()->getRepertoireParametre(_T("Play_list_M3U"));
    Centre();
}

/**
 * Crée les éléments graphiques de la fenêtre
 */
void DialogEnregistreM3U::Creer()
{
    wxBoxSizer *sizerV = new wxBoxSizer(wxVERTICAL);
    SetSizer(sizerV);

    wxStaticText* Text = new wxStaticText[3];
    Text[0].Create(this, wxID_ANY, _("Choisissez une sauvegarde existante"));
    sizerV->Add(&Text[0], 0, wxALL, 5);
    m_liste = new wxChoice(this, wxID_ANY);
    sizerV->Add(m_liste, 0, wxLEFT|wxRIGHT|wxDOWN|wxEXPAND, 5);

    Text[1].Create(this, wxID_ANY, _("Ou bien créez une nouvelle sauvegarde"));
    sizerV->Add(&Text[1], 0, wxALL, 5);
    m_boiteNouveau = new wxTextCtrl(this, wxID_ANY, _T(""));
    sizerV->Add(m_boiteNouveau, 0, wxLEFT|wxRIGHT|wxDOWN|wxEXPAND, 5);

    sizerV->Add(new wxStaticLine(this), 0, wxUP|wxLEFT|wxRIGHT|wxEXPAND, 15);

    Text[2].Create(this, wxID_ANY, _("Créer un raccourci ? Où le place-t-on ?"));
    sizerV->Add(&Text[2], 0, wxALL, 5);

    wxBoxSizer *sizerH1 = new wxBoxSizer(wxHORIZONTAL);
    sizerV->Add(sizerH1, 0, wxDOWN|wxEXPAND, 5);
    m_boiteRaccourci = new wxTextCtrl(this, wxID_ANY, m_raccourci);
    sizerH1->Add(m_boiteRaccourci, 1, wxALL|wxEXPAND, 5);
    m_bouton = new wxButton(this, ID_DIALOGUE_SAUVEGARDE_M3U, _T("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    sizerH1->Add(m_bouton, 0, wxUP|wxDOWN|wxRIGHT, 5);

    sizerV->Add(CreateButtonSizer(wxOK|wxCANCEL), 0, wxALL|wxALIGN_RIGHT, 5);
    CreerListeM3U();
    //Fit();
}

/**
 * Crée une liste de tous les fichiers .m3u présents dans le dossier des paramètres
 */
void DialogEnregistreM3U::CreerListeM3U()
{
    wxString dossierM3U = m_rep;

    wxDir::GetAllFiles(dossierM3U, &m_chaineM3U, _T("*.m3u"));

    for (size_t i=0; i<m_chaineM3U.GetCount(); i++)
        m_liste->Append(m_chaineM3U.Item(i).AfterLast(wxFileName::GetPathSeparator()));
}

/**
 * Retourne le nom complet du fichier .m3u à créer
 * @return le nom complet du fichier
 */
wxString DialogEnregistreM3U::GetChemin()
{
    if (m_liste->GetCurrentSelection() != wxNOT_FOUND)
        return m_chaineM3U.Item(m_liste->GetCurrentSelection());
    else
        return m_rep + wxFileName::GetPathSeparator() + m_boiteNouveau->GetValue() + _T(".m3u");
}

/**
 * Retourne le nom du dossier dans lequel un raccourci doit être placé
 * @return le nom complet du dossier
 */
wxString DialogEnregistreM3U::GetCheminRaccourci()
{
    if (m_boiteRaccourci->IsEmpty() || m_boiteRaccourci->GetValue().StartsWith(m_rep))
        return wxEmptyString;
    else if (!m_boiteNouveau->IsEmpty())
        return m_boiteRaccourci->GetValue() + wxFileName::GetPathSeparator() + m_boiteNouveau->GetValue() + _(" (raccourci).lnk");
    else if (m_liste->GetCurrentSelection() != wxNOT_FOUND)
        return m_boiteRaccourci->GetValue() + wxFileName::GetPathSeparator() + m_chaineM3U.Item(m_liste->GetCurrentSelection()).AfterLast(wxFileName::GetPathSeparator()).BeforeLast('.') + _(" (raccourci).lnk");
    else
        return wxEmptyString;
}

/**
 * Ouvre une fenêtre pour sélectionner un répertoire
 */
void DialogEnregistreM3U::OuvrirDossier(wxCommandEvent &WXUNUSED(event))
{
    int ouvert;

    wxDirDialog navig(this, _("Choisissez le répertoire dans lequel vous voulez créer un raccourci"), m_boiteRaccourci->GetValue());//, wxEmptyString);
    ouvert = navig.ShowModal();

    if (ouvert == wxID_OK)
        m_boiteRaccourci->SetValue(navig.GetPath());
}

//////////////////////////////////////////////////////////////////////////////
/**
 * @class DialogTagMP3
 * @brief Ouvre une boîte de dialogue affichant les propriétés du titre sélectionné
 */

/**
 * Constructeur
 * @param parent la fenêtre parente
 * @param id l'identifiant de l'instance
 * @param chanson le titre
 */
DialogTagMP3::DialogTagMP3(wxWindow *parent, wxWindowID id, wxString chanson) : wxDialog(parent, id, _("Détails"), wxDefaultPosition, wxDefaultSize, wxCAPTION|wxCLOSE_BOX|wxSYSTEM_MENU|wxRESIZE_BORDER)
{
    wxBoxSizer *sizerV = NULL, *sizerH = NULL;
    sizerV = new wxBoxSizer(wxVERTICAL);
    SetSizer(sizerV);
    sizerH = new wxBoxSizer(wxHORIZONTAL);
    sizerV->Add(sizerH, 1, wxALL|wxEXPAND, 5);

    m_image = new ImagePochetteMusique(this, ID_PAGE_PLAYLIST_DETAILS_POCHETTE, wxBitmap(250, 250), false);
    sizerH->Add(m_image, 0, wxALL, 0);

    m_notebook = new wxNotebook(this, -1);
    m_pageInfo = new DialogTagMP3Info(m_notebook, -1, chanson);
    m_commentaires = new wxTextCtrl(m_notebook, -1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    m_notebook->AddPage(m_pageInfo, _("Informations"));
    m_notebook->AddPage(m_commentaires, _("Commentaires"));
    sizerH->Add(m_notebook, 1, wxEXPAND|wxLEFT, 5);

    sizerV->Add(CreateSeparatedButtonSizer(wxOK|wxCANCEL), 0, wxALL|wxALIGN_RIGHT|wxEXPAND, 5);
    sizerV->SetSizeHints(this);
}

/**
 * Associe le titre pour afficher les détails
 * @param chanson le nom complet du titre
 */
void DialogTagMP3::SetChanson(wxString chanson)
{    m_pageInfo->SetChanson(chanson);}

/**
 * Retourne le nom de la chanson
 * @return le nom du fichier
 */
wxString DialogTagMP3::GetNom()
{    return m_pageInfo->GetNom();}

/**
 * Retourne le titre de la chanson - TAG
 * @return le titre
 */
wxString DialogTagMP3::GetTitre()
{    return m_pageInfo->GetTitre();}

/**
 * Retourne l'album de la chanson - TAG
 * @return le nom de l'album
 */
wxString DialogTagMP3::GetAlbum()
{    return m_pageInfo->GetAlbum();}

/**
 * Retourne l'artiste de la chanson - TAG
 * @return le nom de l'artiste
 */
wxString DialogTagMP3::GetArtiste()
{    return m_pageInfo->GetArtiste();}

/**
 * Retourne le genre de la chanson - TAG
 * @return le genre
 */
wxString DialogTagMP3::GetGenre()
{    return m_pageInfo->GetGenre();}

/**
 * Retourne l'année de parution de la chanson - TAG
 * @return l'année de parution
 */
int DialogTagMP3::GetAnnee()
{    return m_pageInfo->GetAnnee();}

/**
 * Retourne les commentaires enregistrés dans la chanson - TAG
 * @return les commentaires
 */
wxString DialogTagMP3::GetCommentaire()
{    return m_commentaires->GetValue();}

/**
 * Modifie le titre affiché dans la boîte Titre
 * @param titre le titre
 */
void DialogTagMP3::SetTitre(wxString titre)
{   m_pageInfo->SetTitre(titre);}

/**
 * Modifie le nom de l'album affiché dans la boîte Album
 * @param album le nom de l'album
 */
void DialogTagMP3::SetAlbum(wxString album)
{   m_pageInfo->SetAlbum(album);}

/**
 * Modifie le nom de l'artiste affiché dans la boîte Artiste
 * @param artiste le nom de l'artiste
 */
void DialogTagMP3::SetArtiste(wxString artiste)
{   m_pageInfo->SetArtiste(artiste);}

/**
 * Modifie le genre affiché dans la boîte Genre
 * @param genre le genre de la chanson
 */
void DialogTagMP3::SetGenre(wxString genre)
{   m_pageInfo->SetGenre(genre);}

/**
 * Modifie le texte affiché dans l'onglet Commentaires
 * @param commentaire les commentaires
 */
void DialogTagMP3::SetCommentaire(wxString commentaire)
{   m_commentaires->SetValue(commentaire);}

/**
 * Modifie l'année affiché dans la boîte Année
 * @param annee l'année de parution de la chanson
 */
void DialogTagMP3::SetAnnee(int annee)
{   m_pageInfo->SetAnnee(annee);}

/**
 * Modifie la durée affiché dans le champs durée
 * @param duree la durée de la chanson
 */
void DialogTagMP3::SetDuree(wxString duree)
{   m_pageInfo->SetDuree(duree);}

/**
 * Modifie le débit affiché dans le champs Débit
 * @param debit le débit de la chanson
 */
void DialogTagMP3::SetDebit(int debit)
{   m_pageInfo->SetDebit(debit);}

/**
 * Modifie la taille affiché dans le champs Taille
 * @param taille la taille de la chanson
 */
void DialogTagMP3::SetTaille(int taille)
{   m_pageInfo->SetTaille(taille);}

/**
 * Indique si un champs textuel a été modifié
 * @return vrai ou faux selon le cas
 */
bool DialogTagMP3::IsModified()
{    return m_pageInfo->IsModified()|m_commentaires->IsModified()|m_image->IsModified();}

/**
 * Retourne l'image contenu dans la chanson
 * @return l'image
 */
ImagePochetteMusique* DialogTagMP3::GetImage()
{    return m_image;}

/**
 * @class DialogTagMP3Info
 * @brief Page affichant les propriétés du titre donné en paramètre
 */

/**
 * Constructeur
 * @param parent la fenêtre parente
 * @param id l'identifiant de la page
 * @param chanson
 */
DialogTagMP3Info::DialogTagMP3Info(wxWindow *parent, wxWindowID id, wxString chanson) : wxPanel(parent, id)
{
    m_annee = 0;
    wxBoxSizer *sizerV = new wxBoxSizer(wxVERTICAL);
    SetSizer(sizerV);
    wxFlexGridSizer *sizerGrid = new wxFlexGridSizer(6, 2, 5, 5);
    sizerV->Add(sizerGrid, 0, wxALL|wxEXPAND, 5);
    sizerGrid->AddGrowableCol(1, 1);
    m_boiteNom = new wxTextCtrl(this, -1, wxEmptyString, wxDefaultPosition, wxSize(200, -1));
    m_boiteArtiste = new wxTextCtrl(this, -1);
    m_boiteAlbum = new wxTextCtrl(this, -1);
    m_boiteTitre = new wxTextCtrl(this, -1);
    m_boiteGenre = new wxTextCtrl(this, -1);
    m_boiteAnnee = new wxSpinCtrl(this, -1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 3000, 0, _("Année de parution"));
    wxStaticText *texte = new wxStaticText[6];
    texte[0].Create(this, -1, _("Nom"));
    texte[1].Create(this, -1, _("Artiste"));
    texte[2].Create(this, -1, _("Album"));
    texte[3].Create(this, -1, _("Titre"));
    texte[4].Create(this, -1, _("Genre"));
    texte[5].Create(this, -1, _("Année"));

    sizerGrid->Add(&texte[0], 0, wxGROW|wxALL, 0);
    sizerGrid->Add(m_boiteNom, 1, wxGROW|wxALL|wxEXPAND, 0);
    sizerGrid->Add(&texte[1], 0, wxGROW|wxALL, 0);
    sizerGrid->Add(m_boiteArtiste, 1, wxGROW|wxALL|wxEXPAND, 0);
    sizerGrid->Add(&texte[2], 0, wxGROW|wxALL, 0);
    sizerGrid->Add(m_boiteAlbum, 1, wxGROW|wxALL|wxEXPAND, 0);
    sizerGrid->Add(&texte[3], 0, wxGROW|wxALL, 0);
    sizerGrid->Add(m_boiteTitre, 1, wxGROW|wxALL|wxEXPAND, 0);
    sizerGrid->Add(&texte[4], 0, wxGROW|wxALL, 0);
    sizerGrid->Add(m_boiteGenre, 1, wxGROW|wxALL|wxEXPAND, 0);
    sizerGrid->Add(&texte[5], 0, wxGROW|wxALL, 0);
    sizerGrid->Add(m_boiteAnnee, 1, wxGROW|wxALL|wxEXPAND, 0);

    m_echantillonage = new wxStaticText(this, -1, _("Débit - inconnu"));
    m_duree = new wxStaticText(this, -1, _("Durée - inconnu"));
    m_taille = new wxStaticText(this, -1, _("Taille - inconnu"));
    sizerV->Add(m_echantillonage, 0, wxALL, 5);
    sizerV->Add(m_duree, 0, wxALL, 5);
    sizerV->Add(m_taille, 0, wxALL, 5);

    SetChanson(chanson);
}

/**
 * Associe le titre pour afficher les détails
 * @param chanson le nom complet du titre
 */
void DialogTagMP3Info::SetChanson(wxString chanson)
{    m_boiteNom->SetValue(chanson.AfterLast(wxFileName::GetPathSeparator()));}

/**
 * Retourne le nom de la chanson
 * @return le nom du fichier
 */
wxString DialogTagMP3Info::GetNom()
{    return m_boiteNom->GetValue();}

/**
 * Retourne le titre de la chanson - TAG
 * @return le titre
 */
wxString DialogTagMP3Info::GetTitre()
{    return m_boiteTitre->GetValue();}

/**
 * Retourne l'album de la chanson - TAG
 * @return le nom de l'album
 */
wxString DialogTagMP3Info::GetAlbum()
{    return m_boiteAlbum->GetValue();}

/**
 * Retourne l'artiste de la chanson - TAG
 * @return le nom de l'artiste
 */
wxString DialogTagMP3Info::GetArtiste()
{    return m_boiteArtiste->GetValue();}

/**
 * Retourne le genre de la chanson - TAG
 * @return le genre
 */
wxString DialogTagMP3Info::GetGenre()
{    return m_boiteGenre->GetValue();}

/**
 * Retourne l'année de parution de la chanson - TAG
 * @return l'année de parution
 */
int DialogTagMP3Info::GetAnnee()
{    return m_boiteAnnee->GetValue();}

/**
 * Modifie le titre affiché dans la boîte Titre
 * @param titre le titre
 */
void DialogTagMP3Info::SetTitre(wxString titre)
{   m_boiteTitre->SetValue(titre);}

/**
 * Modifie le nom de l'album affiché dans la boîte Album
 * @param album le nom de l'album
 */
void DialogTagMP3Info::SetAlbum(wxString album)
{   m_boiteAlbum->SetValue(album);}

/**
 * Modifie le nom de l'artiste affiché dans la boîte Artiste
 * @param artiste le nom de l'artiste
 */
void DialogTagMP3Info::SetArtiste(wxString artiste)
{   m_boiteArtiste->SetValue(artiste);}

/**
 * Modifie le genre affiché dans la boîte Genre
 * @param genre le genre de la chanson
 */
void DialogTagMP3Info::SetGenre(wxString genre)
{   m_boiteGenre->SetValue(genre);}

/**
 * Modifie l'année affiché dans la boîte Année
 * @param annee l'année de parution de la chanson
 */
void DialogTagMP3Info::SetAnnee(int annee)
{
    m_boiteAnnee->SetValue(annee);
    m_annee = annee;
}

/**
 * Modifie la durée affiché dans le champs durée
 * @param duree la durée de la chanson
 */
void DialogTagMP3Info::SetDuree(wxString duree)
{    m_duree->SetLabel(_("Durée - ") + duree);}

/**
 * Modifie le débit affiché dans le champs Débit
 * @param debit le débit de la chanson
 */
void DialogTagMP3Info::SetDebit(int debit)
{
    wxString chaine = _("Débit - ");
    chaine << debit << _(" kbits/s");
    m_echantillonage->SetLabel(chaine);
}

/**
 * Modifie la taille affiché dans le champs Taille
 * @param taille la taille de la chanson
 */
void DialogTagMP3Info::SetTaille(int taille)
{
    wxString chaine = _("Taille - ");
    wxString t;
    t << (float)(taille/1024) /1024 ;
    chaine << t.Truncate(t.First('.') + 3) << _(" Mo") << _T(" (") << taille << _T(" octets)");
    m_taille->SetLabel(chaine);
}

/**
 * Indique si un champs textuel de la page a été modifié
 * @return vrai ou faux selon le cas
 */
bool DialogTagMP3Info::IsModified()
{
    bool annee = false;
    if (m_annee != m_boiteAnnee->GetValue())
        annee = true;
    return  m_boiteNom->IsModified()|m_boiteTitre->IsModified()|m_boiteAlbum->IsModified()|m_boiteArtiste->IsModified()|m_boiteGenre->IsModified()|annee;
}
//////////////////////////////////////////////////////////////////////////////
