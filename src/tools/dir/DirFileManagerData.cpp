/***************************************************************
 * Name:      DirFileManagerData.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2015-08-07
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "tools/dir/DirFileManagerData.h"

using namespace tools::dir;

/** @brief Constructor.
 */
DirFileManagerData::DirFileManagerData() :
    m_recurseHasBeenAsked(false),
    m_recursive(false)
{
    //ctor
}

/** @brief Destructor.
 */
DirFileManagerData::~DirFileManagerData()
{
    //dtor
}

/** @brief Indicates if the operation can be done.
 *
 * @return bool
 *
 */
bool DirFileManagerData::isRecursive() const
{
    return m_recursive;
}

/** @brief Modifies the recursive mode.
 *
 * @param recursive bool
 * @return void
 *
 */
void DirFileManagerData::setRecursive(bool recursive)
{
    m_recursive = recursive;
}

/** @brief Indicates if the problem has been checked by user for all cases.
 *
 * @return bool
 *
 */
bool DirFileManagerData::isRecursiveAsked() const
{
    return m_recurseHasBeenAsked;
}

/** @brief Modifies the question asked for all cases.
 *
 * @return void
 *
 */
void DirFileManagerData::setRecursiveAsked()
{
    m_recurseHasBeenAsked = true;
}


