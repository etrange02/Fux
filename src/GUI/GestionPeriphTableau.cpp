/***************************************************************
 * Name:      GestionPeriphTableau.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (etrange02@aol.com)
 * Created:   2010-09-08
 * Copyright: David Lecoconnier (http://www.fuxplay.com)
 * License:
 **************************************************************/
#include "../../include/GUI/GestionPeriph.h"

/**
 * @class ListeGestionPeriph
 * @brief Liste affichant le contenu d'un fichier ou d'un dossier
 */

BEGIN_EVENT_TABLE(ListeGestionPeriph, wxListCtrl)
    EVT_KEY_DOWN(ListeGestionPeriph::OnKey)
    EVT_MENU(-1, ListeGestionPeriph::OnMenu)
    EVT_RIGHT_DOWN(ListeGestionPeriph::AfficheMenu)
END_EVENT_TABLE()

const wxEventType wxEVT_LISTE_PERIPH_CLAVIER = wxNewEventType();
const wxEventType wxEVT_LISTE_PERIPH_SOURIS = wxNewEventType();
const wxEventType wxEVT_LISTE_RENEW = wxNewEventType();

/**
 * Constructeur
 */
ListeGestionPeriph::ListeGestionPeriph()
{}

/**
 * Constructeur
 * @param Parent un pointeur sur la fenêtre parente
 * @param id l'identifiant de la liste
 */
ListeGestionPeriph::ListeGestionPeriph(wxWindow *Parent, wxWindowID id)
{
    Creer(Parent, id);
}

/**
 * Destructeur
 */
ListeGestionPeriph::~ListeGestionPeriph()
{}

/**
 * Crée les éléments graphiques de la liste
 * @param Parent un pointeur sur la fenêtre parente
 * @param id l'identifiant de la liste
 */
void ListeGestionPeriph::Creer(wxWindow *Parent, wxWindowID id)
{
    Create(Parent, id, wxDefaultPosition, wxDefaultSize, wxLC_REPORT |  wxLC_HRULES | wxLC_VRULES);
    InsertColumn(0, _("Nom"), wxLIST_FORMAT_CENTER, 400);
    InsertColumn(1, _("Type"), wxLIST_FORMAT_CENTER, 60);

    SetDropTarget(new DnDCible(this, Parent));

    m_etat = VIDE;
    m_menu = new wxMenu;

    m_menu->Append(ID_PAGE_PERIHERIQUE_MENU_CREER_DOSSIER, _("Créer un dossier"));
    m_menu->Append(ID_PAGE_PERIHERIQUE_MENU_CREER_M3U, _("Créer un m3u"));
    m_menu->AppendSeparator();
    m_menu->Append(ID_PAGE_PERIHERIQUE_MENU_COUPER, _("Couper\tCtrl-X"));
    m_menu->Append(ID_PAGE_PERIHERIQUE_MENU_COPIER, _("Copier\tCtrl-C"));
    m_menu->Append(ID_PAGE_PERIHERIQUE_MENU_COLLER, _("Coller\tCtrl-V"));
    m_menu->AppendSeparator();
    m_menu->Append(ID_PAGE_PERIHERIQUE_MENU_SUPPRIMER, _("Supprimer\tSuppr"));
    m_menu->Append(ID_PAGE_PERIHERIQUE_MENU_RENOMMER, _("Renommer"));
    m_menu->Append(ID_PAGE_PERIHERIQUE_MENU_RACCOURCI, _("Raccourci"));
    m_menu->AppendSeparator();
    m_menu->Append(ID_PAGE_PERIHERIQUE_MENU_TOUT_SELECTIONNER, _("Tout sélectionner\tCtrl-A"));
    m_menu->Append(ID_PAGE_PERIHERIQUE_MENU_LIRE, _("Lire"));
}

/**
 * Efface la liste et affiche le contenu d'un fichier
 * @param chemin le chemin du fichier à afficher
 * @param debut le numéro de ligne à partir de laquelle doit commencer l'affichage (0-n)
 * @return vrai si réussite, faux sinon
 */
bool ListeGestionPeriph::AfficheContenuFichier(wxString chemin, int debut)
{
    if (!wxFileExists(chemin))
        return false;

    wxTextFile fichier(chemin);
    if (!fichier.Open())
        return false;

    wxString temp;
    size_t i = 0, max = fichier.GetLineCount();
    int pos, j;
    DeleteAllItems();

    for (i = debut; i < max; i++)
    {
        temp = fichier.GetLine(i);
        j = temp.Find(wxFileName::GetPathSeparator(), true);
        pos = GetItemCount();
        pos = InsertItem(pos, temp.Right(temp.Length()-j-1));
        if (!wxFileExists(temp))
        {
            SetItem(pos, 1, _("Fichier inexistant"));//Artiste
            SetItemTextColour(pos, wxColor(255, 255, 255));
            SetItemBackgroundColour(pos, wxColor(255, 0, 0));
        }
    }
    fichier.Close();
    SetFocus();
    wxCommandEvent evt(wxEVT_LISTE_RENEW);
    GetParent()->GetEventHandler()->AddPendingEvent(evt);
    return true;
}

