/***************************************************************
 * Name:      RepeatedQuestionDialogEvent.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-10-22
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/dir/interface/RepeatedQuestionDialogEvent.h"
#include "tools/dir/AskForRecursiveOperationData.h"
#include "tools/thread/ThreadProcess.h"

using namespace tools::dir;

const wxEventType wxEVT_TOOLS_DIR_FILE_ASK_REC_QUESTION = wxNewEventType();

/** @brief Constructor.
 */
RepeatedQuestionDialogEvent::RepeatedQuestionDialogEvent(wxWindow& parent) :
    RepeatedQuestionInterface(),
    m_parent(parent)
{
    //ctor
}

/** @brief Destructor.
 */
RepeatedQuestionDialogEvent::~RepeatedQuestionDialogEvent()
{
    //dtor
}

/** @brief Sends an event to ask user to overwrite a file/directory. Waits until answered.
 *
 * @param data AskForRecursiveOperationData&
 * @return void
 *
 */
void RepeatedQuestionDialogEvent::askQuestion(AskForRecursiveOperationData& data)
{
    //data.m_threadProcess->Sleep(600);
    wxCommandEvent evt(wxEVT_TOOLS_DIR_FILE_ASK_REC_QUESTION);
    evt.SetClientData(&data);
    wxQueueEvent(&m_parent, evt.Clone());
    data.waitThread();
    //data.waitThread();
}

