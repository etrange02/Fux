#ifndef REPEATEDQUESTIONINTERFACE_H
#define REPEATEDQUESTIONINTERFACE_H


/**
 * Name space of tools
 */
namespace tools
{
    namespace dir
    {
        class AskForRecursiveOperationData;

        class RepeatedQuestionInterface
        {
            public:
                /** Default destructor */
                virtual ~RepeatedQuestionInterface() {}

                virtual void askQuestion(AskForRecursiveOperationData& data) = 0;

            protected:
                /** Default constructor */
                RepeatedQuestionInterface() {}
                RepeatedQuestionInterface(const RepeatedQuestionInterface&) {}

            private:
        };
    }
}

#endif // REPEATEDQUESTIONINTERFACE_H
