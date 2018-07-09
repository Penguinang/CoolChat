#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <vector>
using namespace std;

#include "Server.h"
#include "Eio.hh"

namespace Netmodule{

/* --------------------------------------------------------------------------------------------------
 *      Message base
 * -------------------------------------------------------------------------------------------------- */  
    class Message : public EObject{
    public:
        static Message *decodeBytesToMessage(EIoBuffer *input) THROWS(EException);

        Message();
        virtual EIoBuffer *getEncodedMessage();
        // Useless in client
        // virtual Message *getResult();
        virtual void processMessage();
        virtual EString toString();
    };

/* --------------------------------------------------------------------------------------------------
 *      0. SignupMessage
 * -------------------------------------------------------------------------------------------------- */    
    class SignupMessage : public Message{
    private: 
        static unsigned int type_num;
        EString username;
        EString email;
        EString password;

    public:
        static SignupMessage* decodeBytes(EIoBuffer *input);

        SignupMessage(EString _username, EString _email, EString _password);

        EIoBuffer *getEncodedMessage();
        EString toString();
    };

/* --------------------------------------------------------------------------------------------------
 *      2. LoginMessage
 * -------------------------------------------------------------------------------------------------- */ 
    class LoginMessage : public Message{
    public:
        typedef void (*LoginCallBack) (bool success, string extra);
        static LoginCallBack resultCallBack;

    private: 
        static unsigned int type_num;
        EString username;
        EString password;

    public:
        static LoginMessage* decodeBytes(EIoBuffer *input);

        LoginMessage(EString _username, EString _password);

        EIoBuffer *getEncodedMessage();
        EString toString();
    };
/* --------------------------------------------------------------------------------------------------
 *      3. LoginResultMessage
 * -------------------------------------------------------------------------------------------------- */ 
    class LoginResultMessage : public Message{
    private: 
        static unsigned int type_num;
        int retcode;
    public:
        static LoginResultMessage* decodeBytes(EIoBuffer *input);

        LoginResultMessage(int _retcode);

        EIoBuffer *getEncodedMessage();
        void processMessage();
        EString toString();
    };
/* --------------------------------------------------------------------------------------------------
 *      4. PullMessage
 * -------------------------------------------------------------------------------------------------- */  
    class PullMessage : public Message{
    private: 
        static unsigned int type_num;
    public:
        static PullMessage* decodeBytes(EIoBuffer *input);

        PullMessage();

        EIoBuffer *getEncodedMessage();
        EString toString();
    };
/* --------------------------------------------------------------------------------------------------
 *      5. PullResultMessage
 * -------------------------------------------------------------------------------------------------- */  
    class PullResultMessage : public Message{
    private: 
        static unsigned int type_num;
        EA<EString> usernameList;
        EA<EString> contentList;
    public:
        static PullResultMessage* decodeBytes(EIoBuffer *input);

        PullResultMessage(EA<EString> _usernameList, EA<EString> _contentList);

        EIoBuffer *getEncodedMessage();
        EString toString();
    };
/* --------------------------------------------------------------------------------------------------
 *      6. TextMessage
 * -------------------------------------------------------------------------------------------------- */  
    class TextMessage : public Message{
    public:
        typedef void(*GetTextCallBack)(string username, string time, string content);
        static GetTextCallBack resultCallBack;
    private:
        static unsigned int type_num;
        EString username;
        EString content;

    public:
        static TextMessage* decodeBytes(EIoBuffer *input);

        TextMessage(EString _username, EString _content);

        EIoBuffer *getEncodedMessage();
        void processMessage();
        EString toString();
    };
/* --------------------------------------------------------------------------------------------------
 *      7. QueryUserInformationMessage
 * -------------------------------------------------------------------------------------------------- */  
    class QueryUserInformationMessage : public Message{
    public:
        typedef void (*QueryUserInformationCallBack) (vector<struct userinfo> &user_list);
        static QueryUserInformationCallBack resultCallBack;
    private:
        static unsigned int type_num;
        EString keyword;

    public:
        static QueryUserInformationMessage* decodeBytes(EIoBuffer *input);

        QueryUserInformationMessage(EString _keyword);

        EIoBuffer *getEncodedMessage();
        EString toString();
    };
/* --------------------------------------------------------------------------------------------------
 *      8. QueryUserResultMessage
 * -------------------------------------------------------------------------------------------------- */  
    class QueryUserResultMessage : public Message{
    private:
        static unsigned int type_num;
        EA<EString> userList;
    public:
        static QueryUserResultMessage* decodeBytes(EIoBuffer *input);

