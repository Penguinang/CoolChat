#ifndef CONNECTION_LISTENER

#include "Eio.hh"
#include "Server.h"

//
class ConnectionListener : public EIoFutureListener {
  public:
    ConnectionListener(Server *_server, sp<Message> _msg) : server(_server), msg(_msg) {}

    // invoked when connection complete
    void operationComplete(EIoFuture *future) {
        server->setSession(server->getFuture()->getSession());
        EIoBuffer *pb = msg->getEncodedMessage();
        pb->flip();
        server->getSession()->write(pb);
    }

  private:
    Server *server;
    sp<Message> msg;
};

#endif // !CONNECTION_LISTENER