#ifndef DATABASERESPONSE_H
#define DATABASERESPONSE_H

#include <wx/wx.h>

/**
 * Name space of tools
 */
namespace tools
{
    /**
     * Name space of database tools
     */
    namespace database
    {
        /** @brief Abstract database response of a request.
         * Attention, do NOT keep any reference to this class after calling DataBaseRequest::execute
         */
        class DataBaseResponse
        {
            public:
                /** Default constructor */
                DataBaseResponse();
                DataBaseResponse(bool ok);
                DataBaseResponse(bool ok, const wxString& message);
                /** Default destructor */
                virtual ~DataBaseResponse();

                /** Must be overloaded */
                //virtual DataBaseResponse* clone() const = 0;
                //virtual void copyTo(DataBaseResponse& dest) const;

                virtual bool isOK() const;
                void setOK(bool ok);
                virtual int getKind() const;
                const wxString& getErrorMessage() const;
                void setErrorMessage(const wxString& message);

            protected:

            private:
                bool m_isOK;
                wxString m_errorMessage;
        };
    }
}

#endif // DATABASERESPONSE_H
