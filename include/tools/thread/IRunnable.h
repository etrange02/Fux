#ifndef IRUNNABLE_H
#define IRUNNABLE_H

/** @brief Interface for threaded treatments
 * Interface for threaded treatments
 * @class tools::thread::IRunnable
 */

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
        /** @brief Interface of a thread-able task.
         */
        class IRunnable
        {
            public:
                virtual ~IRunnable() {}
                /**
                 * Launches treatment that can be done in a different thread
                 */
                virtual void process() = 0;
        };
    }
}

#endif // IRUNNABLE_H