/**
 * Efface la liste et affiche le contenu d'un dossier
 * @param chemin le chemin du dossier à lister
 * @param cache si vrai, les fichiers cachés seront affichés
 * @param filtre si vrai, seuls les chansons pouvant être lues seront affichées
 * @return vrai si réussite, faux sinon
 */
bool ListeGestionPeriph::AfficheContenuDossier(wxString chemin, bool cache, bool filtre)
{
    if (!wxDirExists(chemin))
        return false;

    bool cont;
    wxString temp;
    int pos = 0, j = 0;
    wxDir repertoire(chemin);

    DeleteAllItems();
//Dossiers
    cont = (cache) ? repertoire.GetFirst(&temp, wxEmptyString, wxDIR_DIRS | wxDIR_HIDDEN) : repertoire.GetFirst(&temp, wxEmptyString, wxDIR_DIRS);

    while (cont)
    {
        j = temp.Find(wxFileName::GetPathSeparator(), true);
        pos = GetItemCount();
        pos = InsertItem(pos, temp.Right(temp.Length()-j-1));
        SetItem(pos, 1, _T("Dossier"));
        SetItemBackgroundColour(pos, wxColor(236, 150, 243));
        SetItemTextColour(pos, wxColor(255, 253, 151));
        cont = repertoire.GetNext(&temp);
    }
//Fichiers
    cont = (cache) ? repertoire.GetFirst(&temp, wxEmptyString, wxDIR_FILES | wxDIR_HIDDEN) : repertoire.GetFirst(&temp, wxEmptyString, wxDIR_FILES);

    if (filtre)
    {
        while (cont)
        {
            if (Parametre::Get()->islisable(temp.AfterLast('.').Lower()) || temp.Lower().EndsWith(_T(".m3u")))// || temp.Lower().EndsWith(".m4a")/*|| temp.Lower().EndsWith(".wav") ||*/ /*temp.Lower().EndsWith(".aac")  || temp.Lower().EndsWith(".ogg")*/)
            {
                j = temp.Find(wxFileName::GetPathSeparator(), true);
                pos = GetItemCount();
                pos = InsertItem(pos, temp.Right(temp.Length()-j-1));
                SetItem(pos, 1, temp.AfterLast('.'));
            }
            cont = repertoire.GetNext(&temp);
        }
    }
    else
    {
        while (cont)
        {
            j = temp.Find(wxFileName::GetPathSeparator(), true);
            pos = GetItemCount();
            pos = InsertItem(pos, temp.Right(temp.Length()-j-1));
            SetItem(pos, 1, temp.AfterLast('.'));
            cont = repertoire.GetNext(&temp);
        }
    }

    SetFocus();
    //if (GetItemCount() != 0)
    //    SetItemState(0, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED);
    wxCommandEvent evt(wxEVT_LISTE_RENEW);
    GetParent()->GetEventHandler()->AddPendingEvent(evt);
    return true;
}

/**
 * Efface la liste
 * @return vrai si réussite, faux sinon
 */
bool ListeGestionPeriph::VideListe()
{
    bool result = DeleteAllItems();
    wxCommandEvent evt(wxEVT_LISTE_RENEW);
    GetParent()->GetEventHandler()->AddPendingEvent(evt);
    return result;
}

/**
 * Évènement clavier
 */
