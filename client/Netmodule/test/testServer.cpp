#include "es_main.h"
#include "Eio.hh"
#include "../http/inc/EHttpServerEncoder.hh"
#include "../http/inc/EHttpServerDecoder.hh"
#include "../http/inc/EHttpEndOfContent.hh"


#define LOG(fmt,...) ESystem::out->printfln(fmt, ##__VA_ARGS__)

class ErrHandler: public EThread::UncaughtExceptionHandler {
public:
	void uncaughtException(EThread* t, EThrowable* e) {
		LOG("This is:%s,Message:%s", t->getName(), e->getMessage());
		e->printStackTrace();
	}
};

class DemoIoHandler: public EIoHandler {
	void sessionCreated(sp<EIoSession>& session) THROWS(EException) {
        session->getConfig()->setIdleTime(EIdleStatus::BOTH_IDLE, 1);
	}

	void sessionOpened(sp<EIoSession>& session) THROWS(EException) {
	}

	void sessionClosed(sp<EIoSession>& session) THROWS(EException) {
	}

	void sessionIdle(sp<EIoSession>& session, EIdleStatus status)
			THROWS(EException) {
	}

	void exceptionCaught(sp<EIoSession>& session, sp<EThrowableType>& cause)
			THROWS(EException) {
		LOG("exceptionCaught");
		session->closeNow();
	}

	void messageReceived(sp<EIoSession>& session, sp<EObject>& message)
			THROWS(EException) {
		EHttpRequest* hr = dynamic_cast<EHttpRequest*>(message.get());
		if (hr) {
			LOG("%s", hr->getHeaders()->toString().c_str());
		}

		EIoBuffer* ib = dynamic_cast<EIoBuffer*>(message.get());
		if (ib) {
			LOG("%s", ib->getString().c_str());
		}

		EHttpEndOfContent* heoc = dynamic_cast<EHttpEndOfContent*>(message.get());
		if (heoc) {
			LOG("%s", heoc->toString().c_str());

			EIoBuffer *out = EIoBuffer::allocate(512);
			out->buf()->put("HTTP/1.1 200 OK\r\nContent-Length: 11\r\nContent-Type: text/html\r\n\r\nHello,world", 75);
			out->flip();
			session->write(out);
		}
	}

	void messageSent(sp<EIoSession>& session, sp<EObject>& message)
			THROWS(EException) {
	}
    
    void inputClosed(sp<EIoSession>& session) THROWS(EException) {
    	session->closeNow();
    }
};

void testAcceptor(){
    ErrHandler errHandler;
    EThread::setDefaultUncaughtExceptionHandler(&errHandler);

    ENioSocketAcceptor *acceptor = new ENioSocketAcceptor();
    ETextLineCodecFactory* tlcf = new ETextLineCodecFactory("\n");
	EProtocolCodecFilter* pcf1 = new EProtocolCodecFilter(tlcf);
    EInetSocketAddress addr("localhost", 9123);
    DemoIoHandler *handler = new DemoIoHandler();
    acceptor->setReuseAddress(true);

	ELoggingFilter* lf = new ELoggingFilter();

    acceptor->getFilterChain()->addLast("codec", pcf1);
	acceptor->getFilterChain()->addLast("logger", lf);
    acceptor->setHandler(handler);
    try{
        acceptor->bind(&addr);
        printf("Server Start\n");
        EThread::sleep(10000000);
    }
    catch(EException e){
        printf("Get exception!!!\n");
        e.printStackTrace();
    }

    delete acceptor;
    delete tlcf;
    delete pcf1;
    delete pcf1;
    delete handler;
}

int main(){
    testAcceptor();
}
