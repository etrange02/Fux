/***************************************************************
 * Name:      PlayListTableau.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2010-08-22
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/


#include "Define.h"
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include <wx/tarstrm.h>
#include <wx/progdlg.h>
#include <wx/dnd.h>
#include <wx/mstream.h>
#include <wx/renderer.h>
#include <algorithm>
#include "gui/musiclist/PlayList.h"
#include "MusicManagerSwitcher.h"
#include "music/MusicManager.h"
#include "music/DeletedLines.h"
#include "widgets/SliderSon.h"
#include "tools/FichierLog.h"
#include "tools/dnd/targets/PlaylistTransitiveDataTarget.h"
#include "tools/dnd/dataObjects/PlaylistTransitiveData.h"
#include "tools/dnd/dataObjects/ContainerFileTransitiveData.h"
#include "tools/dnd/dataObjects/DataObject.h"
#include "predicates/findSharedMusicContainer.h"

using namespace ::music;

/**
 * @class PlayListTableau
 * @brief Tableau (GUI) dans lequel sont affichés les informations des titres mis dans la liste de lecture. D'une certaine manière, c'est la liste de lecture
 */

BEGIN_EVENT_TABLE(PlayListTableau, DroppedMarkedLineListCtrl)
    EVT_LIST_ITEM_ACTIVATED (ID_PAGE_PLAYLIST_LISTE,            PlayListTableau::onActiveLineEvent)
    EVT_LIST_BEGIN_DRAG     (ID_PAGE_PLAYLIST_LISTE,            PlayListTableau::onDragEvent)
    EVT_MENU                (ID_PAGE_PLAYLIST_MENU_LECTURE,     PlayListTableau::onMenuEventPlay)
    EVT_MENU                (ID_PAGE_PLAYLIST_MENU_PAUSE,       PlayListTableau::onMenuEventPause)
    EVT_MENU                (ID_PAGE_PLAYLIST_MENU_SUPPRIMER,   PlayListTableau::onMenuEventDelete)
    EVT_MENU                (ID_PAGE_PLAYLIST_MENU_COUPER,      PlayListTableau::onMenuEventCut)
    EVT_MENU                (ID_PAGE_PLAYLIST_MENU_COLLER,      PlayListTableau::onMenuEventPaste)
    EVT_MENU                (ID_PAGE_PLAYLIST_MENU_DETAILS,     PlayListTableau::onMenuEventDetails)
    EVT_MOUSE_EVENTS        (PlayListTableau::onMouseEvent)
    EVT_RIGHT_DOWN          (PlayListTableau::onDisplayMenu)
    EVT_KEY_DOWN            (PlayListTableau::onKeyboardEvent)
END_EVENT_TABLE()


const wxEventType wxEVT_VIDER_PANNEAU = wxNewEventType();
const wxEventType wxEVT_LISTE_DETAILS = wxNewEventType();

/** @brief Constructor.
 *
 * @param parent The parent window
 */
PlayListTableau::PlayListTableau(wxWindow *parent) :
    DroppedMarkedLineListCtrl(parent, ID_PAGE_PLAYLIST_LISTE, wxDefaultPosition, wxDefaultSize, wxLC_REPORT |  wxLC_HRULES | wxLC_VRULES)
{
    LogFileAppend("PlayListTableau::PlayListTableau - Création");

    InsertColumn(0, _("Nom"),         wxLIST_FORMAT_CENTER,  280);
    InsertColumn(1, _("Artiste"),     wxLIST_FORMAT_LEFT,    150);
    InsertColumn(2, _("Album"),       wxLIST_FORMAT_LEFT,    150);
    InsertColumn(3, _("Titre"),       wxLIST_FORMAT_LEFT,    150);
    InsertColumn(4, _("Durée"),       wxLIST_FORMAT_LEFT,    50);
    InsertColumn(5, _("Année"),       wxLIST_FORMAT_LEFT,    50);
    InsertColumn(6, _("Emplacement"), wxLIST_FORMAT_LEFT,    280);
    InsertColumn(7, _("Genre"),       wxLIST_FORMAT_LEFT,    80);
    InsertColumn(8, _("Ext."),        wxLIST_FORMAT_LEFT,    50);

    SetMinSize(wxSize(10, 10));

    SetDropTarget(new dragAndDrop::PlaylistTransitiveDataTarget(*this, true));
    //DragAcceptFiles(true);

    m_menu = new wxMenu;
    m_menu->Append(ID_PAGE_PLAYLIST_MENU_LECTURE,   _("Lire"));
    m_menu->Append(ID_PAGE_PLAYLIST_MENU_PAUSE,     _("Pause"));
    m_menu->Append(ID_PAGE_PLAYLIST_MENU_SUPPRIMER, _("Effacer"));
    m_menu->Append(ID_PAGE_PLAYLIST_MENU_COUPER,    _("Déplacer"));
    m_menu->Append(ID_PAGE_PLAYLIST_MENU_COLLER,    _("Déposer"));
    m_menu->Append(ID_PAGE_PLAYLIST_MENU_DETAILS,   _("Détails"));
    m_cut = false;
}