void ListeGestionPeriph::OnKey(wxKeyEvent &event)
{
    if (event.GetKeyCode() == 'A' && event.ControlDown())
        SetItemState(-1, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
    else if (event.GetKeyCode() == WXK_DELETE || event.GetKeyCode() == WXK_LEFT || event.GetKeyCode() == WXK_RIGHT || event.GetKeyCode() == WXK_F2
         || ((event.GetKeyCode() == 'R' || event.GetKeyCode() == 'X' || event.GetKeyCode() == 'C' || event.GetKeyCode() == 'V')&& event.ControlDown()))
    {
        wxKeyEvent evt(wxEVT_LISTE_PERIPH_CLAVIER);
        evt = event;
        GetParent()->GetEventHandler()->AddPendingEvent(evt);
    }
    else
        event.Skip();
}

/**
 * Évènement souris - Affiche un menu lors d'un clique droite sur la liste
 */
void ListeGestionPeriph::AfficheMenu(wxMouseEvent &WXUNUSED(event))
{
    int flag = wxLIST_HITTEST_ONITEM | wxLIST_HITTEST_ONITEMRIGHT | wxLIST_HITTEST_TOLEFT | wxLIST_HITTEST_TORIGHT;
    long subitem;
    long pos = HitTest(ScreenToClient(wxGetMousePosition()), flag, &subitem);

    if (GetItemCount() && pos != wxNOT_FOUND && GetItemState(pos, wxLIST_STATE_SELECTED) != wxLIST_STATE_SELECTED)
        while (GetSelectedItemCount() > 0)
            SetItemState(GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED), 0, wxLIST_STATE_SELECTED);

    if (pos != wxNOT_FOUND)//Sélection et désélection des lignes
        SetItemState(pos, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED);

    SetFocus();


    (m_etat == DOSSIER) ? m_menu->Enable(ID_PAGE_PERIHERIQUE_MENU_CREER_DOSSIER, true) : m_menu->Enable(ID_PAGE_PERIHERIQUE_MENU_CREER_DOSSIER, false);
    (m_etat == DOSSIER || m_etat == PLAYLIST) ? m_menu->Enable(ID_PAGE_PERIHERIQUE_MENU_CREER_M3U, true) : m_menu->Enable(ID_PAGE_PERIHERIQUE_MENU_CREER_M3U, false);

    if (m_etat != VIDE && CouperCopierColler::Get()->estCharge())
    {
        if (m_etat == DOSSIER)
            (CouperCopierColler::Get()->GetOrigine() == DOSSIER) ? m_menu->Enable(ID_PAGE_PERIHERIQUE_MENU_COLLER, true) : m_menu->Enable(ID_PAGE_PERIHERIQUE_MENU_COLLER, false);
        else
            m_menu->Enable(ID_PAGE_PERIHERIQUE_MENU_COLLER, true);
    }
    else
        m_menu->Enable(ID_PAGE_PERIHERIQUE_MENU_COLLER, false);

    //Affichage dépend des
    if (pos == wxNOT_FOUND && GetItemCount() > 0)//Element sélectionné est chargé ou pas d'éléments sélectionnés
    {
        m_menu->Enable(ID_PAGE_PERIHERIQUE_MENU_COUPER, false);
        m_menu->Enable(ID_PAGE_PERIHERIQUE_MENU_COPIER, false);
        m_menu->Enable(ID_PAGE_PERIHERIQUE_MENU_SUPPRIMER, false);
        m_menu->Enable(ID_PAGE_PERIHERIQUE_MENU_RENOMMER, false);
        m_menu->Enable(ID_PAGE_PERIHERIQUE_MENU_RACCOURCI, false);
        m_menu->Enable(ID_PAGE_PERIHERIQUE_MENU_TOUT_SELECTIONNER, (m_etat != VIDE));
        m_menu->Enable(ID_PAGE_PERIHERIQUE_MENU_LIRE, false);
    }
    else if (GetItemCount() > 0)//Element sélectionné
    {
        m_menu->Enable(ID_PAGE_PERIHERIQUE_MENU_COUPER, true);
        m_menu->Enable(ID_PAGE_PERIHERIQUE_MENU_COPIER, true);
        m_menu->Enable(ID_PAGE_PERIHERIQUE_MENU_SUPPRIMER, true);
        m_menu->Enable(ID_PAGE_PERIHERIQUE_MENU_RENOMMER, (m_etat == DOSSIER));
        m_menu->Enable(ID_PAGE_PERIHERIQUE_MENU_RACCOURCI, (m_etat == DOSSIER));
        m_menu->Enable(ID_PAGE_PERIHERIQUE_MENU_TOUT_SELECTIONNER, true);
        m_menu->Enable(ID_PAGE_PERIHERIQUE_MENU_LIRE, (m_etat != VIDE));
    }
    else
    {
        m_menu->Enable(ID_PAGE_PERIHERIQUE_MENU_COUPER, false);
        m_menu->Enable(ID_PAGE_PERIHERIQUE_MENU_COPIER, false);
        m_menu->Enable(ID_PAGE_PERIHERIQUE_MENU_SUPPRIMER, false);
        m_menu->Enable(ID_PAGE_PERIHERIQUE_MENU_RENOMMER, false);
        m_menu->Enable(ID_PAGE_PERIHERIQUE_MENU_RACCOURCI, false);
        m_menu->Enable(ID_PAGE_PERIHERIQUE_MENU_TOUT_SELECTIONNER, false);
        m_menu->Enable(ID_PAGE_PERIHERIQUE_MENU_LIRE, false);
    }

    //m_yMenu = pos;
    PopupMenu(m_menu);
}

/**
 * Évènement - Transmet au parent l'évènement si ce n'est pas une sélection
 */
void ListeGestionPeriph::OnMenu(wxCommandEvent &event)
{
    if (event.GetId() == ID_PAGE_PERIHERIQUE_MENU_TOUT_SELECTIONNER)
        SetItemState(-1, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
    else
    {
        wxCommandEvent evt(wxEVT_LISTE_PERIPH_SOURIS);
        evt.SetId(event.GetId());
        GetParent()->GetEventHandler()->AddPendingEvent(evt);
    }
}

/**
 * Retourne l'état de la liste
 * @return l'état
 */
int ListeGestionPeriph::GetEtat()
{    return m_etat;}

/**
 * Associe un état à la liste (VIDE par défaut, DOSSIER, PLAYLIST, M3U)
 */
void ListeGestionPeriph::SetEtat(int etat)
{    m_etat = etat;}

