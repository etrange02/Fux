#ifndef FILEVALIDATOR_H
#define FILEVALIDATOR_H

#include <wx/valtext.h>

namespace tools
{
    namespace validator
    {
        class FileValidator : public wxTextValidator
        {
            public:
                /** Default constructor */
                FileValidator(wxString* valPtr = NULL);
                /** Default destructor */
                virtual ~FileValidator();

            protected:

            private:
        };
    }
}

#endif // FILEVALIDATOR_H
