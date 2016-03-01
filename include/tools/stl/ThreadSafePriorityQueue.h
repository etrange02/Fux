#ifndef THREADSAFEPRIORITYQUEUE_H
#define THREADSAFEPRIORITYQUEUE_H

#include <queue>
#include <wx/wx.h>
#include <wx/thread.h>
#include "FichierLog.h"

namespace std
{
    template <class T, class _Container = vector<T>,
            class _Compare = less<typename _Container::value_type> >
    class ThreadSafePriorityQueue
    {
        public:
            typedef typename _Container::value_type                value_type;
            typedef typename _Container::reference                 reference;
            typedef typename _Container::const_reference           const_reference;
            typedef typename _Container::size_type                 size_type;
            typedef          _Container                            container_type;

        public:
            /** Default constructor */
            ThreadSafePriorityQueue()
            {}

            /** Default destructor */
            virtual ~ThreadSafePriorityQueue()
            {}

            /** Copy constructor
             *  \param other Object to copy from
             */
            ThreadSafePriorityQueue(const ThreadSafePriorityQueue<T>& other)
            {
                wxMutexLocker lock(m_mutex);
                this = other;
            }

            /** Assignment operator
             *  \param other Object to assign from
             *  \return A reference to this
             */
            ThreadSafePriorityQueue& operator=(const ThreadSafePriorityQueue<T>& other)
            {
                if (this == &other) return *this; // handle self assignment
                wxMutexLocker lock(m_mutex);
                this->m_internalQueue = other.m_internalQueue;
                return *this;
            }

            /**  Returns the number of elements in the %queue.  */
            size_type size()
            {
                wxMutexLocker lock(m_mutex);
                return m_internalQueue.size();
            }

            /** Insert element */
            void push(const value_type& value)
            {
                wxMutexLocker lock(m_mutex);
                m_internalQueue.push(value);
            }

            /** Remove top element */
            void pop()
            {
                wxMutexLocker lock(m_mutex);
                m_internalQueue.pop();
            }

            /** Test whether container is empty */
            bool empty()
            {
                wxMutexLocker lock(m_mutex);
                FichierLog::Get()->Ajouter(wxString::Format("empty %s %d", m_internalQueue.empty() ? "true" : "false", m_internalQueue.size()));
                return m_internalQueue.empty();
            }

            /*const_reference pop_front()
            {
                wxMutexLocker lock(m_mutex);
                wxString str;

                while (!m_internalQueue.empty())
                {
                    const_reference val = m_internalQueue.top();
                    size_t length = m_internalQueue.size();
                    m_internalQueue.pop();

                    str.Append(wxString::Format("pop_front %p %d_%d\r\n", val, length, m_internalQueue.size()));
                }
                //FichierLog::Get()->Ajouter(wxString::Format("pop_front %p %d_%d", val, length, m_internalQueue.size()));
                FichierLog::Get()->Ajouter(str);
                return NULL;
            }*/

            /** Access top element */
            const_reference top()
            {
                wxMutexLocker lock(m_mutex);
                return m_internalQueue.top();
            }

            /** Construct and insert element */
            /*template <class... Args>
            void emplace(Args&&... args)
            {
                wxMutexLocker lock(m_mutex);
                m_internalQueue.emplace(args);
            }*/

            /** Swap contents */
            /*void swap(ThreadSafePriorityQueue& x) noexcept
            {
                wxMutexLocker lock(x.m_mutex);
                wxMutexLocker lock(m_mutex);
                m_internalQueue.swap(x);
            }*/

        private:
            std::priority_queue<T, _Container, _Compare> m_internalQueue;
            wxMutex m_mutex;
    };
}

#endif // THREADSAFEPRIORITYQUEUE_H
