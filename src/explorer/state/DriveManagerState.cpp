/***************************************************************
 * Name:      DriveManagerState.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2014-11-19
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "explorer/state/DriveManagerState.h"
#include "explorer/ExplorerManagerData.h"
#include "explorer/ExplorerDriveManagers.h"
#include "settings/Parametre.h"
#include "tools/dir/DirFileManager.h"
#include "GUI/explorer/state/DirCreationDialog.h"

using namespace explorer;

DriveManagerState::DriveManagerState(ExplorerManagerData& data) :
    m_data(data)
{
    //ctor
}

DriveManagerState::~DriveManagerState()
{
    //dtor
}

bool DriveManagerState::isDefault() const
{
    return false;
}

bool DriveManagerState::isDirectory() const
{
    return false;
}

bool DriveManagerState::isFile() const
{
    return false;
}

bool DriveManagerState::isPlaylist() const
{
    return false;
}

void DriveManagerState::addDriveManagerListElement(const wxString& filename)
{
    DriveManagerListElement element;
    element.setFilename(filename);
    m_data.getElements().push_back(element);
}

wxArrayString DriveManagerState::convertPositionToString(const std::vector<unsigned long>& indexes)
{
    const size_t length = m_data.getElements().size();
    wxArrayString names;

    for (std::vector<unsigned long>::const_iterator it = indexes.begin(); it != indexes.end(); ++it)
    {
        if (*it < length)
            names.push_back(m_data.getElements().at(*it).getFilename());
    }
    return names;
}

bool DriveManagerState::isSameKind(const DriveManagerState& other) const
{
    return     isDefault()   == other.isDefault()
            && isDirectory() == other.isDirectory()
            && isPlaylist()  == other.isPlaylist()
            && isFile()      == other.isFile();
}

const wxString& DriveManagerState::getPath() const
{
    return m_data.getPath();
}

wxArrayString DriveManagerState::getSelectedItems()
{
    return convertPositionToString(m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines());
}

wxArrayString DriveManagerState::getSelectedItemsPosition()
{
    wxArrayString positions;
    std::vector<unsigned long> longPosition = m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines();
    for (std::vector<unsigned long>::iterator iter = longPosition.begin(); iter != longPosition.end(); ++iter)
        positions.Add(wxString::Format("%d", *iter));
    return positions;
}

void DriveManagerState::createContainerFile(ExplorerManager& explorerManager)
{
    wxTextEntryDialog dialog(&m_data.getExplorerPanel(), _("Saisissez le nom du fichier m3u :"), wxGetTextFromUserPromptStr, m_data.getPath().AfterLast('\\'));

    if (dialog.ShowModal() != wxID_OK)
        return;

    const wxString containerFileName = dialog.GetValue();

    wxString path = Parametre::get().getRepertoireParametre(_T("Play_list_M3U"), containerFileName);

    if (!Parametre::get().isContainerFile(path))
        path.Append(_T(".m3u"));

    wxTextFile file(path);
    if (file.Exists())
    {
        wxMessageBox(_("Fichier existant"));
        return;
    }
    file.Create();

    file.AddLine(M3U_EXTENSION);
    /*std::vector<unsigned long> selectedLines = m_data.getExplorerPanel().getExplorerListCtrl().getSelectedLines();
    for (std::vector<unsigned long>::iterator iter = selectedLines.begin(); iter != selectedLines.end(); ++iter)
    {
        wxString filename = m_data.getElements().at(*iter).getFilename();
        if (Parametre::get().islisable(filename))
            file.AddLine(filename);
    }*/
    wxArrayString selectedLines = getSelectedItems();
    for (wxArrayString::iterator iter = selectedLines.begin(); iter != selectedLines.end(); ++iter)
    {
        if (Parametre::get().islisable(*iter))
            file.AddLine(*iter);
    }
    file.Write();
    file.Close();

    wxMessageDialog question(&m_data.getExplorerPanel(), _("Autre côté ?"), wxMessageBoxCaptionStr, wxYES_NO|wxCENTRE);
    if (wxID_YES == question.ShowModal())
    {
        ExplorerManager& otherExplorerManager = m_data.getExplorerDriveManagers().getOppositeExplorerManager(explorerManager);
        m_data.getExplorerDriveManagers().setFileState(otherExplorerManager.getExplorerPanel(), path);
    }
}

void DriveManagerState::createDir(ExplorerManager& explorerManager)
{
    tools::dir::DirFileManager* dirFileManager = m_data.getExplorerDriveManagers().getDirFileManager();
    if (NULL == dirFileManager)
        return;

    ExplorerManager& otherExplorerManager = m_data.getExplorerDriveManagers().getOppositeExplorerManager(explorerManager);

    DirCreationDialog dialog(&m_data.getExplorerPanel());
    if (otherExplorerManager.getState().isDirectory())
        dialog.setDirPath(otherExplorerManager.getState().getPath());
    dialog.setDirName(m_data.getPath().AfterLast(wxFileName::GetPathSeparator()));

    if (wxID_OK != dialog.ShowModal())
        return;

    if (!dialog.isDataOK())
    {
        return;
    }

    wxString dirName = dialog.getFullPath();
	if (!wxMkdir(dirName))
    {
        wxMessageBox(_("Impossible de créer le nouveau répertoire."));
        return;
    }

    wxArrayString filenames = getSelectedItems();

    for (wxArrayString::iterator iter = filenames.begin(); iter != filenames.end(); ++iter)
    {
        wxString& sourceName = *iter;
        wxString destination = dirName + wxFileName::GetPathSeparator() + wxFileName::FileName(sourceName).GetFullName();
        dirFileManager->createCopyOperation(sourceName, destination);
    }

    if (dialog.isShowInOtherExplorer())
        m_data.getExplorerDriveManagers().setDirState(otherExplorerManager.getExplorerPanel(), dirName);
    else if (dialog.isShowInSameExplorer())
        m_data.getExplorerDriveManagers().setDirState(explorerManager.getExplorerPanel(), dirName);
}

