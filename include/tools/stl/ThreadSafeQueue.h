#ifndef THREADSAFEQUEUE_H
#define THREADSAFEQUEUE_H

#include <queue>

namespace std
{
    template<typename T, typename _Sequence = deque<T> >
    class ThreadSafeQueue
    {
        public:
            typedef typename _Sequence::value_type                value_type;
            typedef typename _Sequence::reference                 reference;
            typedef typename _Sequence::const_reference           const_reference;
            typedef typename _Sequence::size_type                 size_type;
            typedef          _Sequence                            container_type;

        public:
            /** Default constructor */
            ThreadSafeQueue()
            {}

            /** Default destructor */
            virtual ~ThreadSafeQueue()
            {}

            /** Copy constructor
             *  \param other Object to copy from
             */
            ThreadSafeQueue(const ThreadSafeQueue<T>& other)
            {
                this = other;
            }

            /** Assignment operator
             *  \param other Object to assign from
             *  \return A reference to this
             */
            ThreadSafeQueue& operator=(const ThreadSafeQueue<T>& other)
            {
                if (this == &other) return *this; // handle self assignment
                this->m_internalQueue = other.m_internalQueue;
                return *this;
            }

            /**  Returns the number of elements in the %queue.  */
            size_type size() const
            { return m_internalQueue.size(); }

            void push(const value_type& value)
            { m_internalQueue.push(value); }

            void pop()
            { m_internalQueue.pop(); }

            bool empty() const
            { return m_internalQueue.empty(); }

            value_type& pop_front()
            {
                value_type& val = front();
                pop();
                return val;
            }

            reference front()
            { return m_internalQueue.front(); }

            const_reference front() const
            { return m_internalQueue.front(); }

        private:
            std::queue<T> m_internalQueue;
    };
}

#endif // THREADSAFEQUEUE_H
