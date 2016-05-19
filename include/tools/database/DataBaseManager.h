#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <map>
#include "tools/thread/manager/SingleThreadManager.h"

class wxSQLite3Statement;
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
        class DataBaseRequest;

        /** @brief Manager of database.
         */
        class DataBaseManager : public tools::thread::SingleThreadManager
        {
            public:
                /** Default constructor */
                DataBaseManager();
                /** Default destructor */
                virtual ~DataBaseManager();

                void addDataBaseResquest(DataBaseRequest* request, int priority);
                void addDataBaseResquest(DataBaseRequest* request);
                bool hasStatements() const;
                bool isContainingStatement(int id) const;
                wxSQLite3Statement& initializeStatement(int uid, const wxString& requestForm);

                bool isDatabaseInitialized() const;
                void setDatabase(wxSQLite3Database* database);
                wxSQLite3Database& getDatabase();

            protected:
                wxSQLite3Statement& getStatement(int id);
                void addStatement(int id, wxSQLite3Statement& statement);
                void destroyStatements();
                virtual void doBeforeAddingWork(tools::thread::Runnable& work);

            private:
                std::map<int, wxSQLite3Statement> m_statements;
                wxSQLite3Database *m_database;
                static int m_initializingCounter;
        };
    }
}

#endif // DATABASEMANAGER_H
