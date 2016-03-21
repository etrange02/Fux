#ifndef DATABASEREQUEST_H
#define DATABASEREQUEST_H

#include "tools/thread/Runnable.h"
#include <wx/wx.h>

class sqlite3_stmt;

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
        class DataBaseResponse;
        class DataBaseManager;

        /** @brief Abstract database request
         */
        class DataBaseRequest : public tools::thread::Runnable
        {
            public:
                /** Default constructor */
                DataBaseRequest();
                /** Default destructor */
                virtual ~DataBaseRequest();

                virtual void process();

                void setDataBaseManager(DataBaseManager& dataBaseManager);
                DataBaseManager* getDataBaseManager();

                virtual wxEventType getEventType();
                virtual int getEventId();

            protected:
                virtual void initializeStatements();
                /** @brief Must be overloaded. Brain method of the class.
                 * Attention, do NOT keep any reference to this class after calling DataBaseRequest::execute
                 */
                virtual DataBaseResponse* execute(DataBaseManager& dataBaseManager) = 0;
                void sendEvent(wxEventType commandType, int id, DataBaseResponse* response);

            private:
                DataBaseManager* m_dataBaseManager;
        };
    }
}

#endif // DATABASEREQUEST_H
