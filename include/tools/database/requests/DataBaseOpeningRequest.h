#ifndef DATABASEOPENINGREQUEST_H
#define DATABASEOPENINGREQUEST_H

#include "DataBaseRequest.h"

class wxSQLite3Database;

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
        class DataBaseOpeningRequest : public DataBaseRequest
        {
            public:
                /** Default constructor */
                DataBaseOpeningRequest(const wxString& filename);
                /** Default destructor */
                virtual ~DataBaseOpeningRequest();

            protected:
                virtual void initializeStatements();
                virtual DataBaseResponse* execute(DataBaseManager& dataBaseManager);
                virtual int updateTables(wxSQLite3Database& database, int currentVersion);

            private:
                wxString m_filename;
        };
    }
}

#endif // DATABASEOPENINGREQUEST_H
