#include "es_main.h"
#include "Eio.hh"
#include "../http/inc/EHttpServerEncoder.hh"
#include "../http/inc/EHttpServerDecoder.hh"
#include "../http/inc/EHttpEndOfContent.hh"
#include "inc/EString.hh"

#include "Server.h"
#include "Message.h"
#include "MessageCodec.h"
using namespace Netmodule;


#define LOG(fmt,...) ESystem::out->printfln(fmt, ##__VA_ARGS__)
char *username;
char *password;

void testSignup(EIoSession *session){
	sp<Message> msg = new SignupMessage(username, "1.com", password);
	EIoBuffer *pb = msg->getEncodedMessage();
	pb->flip();
	session->write(pb)->awaitUninterruptibly();
}

void testLogin(EIoSession *session){
	sp<Message> msg = new LoginMessage(username, password);
	EIoBuffer *pb = msg->getEncodedMessage();
	pb->flip();
	session->write(pb)->awaitUninterruptibly();
}

void testPullMessage(EIoSession *session){
	testLogin(session);

	sp<Message> msg = new PullMessage();
	EIoBuffer *pb = msg->getEncodedMessage();
	pb->flip();
	session->write(pb)->awaitUninterruptibly();
}

void testText(EIoSession *session){
	testLogin(session);

	sp<Message> msg = new TextMessage(username, "Hello");
	EIoBuffer *pb = msg->getEncodedMessage();
	pb->flip();
	session->write(pb)->awaitUninterruptibly();
}

void testQueryUserInformation(EIoSession *session){
	testLogin(session);

	sp<Message> msg = new QueryUserInformationMessage("keyword");
	EIoBuffer *pb = msg->getEncodedMessage();
	pb->flip();
	session->write(pb)->awaitUninterruptibly();
}

void testRequestFriend(EIoSession *session){
	testLogin(session);

	sp<Message> msg = new RequestFriendMessage(username, "This mike");
	EIoBuffer *pb = msg->getEncodedMessage();
	pb->flip();
	session->write(pb)->awaitUninterruptibly();
}

void testDeleteFriend(EIoSession *session){
	testLogin(session);

	sp<Message> msg = new DeleteFriendMessage("Tracy");
	EIoBuffer *pb = msg->getEncodedMessage();
	pb->flip();
	session->write(pb)->awaitUninterruptibly();	
}

void testQueryFriend(EIoSession *session){
	testLogin(session);

	sp<Message> msg = new QueryFriendListMessage();
	EIoBuffer *pb = msg->getEncodedMessage();
	pb->flip();
	session->write(pb)->awaitUninterruptibly();
}

void testLogout(EIoSession *session){
	testLogin(session);

	sp<Message> msg = new LogOutMessage();
	EIoBuffer *pb = msg->getEncodedMessage();
	pb->flip();
	session->write(pb)->awaitUninterruptibly();		
}

void testClient(){
	EString a("Text");
	EIoConnector *connector = new ENioSocketConnector();
	ServerHandler *handler = new ServerHandler();
	connector->setConnectTimeoutMillis(30000L);
	connector->setHandler(handler);
	sp<EIoSession> session = null;

	try{
		EInetSocketAddress addr("192.168.137.96", 9123);
		sp<EConnectFuture> future = connector->connect(&addr);
		future->awaitUninterruptibly();
		session = future->getSession();
		LOG("Start client");
		
		// testSignup(session.dismiss());
		// testText(session.dismiss());
		// testPullMessage(session.dismiss());
		// testDeleteFriend(session.dismiss());
		testQueryFriend(session.dismiss());
		// testQueryUserInformation(session.dismiss());
		// testRequestFriend(session.dismiss());
		// testLogout(session.dismiss());
		EThread::sleep(100000);
	}
	catch(EException e){
		e.printStackTrace();
	}
	session->getCloseFuture()->awaitUninterruptibly();
	connector->dispose();

	delete connector;
	delete handler;
	// delete codecFactory;
	// delete filter;
}

int main(int argc, char **argv){
	if(argc < 3){
		printf("./testClient [username] [password]");
		return -1;
	}
	username = argv[1];
	password = argv[2];
	testClient();
	// EA<EString> 
	// Server *s = new Server("192.168.137.96", 9123, );

}
