/***************************************************************
 * Name:      DialogTagMP3.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2010-05-29
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "gui/dialogs/DialogTagMP3.h"
#include "music/Factory.h"

using namespace ::music;

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
DialogTagMP3::DialogTagMP3(wxWindow *parent, const wxWindowID id, const Music& music) :
    wxDialog(parent, id, _("Détails"), wxDefaultPosition, wxDefaultSize, wxCAPTION|wxCLOSE_BOX|wxSYSTEM_MENU|wxRESIZE_BORDER)
{
    m_music = Factory::createMusic(music);
    initialize();
}

DialogTagMP3::~DialogTagMP3()
{
    delete m_music;
}

void DialogTagMP3::initialize()
{
    wxBoxSizer *sizerV = NULL, *sizerH = NULL;
    sizerV = new wxBoxSizer(wxVERTICAL);
    SetSizer(sizerV);
    sizerH = new wxBoxSizer(wxHORIZONTAL);
    sizerV->Add(sizerH, 1, wxALL|wxEXPAND, 5);

    m_image = new ImagePochetteMusique(this, ID_PAGE_PLAYLIST_DETAILS_POCHETTE, 250, 250, false);
    if (m_music->GetRecordSleeve())
    {
        m_image->SetImage(*m_music->GetRecordSleeve());
        m_image->AfficheImage(true);
    }
    sizerH->Add(m_image, 0, wxALL, 0);

    m_notebook = new wxNotebook(this, -1);
    m_pageInfo = new DialogTagMP3Info(m_notebook, -1, m_music);
    m_comment = new wxTextCtrl(m_notebook, -1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    m_notebook->AddPage(m_pageInfo, _("Informations"));
    m_notebook->AddPage(m_comment, _("Commentaires"));
    sizerH->Add(m_notebook, 1, wxEXPAND|wxLEFT, 5);

    sizerV->Add(CreateSeparatedButtonSizer(wxOK|wxCANCEL), 0, wxALL|wxALIGN_RIGHT|wxEXPAND, 5);
    sizerV->SetSizeHints(this);
}

/**
 * Indique si un champs textuel a été modifié
 * @return vrai ou faux selon le cas
 */
bool DialogTagMP3::isModified()
{
    return m_pageInfo->isModified() || m_comment->IsModified() || m_image->IsModified();
}

wxString& DialogTagMP3::getComment() const
{
    m_comment->GetValue();
}

Music* DialogTagMP3::getResult()
{
    m_pageInfo->toMusic();
    Music* music = m_music;
    m_music = NULL;
    return music;
}

