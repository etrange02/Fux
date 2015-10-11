/***************************************************************
 * Name:      DirTransitiveDataTarget.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-06-26
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/dnd/targets/DirTransitiveDataTarget.h"
#include "tools/dnd/dataObjects/DirTransitiveData.h"
#include <wx/filename.h>
#include "tools/dir/DirFileManager.h"

using namespace dragAndDrop;

/** @brief Constructor.
 */
DirTransitiveDataTarget::DirTransitiveDataTarget(DroppedMarkedLineListCtrl& source, const wxString& directory, tools::dir::DirFileManager* dirFileManager) :
    TransitiveDataTarget(source),
    m_directory(directory),
    m_dirFileManager(dirFileManager)
{
}

/** @brief Destructor.
 */
DirTransitiveDataTarget::~DirTransitiveDataTarget()
{
}

void DirTransitiveDataTarget::setDirectory(const wxString& directory)
{
    m_directory = directory;
}

bool DirTransitiveDataTarget::isSameKind() const
{
    if (m_data == NULL)
        return false;
    return m_data->isDirKind();
}

void DirTransitiveDataTarget::doCopyProcessing(const wxArrayString& data, const long position)
{
    if (NULL == m_dirFileManager)
        return;
    wxString destinationPath = m_directory;
    if (position >= 0 && position < m_source.GetItemCount())
    {
        wxFileName filename(m_directory, m_source.GetItemText(position));
        if (filename.Exists())
            destinationPath = filename.GetFullPath();
    }

    for (wxArrayString::const_iterator iter = data.begin(); iter != data.end(); ++iter)
    {
        const wxString& source = *iter;
        wxString destination = destinationPath + wxFileName::GetPathSeparator() + wxFileName::FileName(source).GetFullName();
        m_dirFileManager->createCopyOperation(source, destination);
    }
}

void DirTransitiveDataTarget::doCutProcessing(TransitiveData& transitiveData, const long position)
{
    if (NULL == m_dirFileManager)
        return;
    wxString destinationPath = m_directory;
    if (position >= 0 && position < m_source.GetItemCount())
    {
        wxFileName filename(m_directory, m_source.GetItemText(position));
        if (filename.Exists())
            destinationPath = filename.GetFullPath();
    }

    DirTransitiveData& fileTransitiveData = static_cast<DirTransitiveData&>(transitiveData);
    wxArrayString filenames = fileTransitiveData.getFilenames();
    for (wxArrayString::iterator iter = filenames.begin(); iter != filenames.end(); ++iter)
    {
        wxString& source = *iter;
        wxString destination = destinationPath + wxFileName::GetPathSeparator() + wxFileName::FileName(source).GetFullName();
        m_dirFileManager->createCutOperation(source, destination);
    }
}




