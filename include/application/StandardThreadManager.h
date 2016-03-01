#ifndef STANDARDTHREADMANAGER_H
#define STANDARDTHREADMANAGER_H

#include "tools/thread/ThreadManager.h"

/** @brief Default thread manager. Uses available cores
 * Manages thread on different cores. Producer-Consumer model
 * @class thread::StandardThreadManager
 */

namespace thread
{
    class StandardThreadManager : public tools::thread::ThreadManager
    {
        public:
            /** Singleton */
            static StandardThreadManager& get();

            /** Deletes the instance */
            void deleteInstance();

        protected:

        private:
            /** Default constructor */
            StandardThreadManager();
            /** Default destructor */
            virtual ~StandardThreadManager();
    };
}

#endif // STANDARDTHREADMANAGER_H
