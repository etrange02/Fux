/***************************************************************
 * Name:      GestionPeriphMoitiePage.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2010-09-08
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "../../../include/gui/explorer/GestionPeriphMoitiePage.h"
#include "MusicManagerSwitcher.h"

/**
 * @class PageGestionPeriph
 * @brief Interface graphique permettant un d�placement dans l'arborescence des fichiers.
 */

BEGIN_EVENT_TABLE(PageGestionPeriph, wxPanel)
END_EVENT_TABLE()

/**
 * Constructeur
 * @param Parent la fen�tre parente
 * @param id l'identifiant de la fen�tre parente
 */
PageGestionPeriph::PageGestionPeriph(wxWindow *Parent, wxWindowID id) : wxPanel(Parent, id)
{
    wxWindowID idListe, idBoutonPrec, idBoutonReset, idChampTexte, idCheckBox;
    wxString chaine, navig;
    m_chemin = wxEmptyString;
    m_dragging = false;

    if (id == ID_PAGE_PERIHERIQUE_GAUCHE)
    {
        idListe = ID_PAGE_PERIHERIQUE_LISTE_G;
        idBoutonPrec = ID_PAGE_PERIHERIQUE_BOUTON_PRECEDENT_G;
        idBoutonReset = ID_PAGE_PERIHERIQUE_BOUTON_RECHARGE_G;
        idChampTexte = ID_PAGE_PERIHERIQUE_TEXTE_G;
        idCheckBox = ID_PAGE_PERIHERIQUE_CHECKBOX_CACHE_G;
        m_navigDef = _("Navig gauche");
        m_texteDef = _("Navigation gauche : Fu(X) toujours en d�veloppement");
    }
    else
    {
        idListe = ID_PAGE_PERIHERIQUE_LISTE_D;
        idBoutonPrec = ID_PAGE_PERIHERIQUE_BOUTON_PRECEDENT_D;
        idBoutonReset = ID_PAGE_PERIHERIQUE_BOUTON_RECHARGE_D;
        idChampTexte = ID_PAGE_PERIHERIQUE_TEXTE_D;
        idCheckBox = ID_PAGE_PERIHERIQUE_CHECKBOX_CACHE_D;
        m_navigDef = _("Navig droite");
        m_texteDef = _("Navigation droite : donc toujours plus loin !");
    }

    m_boutonPrecedent = new wxButton(this, idBoutonPrec, _T("<"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    m_text = new wxTextCtrl(this, idChampTexte, m_texteDef, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    m_boutonRecharge = new wxButton(this, idBoutonReset, _T("?"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    m_checkBoxCache = new wxCheckBox(this, idCheckBox, _("Fichiers cach�s"));
    m_checkBoxFiltre = new wxCheckBox(this, idCheckBox, _("Filtrer"));
    m_checkBoxFiltre->SetValue(true);
    m_liste = new ListeGestionPeriph(this, idListe);

    m_boutonPrecedent->SetToolTip(_("Aller au dossier pr�c�dent"));
    m_boutonRecharge->SetToolTip(_("Actualiser"));
    m_checkBoxCache->SetToolTip(_("Afficher les fichiers cach�s"));
    m_checkBoxFiltre->SetToolTip(_("Afficher uniquement les fichiers que Fu(X) peut lire"));

    m_sizer1V = new wxStaticBoxSizer(wxVERTICAL, this, m_navigDef);
    SetSizer(m_sizer1V);
    m_sizer1H = new wxBoxSizer(wxHORIZONTAL);
    m_sizer1V->Add(m_sizer1H, 0, wxALL|wxEXPAND, 5);
    m_sizer1H->Add(m_boutonPrecedent, 0, wxALL, 0);
    m_sizer1H->Add(m_text, 1, wxALL|wxEXPAND, 0);
    m_sizer1H->Add(m_boutonRecharge, 0, wxALL, 0);

    m_sizer2H = new wxBoxSizer(wxHORIZONTAL);
    m_sizer1V->Add(m_sizer2H, 0, wxLEFT|wxRIGHT|wxEXPAND, 5);
    m_sizer2H->Add(m_checkBoxCache, 0, wxALL|wxEXPAND, 0);
    m_sizer2H->Add(m_checkBoxFiltre, 0, wxLEFT|wxEXPAND, 5);
    m_sizer1V->Add(m_liste, 1, wxALL|wxEXPAND, 5);


    Connect(idListe, wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxCommandEventHandler(PageGestionPeriph::OuvrirDossierSuivant));
    Connect(idListe, wxEVT_COMMAND_LIST_BEGIN_DRAG, wxCommandEventHandler(PageGestionPeriph::Glisser));
    Connect(-1, wxEVT_LISTE_PERIPH_CLAVIER, wxKeyEventHandler(PageGestionPeriph::OnKey));
    Connect(-1, wxEVT_LISTE_PERIPH_SOURIS, wxCommandEventHandler(PageGestionPeriph::OnMenu));
    Connect(idBoutonPrec, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(PageGestionPeriph::OuvrirDossierPrecedent));
    Connect(idBoutonReset, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(PageGestionPeriph::RechargerE));
    Connect(idCheckBox, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(PageGestionPeriph::RechargerE));
}

/**
 * Destructeur
 */
PageGestionPeriph::~PageGestionPeriph()
{}

/**
 * Associe cette instance avec sa "jumelle". Ce jumelage permet une interaction entre entre les deux instances : glisser-d�poser, copier-coller
 * @param page l'instance de l'autre page
 */
void PageGestionPeriph::SetPageParallele(PageGestionPeriph *page)
{    m_pageParallele = page;}

/**
 * Affiche � l'�cran le contenu de l'entit� se trouvant � l'adresse <i>chemin</i>
 * @param chemin adresse de l'entit�
 * @param objet la nature de l'entit� : dossier, fichier m3u ou playlist
 * @param activeLigne si vrai, la vue sera active
 */
void PageGestionPeriph::SetFichierDossier(wxString chemin, int objet, bool activeLigne)
{
    m_chemin = chemin;

    if (objet == DOSSIER)
    {
        if (m_liste->AfficheContenuDossier(m_chemin, m_checkBoxCache->IsChecked(), m_checkBoxFiltre->IsChecked()))
        {
            m_liste->SetEtat(DOSSIER);
            if (GetId() == ID_PAGE_PERIHERIQUE_GAUCHE)
                m_sizer1V->GetStaticBox()->SetLabel(_("Navig gauche : Dossier"));
            else
                m_sizer1V->GetStaticBox()->SetLabel(_("Navig droite : Dossier"));
            m_text->SetValue(chemin);
            if (m_liste->GetItemCount() != 0 && activeLigne)
                m_liste->SetItemState(0, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED);
        }
    }
    else if (objet == PLAYLIST)
    {
        if (m_liste->AfficheContenuFichier(m_chemin, 0))
        {
            m_liste->SetEtat(PLAYLIST);
            if (GetId() == ID_PAGE_PERIHERIQUE_GAUCHE)
                m_sizer1V->GetStaticBox()->SetLabel(_("Navig gauche : Liste de lecture"));
            else
                m_sizer1V->GetStaticBox()->SetLabel(_("Navig droite : Liste de lecture"));
            m_text->SetValue(chemin);
            if (m_liste->GetItemCount() != 0 && activeLigne)
                m_liste->SetItemState(0, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED);
        }
    }
    else if (objet == M3U)
    {
        if (m_liste->AfficheContenuFichier(m_chemin, 1))
        {
            m_liste->SetEtat(M3U);
            if (GetId() == ID_PAGE_PERIHERIQUE_GAUCHE)
                m_sizer1V->GetStaticBox()->SetLabel(_("Navig gauche : M3U"));
            else
                m_sizer1V->GetStaticBox()->SetLabel(_("Navig droite : M3U"));
            m_text->SetValue(chemin);
            if (m_liste->GetItemCount() != 0 && activeLigne)
                m_liste->SetItemState(0, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED);
        }
    }
}

/**
 * Retourne le type de l'entit� qui est actuellement affich�
 * @return le type
 * @see PageGestionPeriph::SetFichierDossier
 */
int PageGestionPeriph::GetEtat()
{    return m_liste->GetEtat();}

/**
 * Retourne le chemin dont le contenu est affich�
 * @return le chemin
 */
wxString PageGestionPeriph::GetChemin()
{    return m_chemin;}

////////////////�v�nements
/**
 * �v�nement - Double clic sur un �l�ment
 */
void PageGestionPeriph::OuvrirDossierSuivant(wxCommandEvent &WXUNUSED(event))
{
    wxString nouveauDossier = m_chemin;
    nouveauDossier << wxFileName::GetPathSeparator() << m_liste->GetItemText(m_liste->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED));
    if (wxDirExists(nouveauDossier) && m_liste->GetEtat() == DOSSIER)
        SetFichierDossier(nouveauDossier, DOSSIER, true);
    else if (wxFileExists(nouveauDossier) && nouveauDossier.Lower().EndsWith(_T(".m3u")) && m_liste->GetEtat() == DOSSIER)
        SetFichierDossier(nouveauDossier, M3U, true);
    else if (wxFileExists(nouveauDossier) && Parametre::Get()->islisable(nouveauDossier.AfterLast('.').Lower()) && m_liste->GetEtat() == DOSSIER)
    {
        wxArrayString *tableau = GetDossierLigneSelection();
        MusicManagerSwitcher::get().parse(*tableau, true);
        MusicManagerSwitcher::get().playMusic(tableau->Item(0));
        delete tableau;
    }
    else if (m_liste->GetEtat() == PLAYLIST)
        MusicManagerSwitcher::get().playMusicAt(m_liste->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED));
    else if (m_liste->GetEtat() == M3U)
    {
        wxArrayString *tableau = GetFichierLigneSelection();
        MusicManagerSwitcher::get().parse(*tableau, true);
        MusicManagerSwitcher::get().playMusic(tableau->Item(0));
        delete tableau;
    }
}

/**
 * �v�nement - Clic sur le bouton pr�c�dent
 * @see PageGestionPeriph::OuvrirDossierPrec
 */
void PageGestionPeriph::OuvrirDossierPrecedent(wxCommandEvent &WXUNUSED(event))
{   OuvrirDossierPrec();}

/**
 * Remonte d'un cran dans la hi�rarchie des dossiers.
 *Si l'on �tait dans le r�pertoire racine, affiche une page blanche
 */
void PageGestionPeriph::OuvrirDossierPrec()
{
    if (m_liste->GetEtat() == VIDE)
        return;

    wxString nouveauDossier = m_chemin;
    if (wxDirExists(nouveauDossier.BeforeLast(wxFileName::GetPathSeparator())))
    {
        SetFichierDossier(nouveauDossier.BeforeLast(wxFileName::GetPathSeparator()), DOSSIER);
        long ligneActive = m_liste->FindItem(-1, nouveauDossier.AfterLast(wxFileName::GetPathSeparator()));
        if (ligneActive == wxNOT_FOUND)
            ligneActive = 0;
        if (m_liste->GetItemCount() != 0)
        {
            m_liste->SetItemState(ligneActive, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED);
            m_liste->EnsureVisible(ligneActive);
        }
    }
    else
    {
        m_liste->VideListe();
        m_liste->SetEtat(VIDE);
        m_chemin = wxEmptyString;
        m_text->SetValue(m_texteDef);
        m_sizer1V->GetStaticBox()->SetLabel(m_navigDef);
    }
}

/**
 * �v�nement - Clic sur le bouton recharger
 */
void PageGestionPeriph::RechargerE(wxCommandEvent &WXUNUSED(event))
{    Recharger();}

/**
 * �v�nement clavier - affiche le menu, couper-copier-coller, supprimer
 */
void PageGestionPeriph::OnKey(wxKeyEvent &event)
{
    if (event.GetKeyCode() == WXK_DELETE)
        Suppression();
    else if (event.GetKeyCode() == WXK_RIGHT)
    {
        if (GetId() == ID_PAGE_PERIHERIQUE_GAUCHE)
            Deplace();
    }
    else if (event.GetKeyCode() == WXK_LEFT)
    {
        if (event.AltDown())
            OuvrirDossierPrec();
        else if (GetId() == ID_PAGE_PERIHERIQUE_DROITE)
            Deplace();
    }
    else if ((event.GetKeyCode() == WXK_F5) || (event.GetKeyCode() == 'R' && event.ControlDown()))
        Recharger();
    else if (event.GetKeyCode() == 'X' && event.ControlDown())
        MenuCouper();
    else if (event.GetKeyCode() == 'C' && event.ControlDown())
        MenuCopier();
    else if (event.GetKeyCode() == 'V' && event.ControlDown())
        MenuColler();
    else if (event.GetKeyCode() == WXK_F2)
        Copie();
    else
        event.Skip();
}

/**
 * �v�nement menu
 */
void PageGestionPeriph::OnMenu(wxCommandEvent &event)
{
    switch (event.GetId())
    {
        case ID_PAGE_PERIHERIQUE_MENU_CREER_DOSSIER :
            MenuCreerDossier();
            break;
        case ID_PAGE_PERIHERIQUE_MENU_CREER_M3U :
            MenuCreerM3U();
            break;
        case ID_PAGE_PERIHERIQUE_MENU_COUPER :
            MenuCouper();
            break;
        case ID_PAGE_PERIHERIQUE_MENU_COPIER :
            MenuCopier();
            break;
        case ID_PAGE_PERIHERIQUE_MENU_COLLER :
            MenuColler();
            break;
        case ID_PAGE_PERIHERIQUE_MENU_RACCOURCI :
            MenuRaccourci();
            break;
        case ID_PAGE_PERIHERIQUE_MENU_RENOMMER :
            MenuRenommer();
            break;
        case ID_PAGE_PERIHERIQUE_MENU_SUPPRIMER :
            MenuSuprimer();
            break;
        case ID_PAGE_PERIHERIQUE_MENU_LIRE :
            MenuLire();
            break;
    }
    //wxLogWarning("C�t� %s", (GetId() == ID_PAGE_PERIHERIQUE_GAUCHE) ? "gauche" : "droit");
}

////////////////Manipulation
/**
 * Provoque un rechargement du contenu de la liste
 */
void PageGestionPeriph::Recharger()
{
    if (m_liste->GetEtat() == VIDE)
        return;
    long ligneActive = 0;
    wxString extrait;

    if (m_liste->GetEtat() == DOSSIER && wxDirExists(m_chemin))
    {
        if (m_liste->GetItemCount() != 0 && m_liste->GetSelectedItemCount())
            extrait = m_liste->GetItemText(m_liste->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED));
        SetFichierDossier(m_chemin, DOSSIER);

        if (m_liste->GetItemCount() != 0)
        {
            if (!extrait.IsEmpty())
                ligneActive = m_liste->FindItem(-1, extrait);
            if (ligneActive == wxNOT_FOUND)
                ligneActive = 0;
            m_liste->SetItemState(ligneActive, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED);
            m_liste->EnsureVisible(ligneActive);
        }
    }
    else if ((m_liste->GetEtat() == PLAYLIST || m_liste->GetEtat() == M3U) && wxFileExists(m_chemin))
    {
        if (m_liste->GetItemCount() != 0 && m_liste->GetSelectedItemCount())
            extrait = m_liste->GetItemText(m_liste->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED));
        SetFichierDossier(m_chemin, m_liste->GetEtat());

        if (m_liste->GetItemCount() != 0)
        {
            if (!extrait.IsEmpty())
                ligneActive = m_liste->FindItem(-1, extrait);
            if (ligneActive == wxNOT_FOUND)
                ligneActive = 0;
            m_liste->SetItemState(ligneActive, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED);
            m_liste->EnsureVisible(ligneActive);
        }
    }
    else
    {
        m_liste->DeleteAllItems();
        m_liste->SetEtat(VIDE);
        m_chemin = wxEmptyString;
        m_text->SetValue(m_texteDef);
        m_sizer1V->GetStaticBox()->SetLabel(m_navigDef);
    }
}

/**
 * Supprime un dossier, fichier, ou ligne d'un fichier
 */
void PageGestionPeriph::Suppression()
{
    if (m_liste->GetEtat() == VIDE)
        return;
    long position = m_liste->GetItemCount() ? m_liste->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED) : 0;

    switch (m_liste->GetEtat())
    {
        case M3U : SuppressionDansFichierLigneM3u(); break;
        case PLAYLIST : SuppressionDansFichierLignePlaylist(); break;
        case DOSSIER : SuppressionDansDossier(); break;
    }

    if (m_liste->GetItemCount() > position)//Toujours avoir une ligne active
        m_liste->SetItemState(position, wxLIST_STATE_FOCUSED|wxLIST_STATE_SELECTED, wxLIST_STATE_FOCUSED|wxLIST_STATE_SELECTED);
    else if (m_liste->GetItemCount() >= 1)
        m_liste->SetItemState(position-1, wxLIST_STATE_FOCUSED|wxLIST_STATE_SELECTED, wxLIST_STATE_FOCUSED|wxLIST_STATE_SELECTED);
}

