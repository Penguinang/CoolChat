#include "Server.h"
#include "Message.h"

namespace Netmodule{
/* --------------------------------------------------------------------------------------------------
 *      ServerHandler
 * -------------------------------------------------------------------------------------------------- */  
    void ServerHandler::sessionCreated(sp<EIoSession>& session) THROWS(EException){

    }
    void ServerHandler::sessionOpened(sp<EIoSession>& session) THROWS(EException){

    }
    void ServerHandler::sessionClosed(sp<EIoSession>& session) THROWS(EException){

    }
    void ServerHandler::sessionIdle(sp<EIoSession>& session, EIdleStatus status) THROWS(EException){

    }
    void ServerHandler::exceptionCaught(sp<EIoSession>& session, sp<EThrowableType>& cause) THROWS(EException){
        cause->getThrowable()->printStackTrace();
    }
    void ServerHandler::messageReceived(sp<EIoSession>& session, sp<EObject>& message) THROWS(EException){
        Message *msg = static_cast<Message*>(message.dismiss());
        printf("Get Message:\n%s", msg->toString().c_str());
    }
    void ServerHandler::messageSent(sp<EIoSession>& session, sp<EObject>& message) THROWS(EException){

    }
    void ServerHandler::inputClosed(sp<EIoSession>& session) THROWS(EException){

    }
}