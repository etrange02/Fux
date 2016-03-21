#ifndef DATABASECLOSINGREQUEST_H
#define DATABASECLOSINGREQUEST_H

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
        class DataBaseClosingRequest : public DataBaseRequest
        {
            public:
                /** Default constructor */
                DataBaseClosingRequest();
                /** Default destructor */
                virtual ~DataBaseClosingRequest();

            protected:
                virtual DataBaseResponse* execute(DataBaseManager& dataBaseManager);
        };
    }
}

#endif // DATABASECLOSINGREQUEST_H
