#include "Message.h"

/**
 *
 * Result 消息在客户端只需要实现decode， 非Result消息只需实现encode
 *
 */

#define DEBUG printf

namespace Netmodule{
    /* --------------------------------------------------------------------------------------------------
    *      Message base
    * -------------------------------------------------------------------------------------------------- */    
    Message* Message::decodeBytesToMessage(EIoBuffer *input) THROWS(EException){
        switch(input->get()){
            case 0: return SignupMessage::decodeBytes(input);
            case 1: DEBUG("Get Umimplemented SignupResultMessage");return nullptr;
            case 2: return LoginMessage::decodeBytes(input);
            case 3: return LoginResultMessage::decodeBytes(input);
            case 4: return PullMessage::decodeBytes(input);
            case 5: return PullResultMessage::decodeBytes(input);
            case 6: return TextMessage::decodeBytes(input);                        
            case 7: return QueryUserInformationMessage::decodeBytes(input);
            case 8: return QueryUserResultMessage::decodeBytes(input);
            case 9: return RequestFriendMessage::decodeBytes(input);
            case 10: return SendRequestMessage::decodeBytes(input);
            case 11: return ReplyPermissionMessage::decodeBytes(input);                        
            case 12: return SendReplyMessage::decodeBytes(input);
            case 13: return DeleteFriendMessage::decodeBytes(input);
            case 14: return QueryFriendListMessage::decodeBytes(input);
            case 15: return QueryFriendListResultMessage::decodeBytes(input);
            case 16: return LogOutMessage::decodeBytes(input);
            default:
                DEBUG("Undefined Message Type");
                return nullptr;
        }
    }

    Message::Message() {}

    EIoBuffer* Message::getEncodedMessage(){
        DEBUG("BaseMessage Cant be encoded\n");
    }

    void Message::processMessage(){
        DEBUG("Base Message havnot any function");
    }

    EString Message::toString(){
        return EString("Base Message");
    }
    /* --------------------------------------------------------------------------------------------------
     *      0. SignupMessage
     * -------------------------------------------------------------------------------------------------- */   
    unsigned int SignupMessage::type_num = 0;

    SignupMessage* SignupMessage::decodeBytes(EIoBuffer *input){
        DEBUG("SignupMessage decode hasnot been implemented\n");
    }

    SignupMessage::SignupMessage(EString _username, EString _email, EString _password) : 
        username(_username), email(_email), password(_password) {}; 

    EIoBuffer* SignupMessage::getEncodedMessage(){        
        EIoBuffer *ret = EIoBuffer::allocate();
        byte type = type_num;
        int usernameLength = username.length();
        int emailLength = email.length();
        int passwordLength = password.length();

        ret->put(type);
        ret->putInt(usernameLength+1);
        ret->putString(username.c_str(), usernameLength);
        ret->putInt(emailLength+1);
        ret->putString(email.c_str(),emailLength);
        ret->putInt(passwordLength+1);
        ret->putString(password.c_str(),passwordLength);

        return ret;
    }

    EString SignupMessage::toString(){
        return EString("SignUpMessage:\nUsername: ")+username+EString("\nEmail: ")+email+EString("\nPassword")+password+EString("\n");
    }
    /* --------------------------------------------------------------------------------------------------
     *      2. LoginMessage
     * -------------------------------------------------------------------------------------------------- */   
    unsigned int LoginMessage::type_num = 2;
    LoginMessage::LoginCallBack LoginMessage::resultCallBack = nullptr;

    LoginMessage* LoginMessage::decodeBytes(EIoBuffer *input){
        DEBUG("LoginMessage decode hasnot been implemented\n");
    }

    LoginMessage::LoginMessage(EString _username, EString _password) : 
        username(_username), password(_password) {}; 

    EIoBuffer* LoginMessage::getEncodedMessage(){
        EIoBuffer *ret = EIoBuffer::allocate();
        byte type = type_num;
        int usernameLength = username.length();
        int passwordLength = password.length();

        ret->put(type);
        ret->putInt(usernameLength+1);
        ret->putString(username.c_str(), usernameLength);
        ret->putInt(passwordLength+1);
        ret->putString(password.c_str(),passwordLength);

        return ret;
    }

