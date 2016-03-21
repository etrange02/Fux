#ifndef DBTHREADEVENT_H
#define DBTHREADEVENT_H

#include <wx/wx.h>
#include <wx/event.h>

namespace tools {
    namespace database {
        class DataBaseResponse;
    }
}
class DBThreadEvent;

wxDECLARE_EVENT(wxEVT_DB_THREAD, wxThreadEvent);

/** @brief Overload of wxThreadEvent to facilitate integration.
 */
class DBThreadEvent : public wxThreadEvent
{
    public:
        /** Default constructor */
        DBThreadEvent(wxEventType eventType = wxEVT_DB_THREAD, int id = wxID_ANY);
        DBThreadEvent(const DBThreadEvent& other);
        /** Default destructor */
        virtual ~DBThreadEvent();

        virtual wxEvent* Clone() const;

        void setResponse(tools::database::DataBaseResponse* response);
        tools::database::DataBaseResponse* getResponse() const;

    protected:

    private:
        tools::database::DataBaseResponse* m_response;
};

typedef void (wxEvtHandler::*DBThreadEventFunction)(DBThreadEvent &);

#define DBThreadEventHandler(func) wxEVENT_HANDLER_CAST(DBThreadEventFunction, func)

#define EVT_DB_THREAD(id, func)                               \
        wx__DECLARE_EVT1(wxEVT_DB_THREAD, id, DBThreadEventHandler(func))

#define EVT_DB_THREAD_RANGE(id1, id2, func)                               \
        wx__DECLARE_EVT2(wxEVT_DB_THREAD, id1, id2, DBThreadEventHandler(func))


#endif // DBTHREADEVENT_H
