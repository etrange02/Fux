#ifndef TCPSERVEUR_H
#define TCPSERVEUR_H

#include <wx/wx.h>
#include <wx/ipc.h>
#include "../Define.h"
#include "TCPConnexionEchangeInstanceLocalHost.h"

WX_DEFINE_ARRAY(TCPConnexionEchangeInstanceLocalHost*, ArrayOfConnexion);

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

#endif // TCPSERVEUR_H
