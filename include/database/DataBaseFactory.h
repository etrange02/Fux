#ifndef DATABASEFACTORY_H
#define DATABASEFACTORY_H

#include <wx/wx.h>

namespace tools {
    namespace database {
        class DataBaseRequest;
    }
}

class DataBaseFactory
{
    public:
        static tools::database::DataBaseRequest* createOpeningRequest(const wxString& filename);
        static tools::database::DataBaseRequest* createClosingRequest();

    protected:
        /** Default constructor */
        DataBaseFactory();
        /** Default destructor */
        virtual ~DataBaseFactory();

    private:
};

#endif // DATABASEFACTORY_H
