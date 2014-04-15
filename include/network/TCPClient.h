#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <wx/wx.h>
#include <wx/ipc.h>
#include "../Define.h"
#include "TCPConnexionEchangeInstanceLocalHost.h"

class TCPClient : public wxClient
{
    public:
        TCPClient();
        virtual ~TCPClient() {}
        wxConnectionBase* OnMakeConnection(void);
};

#endif // TCPCLIENT_H