        QueryUserResultMessage(EA<EString> _userList);

        EIoBuffer *getEncodedMessage();
        void processMessage();
        EString toString();
    };
/* --------------------------------------------------------------------------------------------------
 *      9. RequestFriendMessage
 * -------------------------------------------------------------------------------------------------- */  
    class RequestFriendMessage : public Message{
    public:
        // typedef void (*RequestFriendCallBack) (bool success, bool permission, string cause);
        // static RequestFriendCallBack resultCallBack;
    private:
        static unsigned int type_num;
        EString username;
        EString note;

    public:
        static RequestFriendMessage* decodeBytes(EIoBuffer *input);

        RequestFriendMessage(EString _username, EString _note);

        EIoBuffer *getEncodedMessage();
        EString toString();
    };
/* --------------------------------------------------------------------------------------------------
 *      10. SendRequestMessage
 * -------------------------------------------------------------------------------------------------- */  
    class SendRequestMessage : public Message{
    private:
        static unsigned int type_num;
        EString username;
        EString note;

    public:
        static SendRequestMessage* decodeBytes(EIoBuffer *input);

        SendRequestMessage(EString _username, EString _note);

        EIoBuffer *getEncodedMessage();
        EString toString();
    };
/* --------------------------------------------------------------------------------------------------
 *      11. ReplyPermissionMessage
 * -------------------------------------------------------------------------------------------------- */  
    class ReplyPermissionMessage : public Message{
    private:
        static unsigned int type_num;
        boolean success;
        EString username;
        EString note;

    public:
        static ReplyPermissionMessage* decodeBytes(EIoBuffer *input);

        ReplyPermissionMessage(boolean _success, EString _username, EString _note);

        EIoBuffer *getEncodedMessage();
        EString toString();
    };
/* --------------------------------------------------------------------------------------------------
 *      12. SendReplyMessage
 * -------------------------------------------------------------------------------------------------- */  
    class SendReplyMessage : public Message{
    private:
        static unsigned int type_num;
        boolean success;
        EString username;
        EString note;

    public:
        static SendReplyMessage* decodeBytes(EIoBuffer *input);

        SendReplyMessage(boolean _success, EString _username, EString _note);

        EIoBuffer *getEncodedMessage();
        void processMessage();
        EString toString();
    };
/* --------------------------------------------------------------------------------------------------
 *      13. DeleteFriendMessage
 * -------------------------------------------------------------------------------------------------- */  
    class DeleteFriendMessage : public Message{
    private:
        static unsigned int type_num;
        EString username;

    public:
        static DeleteFriendMessage* decodeBytes(EIoBuffer *input);

        DeleteFriendMessage(EString _username);

        EIoBuffer *getEncodedMessage();
        EString toString();
    };
/* --------------------------------------------------------------------------------------------------
 *      14. QueryFriendListMessage
 * -------------------------------------------------------------------------------------------------- */  
    class QueryFriendListMessage : public Message{
    public:
        typedef void (*QueryFriendListMessageCallBack) (vector<struct userinfo> &friends_list);
        static QueryFriendListMessageCallBack resultCallBack;
    private:
        static unsigned int type_num;

    public:
        static QueryFriendListMessage* decodeBytes(EIoBuffer *input);

        QueryFriendListMessage();

        EIoBuffer *getEncodedMessage();
        EString toString();
    };
/* --------------------------------------------------------------------------------------------------
 *      15. QueryFriendListResultMessage
 * -------------------------------------------------------------------------------------------------- */  
    class QueryFriendListResultMessage : public Message{
    private:
        static unsigned int type_num;
        EA<EString> friendList;

    public:
        static QueryFriendListResultMessage* decodeBytes(EIoBuffer *input);

        QueryFriendListResultMessage(EA<EString> _friendList);

        EIoBuffer *getEncodedMessage();
        void processMessage();
        EString toString();
    };
/* --------------------------------------------------------------------------------------------------
 *      16. LogOutMessage
 * -------------------------------------------------------------------------------------------------- */  
    class LogOutMessage : public Message{
    private:
        static unsigned int type_num;

    public:
        static LogOutMessage* decodeBytes(EIoBuffer *input);

        LogOutMessage();

        EIoBuffer *getEncodedMessage();
        EString toString();
    };
}

#endif // !MESSAGE_H
