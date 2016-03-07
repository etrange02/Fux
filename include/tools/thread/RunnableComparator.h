#ifndef RUNNABLECOMPARATOR_H
#define RUNNABLECOMPARATOR_H


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
        class ThreadProcess;

        /** @brief Priority organizer
         */
        class RunnableComparator
        {
            public:
                /** Compares two Runnable to order them according priority value.  */
                bool operator()(tools::thread::Runnable* left, tools::thread::Runnable* right)
                {
                    if (NULL == left || NULL == right)
                        wxLogMessage("pointeur nul");
                    return left->getPriority() <= right->getPriority();
                }
        };
    }
}
#endif // RUNNABLECOMPARATOR_H