/** @brief Destructor.
 */
PlayListTableau::~PlayListTableau()
{
    LogFileAppend(_T("PlayListTableau::~PlayListTableau"));
    SetDropTarget(NULL);
}

/** @brief Clears the list and redraw all data.
 *
 */
void PlayListTableau::updateLines()
{
    wxMutexLocker lock(m_mutexListUpdating);
    LogFileAppend("PlayListTableau::updateLines - Début après les tests");

    wxString chaine, extrait;

    if (GetSelectedItemCount() > 0)
        extrait = GetItemText(GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED));

    long ligneVisible = 0;
    if (GetItemCount() >= GetCountPerPage())
        ligneVisible = GetTopItem() + GetCountPerPage()-1;

    DeleteAllItems();

    if (MusicManagerSwitcher::getSearch().getMusics().empty())
    {
        return;
    }

    Freeze();

    LogFileAppend("PlayListTableau::updateLines - Début du for");

    SetDoubleBuffered(true);
    for (MusicIterator iter = MusicManagerSwitcher::getSearch().getMusics().begin(); iter != MusicManagerSwitcher::getSearch().getMusics().end(); ++iter)
        addLine(**iter);

    if (!GetSelectedItemCount() && GetTopItem() == 0)
    {
        if (GetItemCount() > 0)
            EnsureVisible(ligneVisible);

        if (!extrait.IsEmpty())
        {
            long ligne = FindItem(-1, extrait);
            SetItemState(ligne, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED);
            EnsureVisible(ligne);
        }
    }
    updateColors();

    SetDoubleBuffered(false);
    Thaw();

    LogFileAppend(_T("PlayListTableau::updateLines - Fin du for : ") + wxString::Format(_T("%u"), GetItemCount()));
    LogFileAppend(_T("PlayListTableau::updateLines - Fin"));
}

/** @brief Adds a line at the end of the list
 *
 * @param music a music data
 * @return void
 *
 */
void PlayListTableau::addLine(IMusic& music)
{
    addLine(music, GetItemCount());
}

/** @brief Adds a line at the specified position
 *
 * @param music a music data
 * @param position position to place the line
 * @return void
 *
 */
void PlayListTableau::addLine(IMusic& music, const int position)
{
    int pos = InsertItem(position, wxEmptyString);
    modifyLine(music, pos);
}

/** @brief Adds a line at the specified position.
 * It creates intermediate lines if needed.
 * @param music a music
 * @param position position to insert
 * @return void
 *
 */
void PlayListTableau::addLineThread(IMusic& music, const int position)
{
    if (GetItemCount() < position+1) // end adding
    {
        while (GetItemCount() < position+1)
        {
            InsertItem(GetItemCount(), wxEmptyString);
        }
    }
    else if (!GetItemText(position).IsEmpty()) // insertion case or completion
    {
        music::MusicCollection& musicCollection = MusicManagerSwitcher::getSearch().getMusics();
        music::Music& musicToComplete = *(musicCollection.at(position));

        if (musicToComplete.GetName() != GetItemText(position)) // it is an insertion
        {
            const int nextElementPositionInCollection = position + 1;
            music::Music& nextMusic = *(musicCollection.at(nextElementPositionInCollection));

            const wxString& nextMusicName = nextMusic.GetName();
            int nextElementPositionInList = position;
            wxString nextItemText = GetItemText(nextElementPositionInList, 0);
            while (-1 != nextElementPositionInList && nextItemText != nextMusicName)
            {
                --nextElementPositionInList;
                if (nextElementPositionInList > 0)
                    nextItemText = GetItemText(nextElementPositionInList);
            }

            // The delta test is useful in case of many loading of the same title.
            // It is not possible to determine each occurrence so I limit the algorithm effect.
            const int delta = position - nextElementPositionInList;
            if (-1 == nextElementPositionInList || delta > wxThread::GetCPUCount())
                nextElementPositionInList = position;

            while (nextElementPositionInList < nextElementPositionInCollection)
            {
                InsertItem(nextElementPositionInList, wxEmptyString);
                ++nextElementPositionInList;
            }
        }
    }

    modifyLine(music, position);
}

