#ifndef DIRFILECOMMUNICATIONFACTORY_H
#define DIRFILECOMMUNICATIONFACTORY_H


/**
 * Name space of tools
 */
namespace tools
{
    namespace dir
    {
        class DirFileUserInterface;
        class RepeatedQuestionInterface;

        class DirFileCommunicationFactory
        {
            public:
                /** Default destructor */
                virtual ~DirFileCommunicationFactory() {}

                virtual DirFileUserInterface*      createDirFileUser() = 0;
                virtual RepeatedQuestionInterface* createRepeatedQuestion() = 0;

            protected:
                /** Default constructor */
                DirFileCommunicationFactory() {}
                DirFileCommunicationFactory(DirFileCommunicationFactory&) {}

            private:
        };
    }
}

#endif // DIRFILECOMMUNICATIONFACTORY_H
