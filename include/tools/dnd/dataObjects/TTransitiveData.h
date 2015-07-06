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
            TTransitiveData() :
                m_isCopy(false)
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
                m_isCopy    = rhs.m_isCopy;

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

            virtual const wxString getName() const = 0;

        protected:
            void setCopy(const bool copy)
            {
                m_isCopy = copy;
            }
            bool isCopy() const
            {
                return m_isCopy;
            }

            virtual bool isSameKind() const = 0;
            virtual void doCopy() = 0;
            virtual void doCut() = 0;

        private:
            std::vector<T> m_items;
            bool m_isCopy;
    };
}

#endif // TTRANSITIVEDATA_H
