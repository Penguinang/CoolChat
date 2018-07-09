#include<iostream>

#include "Server.h"
#include "Message.h"

#define DEBUG_ERROR(s) cerr<<s<<endl

namespace Netmodule{
    /* --------------------------------------------------------------------------------------------------
     *      Server
     * -------------------------------------------------------------------------------------------------- */  
    long Server::connect_timeout = 30000L;
    // Server::Server() {}

    Server::~Server() {
        connector->dispose();
        delete connector;
        delete handler;
    }

    Server::Server(string ip, int port, void(*get_text_callback)(string username, string time, string content)){
        connector = new ENioSocketConnector();
        handler = new ServerHandler();
        connector->setConnectTimeoutMillis(connect_timeout);
        connector->setHandler(handler);

        try{
            EInetSocketAddress addr(ip.c_str(), port);
            sp<EConnectFuture> future = connector->connect(&addr);
            future->awaitUninterruptibly();
            session = future->getSession();
        }
        catch(EException e){
            throw exception();
            DEBUG_ERROR("!!!!!!!  Cant Connect Server, Init Connection Fail  !!!!!!!");
        }
    }

    /**
     * LoginCallBack      -->     void (*) (bool success, string extra)
     */
    void Server::Login (string uID, string password, LoginMessage::LoginCallBack callback){
        Message *msg = new LoginMessage(EString(uID.c_str()), EString(password.c_str()));
        EIoBuffer *msg_buffer = msg->getEncodedMessage();
        session->write(msg_buffer);
        delete msg;
        LoginMessage::resultCallBack = callback;
        setUid(uID);
    }

    /**
     * QueryFriendListMessageCallBacl     -->   void (*) (vector<struct userinfo> &friends_list)
     */
    void Server::GetFriendList (QueryFriendListMessage::QueryFriendListMessageCallBack callback){
        Message *msg = new QueryFriendListMessage();
        EIoBuffer *msg_buffer = msg->getEncodedMessage();
        session->write(msg_buffer);
        delete msg;
        QueryFriendListMessage::resultCallBack = callback;
    }

    /**
     * QueryUserInformationCallBack   -->   void (*) (vector<struct userinfo> &user_list
     */
    void Server::QueryInformationByID (string uID, QueryUserInformationMessage::QueryUserInformationCallBack callback){
        Message *msg = new QueryUserInformationMessage(EString(uID.c_str()));
        EIoBuffer *msg_buffer = msg->getEncodedMessage();
        session->write(msg_buffer);
        delete msg;
        QueryUserInformationMessage::resultCallBack = callback;
    }

    /**
     * RequestFriendCallBack  -->  void (*) (bool success, bool permission, string cause)
     */
    void Server::RequestAddFriend (string uID, string note){
        Message *msg = new RequestFriendMessage(EString(uID.c_str()), EString(note.c_str()));
        EIoBuffer *msg_buffer = msg->getEncodedMessage();
        session->write(msg_buffer);
        delete msg;
        // XXX
        // 根据商议， 决定将此回复忽略， 改用GetTextMessage的回调
        // RequestFriendMessage::resultCallBack = callback;        
    }

    void Server::ReplyFriendRequest (string uID, bool permission, string note){
        Message *msg = new ReplyPermissionMessage(permission, uID, note);
        EIoBuffer *msg_buffer = msg->getEncodedMessage();
        session->write(msg_buffer);
        delete msg;
    }

    void Server::DeleteFriend (string uID){
        Message *msg = new DeleteFriendMessage(uID);
        EIoBuffer *msg_buffer = msg->getEncodedMessage();
        session->write(msg_buffer);
        delete msg;
    }
    

    void Server::SendText (string uID, string content, void (*callback) (bool success)){
        Message *msg = new TextMessage(EString(uID.c_str()), EString(content.c_str()));
        EIoBuffer *msg_buffer = msg->getEncodedMessage();
        sp<EWriteFuture> future = session->write(msg_buffer);
        delete msg;
        try{
            future->awaitUninterruptibly();
        }
        catch(EException e){
            e.printStackTrace();
            callback(false);
            return;
        }
        callback(true);
    }

    void Server::Logout (){
        Message *msg = new LogOutMessage();
        EIoBuffer *msg_buffer = msg->getEncodedMessage();
        session->write(msg_buffer);
        delete msg;
    }

    string Server::getUid(){
        return userID;
    }

    void Server::setUid(string _uid){
        userID = _uid;
    }
    /* --------------------------------------------------------------------------------------------------
     *      ServerHandler
     * -------------------------------------------------------------------------------------------------- */  
    ServerHandler::ServerHandler() {}

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
        EIoBuffer *buffer = dynamic_cast<EIoBuffer*>(message.dismiss());
        Message *msg = Message::decodeBytesToMessage(buffer);
        msg->processMessage();
        if(msg != nullptr){
            printf("Receive message:\n%s", msg->toString().c_str());
            delete msg;
        }
    }
    void ServerHandler::messageSent(sp<EIoSession>& session, sp<EObject>& message) THROWS(EException){

    }
    void ServerHandler::inputClosed(sp<EIoSession>& session) THROWS(EException){

    }
}