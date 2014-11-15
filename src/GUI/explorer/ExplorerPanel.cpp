#include "../../../include/gui/explorer/ExplorerPanel.h"

ExplorerPanel::ExplorerPanel(wxWindow* parent, wxWindowID id, wxWindowID idExplorerList, wxWindowID idPreviousButton, wxWindowID idRefreshButton, wxWindowID idTextField, wxWindowID idCheckBox, wxString& managerName, wxString& managerDescription)
{
    Create(parent, id, idExplorerList, idPreviousButton, idRefreshButton, idTextField, idCheckBox, managerName, managerDescription);
    m_explorerManager = NULL;
}

ExplorerPanel::~ExplorerPanel()
{
    //dtor
}

void ExplorerPanel::Create(wxWindow* parent, wxWindowID id, wxWindowID idExplorerList, wxWindowID idPreviousButton, wxWindowID idRefreshButton, wxWindowID idTextField, wxWindowID idCheckBox, wxString& managerName, wxString& managerDescription)
{
    wxPanel::Create(parent, id);

    m_managerName = managerName;
    m_managerDescription = managerDescription;

    m_previousButton = new wxButton(this, idPreviousButton, _T("<"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    m_pathTextCtrl = new wxTextCtrl(this, idTextField, m_managerDescription, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    m_refreshButton = new wxButton(this, idRefreshButton, _T("?"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    m_hiddenFilesCheckBox = new wxCheckBox(this, idCheckBox, _("Fichiers cachés"));
    m_filterCheckBox = new wxCheckBox(this, idCheckBox, _("Filtrer"));
    m_filterCheckBox->SetValue(true);
    m_explorerList = new ExplorerListCtrl(this, idExplorerList);

    m_previousButton->SetToolTip(_("Aller au dossier précédent"));
    m_refreshButton->SetToolTip(_("Actualiser"));
    m_hiddenFilesCheckBox->SetToolTip(_("Afficher les fichiers cachés"));
    m_filterCheckBox->SetToolTip(_("Afficher uniquement les fichiers que Fu(X) peut lire"));

    m_sizer1V = new wxStaticBoxSizer(wxVERTICAL, this, m_managerName);
    SetSizer(m_sizer1V);
    m_sizer1H = new wxBoxSizer(wxHORIZONTAL);
    m_sizer1V->Add(m_sizer1H, 0, wxALL|wxEXPAND, 5);
    m_sizer1H->Add(m_previousButton, 0, wxALL, 0);
    m_sizer1H->Add(m_pathTextCtrl, 1, wxALL|wxEXPAND, 0);
    m_sizer1H->Add(m_refreshButton, 0, wxALL, 0);

    m_sizer2H = new wxBoxSizer(wxHORIZONTAL);
    m_sizer1V->Add(m_sizer2H, 0, wxLEFT|wxRIGHT|wxEXPAND, 5);
    m_sizer2H->Add(m_hiddenFilesCheckBox, 0, wxALL|wxEXPAND, 0);
    m_sizer2H->Add(m_filterCheckBox, 0, wxLEFT|wxEXPAND, 5);
    m_sizer1V->Add(m_explorerList, 1, wxALL|wxEXPAND, 5);

//    Connect(idListe, wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxCommandEventHandler(PageGestionPeriph::OuvrirDossierSuivant));
//    Connect(idListe, wxEVT_COMMAND_LIST_BEGIN_DRAG, wxCommandEventHandler(PageGestionPeriph::Glisser));
//    Connect(-1, wxEVT_LISTE_PERIPH_CLAVIER, wxKeyEventHandler(PageGestionPeriph::OnKey));
//    Connect(-1, wxEVT_LISTE_PERIPH_SOURIS, wxCommandEventHandler(PageGestionPeriph::OnMenu));
//    Connect(idBoutonPrec, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(PageGestionPeriph::OuvrirDossierPrecedent));
//    Connect(idBoutonReset, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(PageGestionPeriph::RechargerE));
//    Connect(idCheckBox, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(PageGestionPeriph::RechargerE));
}

void ExplorerPanel::SetExplorerManager(ExplorerManager* explorerManager)
{
    m_explorerManager = explorerManager;
}
