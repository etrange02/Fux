#ifndef RUNNABLE_H
#define RUNNABLE_H

#include "IRunnable.h"

/**
 * Name space of tools
 */
namespace tools
{
    /**
     * Name space of multi-threading tools
     */
    namespace thread
    {
        /** @brief Container of a task.
         */
        class Runnable : public IRunnable
        {
            public:
                /** Default constructor */
                Runnable();
                /** Default destructor */
                virtual ~Runnable();

                bool operator<(const Runnable& other);

                virtual void process() = 0;

                int getPriority() const;
                void setPriority(int priority);

            protected:

            private:
                int m_priority;
        };
    }
}

#endif // RUNNABLE_H
