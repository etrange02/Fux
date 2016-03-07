#ifndef FILEVALIDATOR_H
#define FILEVALIDATOR_H

#include <wx/valtext.h>

/**
 * Name space of tools
 */
namespace tools
{
    /**
     * Name space of validator tools
     */
    namespace validator
    {
        /** @brief Validate a file name.
         */
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
