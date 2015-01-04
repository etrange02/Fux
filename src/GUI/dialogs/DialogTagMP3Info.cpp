/***************************************************************
 * Name:      DialogTagMP3Info.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2010-05-29
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "../../../include/gui/dialogs/DialogTagMP3Info.h"

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
    m_texte = new wxStaticText[6];
    m_texte[0].Create(this, -1, _("Nom"));
    m_texte[1].Create(this, -1, _("Artiste"));
    m_texte[2].Create(this, -1, _("Album"));
    m_texte[3].Create(this, -1, _("Titre"));
    m_texte[4].Create(this, -1, _("Genre"));
    m_texte[5].Create(this, -1, _("Année"));

    sizerGrid->Add(&m_texte[0], 0, wxGROW|wxALL, 0);
    sizerGrid->Add(m_boiteNom, 1, wxGROW|wxALL|wxEXPAND, 0);
    sizerGrid->Add(&m_texte[1], 0, wxGROW|wxALL, 0);
    sizerGrid->Add(m_boiteArtiste, 1, wxGROW|wxALL|wxEXPAND, 0);
    sizerGrid->Add(&m_texte[2], 0, wxGROW|wxALL, 0);
    sizerGrid->Add(m_boiteAlbum, 1, wxGROW|wxALL|wxEXPAND, 0);
    sizerGrid->Add(&m_texte[3], 0, wxGROW|wxALL, 0);
    sizerGrid->Add(m_boiteTitre, 1, wxGROW|wxALL|wxEXPAND, 0);
    sizerGrid->Add(&m_texte[4], 0, wxGROW|wxALL, 0);
    sizerGrid->Add(m_boiteGenre, 1, wxGROW|wxALL|wxEXPAND, 0);
    sizerGrid->Add(&m_texte[5], 0, wxGROW|wxALL, 0);
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
 * Destructeur
 */
DialogTagMP3Info::~DialogTagMP3Info()
{
    delete[] m_texte;
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