/** @brief Modifies a line in the list
 *
 * @param music a music data
 * @param position line to modify
 * @return void
 *
 */
void PlayListTableau::modifyLine(IMusic& music, const int position)
{
    SetItem(position, 0, music.GetName());//Nom du fichier
    SetItem(position, 1, music.GetArtists());//Artiste
    SetItem(position, 2, music.GetAlbum());//Album
    SetItem(position, 3, music.GetTitle());//Titre
    SetItem(position, 4, music.GetStringDuration());//Durée
    SetItem(position, 5, music.GetYear() == 0 ? _T("?") : music.GetStringYear());//Année
    SetItem(position, 6, music.GetPath());//Emplacement
    SetItem(position, 7, music.GetGenres());//Genre
    SetItem(position, 8, music.GetExtension());//Extension
}

/** @brief Event. Plays the activated line
 *
 */
void PlayListTableau::onActiveLineEvent(wxListEvent& event)
{
    MusicManagerSwitcher::getSearch().playMusicAt(event.GetIndex());
}

/** @brief Event. Keyboard
 *
 */
void PlayListTableau::onKeyboardEvent(wxKeyEvent& event)
{
    if (event.GetKeyCode() == WXK_DELETE)
        removeSelectedLines();
    else if ((event.GetKeyCode() == 'R' && event.ControlDown()) || event.GetKeyCode() == WXK_F5)
        updateLines();
    else if (event.ControlDown() && (event.GetKeyCode() == '+' || event.GetKeyCode() == WXK_ADD || event.GetKeyCode() == WXK_NUMPAD_ADD ||
                                     event.GetKeyCode() == '-' || event.GetKeyCode() == WXK_SUBTRACT || event.GetKeyCode() == WXK_NUMPAD_SUBTRACT))
    {
        wxKeyEvent evt(wxEVT_KEY_DOWN);
        evt = event;
        GetParent()->GetEventHandler()->AddPendingEvent(evt);
    }
    else
        event.Skip();
}

/** @brief Event. Mouse.
 *
 */
void PlayListTableau::onMouseEvent(wxMouseEvent &event)
{
    if (event.ControlDown() && event.GetWheelRotation() != 0)
    {
        if (event.GetWheelRotation() < 0)
            MusicManagerSwitcher::getSearch().playNextMusic();
        else
            MusicManagerSwitcher::getSearch().playPreviousMusic();
    }
    else if (event.AltDown() && event.GetWheelRotation() != 0)
    {
        if (event.GetWheelRotation() < 0)
            SliderSon::Get()->SonUp();
        else
            SliderSon::Get()->SonDown();
    }
    else if (event.LeftDown())
    {
        wxPoint pt = event.GetPosition();
        event.Skip();

        int taille = -GetScrollPos(wxHORIZONTAL);
        for (int i = 0; i < 5; i++)
            taille += GetColumnWidth(i);

        if ((pt.x >= taille) && pt.x <= (taille + GetColumnWidth(5)))
        {
            //int flag = wxLIST_HITTEST_ONITEM | wxLIST_HITTEST_ONITEMRIGHT | wxLIST_HITTEST_TOLEFT | wxLIST_HITTEST_TORIGHT;
            //long pos = HitTest(pt, flag);

            //SetItemState(pos, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED);

            //wxLogMessage(wxString::Format(_T("sur année %d, %d %d"), GetColumnWidth(5), pt.x, pt.y));
            // Afficher le menu donnant la liste des noms enregistrés en mémoire
        }
    }
    else
        event.Skip();
}

/** @brief Remove a line from the control
 *
 * @param position line to remove
 */
