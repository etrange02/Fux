/***************************************************************
 * Name:      DirDriveManagerState.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2014-11-19
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "explorer/state/DirDriveManagerState.h"
#include <wx/dir.h>
#include "Parametre.h"
#include "explorer/ExplorerFactory.h"
#include "explorer/ExplorerManagerData.h"
#include "explorer/ExplorerDriveManagers.h"
#include "music/MusicManagerSwitcher.h"
#include "tools/thread/ThreadManager.h"
#include "tools/thread/ThreadFactory.h"
#include "tools/dnd/dataObjects/DirTransitiveData.h"
#include "tools/dnd/targets/DirTransitiveDataTarget.h"
#include "tools/dir/DirFileManager.h"

using namespace explorer;

DirDriveManagerState::DirDriveManagerState(ExplorerManagerData& data) :
    DriveManagerState(data)
{
    gui::explorer::ExplorerListCtrl& listCtrl = data.getExplorerPanel().getExplorerListCtrl();
    m_transitiveDataTarget = new dragAndDrop::DirTransitiveDataTarget(listCtrl, data.getPath(), data.getExplorerDriveManagers().getDirFileManager());
    listCtrl.SetDropTarget(m_transitiveDataTarget);
}

DirDriveManagerState::~DirDriveManagerState()
{
    //dtor
    // Deletion done by GUI
    //delete m_transitiveDataTarget;
}

bool DirDriveManagerState::isDirectory() const
{
    return true;
}

bool DirDriveManagerState::fillExplorerList()
{
    if (!wxDirExists(m_data.getPath()))
        return false;

    const bool hidden = m_data.getExplorerPanel().isHiddenFilesChecked();
    const bool filtre = m_data.getExplorerPanel().isFilterActivated();
    wxString filename;
    wxDir repertoire(m_data.getPath());

    m_data.getExplorerPanel().getExplorerListCtrl().DeleteAllItems();
    m_data.getElements().clear();

    //Dossiers
    bool cont = (hidden) ? repertoire.GetFirst(&filename, wxEmptyString, wxDIR_DIRS | wxDIR_HIDDEN) : repertoire.GetFirst(&filename, wxEmptyString, wxDIR_DIRS);
    while (cont)
    {
        addDriveManagerListElement(repertoire.GetNameWithSep() + filename);
        m_data.getExplorerPanel().getExplorerListCtrl().addDir(filename);
        cont = repertoire.GetNext(&filename);
    }

    //Fichiers
    cont = (hidden) ? repertoire.GetFirst(&filename, wxEmptyString, wxDIR_FILES | wxDIR_HIDDEN) : repertoire.GetFirst(&filename, wxEmptyString, wxDIR_FILES);
    if (filtre)
    {
        while (cont)
        {
            if (Parametre::Get()->islisable(filename) || Parametre::get().isContainerFile(filename))
            {
                addDriveManagerListElement(repertoire.GetNameWithSep() + filename);
                m_data.getExplorerPanel().getExplorerListCtrl().addFile(filename);
            }
            cont = repertoire.GetNext(&filename);
        }
    }
    else
    {
        while (cont)
        {
            addDriveManagerListElement(repertoire.GetNameWithSep() + filename);
            m_data.getExplorerPanel().getExplorerListCtrl().addFile(filename);
            cont = repertoire.GetNext(&filename);
        }
    }
    //m_data.getExplorerPanel().getExplorerListCtrl().selectLine(0);
    m_data.getExplorerPanel().setTexts("Dossier", m_data.getPath());

    //SetFocus();
    //wxCommandEvent evt(wxEVT_LISTE_RENEW);
    //GetParent()->GetEventHandler()->AddPendingEvent(evt);
    return true;
}

bool DirDriveManagerState::fillExplorerList(const wxString& elementToSelect)
{
    bool result = fillExplorerList();
    m_data.getExplorerPanel().getExplorerListCtrl().selectLine(elementToSelect);
    return result;
}

DriveManagerState& DirDriveManagerState::getPreviousState()
{
    const wxString path = m_data.getPath().BeforeLast(wxFileName::GetPathSeparator());
    if (wxDirExists(path))
        return *this;
    return *(explorer::ExplorerFactory::createDefaultDriveManagerState(m_data, true));
}

void DirDriveManagerState::openElement()
{
    std::vector<unsigned long> indexes = m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines();
    if (indexes.empty() || indexes.at(0) >= m_data.getElements().size())
        return;

    const wxString& path = m_data.getElements().at(indexes.at(0)).getFilename();

    if (Parametre::get().isID3V2(path))
    {
        music::MusicManagerSwitcher::get().parse(convertPositionToString(indexes));
        //MusicManagerSwitcher::get().playMusic(path);
    }
    else if (Parametre::get().isContainerFile(path))
    {
        m_data.setPath(path);
        explorer::DriveManagerState& newState = *(explorer::ExplorerFactory::createFileDriveManagerState(m_data));
        newState.fillExplorerList();
        m_data.setState(newState);
    }
    else
    {
        m_data.setPath(path);
        m_transitiveDataTarget->setDirectory(path);
        fillExplorerList();
    }
}

void DirDriveManagerState::deleteSelectedItems()
{
    tools::thread::ThreadManager::get().addRunnable(tools::thread::ThreadFactory::createFileDeletionThread(getSelectedItems()));
}

bool DirDriveManagerState::canCopyTo(const DriveManagerState& other) const
{
    return !this->getPath().IsSameAs(other.getPath());
}

bool DirDriveManagerState::canMoveTo(const DriveManagerState& other) const
{
    return other.isDirectory() && !this->getPath().IsSameAs(other.getPath());
}

bool DirDriveManagerState::canDeleteSelectedItems() const
{
    return !m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines().empty();
}

bool DirDriveManagerState::canSelectAll() const
{
    return true;
}

bool DirDriveManagerState::canCreateDir() const
{
    return true;
}

bool DirDriveManagerState::canCreateContainerFile() const
{
    return true;
}

bool DirDriveManagerState::canPlayItems() const
{
    return !m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines().empty();
}

bool DirDriveManagerState::canRename() const
{
    return !m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines().empty();
}

bool DirDriveManagerState::canCreateShortcut() const
{
    return !m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines().empty();
}

void DirDriveManagerState::copyElements(DriveManagerState& source)
{
    wxArrayString filenames = source.getSelectedItems();
    wxString destinationPath = m_data.getPath();
    tools::dir::DirFileManager* dirFileManager = m_data.getExplorerDriveManagers().getDirFileManager();

    if (NULL == dirFileManager)
        return;
    for (wxArrayString::iterator iter = filenames.begin(); iter != filenames.end(); ++iter)
    {
        wxString& source = *iter;
        wxString destination = destinationPath + wxFileName::GetPathSeparator() + wxFileName::FileName(source).GetFullName();
        dirFileManager->createCopyOperation(source, destination);
    }
}

void DirDriveManagerState::moveElements(DriveManagerState& source)
{
    wxArrayString filenames = source.getSelectedItems();
    wxString destinationPath = m_data.getPath();
    tools::dir::DirFileManager* dirFileManager = m_data.getExplorerDriveManagers().getDirFileManager();

    if (NULL == dirFileManager)
        return;
    for (wxArrayString::iterator iter = filenames.begin(); iter != filenames.end(); ++iter)
    {
        wxString& source = *iter;
        wxString destination = destinationPath + wxFileName::GetPathSeparator() + wxFileName::FileName(source).GetFullName();
        dirFileManager->createCutOperation(source, destination);
    }
}

void DirDriveManagerState::createDir()
{
    wxTextEntryDialog dialog(&m_data.getExplorerPanel(), _("Nom du nouveau dossier"), _("Création de dossier"));

    if (dialog.ShowModal() == wxID_OK)
    {
        wxString dirname = m_data.getPath();
        dirname << wxFileName::GetPathSeparator() << dialog.GetValue();

        if (wxDirExists(dirname))
        {
            wxLogWarning(_("Dossier déjà existant, opération annulée"));
            return;
        }
        if (!wxMkdir(dirname))
            wxLogError(_("Création impossible"));
        else
        {
            gui::explorer::ExplorerPanel& panel = m_data.getExplorerPanel();
            panel.refreshListCtrl();
            panel.getExplorerListCtrl().selectLine(dialog.GetValue());
        }
    }
}

void DirDriveManagerState::createContainerFile()
{
    wxLogMessage("createContainerFile - Must be implemented.");
    ///TODO (David): DirDriveManagerState::createContainerFile
    /*
    - Demander le nom du fichier m3u, pré-remplir avec le nom du répertoire courant
    - Créer le fichier m3u dans le répertoire habituel
    - Demander de le charger dans l'autre écran
    - Importer automatiquement les lignes sélectionnées dans la colonne de gauche. titres et sous-répertoires
    */
}

