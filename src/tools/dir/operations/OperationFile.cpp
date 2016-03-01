/***************************************************************
 * Name:      OperationFile.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-08-07
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/dir/operations/OperationFile.h"
#include "tools/dir/DirFileManagerData.h"
#include "tools/dir/factory/DirFileCommunicationFactory.h"
#include "tools/dir/interface/RepeatedQuestionInterface.h"
//#include "tools/dir/interface/RepeatedQuestionDialog.h"
#include "tools/dir/AskForRecursiveOperationData.h"
#include <wx/filename.h>

using namespace tools::dir;

/** @brief Constructor.
 */
OperationFile::OperationFile(const wxString& source) :
    tools::thread::Runnable(),
    m_source(source),
    m_thread(NULL),
    m_factory(NULL)
{
    //ctor
}

/** @brief Destructor.
 */
OperationFile::~OperationFile()
{
    //dtor
}

/** @brief Returns the file source
 *
 * @return const wxString&
 *
 */
const wxString& OperationFile::getSource() const
{
    return m_source;
}

/** @brief Returns a description of the operation
 *
 * @return wxString
 *
 */
wxString OperationFile::operationName() const
{
    return _("Aucune opération en cours");
}

/** @brief Processes operation. Must be overloaded.
 *
 * @return void
 *
 */
void OperationFile::process()
{
    doOperation();
    sendEvent();
}

/** @brief Displays a dialogue get information from the user. Also ask to be shown again.
 *
 * @param data DirFileManagerData&
 * @param message const wxString&
 * @return bool
 *
 */
bool OperationFile::askForRecursiveOperation(DirFileManagerData& data, const wxString& message)
{
    if (data.isRecursiveAsked())
        return data.isRecursive();

    AskForRecursiveOperationData recursiveData(m_thread, message);
    /// Sets default values - Nothing to do

    /// Sends event
    #ifndef DEBUG
    if (m_factory)
    {
        RepeatedQuestionInterface* rqInterface = m_factory->createRepeatedQuestion();
        rqInterface->askQuestion(recursiveData);
        delete rqInterface;
    }
    #else
    {
        wxMessageDialog dialog(NULL, recursiveData.getMessage(), _("Confirmation"), wxOK|wxCANCEL|wxCENTRE);
        int answer = dialog.ShowModal();

        recursiveData.setOverWrite(answer == wxID_OK);
        recursiveData.setRecursive(false);
    }
    #endif

    /// Reads default values
    if (recursiveData.isRecursive())
    {
        data.setRecursiveAsked();
        data.setRecursive(recursiveData.canBeOverWritten());
    }

    return recursiveData.canBeOverWritten();
}

wxString OperationFile::getSourceFilename() const
{
    return getSource().AfterLast(wxFileName::GetPathSeparator());
}

/** @brief Modifies the thread processing the operation
 *
 * @param thread tools::thread::ThreadProcess*
 * @return void
 *
 */
void OperationFile::setThread(tools::thread::ThreadProcess* thread)
{
    m_thread = thread;
}

/** @brief Modifies the factory to create objects...
 *
 * @param factory DirFileCommunicationFactory*
 * @return void
 *
 */
void OperationFile::setFactory(DirFileCommunicationFactory* factory)
{
    m_factory = factory;
}