void PlayListTableau::removeLine(const long position)
{
    if (position < 0)
        return;

    wxMutexLocker lock(m_mutexListUpdating);
    LogFileAppend("PlayListTableau::removeLine(const long position)");

    DeleteItem(position);

    wxArrayInt::iterator iterToDelete = std::find(m_similarLinesOccurences.begin(), m_similarLinesOccurences.end(), position);
    if (m_similarLinesOccurences.end() != iterToDelete)
        m_similarLinesOccurences.erase(iterToDelete);

    for (wxArrayInt::iterator iter = m_similarLinesOccurences.begin(); iter != m_similarLinesOccurences.end(); ++iter)
    {
        if (*iter >= position)
            --(*iter);
    }

    /*if (getSelectedLines().empty())
    {
        long lineToSelect = position;
        if (position > GetItemCount()-1)
            lineToSelect = GetItemCount()-1;
        SetItemState(lineToSelect, wxLIST_STATE_FOCUSED|wxLIST_STATE_SELECTED, wxLIST_STATE_FOCUSED|wxLIST_STATE_SELECTED);
    }*/
}

/** @brief Update colours of each line
 *
 * @param titre les nom et position du titre en cours
 */
void PlayListTableau::updateColors()
{
    LogFileAppend(_T("PlayListTableau::updateColors"));
    if (MusicManagerSwitcher::getSearch().getMusics().empty())
        return;

    for (wxArrayInt::iterator iter = m_similarLinesOccurences.begin(); iter != m_similarLinesOccurences.end(); ++iter)
    {
        if (*iter < GetItemCount())
        {
            setDefaultColor(*iter);
        }
    }

    m_similarLinesOccurences.Empty();

    for (size_t i = 0; i < (size_t) GetItemCount(); ++i)
    {
        updateColor(i);
    }
}

/** @brief Update the colour of one line according to its attributes
 *
 * @param position const size_t
 * @return void
 *
 */
void PlayListTableau::updateColor(const size_t position)
{
    IMusicManager& musicManager = MusicManagerSwitcher::getSearch();
    if (GetItemText(position).IsSameAs(musicManager.getMusic()->GetName()))
    {
        m_similarLinesOccurences.Add(position);
        long pos = musicManager.getCurrentMusicPosition();
        if (pos == position && !musicManager.hasEfficientSearchedWord())//La couleur orange perd son sens lorsqu'il y a une recherche locale
            updateColorNormalMode(position);
        else
            updateColorSearchMode(position);
    }
}

/** @brief Sets the colours of the playing title (orange and yellow)
 *
 * @param position const size_t
 * @return void
 *
 */
void PlayListTableau::updateColorNormalMode(const size_t position)
{
    SetItemTextColour       (position, wxColor(247, 236, 50)); // yellow
    SetItemBackgroundColour (position, wxColor(243, 124, 45)); // orange
}

/** @brief Sets the colours of the similar titles (green and indigo)
 *
 * @param position const size_t
 * @return void
 *
 */
void PlayListTableau::updateColorSearchMode(const size_t position)
{
    SetItemTextColour       (position, wxColor(24, 14, 154)); // indigo
    SetItemBackgroundColour (position, wxColor(64, 247, 32)); // green
}

/** @brief Sets the colour of normal line (white and black)
 *
 * @param position const size_t
 * @return void
 *
 */
void PlayListTableau::setDefaultColor(const size_t position)
{
    SetItemTextColour       (position, wxColor(0, 0, 0));       // black
    SetItemBackgroundColour (position, wxColor(255, 255, 255)); // white
}

/** Drag&Drop event. Moves the selected lines to another location.
 *
 */
void PlayListTableau::onDragEvent(wxListEvent &WXUNUSED(event))
{
    wxMutexLocker locker(m_mutexListUpdating);

    dragAndDrop::PlaylistTransitiveData data;
    MusicManagerSwitcher::getSearch().convertPositionsToTransitiveData(getSelectedLines(), data);

    if (data.isEmpty())
        return;

    dragAndDrop::DataObject container(&data);
    wxDropSource source(this, wxDROP_ICON(dnd_copy), wxDROP_ICON(dnd_move), wxDROP_ICON(dnd_none));
    source.SetData(container);
    source.DoDragDrop(true);
}

/** @brief Event. Display a menu.
 *
 */