void DirDriveManagerState::playItems()
{
    wxLogMessage("playItems - Must be implemented.");
    ///TODO (David): DirDriveManagerState::playItems
    /*
    - Charger les titres sélectionnés.
    */
}

void DirDriveManagerState::rename()
{
    wxLogMessage("rename - Must be implemented.");
    ///TODO (David): DirDriveManagerState::rename
    /*
    - Renommer le premier de la liste
    - Modifier le texte de la ligne sélectionné
    - Si fichier musical, passer par le thread de renommage et transmettre l'info au MusicManager
    - Mettre à jour les m3u sous contrôle
    */
}

void DirDriveManagerState::createShortcut()
{
    wxLogMessage("createShortcut - Must be implemented.");
    ///TODO (David): DirDriveManagerState::createShortcut
    /*
    - Créer un raccourci. Rennomer la class en tools...
    */
}

dragAndDrop::TransitiveData* DirDriveManagerState::getDraggedElements()
{
    dragAndDrop::DirTransitiveData* transitiveData = new dragAndDrop::DirTransitiveData;
    wxArrayString selectedLines = getSelectedItems();
    for (wxArrayString::iterator it = selectedLines.begin(); it != selectedLines.end(); ++it)
        transitiveData->add(*it);

    return transitiveData;
}


