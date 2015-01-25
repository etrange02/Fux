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
DialogTagMP3Info::DialogTagMP3Info(wxWindow *parent, wxWindowID id, Music* music) :
    wxPanel(parent, id),
    m_music(music)
{
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

    fillFields();
}

/**
 * Destructeur
 */
DialogTagMP3Info::~DialogTagMP3Info()
{
    delete[] m_texte;
}

void DialogTagMP3Info::fillFields()
{
    m_boiteNom      ->SetValue(m_music->GetName());
    m_boiteArtiste  ->SetValue(m_music->GetArtists());
    m_boiteAlbum    ->SetValue(m_music->GetAlbum());
    m_boiteTitre    ->SetValue(m_music->GetTitle());
    m_boiteGenre    ->SetValue(m_music->GetGenres());
    m_boiteAnnee    ->SetValue(m_music->GetYear());

    fillDuration(m_music->GetStringDuration());
    fillDebit   (m_music->GetDebit());
    fillSize    (m_music->GetSize());
}

/**
 * Modifie la durée affiché dans le champs durée
 * @param duree la durée de la chanson
 */
void DialogTagMP3Info::fillDuration(wxString duree)
{    m_duree->SetLabel(_("Durée - ") + duree);}

/**
 * Modifie le débit affiché dans le champs Débit
 * @param debit le débit de la chanson
 */
void DialogTagMP3Info::fillDebit(const int debit)
{
    wxString chaine = _("Débit - ");
    chaine << debit << _(" kbits/s");
    m_echantillonage->SetLabel(chaine);
}

/**
 * Modifie la taille affiché dans le champs musicSize
 * @param musicSize la taille de la chanson
 */
void DialogTagMP3Info::fillSize(const int musicSize)
{
    wxString chaine = _("Taille - ");
    wxString t;
    t << (float)(musicSize/1024) /1024 ;
    chaine << t.Truncate(t.First('.') + 3) << _(" Mo") << _T(" (") << musicSize << _T(" octets)");
    m_taille->SetLabel(chaine);
}

/**
 * Indique si un champs textuel de la page a été modifié
 * @return vrai ou faux selon le cas
 */
bool DialogTagMP3Info::isModified()
{
    bool isYearModified = false;
    if (m_music->GetYear() != m_boiteAnnee->GetValue())
        isYearModified = true;
    return      m_boiteNom->IsModified()
            ||  m_boiteTitre->IsModified()
            ||  m_boiteAlbum->IsModified()
            ||  m_boiteArtiste->IsModified()
            ||  m_boiteGenre->IsModified()
            ||  isYearModified;
}

void DialogTagMP3Info::toMusic()
{
    m_music->SetName    (m_boiteNom->GetValue());
    m_music->SetArtists (m_boiteArtiste->GetValue());
    m_music->SetAlbum   (m_boiteAlbum->GetValue());
    m_music->SetTitle   (m_boiteTitre->GetValue());
    m_music->SetGenres  (m_boiteGenre->GetValue());
    m_music->SetYear    (m_boiteAnnee->GetValue());
}

