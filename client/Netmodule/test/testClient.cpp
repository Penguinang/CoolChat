#include "es_main.h"
#include "Eio.hh"
#include "../http/inc/EHttpServerEncoder.hh"
#include "../http/inc/EHttpServerDecoder.hh"
#include "../http/inc/EHttpEndOfContent.hh"


#define LOG(fmt,...) ESystem::out->printfln(fmt, ##__VA_ARGS__)
class MinaClientHandler : public EIoHandlerAdapter {
public:
	void exceptionCaught(sp<EIoSession>& session, EThrowableType* cause) THROWS(EException) {
		LOG("exceptionCaught");
		cause->getThrowable()->printStackTrace();
		session->closeNow();
	}

	void messageReceived(sp<EIoSession>& session, const void* message)THROWS(EException) {
		LOG("messageReceived");
	}

	void messageSent(sp<EIoSession>& session, const void* message) THROWS(EException) {
		LOG("messageSent");
	}

	void sessionClosed(sp<EIoSession>& session) THROWS(EException) {
		LOG("sessionClosed");
	}

	void sessionCreated(sp<EIoSession>& session) THROWS(EException) {
		LOG("sessionCreated");
		session->getConfig()->setIdleTime(EIdleStatus::BOTH_IDLE, 1);
	}

	void sessionIdle(sp<EIoSession>& session, EIdleStatus status) THROWS(EException) {
		LOG("sessionIdle");
	}

	void sessionOpened(sp<EIoSession>& session) THROWS(EException) {
		LOG("sessionOpened");
	}

	 void inputClosed(sp<EIoSession>& session) THROWS(EException) {
		LOG("inputClosed");
		session->closeNow();
	}
};

void testConnector(){
    EIoConnector *connector = new ENioSocketConnector();
    MinaClientHandler *handler = new MinaClientHandler();
    connector->setConnectTimeoutMillis(30000L);
    connector->setHandler(handler);
    sp<EIoSession> session = null;

    try{
        EInetSocketAddress addr("localhost", 9123);
        sp<EConnectFuture> future = connector->connect(&addr);
        future->awaitUninterruptibly();
        session = future->getSession();

        EIoBuffer *ib = EIoBuffer::allocate(1024);
        ib->buf()->put("Hello\n\n\n\n", 11);
        ib->flip();
        session->write(ib);
    }
    catch(EException e){
        LOG("Get a exception");
        e.printStackTrace();
    }

    if(session != null){
        session->getCloseFuture()->awaitUninterruptibly();
    }
    connector->dispose();

    delete connector;
    delete handler;
}

int main(){
    testConnector();
}