void PlayListTableau::onDisplayMenu(wxMouseEvent &WXUNUSED(event))
{
    int flag = wxLIST_HITTEST_ONITEM | wxLIST_HITTEST_ONITEMRIGHT | wxLIST_HITTEST_TOLEFT | wxLIST_HITTEST_TORIGHT;
    long pos = HitTest(ScreenToClient(wxGetMousePosition()), flag);

    if (pos != wxNOT_FOUND)//Sélection et dé-sélection des lignes
    {
        if (GetItemState(pos, wxLIST_STATE_SELECTED) != wxLIST_STATE_SELECTED)
            while (GetSelectedItemCount() > 0)
                SetItemState(GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED), 0, wxLIST_STATE_SELECTED);
        SetItemState(pos, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED);
    }

    const long position = MusicManagerSwitcher::getSearch().getCurrentMusicPosition();
    if ((pos == position) || (pos == wxNOT_FOUND && GetItemCount() > 0))//Element sélectionné est chargé ou pas d'éléments sélectionnés
    {
       ////////////////////// Musique::Get()->GetNomChanson().IsSameAs(GetItem(pos));/////////////////
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_LECTURE, false);
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_PAUSE, true);
        if (MusicManagerSwitcher::getSearch().getMusicPlayer().isPlaying())//En lecture
            m_menu->SetLabel(ID_PAGE_PLAYLIST_MENU_PAUSE, _("Pause"));
        else
            m_menu->SetLabel(ID_PAGE_PLAYLIST_MENU_PAUSE, _("Reprendre"));
    }
    else if (GetItemCount() > 0)//L'élément sélectionné n'est pas en lecture
    {
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_LECTURE, true);
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_PAUSE, true);
        if (MusicManagerSwitcher::getSearch().getMusicPlayer().isPlaying())//En lecture
            m_menu->SetLabel(ID_PAGE_PLAYLIST_MENU_PAUSE, _("Pause"));
        else
            m_menu->SetLabel(ID_PAGE_PLAYLIST_MENU_PAUSE, _("Reprendre"));
    }
    else//Liste vierge
    {
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_LECTURE, false);
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_PAUSE, false);
    }


    if (m_cut && !MusicManagerSwitcher::getSearch().hasEfficientSearchedWord())
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_COLLER, true);
    else
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_COLLER, false);

    if (pos == wxNOT_FOUND)//Pas d'élément sélectionnés
    {
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_COUPER, false);
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_SUPPRIMER, false);
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_DETAILS, false);
    }
    else
    {
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_COUPER, !MusicManagerSwitcher::getSearch().hasEfficientSearchedWord());// couper accessible si on est pas en recherche
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_SUPPRIMER, !MusicManagerSwitcher::getSearch().hasEfficientSearchedWord());// idem
        m_menu->Enable(ID_PAGE_PLAYLIST_MENU_DETAILS, true);
    }

    m_yMenu = pos;

    PopupMenu(m_menu);
}

/** @brief Event. Play the first selected music.
 *
 */
void PlayListTableau::onMenuEventPlay(wxCommandEvent &WXUNUSED(event))
{
    long pos = GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_FOCUSED);
    MusicManagerSwitcher::getSearch().playMusicAt(pos);
}

/** @brief Event. Put the music in a pause state.
 *
 */
void PlayListTableau::onMenuEventPause(wxCommandEvent &WXUNUSED(event))
{
    if (MusicManagerSwitcher::getSearch().getMusicPlayer().isPlaying())
        MusicManagerSwitcher::getSearch().getMusicPlayer().setPause(true);
    else if (MusicManagerSwitcher::getSearch().getMusicPlayer().isPaused())
        MusicManagerSwitcher::getSearch().getMusicPlayer().setPause(false);
    else//Musique stoppée
        MusicManagerSwitcher::getSearch().playSameMusic();
}

/** @brief Event - Delete selected lines.
 *
 */
void PlayListTableau::onMenuEventDelete(wxCommandEvent &WXUNUSED(event))
{
    removeSelectedLines();
}

/** @brief Event. Cut&Paste scenario. Data placed in memory, Ctrl+X.
 *
 */
void PlayListTableau::onMenuEventCut(wxCommandEvent &WXUNUSED(event))
{
    long item = -1;
    item = GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    while (item != -1)
    {
        m_cutTitles.Add(wxString::Format(_T("%ld"), item));
        item = GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    }
    m_cut = true;
}