    EString LoginMessage::toString(){
        return EString("LoginMessage");
    }
    /* --------------------------------------------------------------------------------------------------
     *      3. LoginResultMessage
     * -------------------------------------------------------------------------------------------------- */   
    unsigned int LoginResultMessage::type_num = 3;

    LoginResultMessage* LoginResultMessage::decodeBytes(EIoBuffer *input){
        int retcode = input->getInt();
        return new LoginResultMessage(retcode);
    }

    LoginResultMessage::LoginResultMessage(int _retcode) : retcode(_retcode) {}

    EIoBuffer* LoginResultMessage::getEncodedMessage(){
        DEBUG("LoginResult encode hasnot been implemented\n");
    }

    void LoginResultMessage::processMessage(){
        bool success = retcode == 0;
        string extra = "";
        if(!success){
            switch(retcode){
                case -1: extra = "Wrong user name or password"; break;
                case -2: extra = "Already Login"; break;
                default:
                    extra = "Login Fail For Unknown Reason";
            }
        }
        if(LoginMessage::resultCallBack){
            LoginMessage::resultCallBack(success, extra);    
        }
        else{
            DEBUG("Get a nullptr LoginResult callback\n");
        }
        LoginMessage::resultCallBack = nullptr;
    }

    EString LoginResultMessage::toString(){
        return EString("LoginResultMessgae\nResultCode: "+retcode);
    }
    /* --------------------------------------------------------------------------------------------------
     *      4. PullMessage
     * -------------------------------------------------------------------------------------------------- */  
    unsigned int PullMessage::type_num = 4;

    PullMessage* PullMessage::decodeBytes(EIoBuffer *input){
        DEBUG("PullMessage decode hasnot been implemented\n");
    }

    PullMessage::PullMessage(){}

    EIoBuffer* PullMessage::getEncodedMessage(){
        EIoBuffer *ret = EIoBuffer::allocate();
        byte type = type_num;

        ret->put(type);

        return ret;
    }

    EString PullMessage::toString(){
        return EString("PullMessage");
    }
    /* --------------------------------------------------------------------------------------------------
     *      5. PullResultMessage
     * -------------------------------------------------------------------------------------------------- */  
    unsigned int PullResultMessage::type_num = 5;

    PullResultMessage* PullResultMessage::decodeBytes(EIoBuffer *input){
        int messageCount = input->getInt();
        EA<EString> nameList(messageCount, EString(""));
        EA<EString> messageList(messageCount, EString(""));
        for(int i = 0; i<messageCount; i++){
            int nameLength = input->getInt();
            EString name = input->getString(nameLength);
            int messageLength = input->getInt();
            EString message = input->getString(messageLength);

            nameList.setAt(i, name);
            messageList.setAt(i, message);
        }

        return new PullResultMessage(nameList, messageList);
    }

    PullResultMessage::PullResultMessage(EA<EString> _usernameList, EA<EString> _contentList) 
        : usernameList(_usernameList), contentList(_contentList) {}

    EIoBuffer* PullResultMessage::getEncodedMessage(){
        DEBUG("PullResultMessage encode hasnot been implemented\n");
    }

    // void processMessage(){

    // }

    EString PullResultMessage::toString(){
        return EString("PullResultMessgae");
    }
    /* --------------------------------------------------------------------------------------------------
     *      6. TextMessage
     * -------------------------------------------------------------------------------------------------- */  
    unsigned int TextMessage::type_num = 6;
    TextMessage::GetTextCallBack TextMessage::resultCallBack = nullptr;
    
    TextMessage* TextMessage::decodeBytes(EIoBuffer *input){
        int nameLength = input->getInt();
        EString name = input->getString(nameLength);
        int contentLength = input->getInt();
        EString content = input->getString(contentLength);

        return new TextMessage(name, content);
    }