/**
 * Provoque la recopie des lignes actives dans l'autre liste. Dossier � Dossier et Fichier � Fichier
 */
void PageGestionPeriph::Copie()
{
    if ((m_liste->GetEtat() == M3U || m_liste->GetEtat() == PLAYLIST) && (m_pageParallele->GetEtat() == M3U || m_pageParallele->GetEtat() == PLAYLIST))
        CopieDansFichier();
    else if (m_liste->GetEtat() == DOSSIER && m_pageParallele->GetEtat() == DOSSIER)
        CopieDansDossier();
}

/**
 * Transfert en fonction de la nature des donn�es dans l'autre liste en fonction de la nature de celle-ci. Ce peut-�tre un d�placement ou une copie
 */
void PageGestionPeriph::Deplace()
{
    if ((m_liste->GetEtat() == M3U || m_liste->GetEtat() == PLAYLIST) && (m_pageParallele->GetEtat() == M3U || m_pageParallele->GetEtat() == PLAYLIST))
        DeplaceDansFichierLigne();
    else if (m_liste->GetEtat() == DOSSIER && (m_pageParallele->GetEtat() == M3U || m_pageParallele->GetEtat() == PLAYLIST))
        CopieDossierDansFichier();
    else if (m_liste->GetEtat() == DOSSIER && m_pageParallele->GetEtat() == DOSSIER)
        DeplaceDansDossier();
}

