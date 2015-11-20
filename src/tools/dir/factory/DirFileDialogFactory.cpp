/***************************************************************
 * Name:      DirFileDialogFactory.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-10-22
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/dir/factory/DirFileDialogFactory.h"
#include "tools/dir/interface/DirFileDialogEvent.h"
#include "tools/dir/interface/RepeatedQuestionDialogEvent.h"

using namespace tools::dir;

/** @brief Constructor.
 */
DirFileDialogFactory::DirFileDialogFactory(wxWindow& parent) :
    DirFileCommunicationFactory(),
    m_parent(parent)
{
    //ctor
}

/** @brief Destructor.
 */
DirFileDialogFactory::~DirFileDialogFactory()
{
    //dtor
}

/** @brief
 *
 * @return DirFileUserInterface*
 *
 */
DirFileUserInterface* DirFileDialogFactory::createDirFileUser()
{
    return new DirFileDialogEvent(m_parent);
}

/** @brief
 *
 * @return RepeatedQuestionInterface*
 *
 */
RepeatedQuestionInterface* DirFileDialogFactory::createRepeatedQuestion()
{
    return new RepeatedQuestionDialogEvent(m_parent);
}



