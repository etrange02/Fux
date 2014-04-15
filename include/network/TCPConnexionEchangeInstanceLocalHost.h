#ifndef COMINTERPROCESS_H_INCLUDED
#define COMINTERPROCESS_H_INCLUDED

#include <wx/wx.h>
#include <wx/ipc.h>
#include "../Define.h"

extern const wxEventType wxEVT_SERVEUR;

class TCPConnexionEchangeInstanceLocalHost : public wxConnection
{
    public:
        TCPConnexionEchangeInstanceLocalHost(wxWindow *parent = NULL, int id = -1);
        virtual bool Execute(const wxString data);
        virtual bool OnExecute(const wxString& topic, wxChar *data, int size, wxIPCFormat format);

        virtual bool OnDisconnect();
        wxArrayString *GetTableau();
        int GetId();

    private:
        wxWindow *m_parent;
        wxArrayString m_tableau;
        int m_nombreString;
        int m_id;
};



#endif // COMINTERPROCESS_H_INCLUDED
