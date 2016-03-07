#ifndef DIALOGDIRFILEDIALOGFACTORY_H
#define DIALOGDIRFILEDIALOGFACTORY_H

#include <wx/wx.h>
#include "tools/dir/factory/DirFileCommunicationFactory.h"

/**
 * Name space of tools
 */
namespace tools
{
    namespace dir
    {
        class DirFileDialogFactory : public DirFileCommunicationFactory
        {
            public:
                /** Default constructor */
                DirFileDialogFactory(wxWindow& parent);
                /** Default destructor */
                virtual ~DirFileDialogFactory();

                virtual DirFileUserInterface*      createDirFileUser();
                virtual RepeatedQuestionInterface* createRepeatedQuestion();

            protected:

            private:
                wxWindow& m_parent;
        };
    }
}

#endif // DIALOGDIRFILEDIALOGFACTORY_H
