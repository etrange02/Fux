/***************************************************************
 * Name:      Runnable.cpp
 * Purpose:   Code for Fu(X) 2.0
 * Author:    David Lecoconnier (david.lecoconnier@free.fr)
 * Created:   2016-02-25
 * Copyright: David Lecoconnier (http://www.getfux.fr)
 * License:
 **************************************************************/
#include "Runnable.h"

using namespace tools::thread;

/** @brief Default constructor. Priority of 50.
 */
Runnable::Runnable() : IRunnable(),
    m_priority(50)
{
    //ctor
}

/** @brief Destructor.
 */
Runnable::~Runnable()
{
    //dtor
}

/** @brief
 *
 * @param other const Runnable&
 * @return bool
 *
 */
bool Runnable::operator<(const Runnable& other)
{
    return this->getPriority() < other.getPriority();
}

/** @brief
 *
 * @return int
 *
 */
int Runnable::getPriority() const
{
    return m_priority;
}

/** @brief
 *
 * @param priority int
 * @return void
 *
 */
void Runnable::setPriority(int priority)
{
    m_priority = priority;
}

