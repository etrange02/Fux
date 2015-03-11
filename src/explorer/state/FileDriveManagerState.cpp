/***************************************************************
 * Name:      FileDriveManagerState.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2014-11-19
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "explorer/state/FileDriveManagerState.h"
#include "MusicManagerSwitcher.h"
#include <wx/textfile.h>
#include "explorer/ExplorerManagerData.h"
#include "explorer/ExplorerFactory.h"

using namespace explorer;

FileDriveManagerState::FileDriveManagerState(ExplorerManagerData& data) :
    DriveManagerState(data)
{
    //ctor
}

FileDriveManagerState::~FileDriveManagerState()
{
    //dtor
}

bool FileDriveManagerState::isFile()
{
    return true;
}

bool FileDriveManagerState::fillExplorerList()
{
    wxTextFile file(m_data.getPath());
    if (!file.Exists() || !file.Open())
        return false;

    wxString filename;
    const size_t max = file.GetLineCount();

    m_data.getExplorerPanel().getExplorerListCtrl().DeleteAllItems();
    m_data.getElements().clear();

    int debut = 0;

    for (size_t i = debut; i < max; i++)
    {
        filename = file.GetLine(i);

        if (wxFileExists(filename))
            m_data.getExplorerPanel().getExplorerListCtrl().addFile(filename);
        else
            m_data.getExplorerPanel().getExplorerListCtrl().addInexistantFile(filename);
        addDriveManagerListElement(filename);
    }
    file.Close();

    m_data.getExplorerPanel().setTexts("Ficher m3u", m_data.getPath());
    //SetFocus();
    //wxCommandEvent evt(wxEVT_LISTE_RENEW);
    //GetParent()->GetEventHandler()->AddPendingEvent(evt);
    return true;
}

bool FileDriveManagerState::fillExplorerList(const wxString& elementToSelect)
{
    fillExplorerList();
    return true;
}

DriveManagerState& FileDriveManagerState::getPreviousState()
{
    return *(explorer::ExplorerFactory::createDirDriveManagerState(m_data));
}

void FileDriveManagerState::openElement(const std::vector<long>& indexes)
{
    MusicManagerSwitcher::get().parse(convertPositionToString(indexes));
}




