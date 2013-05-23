#ifndef COMINTERPROCESS_H_INCLUDED
#define COMINTERPROCESS_H_INCLUDED

#include "Define.h"
#include <wx/wx.h>
#include <wx/ipc.h>

extern const wxEventType wxEVT_SERVEUR;
class TCPConnexionEchangeInstanceLocalHost;

WX_DEFINE_ARRAY(TCPConnexionEchangeInstanceLocalHost*, ArrayOfConnexion);

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

class TCPClient : public wxClient
{
    public:
        TCPClient();
        virtual ~TCPClient() {}
        wxConnectionBase* OnMakeConnection(void);
};

class TCPServeur : public wxServer
{
    public:
        TCPServeur(wxWindow*);
        virtual ~TCPServeur();
        wxConnectionBase *OnAcceptConnection(const wxString &topic);
        void Deconnecter(int);
        wxArrayString* GetConnexionTableau(int);

    private:
        wxWindow *m_parent;
        ArrayOfConnexion *m_connexions;
        int m_compte;
};

#endif // COMINTERPROCESS_H_INCLUDED
