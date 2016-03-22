#ifndef DATABASEOPENINGREQUEST_01_H
#define DATABASEOPENINGREQUEST_01_H

#include "tools/database/requests/DataBaseOpeningRequest.h"

class wxSQLite3Database;

/**
 * Name space of database tools
 */
namespace database
{
    class DataBaseOpeningRequest_01 : public tools::database::DataBaseOpeningRequest
    {
        public:
            /** Default constructor */
            DataBaseOpeningRequest_01(const wxString& filename);
            /** Default destructor */
            virtual ~DataBaseOpeningRequest_01();

        protected:
            virtual int updateTables(wxSQLite3Database& database, int currentVersion);

        private:
    };
}

#endif // DATABASEOPENINGREQUEST_01_H