/**
 * Retourne un tableau contenant la s�lection faite dans un fichier
 * @return le tableau de caract�res
 * @see PageGestionPeriph::GetFichierLigneSelectionInt
 */
wxArrayString* PageGestionPeriph::GetFichierLigneSelection()
{
    wxTextFile fichier;
    if (!fichier.Open(m_text->GetValue()))
        return NULL;

    wxArrayString *tableau = new wxArrayString;
    long position = -1;

    int dec = 0, i = 0, max = m_liste->GetSelectedItemCount();
    if (m_liste->GetEtat() == M3U)
        dec = 1;
    tableau->Alloc(max);

    while (i < max)
    {
        position = m_liste->GetNextItem(position,wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
        tableau->Add(fichier.GetLine(position+dec));
        i++;
    }

    fichier.Close();
    return tableau;
}

/**
 * Retourne un tableau contenant la s�lection faite dans un fichier. Tableau de nombre.
 * @return le tableau de nombres (sous forme de texte)
 * @see GetFichierLigneSelection
 */
wxArrayString* PageGestionPeriph::GetFichierLigneSelectionInt()
{
    wxTextFile fichier;
    if (!fichier.Open(m_text->GetValue()))
        return NULL;

    wxArrayString *tableau = new wxArrayString;
    long position = -1;

    int dec = 0, i = 0, max = m_liste->GetSelectedItemCount();
    if (m_liste->GetEtat() == M3U)
        dec = 1;
    tableau->Alloc(max);

    while (i < max)
    {
        position = m_liste->GetNextItem(position,wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
        tableau->Add(wxString::Format(_T("%ld"), position+dec));
        i++;
    }

    fichier.Close();
    return tableau;
}

/**
 * Retourne un tableau contenant la s�lection faite dans un dossier.
 * @return le tableau de caract�res
 */
wxArrayString* PageGestionPeriph::GetDossierLigneSelection()
{
    wxArrayString *tableau = new wxArrayString;
    long position = -1;
    int i = 0, max = m_liste->GetSelectedItemCount();
    tableau->Alloc(max);

    while (i < max)
    {
        position = m_liste->GetNextItem(position,wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
        //if (Parametre::Get()->islisable(m_liste->GetItemText(position).AfterLast('.')))
            tableau->Add(m_chemin + wxFileName::GetPathSeparator() + m_liste->GetItemText(position));
        i++;
    }

    return tableau;
}

////////////////Fichier
/**
 * Incorpore dans un fichier le contenu d'un tableau. Les lignes sont ajout�es � la fin du fichier
 * @param tableau tableau de caract�res
 */
void PageGestionPeriph::AjoutDansFichierLigne(wxArrayString *tableau)
{
    if (tableau == NULL)
        return;
    wxString chem = m_text->GetValue();
/////////////// M3U -> M3U
    if (m_liste->GetEtat() == M3U)
    {
        wxTextFile fichier;
        if (!fichier.Open(m_text->GetValue()))
            return;
        size_t max = tableau->GetCount();
        for (size_t i = 0; i < max; i++)
        {
            if (wxFileExists(tableau->Item(i)))
                fichier.AddLine(tableau->Item(i));
            else
                wxLogMessage(_("Fichier introuvable : ") + tableau->Item(i));
        }
        fichier.Write();
        fichier.Close();
    }
//////////////// M3U -> Liste de lecture
    else if (m_liste->GetEtat() == PLAYLIST)
    {
        MusicManagerSwitcher::get().parse(*tableau, true);
        return;
    }

    if (m_chemin.IsSameAs(chem))
        Recharger();
}

/**
 * Supprime les lignes s�lectionn�es dans le fichier correspondant. Fichier M3U
 * @return vrai si r�ussite, faux sinon
 */
bool PageGestionPeriph::SuppressionDansFichierLigneM3u()
{
    wxTextFile fichier;
    if (!fichier.Open(m_text->GetValue()))
        return false;

    long position = 0;

    while (m_liste->GetSelectedItemCount())
    {
        position = m_liste->GetNextItem(-1,wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
        fichier.RemoveLine(position + 1);
        m_liste->DeleteItem(position);
    }
    fichier.Write();
    fichier.Close();
    return true;
}

/**
 * Supprime les lignes s�lectionn�es dans la playlist
 * @return vrai si r�ussite, faux sinon
 */
bool PageGestionPeriph::SuppressionDansFichierLignePlaylist()
{
    wxTextFile fichier;
    if (!fichier.Open(m_text->GetValue()))
        return false;

    wxArrayString tableau;
    long position = 0;
    int i = 0, max = m_liste->GetSelectedItemCount();
    tableau.Alloc(max);

    while (i < max)
    {
        position = m_liste->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
        tableau.Add(fichier.GetLine(position+i));
        m_liste->DeleteItem(position);
        i++;
    }

    fichier.Close();
    MusicManagerSwitcher::get().deleteTitles(tableau, true);
    return true;
}

/**
 * FICHIER - D�place les lignes s�lectionn�es de la page parall�le dans cette page
 */
void PageGestionPeriph::DeplaceDansFichierLigne()
{
    wxArrayString *tableau = GetFichierLigneSelection();
    m_pageParallele->AjoutDansFichierLigne(tableau);
    Suppression();
    tableau->Clear();
    delete tableau;
}

/**
 * FICHIER - Copie les lignes s�lectionn�es de la page parall�le dans cette page
 */
void PageGestionPeriph::CopieDansFichier()
{
    wxArrayString *tableau = GetFichierLigneSelection();
    m_pageParallele->AjoutDansFichierLigne(tableau);
    tableau->Clear();
    delete tableau;
}

/**
 * DOSSIER -> FICHIER - Copie les lignes s�lectionn�es de la page parall�le dans cette page
 */
void PageGestionPeriph::CopieDossierDansFichier()
{
    wxArrayString *tableau = GetDossierLigneSelection();
    m_pageParallele->AjoutDansFichierLigne(tableau);
    tableau->Clear();
    delete tableau;
}

////////////////Dossier
/**
 * DOSSIER - Copie les lignes s�lectionn�es de la page parall�le dans cette page
 */
void PageGestionPeriph::CopieDansDossier()
{
    wxArrayString *tableau = GetDossierLigneSelection();
    ThreadFichierFichier::Get()->AjoutDonnee(tableau, COPIE, m_pageParallele->GetChemin());
    if (!ThreadFichierFichier::Get()->GetEtat())
        ThreadFichierFichier::Get()->Run();
}

/**
 * DOSSIER - D�place les lignes s�lectionn�es de la page parall�le dans cette page
 */
void PageGestionPeriph::DeplaceDansDossier()
{
    wxArrayString *tableau = GetDossierLigneSelection();
    ThreadFichierFichier::Get()->AjoutDonnee(tableau, DEPLACE, m_pageParallele->GetChemin());
    if (!ThreadFichierFichier::Get()->GetEtat())
        ThreadFichierFichier::Get()->Run();
}

/**
 * DOSSIER - Supprime les lignes s�lectionn�es dans cette page
 */
void PageGestionPeriph::SuppressionDansDossier()
{
    wxArrayString *tableau = GetDossierLigneSelection();
    ThreadFichierFichier::Get()->AjoutDonnee(tableau, SUPPRIME);
    if (!ThreadFichierFichier::Get()->GetEtat())
        ThreadFichierFichier::Get()->Run();
}

////////////////Menu
/**
 * Menu - Affiche une fen�tre pour la cr�ation de dossier
 */
void PageGestionPeriph::MenuCreerDossier()
{
    wxTextEntryDialog boite(this, _("Nom du nouveau dossier"), _("Cr�ation de dossier"));

    if (boite.ShowModal() == wxID_OK)
    {
        wxString nom = m_text->GetValue();
        nom << wxFileName::GetPathSeparator() << boite.GetValue();

        if (wxDirExists(nom))
        {
            wxLogWarning(_("Dossier d�j� existant, op�ration annul�e"));
            return;
        }
        if (!wxMkdir(nom))
            wxLogError(_("Cr�ation impossible"));
        else
        {
            SetFichierDossier(m_chemin, DOSSIER);
            m_liste->SetItemState(m_liste->FindItem(-1, boite.GetValue()), wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
        }
    }
}

/**
 * Menu - Affiche une fen�tre pour la cr�ation d'un fichier M3U
 */
void PageGestionPeriph::MenuCreerM3U()
{
    if (m_liste->GetEtat() != DOSSIER && m_liste->GetEtat() != PLAYLIST)
        return;

    DialogEnregistreM3U fen(this, wxID_ANY, (m_liste->GetEtat() == PLAYLIST) ? _T("") : m_chemin);
    fen.Creer();
    bool modif = true;

    if (fen.ShowModal() == wxID_OK)
    {
        wxTextFile fichierEcr(fen.GetChemin());
        if (fichierEcr.Exists())
        {
            wxMessageDialog boite2(NULL, _("Fichier d�j� existant. Souhaitez-vous le remplacer ?"), _("Fichier d�j� existant"), wxYES_NO|wxICON_QUESTION|wxCENTRE|wxYES_DEFAULT);
            if (boite2.ShowModal() != wxID_YES)
                modif = false;
            else
            {
                fichierEcr.Open();
                fichierEcr.Clear();
            }
        }
        else
        {
            if (!fichierEcr.Create())
            {
                wxLogError(_("Erreur dans le nom.\nV�rifiez que vous utilisez des caract�res autoris�s."), _("Erreur"));
                return;
            }
        }

        if (modif)
        {
            fichierEcr.AddLine(_T("#EXTM3U"));
            if (m_liste->GetSelectedItemCount() > 1 && m_liste->GetEtat() == DOSSIER)
            {
                wxArrayString *tableau = GetDossierLigneSelection();

                for (size_t i = 0; i<tableau->GetCount(); i++)
                    fichierEcr.AddLine(tableau->Item(i));
                delete tableau;
            }
            else if (m_liste->GetSelectedItemCount() > 1 && m_liste->GetEtat() == PLAYLIST)
            {
                /*wxTextFile fichierLec(FichierListe::Get()->GetCheminListe());
                if (!fichierLec.Open())
                {   fichierEcr.Write(); fichierEcr.Close(); return;}

                wxArrayString *tableau = GetFichierLigneSelection();
                for (size_t i=0; i<tableau->GetCount(); i++)
                    fichierEcr.AddLine(tableau->Item(i));
                fichierLec.Close();
                delete tableau;*/
            }
            fichierEcr.Write();
            if (fen.GetCheminRaccourci() != wxEmptyString && !wxFileExists(fen.GetCheminRaccourci()))
            {
                if (!CreationRaccourci(fen.GetCheminRaccourci(), fen.GetChemin()))
                {
                    wxLogMessage(_("Echec de la cr�ation du raccourci."));
                }
            }

            wxArrayString chaine;
            chaine.Add(_("Non"));
            chaine.Add(_("A gauche"));
            chaine.Add(_("A droite"));
            wxSingleChoiceDialog boite3(NULL, _("Souhaitez-vous afficher le contenu du fichier ?"), _("Cr�ation M3U"), chaine);
            if (boite3.ShowModal() == wxID_OK)
            {
                int choix = boite3.GetSelection();
                if (choix)
                {
                    if (GetId() == ID_PAGE_PERIHERIQUE_GAUCHE && choix==1)
                        SetFichierDossier(fen.GetChemin(), M3U, true);
                    else if (GetId() == ID_PAGE_PERIHERIQUE_DROITE && choix==2)
                        SetFichierDossier(fen.GetChemin(), M3U, true);
                    else
                        m_pageParallele->SetFichierDossier(fen.GetChemin(), M3U, true);
                }
            }
        }
        fichierEcr.Close();
    }
    fen.CallPanel();
}

/**
 * Menu - Provoque la suppression des lignes s�lectionn�es
 */
void PageGestionPeriph::MenuSuprimer()
{
    long pos = m_liste->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    Suppression();
    SetFichierDossier(m_chemin, DOSSIER);
    pos = (pos<m_liste->GetItemCount()) ? pos : pos-1;
    m_liste->SetItemState(pos, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
}

/**
 * Menu - Affiche une fen�tre permettant de renommer un dossier ou un fichier
 */
void PageGestionPeriph::MenuRenommer()//Uniquement dans un dossier
{
    long pos = m_liste->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    wxString nomF = m_text->GetValue();
    nomF << wxFileName::GetPathSeparator() << m_liste->GetItemText(pos);

    bool est_dossier = wxDirExists(nomF);
    wxString mes1 = est_dossier ? _("Nouveau nom du dossier") : _("Nouveau nom du fichier");
    wxString titre1 = est_dossier ? _("Renommer un dossier") : _("Renommer un fichier");
    wxTextEntryDialog boite(this, mes1, titre1);
    if (est_dossier)
        boite.SetValue(m_liste->GetItemText(pos));
    else
        boite.SetValue(m_liste->GetItemText(pos).BeforeLast('.'));

    if (boite.ShowModal() == wxID_OK)
    {
        wxString nom = m_text->GetValue();
        nom << wxFileName::GetPathSeparator() << boite.GetValue();

        if (est_dossier)
        {
            if (wxDirExists(nom))
            {
                wxLogWarning(_("Ce nom est d�j� pris !"));
                return;
            }
            if (wxRename(nomF, nom))
                wxLogError(_("Impossible de renommer le fichier"));
            else
            {
                SetFichierDossier(m_chemin, DOSSIER);
                m_liste->SetItemState(m_liste->FindItem(-1, boite.GetValue()), wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
            }
        }
        else
        {
            nom << _T(".") << nomF.AfterLast('.');
            bool modif = true;
            if (wxFileExists(nom))
            {
                wxMessageDialog boite2(this, _("Fichier d�j� existant. Souhaitez-vous le remplacer ?"), _("Fichier d�j� existant"), wxYES_NO|wxICON_QUESTION|wxCENTRE|wxYES_DEFAULT);
                if (boite2.ShowModal() != wxID_YES)
                {
                    modif = false;
                }
            }
            if (modif)
            {
                if (!wxRenameFile(nomF, nom, true))
                {
                    wxLogError(_("Impossible de modifier le nom"));
                    if (nom.EndsWith(_(".m3u")))
                        DialogEnregistreM3U::CallPanel();
                }
            }
        }
    }
}

/**
 * Menu - Op�rations Couper-Copier-Coller - Met en m�moire les lignes s�lectionn�es pour un d�placement
 */
void PageGestionPeriph::MenuCouper()
{
    wxArrayString *tableau = NULL;
    if (m_liste->GetEtat() == VIDE)
        return;
    else if (m_liste->GetEtat() == DOSSIER)
    {
        tableau = GetDossierLigneSelection();
        CouperCopierColler::Get()->SetArrayString(tableau, COUPER, DOSSIER);
        delete tableau;
    }
    else if (m_liste->GetEtat() == PLAYLIST)
    {
        tableau = GetFichierLigneSelection();
        CouperCopierColler::Get()->SetArrayString(tableau, COUPER, PLAYLIST);
        delete tableau;
    }
    else if (m_liste->GetEtat() == M3U)
    {
        tableau = GetFichierLigneSelection();
        CouperCopierColler::Get()->SetArrayString(tableau, COUPER, M3U, m_chemin);
        delete tableau;
    }
}

/**
 * Menu - Op�rations Couper-Copier-Coller - Met en m�moire les lignes s�lectionn�es pour une copie
 */
void PageGestionPeriph::MenuCopier()
{
    wxArrayString *tableau = NULL;
    if (m_liste->GetEtat() == VIDE)
        return;
    else if (m_liste->GetEtat() == DOSSIER)
    {
        tableau = GetDossierLigneSelection();
        CouperCopierColler::Get()->SetArrayString(tableau, COPIE, DOSSIER);
        delete tableau;
    }
    else if (m_liste->GetEtat() == PLAYLIST)
    {
        tableau = GetFichierLigneSelection();
        CouperCopierColler::Get()->SetArrayString(tableau, COPIE, PLAYLIST);
        delete tableau;
    }
    else if (m_liste->GetEtat() == M3U)
    {
        tableau = GetFichierLigneSelection();
        CouperCopierColler::Get()->SetArrayString(tableau, COPIE, M3U, m_chemin);
        delete tableau;
    }
}

/**
 * Menu - Op�rations Couper-Copier-Coller - D�place les lignes pr�c�demment coup�es/copi�es dans le r�pertoire/fichier courant
 */
void PageGestionPeriph::MenuColler()
{
    if (m_liste->GetEtat() == VIDE)
        return;
    else if (m_liste->GetEtat() == DOSSIER)
        CouperCopierColler::Get()->SetDestination(m_chemin, DOSSIER);
    else if (m_liste->GetEtat() == PLAYLIST)
    {
        CouperCopierColler::Get()->SetDestination(wxEmptyString, PLAYLIST);
        Recharger();
    }
    else if (m_liste->GetEtat() == M3U)
    {
        CouperCopierColler::Get()->SetDestination(m_chemin, M3U);
        Recharger();
    }
}

/**
 * Menu - Provoque la lecture de la chanson s�lectionn�e. Si la liste courante n'est pas positionn�e sur la playlist, le titre s�lectionn� est ajout� � la playlist
 */
void PageGestionPeriph::MenuLire()
{
    if (m_liste->GetEtat() == PLAYLIST)
        MusicManagerSwitcher::get().playMusicAt(m_liste->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED));
    else if (m_liste->GetEtat() == M3U)
    {
        wxArrayString *tableau = GetFichierLigneSelection();
        MusicManagerSwitcher::get().parse(*tableau, true);
        MusicManagerSwitcher::get().playMusic(tableau->Item(0));
        delete tableau;
    }
    else if (m_liste->GetEtat() == DOSSIER)
    {
        wxArrayString *tableau = GetDossierLigneSelection();
        size_t i = 0;
        while(i < tableau->GetCount())
        {
            if (Parametre::Get()->islisable(tableau->Item(i).AfterLast('.').Lower()) || tableau->Item(i).AfterLast('.').Lower().IsSameAs(_("m3u")))
                i++;
            else
                tableau->RemoveAt(i);
        }
        if (!tableau->IsEmpty())
        {
            MusicManagerSwitcher::get().parse(*tableau, true);
            MusicManagerSwitcher::get().playMusic(tableau->Item(0));
        }
        delete tableau;
    }
}

/**
 * Menu - Affiche une fen�tre permettant la cr�ation d'un raccourci d'un fichier ou dossier
 */
void PageGestionPeriph::MenuRaccourci()
{
    int ouvert;
    wxDirDialog navig(this, _("Dans quel r�pertoire voulez-vous cr�er un raccourci de l'�l�ment s�lectionn� ?"));//, wxEmptyString);
    ouvert = navig.ShowModal();

    if (ouvert == wxID_OK)
    {
        if (!CreationRaccourci(navig.GetPath() + wxFileName::GetPathSeparator() + m_liste->GetItemText(m_liste->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)).BeforeLast('.') + _(" (raccourci).lnk"), m_chemin + wxFileName::GetPathSeparator() + m_liste->GetItemText(m_liste->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED))))
        {
            wxLogMessage(_("Echec de la cr�ation du raccourci."));
        }
    }
}

////////////////Dnd
/**
 * Drag & Drop - Initialise une op�ration de DnD
 */
void PageGestionPeriph::Glisser(wxCommandEvent &WXUNUSED(event))
{
    if (m_liste->GetEtat() == VIDE)
        return;
    m_dragging = true;
    //wxLogMessage("Dnd captur� " + m_navigDef);
    DnDListeFichier *transfile = new DnDListeFichier();
    if (m_liste->GetEtat() == M3U || m_liste->GetEtat() == PLAYLIST)
        transfile->AddStringArray(GetFichierLigneSelectionInt());
    else if (m_liste->GetEtat() == DOSSIER)
        transfile->AddStringArray(GetDossierLigneSelection());

    if (transfile->GetCount() == 0)
    {
        delete transfile;
        m_dragging = false;
        return;
    }

    MusicPlayListDnDBufferData UploadData(transfile);//Conversion tableau dans buffer
    wxDropSource s()
    wxDropSource source(UploadData, this);//met le buffer en d�placement
    source.DoDragDrop(wxDrag_DefaultMove);//D�place !

    delete transfile;
    m_dragging = false;
}

/**
 * Drag & Drop - G�re la modification des donn�es suite � l'appel de DnD
 * @param tableau tableau de caract�res
 * @param pos position/indice ou doit s'effectuer l'op�ration
 */
void PageGestionPeriph::GlisserTraitement(wxArrayString *tableau, long pos)
{
    if (m_dragging)
    {
        if (m_liste->GetEtat() == DOSSIER)
        {
            if (pos < m_liste->GetItemCount())
            {
                wxString nom = m_text->GetValue();
                nom << wxFileName::GetPathSeparator() << m_liste->GetItemText(pos);

                if (wxDirExists(nom))
                {
                    tableau->Remove(nom);//Retirer le r�pertoire de la s�lection si celui-ci y est
                    CouperCopierColler::Get()->SetArrayString(tableau, COUPER, DOSSIER);
                    CouperCopierColler::Get()->SetDestination(nom, DOSSIER);
                }
            }
        }
        else if (m_liste->GetEtat() == M3U)
        {
            PlacerLigneInt(tableau, pos, true);
            Recharger();
        }
        if (m_liste->GetEtat() == PLAYLIST)
        {
            MusicManagerSwitcher::get().moveIntTitlesAt(tableau, pos);/*, true, true*/
            //Recharger();
        }
    }
    else if (m_pageParallele->isDragging())
    {
        if (m_liste->GetEtat() == VIDE);
        else if (m_liste->GetEtat() == DOSSIER)
        {
            if (m_pageParallele->GetEtat() == DOSSIER)//Transfert entre dossier
            {
                wxString nom = m_text->GetValue();

                 if (pos < m_liste->GetItemCount())
                    nom << wxFileName::GetPathSeparator() << m_liste->GetItemText(pos);

                if (wxDirExists(nom))
                {
                    tableau->Remove(nom);//Retirer le r�pertoire de la s�lection si celui-ci y est
                    CouperCopierColler::Get()->SetArrayString(tableau, COUPER, DOSSIER);
                    CouperCopierColler::Get()->SetDestination(nom, DOSSIER);
                }
            }
        }
        else if (m_liste->GetEtat() == M3U)
        {
            if (m_pageParallele->GetEtat() == DOSSIER)
                PlacerLigneString(tableau, pos);
            else if (m_pageParallele->GetEtat() == M3U)
            {
                PlacerLigneInt(tableau, pos, false);
                m_pageParallele->SuppressionDansFichierLigneM3u();
            }
            else if (m_pageParallele->GetEtat() == PLAYLIST)
            {
                ArrayIntToString(tableau, m_pageParallele->GetChemin());
                PlacerLigneString(tableau, pos);
                m_pageParallele->SuppressionDansFichierLignePlaylist();
            }
            Recharger();
        }
        else if(m_liste->GetEtat() == PLAYLIST)
        {
            if (m_pageParallele->GetEtat() == DOSSIER)//A modifier, interdiction formel d'ouvrir directement le fichier sans passer par Musique
                MusicManagerSwitcher::get().placeStringTitlesAt(tableau, pos/*, true*/);
            else if (m_pageParallele->GetEtat() == M3U)
            {
                ArrayIntToString(tableau, m_pageParallele->GetChemin());
                MusicManagerSwitcher::get().placeStringTitlesAt(tableau, pos/*, true*/);
                m_pageParallele->SuppressionDansFichierLigneM3u();
            }
            else if (m_pageParallele->GetEtat() == PLAYLIST)
                MusicManagerSwitcher::get().moveIntTitlesAt(tableau, pos/*, true, true*/);
            //Recharger();
        }
    }
}

/**
 * Indique si une op�ration de d�placement est en cours
 * @return vrai si une op�ration de d�placement est en cours
 */
bool PageGestionPeriph::isDragging()
{    return m_dragging;}

/**
 * Modifie l'ordre des lignes d'un m3u � partir du num�ro des lignes. Ce peut �tre un d�placement ou une copie selon <b>supprime</b>
 * @param ligne un tableau d'indice des lignes � d�placer
 * @param pos l'indice de ligne o� doit �tre faite l'op�ration
 * @param supprime si vrai les lignes s�lectionn�es sont supprim� de leur position d'origine
 */
void PageGestionPeriph::PlacerLigneInt(wxArrayString *ligne, long pos, bool supprime)
{
    wxTextFile fichierListe(m_text->GetValue());
    if (!fichierListe.Open())
        return;

    int j = 0, k = 0;
    long val, insert = pos;
    bool deplace = true;
    wxArrayString chaine;
    chaine.Alloc(ligne->GetCount());

    if (insert < 0)
        insert = 0;
    else if (insert > long(fichierListe.GetLineCount()+1))
        insert = fichierListe.GetLineCount()+1;

    for (unsigned int i=0; i<ligne->GetCount(); i++)
    {
        ligne->Item(i).ToLong(&val);
        chaine.Add(fichierListe.GetLine(val));
        if (val == insert-1)
            deplace = false;
    }
    insert++;
    if (deplace)
    {
        for (unsigned int i=0; i<ligne->GetCount(); i++)
        {
            ligne->Item(i).ToLong(&val);
            if (val > insert)//Remonte
            {
                if (supprime)
                    fichierListe.RemoveLine(val);
                fichierListe.InsertLine(chaine.Item(i), insert+j);
                j++;
            }
            else if (val < insert)//Descend
            {
                if (supprime)
                    fichierListe.RemoveLine(val-k);
                fichierListe.InsertLine(chaine.Item(i), insert-1);///////
                k++;
            }
        }
        fichierListe.Write();
    }
    fichierListe.Close();
}

/**
 * Place le contenu du tableau <b>ligne</b> � la position <b>pos</b> dans le fichier courant
 * @param ligne un tabeau de caract�res
 * @param pos l'indice de ligne o� doit �tre ajout� du texte
 */
void PageGestionPeriph::PlacerLigneString(wxArrayString *ligne, long pos)
{
    wxTextFile fichierListe(m_text->GetValue());
    if (!fichierListe.Open())
        return;

    long insert = pos+1;

    if (insert < 1)
        insert = 1;
    else if (insert > long(fichierListe.GetLineCount()+1))
        insert = fichierListe.GetLineCount()+1;

    for (unsigned int i=0; i<ligne->GetCount(); i++)
    {
        if (Parametre::Get()->islisable(ligne->Item(i).AfterLast('.').Lower()))
        {
            fichierListe.InsertLine(ligne->Item(i), insert);
            insert++;
        }
    }
    fichierListe.Write();
    fichierListe.Close();
}

/**
 * Conversion num�ro de ligne � cha�ne de caract�res. Le tableau contient des indices de lignes qui seront �chang�s par le texte correspondant
 * @param tableau le tableau � modifier
 * @param source le fichier permettant de faire la correspondance
 */
void PageGestionPeriph::ArrayIntToString(wxArrayString* tableau, wxString source)
{
    wxTextFile fichier(source);
    if (!fichier.Open())
        return;

    long valeur = 0;

    for (unsigned int i=0; i<tableau->GetCount(); i++)
    {
        tableau->Item(i).ToLong(&valeur);
        tableau->Item(i) = fichier.GetLine(valeur);
    }
    fichier.Close();
}

