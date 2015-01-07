/***************************************************************
 * Name:      DialogTagMP3.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2010-05-29
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "../../../include/gui/dialogs/DialogTagMP3.h"

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
void DialogTagMP3::SetDuration(wxString duree)
{   m_pageInfo->SetDuration(duree);}

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
