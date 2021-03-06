/***************************************************************
 * Name:      DialogEnregistreM3U.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2010-05-29
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
 #include "gui/dialogs/DialogEnregistreM3U.h"

static wxPanel *s_panelToBeCall = NULL;
const wxEventType wxEVT_PREFERENCE_MAJ_M3U = wxNewEventType();

/**
 * @class DialogEnregistreM3U
 * @brief Ouvre une bo�te de dialogue permettant de choisir le nom du fichiers .m3u � cr�er et �ventuellement le raccourci.
 */
BEGIN_EVENT_TABLE(DialogEnregistreM3U, wxDialog)
    EVT_BUTTON(ID_DIALOGUE_SAUVEGARDE_M3U, DialogEnregistreM3U::OuvrirDossier)
END_EVENT_TABLE()

/**
 * Constructeur
 * @param parent la fen�tre parente
 * @param id l'identifiant de l'instance
 * @param racc le r�pertoire o� doit �tre cr�� un raccourci
 */
 DialogEnregistreM3U::DialogEnregistreM3U(wxWindow *parent, wxWindowID id, wxString racc) :
     wxDialog(parent, id, _("Cr�ation de playlist (fichier .m3u)"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER),
     m_chemin(wxEmptyString),
     m_raccourci(racc),
     m_rep(Parametre::Get()->getRepertoireParametre(_T("Play_list_M3U")))
{
    Centre();
}

/**
 * Destructeur
 */
DialogEnregistreM3U::~DialogEnregistreM3U()
{
    delete[] m_text;
}

/**
 * Cr�e les �l�ments graphiques de la fen�tre
 */
void DialogEnregistreM3U::Creer()
{
    wxBoxSizer *sizerV = new wxBoxSizer(wxVERTICAL);
    SetSizer(sizerV);

    m_text = new wxStaticText[3];
    m_text[0].Create(this, wxID_ANY, _("Choisissez une sauvegarde existante"));
    sizerV->Add(&m_text[0], 0, wxALL, 5);
    m_liste = new wxChoice(this, wxID_ANY);
    sizerV->Add(m_liste, 0, wxLEFT|wxRIGHT|wxDOWN|wxEXPAND, 5);

    m_text[1].Create(this, wxID_ANY, _("Ou bien cr�ez une nouvelle sauvegarde"));
    sizerV->Add(&m_text[1], 0, wxALL, 5);
    m_boiteNouveau = new wxTextCtrl(this, wxID_ANY, _T(""));
    sizerV->Add(m_boiteNouveau, 0, wxLEFT|wxRIGHT|wxDOWN|wxEXPAND, 5);

    sizerV->Add(new wxStaticLine(this), 0, wxUP|wxLEFT|wxRIGHT|wxEXPAND, 15);

    m_text[2].Create(this, wxID_ANY, _("Cr�er un raccourci ? O� le place-t-on ?"));
    sizerV->Add(&m_text[2], 0, wxALL, 5);

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
 * Cr�e une liste de tous les fichiers .m3u pr�sents dans le dossier des param�tres
 */
void DialogEnregistreM3U::CreerListeM3U()
{
    wxString dossierM3U = m_rep;

    if (!wxDir::Exists(dossierM3U))
        return;

    wxDir::GetAllFiles(dossierM3U, &m_chaineM3U, _T("*.m3u"));

    for (size_t i=0; i<m_chaineM3U.GetCount(); i++)
        m_liste->Append(m_chaineM3U.Item(i).AfterLast(wxFileName::GetPathSeparator()));
}

/**
 * Retourne le nom complet du fichier .m3u � cr�er
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
 * Retourne le nom du dossier dans lequel un raccourci doit �tre plac�
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
 * Ouvre une fen�tre pour s�lectionner un r�pertoire
 */
void DialogEnregistreM3U::OuvrirDossier(wxCommandEvent &WXUNUSED(event))
{
    int ouvert;

    wxDirDialog navig(this, _("Choisissez le r�pertoire dans lequel vous voulez cr�er un raccourci"), m_boiteRaccourci->GetValue());//, wxEmptyString);
    ouvert = navig.ShowModal();

    if (ouvert == wxID_OK)
        m_boiteRaccourci->SetValue(navig.GetPath());
}

/**
 * Associe un panel qui doit recevoir un �v�nement lors d'une modification
 * @param Panel un panel qui doit recevoir les �v�nements
 */
void DialogEnregistreM3U::SetPanelToBeCall(wxPanel* Panel)
{
    s_panelToBeCall = Panel;
}

/**
 * Informe le panel de la mise � jour
 * @see DialogEnregistreM3U::SetPanelToBeCall
 */
void DialogEnregistreM3U::CallPanel()
{
    if (s_panelToBeCall)
    {
        wxCommandEvent evt(wxEVT_PREFERENCE_MAJ_M3U, wxID_ANY);
        s_panelToBeCall->GetEventHandler()->AddPendingEvent(evt);
    }
}