    TextMessage::TextMessage(EString _username, EString _content) : username(_username), content(_content) {}

    EIoBuffer* TextMessage::getEncodedMessage(){
        EIoBuffer *ret = EIoBuffer::allocate();
        byte type = type_num;
        int usernameLength = username.length();
        int contentLength = content.length();

        ret->put(type);
        ret->putInt(usernameLength+1);
        ret->putString(username.c_str(), usernameLength);
        ret->putInt(contentLength+1);
        ret->putString(content.c_str(),contentLength);
        return ret;
    }

    void TextMessage::processMessage(){
        string _time = content.substring(0, 20).c_str();
        if(resultCallBack){
            resultCallBack(username.c_str(), _time, content.c_str());
        }
        else{
            DEBUG("Get a nullptr TextMessage callback function\n");
        }
        resultCallBack = nullptr;
    }

    EString TextMessage::toString(){
        return EString("TextMessage:\nFrom: ")+username+("\nContent:")+content+("\n");
    }
    /* --------------------------------------------------------------------------------------------------
     *      7. QueryUserInformationMessage
     * -------------------------------------------------------------------------------------------------- */ 
    unsigned int QueryUserInformationMessage::type_num = 7; 
    QueryUserInformationMessage::QueryUserInformationCallBack QueryUserInformationMessage::resultCallBack = nullptr;

    QueryUserInformationMessage* QueryUserInformationMessage::decodeBytes(EIoBuffer *input){
        DEBUG("QueryUserInformation decode hasnot been implemented\n");
    }

    QueryUserInformationMessage::QueryUserInformationMessage(EString _keyword) : keyword(_keyword) {}

    EIoBuffer* QueryUserInformationMessage::getEncodedMessage(){
        EIoBuffer *ret = EIoBuffer::allocate();
        byte type = type_num;
        int keywordLength = keyword.length();

        ret->put(type);
        ret->putInt(keywordLength+1);
        ret->putString(keyword.c_str(), keywordLength);

        return ret;
    }

    EString QueryUserInformationMessage::toString(){
        return EString("QueryUserInformationMessage")    ;
    }
    /* --------------------------------------------------------------------------------------------------
     *      8. QueryUserResultMessage
     * -------------------------------------------------------------------------------------------------- */  
    unsigned int QueryUserResultMessage::type_num = 8;

    QueryUserResultMessage* QueryUserResultMessage::decodeBytes(EIoBuffer *input){
        int userCount = input->getInt();
        EA<EString> nameList(userCount, EString(""));
        for(int i = 0; i<userCount; i++){
            int nameLength = input->getInt();
            EString name = input->getString(nameLength);
            nameList.setAt(i, name);
        }

        return new QueryUserResultMessage(nameList);
    }

    QueryUserResultMessage::QueryUserResultMessage(EA<EString> _userList) : userList(_userList) {}

    EIoBuffer* QueryUserResultMessage::getEncodedMessage(){
        DEBUG("QueryUserResultMessage encode hasnot been implemented\n");
    }

    void QueryUserResultMessage::processMessage(){
        if(QueryUserInformationMessage::resultCallBack){
            vector<struct userinfo> user_info_list;
            for(int i = 0; i<userList.length(); i++){
                user_info_list.push_back({userList[i].c_str()});
            }
            QueryUserInformationMessage::resultCallBack(user_info_list);
        }
        else{
            DEBUG("Get a nullptr QueryUserInformation callback\n");
        }
    }

    EString QueryUserResultMessage::toString(){
        return EString("QueryUserResultMessage");
    }
    /* --------------------------------------------------------------------------------------------------
     *      9. RequestFriendMessage
     * -------------------------------------------------------------------------------------------------- */  
    unsigned int RequestFriendMessage::type_num = 9;
    // RequestFriendMessage::RequestFriendCallBack RequestFriendMessage::resultCallBack = nullptr;

    RequestFriendMessage* RequestFriendMessage::decodeBytes(EIoBuffer *input){
        DEBUG("RequestFriendMessage decode hasnot been implemented\n");
    }

