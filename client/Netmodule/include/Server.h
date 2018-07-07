#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <vector>
using namespace std;

#include "Eio.hh"



namespace Netmodule{
/* --------------------------------------------------------------------------------------------------
 *      Server
 * -------------------------------------------------------------------------------------------------- */  
    class Server{
    public:
        // Constructors/Destructors
        //  


        /**
         * Empty Constructor
         */
        Server ();

        /**
         * Empty Destructor
         */
        virtual ~Server ();

        // Static Public attributes
        //  

        // Public attributes
        //  


        // Public attribute accessor methods
        //  


        // Public attribute accessor methods
        //  



        /**
         * Constructor
         * @param  ip 服务器ip
         * @param  port 端口
         */
        Server (string ip = "localhost", int port = 9123);


        /**
         * 通知服务器登录
         * @param  uID User ID
         * @param  password 密码
         * @param  callback 登录功能执行结果的回调函数，第一个bool参数为登录是否成功，若失败，第二个参数为失败原因
         */
        void Login (string uID, string password, void (*callback) (bool success, string extra));


        /**
         * 向服务器查询好友列表
         * @param  callback 得到服务器查询结果后的使用回调函数，其中函数参数是好友信息的数组
         */
        void GetFriendList (void (*callback) (vector<struct userinfo> &friends_list));


        /**
         * 根据ID查找用户
         * @param  uID User ID
         * @param  callback 向服务器查询用户列表得到结果时的回调函数
         */
        void QueryInformationByID (string uID, void (*callback) (vector<struct userinfo> &user_list));

        // XXX
        // 改了参数
        /**
         * 请求添加好友
         * @param  uID 目标用户ID
         * @param  callback 请求添加好友得到结果时的回调函数
         * @param  note 请求添加好友时候向对方的说明
         */
        void RequestAddFriend (string uID, string note, void (*callback) (bool success, bool permission, string cause));


        /**
         * 向好友发送文字信息
         * @param  uID 目标用户ID
         * @param  content 文字消息内容
         * @param  callback 发送消息得到结果时的回调函数
         */
        void SendText (string uID, string content, void (*callback) (bool success));


        /**
         */
        void Logout ();

    protected:

        // Static Protected attributes
        //  
        static long connect_timeout;

        // Protected attributes
        //  
        EIoConnector *connector;
        EIoHandler *handler;
        sp<EIoSession> session;

    public:


        // Protected attribute accessor methods
        //  

    protected:

    public:


        // Protected attribute accessor methods
        //  

    protected:


    private:

        // Static Private attributes
        //  

        // Private attributes
        //  

    public:


        // Private attribute accessor methods
        //  

    private:

    public:


        // Private attribute accessor methods
        //  

    private:



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
