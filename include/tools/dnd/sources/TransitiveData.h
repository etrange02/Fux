#ifndef TRANSITIVEDATA_H
#define TRANSITIVEDATA_H

#include <vector>
#include "tools/dnd/targets/TransitiveDataTarget.h"

namespace dragAndDrop
{
    template<typename T>
    class TransitiveData
    {
        public:
            /** Default constructor */
            TransitiveData() :
                m_isCopy(false),
                m_target(nullptr)
            {
                //ctor
            }

            /** Default destructor */
            virtual ~TransitiveData()
            {
                //dtor
            }

            /** Copy constructor
             *  \param other Object to copy from
             */
            TransitiveData(const TransitiveData& other)
            {
                *this = other;
            }

            /** Assignment operator
             *  \param rhs Object to assign from
             *  \return A reference to this
             */
            TransitiveData& operator=(const TransitiveData<T>& rhs)
            {
                if (this == &rhs) return *this; // handle self assignment
                //assignment operator

                m_items     = rhs.m_items;
                m_isCopy    = rhs.m_isCopy;
                m_target    = rhs.m_target;

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

            void setDestination(TransitiveDataTarget& target)
            {
                m_target = &target;
            }

            virtual void doPaste() = 0;

        protected:
            void setCopy(const bool isCopy)
            {
                m_isCopy = isCopy;
            }
            bool isCopy() const;

            virtual bool isSameKind() const = 0;
            virtual void doCopy() = 0;
            virtual void doCut() = 0;

        private:
            std::vector<T> m_items;
            bool m_isCopy;
            dragAndDrop::TransitiveDataTarget* m_target;
    };
}

#endif // TRANSITIVEDATA_H