    RequestFriendMessage::RequestFriendMessage(EString _username, EString _note) : username(_username), note(_note) {}

    EIoBuffer* RequestFriendMessage::getEncodedMessage(){
        EIoBuffer *ret = EIoBuffer::allocate();
        byte type = type_num;
        int usernameLength = username.length();
        int noteLength = note.length();

        ret->put(type);
        ret->putInt(usernameLength+1);
        ret->putString(username.c_str(), usernameLength);
        ret->putInt(noteLength+1);
        ret->putString(note.c_str(),noteLength);

        return ret;
    }

    EString RequestFriendMessage::toString(){
        return EString("RequestFriendMessage");            
    }
    /* --------------------------------------------------------------------------------------------------
     *      10. SendRequestMessage
     * -------------------------------------------------------------------------------------------------- */  
    unsigned int SendRequestMessage::type_num = 10;

    SendRequestMessage* SendRequestMessage::decodeBytes(EIoBuffer *input){
        int nameLength = input->getInt();
        EString name = input->getString(nameLength);
        int noteLength = input->getInt();
        EString note = input->getString(noteLength);
        return new SendRequestMessage(name, note);
    }

    SendRequestMessage::SendRequestMessage(EString _username, EString _note) : username(_username), note(_note) {}

    EIoBuffer* SendRequestMessage::getEncodedMessage(){
        DEBUG("SendQRequestMessage encode hasnot been implemented\n");
    }

    EString SendRequestMessage::toString(){
        return EString("SendRequestMessage");        
    }
    /* --------------------------------------------------------------------------------------------------
     *      11. ReplyPermissionMessage
     * -------------------------------------------------------------------------------------------------- */  
    unsigned int ReplyPermissionMessage::type_num = 11;
    
    ReplyPermissionMessage* ReplyPermissionMessage::decodeBytes(EIoBuffer *input){
        DEBUG("ReplyPermissionMessage decode hasnot been implemented\n");
    }

    ReplyPermissionMessage::ReplyPermissionMessage(boolean _success, EString _username, EString _note) 
        : success(_success), username(_username), note(_note) {}

    EIoBuffer* ReplyPermissionMessage::getEncodedMessage(){
        EIoBuffer *ret = EIoBuffer::allocate();
        byte type = type_num;
        byte suc = success;
        int usernameLength = username.length();
        int noteLength = note.length();

        ret->put(type);
        ret->put(suc);
        ret->putInt(usernameLength+1);
        ret->putString(username.c_str(), usernameLength);
        ret->putInt(noteLength+1);
        ret->putString(note.c_str(),noteLength);

        return ret;
    }

    EString ReplyPermissionMessage::toString(){
        return EString("ReplyPermissionMessage");        
    }
    /* --------------------------------------------------------------------------------------------------
     *      12. SendReplyMessage
     * -------------------------------------------------------------------------------------------------- */  
    unsigned int SendReplyMessage::type_num = 12;

    SendReplyMessage* SendReplyMessage::decodeBytes(EIoBuffer *input){
        byte success = input->get();
        int nameLength = input->getInt();
        EString name = input->getString(nameLength);
        int noteLength = input->getInt();
        EString note = input->getString(noteLength);

        return new SendReplyMessage(success, name, note);
    }

    SendReplyMessage::SendReplyMessage(boolean _success, EString _username, EString _note)
        : success(_success), username(_username), note(_note) {}

    EIoBuffer* SendReplyMessage::getEncodedMessage(){
        DEBUG("SendReplyMessage encode hasnot been implemented\n");
    }

    void SendReplyMessage::processMessage(){
        TextMessage::resultCallBack("server friend reply", username.c_str, success ? "true" : "false");
    }

    EString SendReplyMessage::toString(){
        return EString("SendReplyMessage");        
    }
    /* --------------------------------------------------------------------------------------------------
     *      13. DeleteFriendMessage
     * -------------------------------------------------------------------------------------------------- */  
    unsigned int DeleteFriendMessage::type_num = 13;

