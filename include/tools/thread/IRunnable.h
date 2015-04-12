#ifndef IRUNNABLE_H
#define IRUNNABLE_H

/** @brief Interface for threaded treatments
 * Interface for threaded treatments
 * @class tools::thread::IRunnable
 */

namespace tools
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
