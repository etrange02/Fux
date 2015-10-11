#ifndef TTRANSITIVEDATA_H
#define TTRANSITIVEDATA_H

#include <vector>
#include "tools/dnd/dataObjects/TransitiveData.h"

namespace dragAndDrop
{
    template<typename T>
    class TTransitiveData : public TransitiveData
    {
        public:
            /** Default constructor */
            TTransitiveData()
            {
            }

            /** Default destructor */
            virtual ~TTransitiveData()
            {
            }

            /** Copy constructor
             *  \param other Object to copy from
             */
            TTransitiveData(const TTransitiveData& other)
            {
                *this = other;
            }

            /** Assignment operator
             *  \param rhs Object to assign from
             *  \return A reference to this
             */
            TTransitiveData& operator=(const TTransitiveData<T>& rhs)
            {
                if (this == &rhs)
                    return *this;

                m_items     = rhs.m_items;

                return *this;
            }

            void setCopy()
            {
                setCopy(true);
            }

            void setCut()
            {
                setCopy(false);
            }

            const std::vector<T>& getItems() const
            {
                return m_items;
            }

            void add(const T& item)
            {
                m_items.push_back(item);
            }

            void add(const std::vector<T>& items)
            {
                m_items.insert(m_items.end(), items.begin(), items.end());
            }

            virtual wxArrayString getFilenames() const = 0;

            virtual bool isEmpty() const
            {
                return m_items.empty();
            }

        protected:

        private:
            std::vector<T> m_items;
    };
}

#endif // TTRANSITIVEDATA_H