    DeleteFriendMessage* DeleteFriendMessage::decodeBytes(EIoBuffer *input){
        DEBUG("DeleteFriendMessage decode hasnot been implemented\n");
    }

    DeleteFriendMessage::DeleteFriendMessage(EString _username) : username(_username){}

    EIoBuffer* DeleteFriendMessage::getEncodedMessage(){
        EIoBuffer *ret = EIoBuffer::allocate();
        byte type = type_num;
        int usernameLength = username.length();

        ret->put(type);
        ret->putInt(usernameLength+1);
        ret->putString(username.c_str(), usernameLength);

        return ret;
    }

    EString DeleteFriendMessage::toString(){
        return EString("DeleteFriendMessage");        
    }
    /* --------------------------------------------------------------------------------------------------
     *      14. QueryFriendListMessage
     * -------------------------------------------------------------------------------------------------- */
    unsigned int QueryFriendListMessage::type_num = 14;         
    QueryFriendListMessage::QueryFriendListMessageCallBack  QueryFriendListMessage::resultCallBack = nullptr;

    QueryFriendListMessage* QueryFriendListMessage::decodeBytes(EIoBuffer *input){
        DEBUG("QueryFriendListMessage decode hasnot been implemented\n");
    }

    QueryFriendListMessage::QueryFriendListMessage(){}

    EIoBuffer* QueryFriendListMessage::getEncodedMessage(){
        EIoBuffer *ret = EIoBuffer::allocate();
        byte type = type_num;

        ret->put(type);

        return ret;
    }

    EString QueryFriendListMessage::toString(){
        return EString("QueryFriendListMessage");        
    }
    /* --------------------------------------------------------------------------------------------------
     *      15. QueryFriendListResultMessage
     * -------------------------------------------------------------------------------------------------- */  
    unsigned int QueryFriendListResultMessage::type_num = 15;

    QueryFriendListResultMessage* QueryFriendListResultMessage::decodeBytes(EIoBuffer *input){
        int friendCount = input->getInt();
        EA<EString> friendList(friendCount, EString(""));
        for(int i = 0; i<friendCount; i++){
            int nameLength = input->getInt();
            EString name = input->getString(nameLength);
            friendList.setAt(i, name);
        }

        return new QueryFriendListResultMessage(friendList);
    }

    QueryFriendListResultMessage::QueryFriendListResultMessage(EA<EString> _friendList) : friendList(_friendList) {}

    EIoBuffer* QueryFriendListResultMessage::getEncodedMessage(){
        DEBUG("QueryFriendListResult encode hasnot been implemented\n");
    }

    void QueryFriendListResultMessage::processMessage(){
        vector<struct userinfo> friend_list;
        for(int i = 0; i<friendList.length(); i++){
            struct userinfo user_info = {string(friendList[i].c_str())};
            friend_list.push_back(user_info);
        }
        if(QueryFriendListMessage::resultCallBack){
            QueryFriendListMessage::resultCallBack(friend_list);
        }
        else{
            DEBUG("Get a nullptr QueryFriendList callback\n");
        }
        QueryFriendListMessage::resultCallBack = nullptr;
    }

    EString QueryFriendListResultMessage::toString(){
        return EString("QueryFriendListResultMessage");        
    }
    /* --------------------------------------------------------------------------------------------------
     *      16. LogOutMessage
     * -------------------------------------------------------------------------------------------------- */  
    unsigned int LogOutMessage::type_num = 16;

    LogOutMessage* LogOutMessage::decodeBytes(EIoBuffer *input){
        DEBUG("LogoutMessage decode hasnot been implemented\n");
    }

    LogOutMessage::LogOutMessage() {}

    EIoBuffer* LogOutMessage::getEncodedMessage(){
        EIoBuffer *ret = EIoBuffer::allocate();
        byte type = type_num;

        ret->put(type);

        return ret;
    }

    EString LogOutMessage::toString(){
        return EString("LogOutMessage");       
    }

}