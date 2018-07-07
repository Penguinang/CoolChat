#ifndef SERVER_H
#define SERVER_H


#include "Eio.hh"



namespace Netmodule{
/* --------------------------------------------------------------------------------------------------
 *      Server
 * -------------------------------------------------------------------------------------------------- */  
    class Server{
        
    };

/* --------------------------------------------------------------------------------------------------
 *      ServerHandler
 * -------------------------------------------------------------------------------------------------- */  
    class ServerHandler : public EIoHandlerAdapter{
    public:
        ServerHandler();
        void sessionCreated(sp<EIoSession>& session) THROWS(EException);
        void sessionOpened(sp<EIoSession>& session) THROWS(EException);
        void sessionClosed(sp<EIoSession>& session) THROWS(EException);
        void sessionIdle(sp<EIoSession>& session, EIdleStatus status) THROWS(EException);
        void exceptionCaught(sp<EIoSession>& session, sp<EThrowableType>& cause) THROWS(EException);
        void messageReceived(sp<EIoSession>& session, sp<EObject>& message) THROWS(EException);
        void messageSent(sp<EIoSession>& session, sp<EObject>& message) THROWS(EException);
        void inputClosed(sp<EIoSession>& session) THROWS(EException);
    };


}

#endif // !SERVER_H
