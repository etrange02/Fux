#ifndef IRUNNABLE_H
#define IRUNNABLE_H

/** @brief Interface for threaded treatments
 * Interface for threaded treatments
 * @class fux::thread::IRunnable
 */

namespace fux
{
    namespace thread
    {
        class IRunnable
        {
            public:
                /**
                 * Launches treatment that can be done in a different thread
                 */
                virtual void process() = 0;
        };
    }
}

#endif // IRUNNABLE_H
