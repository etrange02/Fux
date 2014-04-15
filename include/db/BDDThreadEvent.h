#ifndef BDDTHREADEVENT_H
#define BDDTHREADEVENT_H

#include <wx/wx.h>
#include <wx/event.h>


class BDDThreadEvent : public wxEvent
{
    public:
        BDDThreadEvent(wxWindow* win = (wxWindow*) NULL);
        virtual ~BDDThreadEvent();
        wxEvent* Clone() const {return new BDDThreadEvent(*this);}

        wxArrayString *GetArrayString();
        void SetArrayString(wxArrayString* arrayS);

    protected:
        wxArrayString *m_array;


	DECLARE_DYNAMIC_CLASS(BDDThreadEvent)
};

typedef void (wxEvtHandler::*wxBDDResultatEventFunction)(BDDThreadEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_BDDTHREAD_RESULTAT, 1 )
END_DECLARE_EVENT_TYPES()

#define EVT_MYEVENT(func)                              \
	DECLARE_EVENT_TABLE_ENTRY( wxEVT_BDDTHREAD_RESULTAT,      \
		-1,                                    \
		-1,                                    \
		(wxObjectEventFunction) (myEventFunction) & func,              \
		(wxObject *) NULL ),

/*#define EVT_BDDTHREAD_RESULTAT(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_BDDTHREAD_RESULTAT, id, wxID_ANY, \
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxBDDResultatEventFunction, &fn ), \
    (wxObject *) NULL ),
*/
#endif // BDDTHREADEVENT_H