/** @brief Event. Cut&Paste scenario. Memorised data pasted, Ctrl+V.
 *
 */
void PlayListTableau::onMenuEventPaste(wxCommandEvent &WXUNUSED(event))
{
    MusicManagerSwitcher::getSearch().moveIntTitlesAt(m_cutTitles, m_yMenu/*, true*/);
    m_cutTitles.Clear();
    m_cut = false;
}

/** @brief Event. Show a dialogue with some data of the selected title.
 *
 */
void PlayListTableau::onMenuEventDetails(wxCommandEvent &WXUNUSED(event))
{
    wxCommandEvent evt(wxEVT_LISTE_DETAILS, GetId());
    GetParent()->GetEventHandler()->AddPendingEvent(evt);
}

/** @brief Removes selected lines.
 *
 */
void PlayListTableau::removeSelectedLines()
{
    wxMutexLocker lock(m_mutexListUpdating);
    if (GetItemCount() == 0)
        return;

    LogFileAppend("PlayListTableau::removeSelectedLines - Début");
    std::vector<unsigned long> selectedLines = getSelectedLines();

    if (selectedLines.empty())
        return;

    LogFileAppend(_T("PlayListTableau::SuppressionLigne - ") + wxString::Format(_T("%ld lignes"), selectedLines.size()));

    int lastSelectedLine = selectedLines.back() + 1;
    if (GetItemCount() >= lastSelectedLine)//Toujours avoir une ligne active
        SetItemState(lastSelectedLine, wxLIST_STATE_FOCUSED|wxLIST_STATE_SELECTED, wxLIST_STATE_FOCUSED|wxLIST_STATE_SELECTED);
    else
    {
        int lineToSelect = 0;
        if (selectedLines.size() > 1 && selectedLines.front() != 0)
        {
            bool found = false;
            std::vector<unsigned long>::iterator currentIter = selectedLines.begin();
            std::vector<unsigned long>::iterator nextIter = selectedLines.begin()+1;

            while (nextIter != selectedLines.end() && !found)
            {
                if (*nextIter - *currentIter > 1)
                {
                    lineToSelect = *currentIter + 1;
                    found = true;
                }
                ++currentIter;
                ++nextIter;
            }
        }
        SetItemState(lineToSelect, wxLIST_STATE_FOCUSED|wxLIST_STATE_SELECTED, wxLIST_STATE_FOCUSED|wxLIST_STATE_SELECTED);
    }

    MusicManagerSwitcher::getSearch().deleteTitleAt(selectedLines);

    SetFocus();

    LogFileAppend(_T("PlayListTableau::SuppressionLigne - Fin"));
}

/** @brief Event. Removes a music line in the list
 *
 * @param event an event
 * @return void
 *
 */
void PlayListTableau::onDeleteLine(wxCommandEvent& event)
{
    DeletedLines* deletedLines = static_cast<DeletedLines*>(event.GetClientData());
    const long position = MusicManagerSwitcher::getSearch().getDeletedLine(*deletedLines);
    removeLine(position);
}

/** @brief Event. Adds a music line in the list
 *
 * @param event an event
 * @return void
 *
 */
void PlayListTableau::onUpdateLine(wxCommandEvent& event)
{
    ///FIXME: Might be useless because events come from only one manager.
    wxMutexLocker lock(m_mutexListUpdating);
    Music* music = static_cast<Music*>(event.GetClientData());

    findSharedMusicContainer finder(*music);
    music::MusicCollection& musicCollection = MusicManagerSwitcher::getSearch().getMusics();
    MusicIterator iter = std::find_if(musicCollection.begin(),
                                    musicCollection.end(),
                                    finder);

    if (iter == musicCollection.end())
        return;

    const int position = std::distance(musicCollection.begin(), iter);
    addLineThread(**iter, position);
    updateColor(position);
}

/** @brief Collects selected lines
 *
 * @return an array of positions
 *
 */
std::vector<unsigned long> PlayListTableau::getSelectedLines()
{
    std::vector<unsigned long> selectedItemsPosition;
    long index = GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

    while (index != -1)
    {
        selectedItemsPosition.push_back(index);
        index = GetNextItem(index, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    }
    return selectedItemsPosition;
}


