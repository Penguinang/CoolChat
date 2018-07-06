#include "Message.h"

namespace Netmodule{
/* --------------------------------------------------------------------------------------------------
 *      Message base
 * -------------------------------------------------------------------------------------------------- */    

    Message* Message::decodeBytesToMessage(EIoBuffer *input) THROWS(EException){
        switch(input->get(0)){
            case 0: return SignupMessage::decodeBytes(input);
            case 1:
            case 2:
            case 3:
        }
    }

    EString Message::toString(){
        // return EString("Raw String");
    }

/* --------------------------------------------------------------------------------------------------
 *      0. SignupMessage
 * -------------------------------------------------------------------------------------------------- */   
    unsigned int SignupMessage::type_num = 0;

    SignupMessage* SignupMessage::decodeBytes(EIoBuffer *input){

    }

    SignupMessage::SignupMessage(EString _username, EString _email, EString _password) : 
        username(_username), email(_email), password(_password) {}; 

    EIoBuffer* SignupMessage::getEncodedMessage(){
        // return EIoBuffer(); 
    }

    EString SignupMessage::toString(){
        
    }

/* --------------------------------------------------------------------------------------------------
 *      2. LoginMessage
 * -------------------------------------------------------------------------------------------------- */   
    unsigned int LoginMessage::type_num = 2;
    LoginMessage* LoginMessage::decodeBytes(EIoBuffer *input){

    }

    LoginMessage::LoginMessage(EString _username, EString _password) : 
        username(_username), password(_password) {}; 

    EIoBuffer* LoginMessage::getEncodedMessage(){

    }

    EString LoginMessage::toString(){

    }
/* --------------------------------------------------------------------------------------------------
 *      3. LoginResultMessage
 * -------------------------------------------------------------------------------------------------- */   
    unsigned int LoginResultMessage::type_num = 3;
    LoginResultMessage* LoginResultMessage::decodeBytes(EIoBuffer *input){

    }

    LoginResultMessage::LoginResultMessage(int _retcode) : retcode(_retcode) {}
    EIoBuffer* LoginResultMessage::getEncodedMessage(){

    }

    EString LoginResultMessage::toString(){

    }
/* --------------------------------------------------------------------------------------------------
 *      4. PullMessage
 * -------------------------------------------------------------------------------------------------- */  
    unsigned int PullMessage::type_num = 4;
    PullMessage* PullMessage::decodeBytes(EIoBuffer *input){

    }

    PullMessage::PullMessage(){

    }

    EIoBuffer* PullMessage::getEncodedMessage(){

    }

    EString PullMessage::toString(){

    }
/* --------------------------------------------------------------------------------------------------
 *      5. PullResultMessage
 * -------------------------------------------------------------------------------------------------- */  
    unsigned int PullResultMessage::type_num = 5;
    PullResultMessage* PullResultMessage::decodeBytes(EIoBuffer *input){

    }

    PullResultMessage::PullResultMessage(EA<EString> _usernameList, EA<EString> _contentList) 
        : usernameList(_usernameList), contentList(_contentList) {}

    EIoBuffer* PullResultMessage::getEncodedMessage(){

    }

    EString PullResultMessage::toString(){

    }
/* --------------------------------------------------------------------------------------------------
 *      6. TextMessage
 * -------------------------------------------------------------------------------------------------- */  
    unsigned int TextMessage::type_num = 6;
    TextMessage* TextMessage::decodeBytes(EIoBuffer *input){

    }

    TextMessage::TextMessage(EString _username, EString _content) : username(_username), content(_content) {}

    EIoBuffer* TextMessage::getEncodedMessage(){
        EIoBuffer *ret = EIoBuffer::allocate();
        byte type = type_num;
        int usernameLength = username.length();
        int contentLength = content.length();

        ret->put(type);
        ret->putInt(usernameLength);
        ret->putString(username.c_str());
        ret->putInt(contentLength);
        ret->putString(content.c_str());
        return ret;
    }

    EString TextMessage::toString(){
        return EString("TextMessage:\nFrom: ")+username+("\nContent:")+content+("\n");
    }
/* --------------------------------------------------------------------------------------------------
 *      7. QueryUserInformationMessage
 * -------------------------------------------------------------------------------------------------- */ 
    unsigned int QueryUserInformationMessage::type_num = 7; 
    QueryUserInformationMessage* QueryUserInformationMessage::decodeBytes(EIoBuffer *input){

    }

    QueryUserInformationMessage::QueryUserInformationMessage(EString _keyword) : keyword(_keyword) {}

    EIoBuffer* QueryUserInformationMessage::getEncodedMessage(){

    }

    EString QueryUserInformationMessage::toString(){
        
    }
/* --------------------------------------------------------------------------------------------------
 *      8. QueryUserResultMessage
 * -------------------------------------------------------------------------------------------------- */  
    unsigned int QueryUserResultMessage::type_num = 8;
    QueryUserResultMessage* QueryUserResultMessage::decodeBytes(EIoBuffer *input){

    }

    QueryUserResultMessage::QueryUserResultMessage(EA<EString> _userList) : userList(_userList) {}

    EIoBuffer* QueryUserResultMessage::getEncodedMessage(){

    }

    EString QueryUserResultMessage::toString(){
        
    }
/* --------------------------------------------------------------------------------------------------
 *      9. RequestFriendMessage
 * -------------------------------------------------------------------------------------------------- */  
    unsigned int RequestFriendMessage::type_num = 9;
    RequestFriendMessage* RequestFriendMessage::decodeBytes(EIoBuffer *input){

    }

    RequestFriendMessage::RequestFriendMessage(EString _username, EString _note) : username(_username), note(_note) {}

    EIoBuffer* RequestFriendMessage::getEncodedMessage(){

    }

    EString RequestFriendMessage::toString(){
        
    }
/* --------------------------------------------------------------------------------------------------
 *      10. SendRequestMessage
 * -------------------------------------------------------------------------------------------------- */  
    unsigned int SendRequestMessage::type_num = 10;
    SendRequestMessage* SendRequestMessage::decodeBytes(EIoBuffer *input){

    }

    SendRequestMessage::SendRequestMessage(EString _username, EString _note) : username(_username), note(_note) {}

    EIoBuffer* SendRequestMessage::getEncodedMessage(){

    }

    EString SendRequestMessage::toString(){
        
    }
/* --------------------------------------------------------------------------------------------------
 *      11. ReplyPermissionMessage
 * -------------------------------------------------------------------------------------------------- */  
    unsigned int ReplyPermissionMessage::type_num = 11;
    ReplyPermissionMessage* ReplyPermissionMessage::decodeBytes(EIoBuffer *input){

    }

    ReplyPermissionMessage::ReplyPermissionMessage(boolean _success, EString _username, EString _note) 
        : success(_success), username(_username), note(_note) {}

    EIoBuffer* ReplyPermissionMessage::getEncodedMessage(){

    }

    EString ReplyPermissionMessage::toString(){
        
    }
/* --------------------------------------------------------------------------------------------------
 *      12. SendReplyMessage
 * -------------------------------------------------------------------------------------------------- */  
    unsigned int SendReplyMessage::type_num = 12;
    SendReplyMessage* SendReplyMessage::decodeBytes(EIoBuffer *input){

    }

    SendReplyMessage::SendReplyMessage(boolean _success, EString _username, EString _note)
        : success(_success), username(_username), note(_note) {}

    EIoBuffer* SendReplyMessage::getEncodedMessage(){

    }

    EString SendReplyMessage::toString(){
        
    }
/* --------------------------------------------------------------------------------------------------
 *      13. DeleteFriendMessage
 * -------------------------------------------------------------------------------------------------- */  
    unsigned int DeleteFriendMessage::type_num = 13;
    DeleteFriendMessage* DeleteFriendMessage::decodeBytes(EIoBuffer *input){

    }

    DeleteFriendMessage::DeleteFriendMessage(EString _username) : username(_username){}

    EIoBuffer* DeleteFriendMessage::getEncodedMessage(){

    }

    EString DeleteFriendMessage::toString(){
        
    }
/* --------------------------------------------------------------------------------------------------
 *      14. QueryFriendListMessage
 * -------------------------------------------------------------------------------------------------- */
    unsigned int QueryFriendListMessage::type_num = 14; 
    QueryFriendListMessage* QueryFriendListMessage::decodeBytes(EIoBuffer *input){

    }

    QueryFriendListMessage::QueryFriendListMessage(){}

    EIoBuffer* QueryFriendListMessage::getEncodedMessage(){

    }

    EString QueryFriendListMessage::toString(){
        
    }
/* --------------------------------------------------------------------------------------------------
 *      15. QueryFriendListResultMessage
 * -------------------------------------------------------------------------------------------------- */  
    unsigned int QueryFriendListResultMessage::type_num = 15;
    QueryFriendListResultMessage* QueryFriendListResultMessage::decodeBytes(EIoBuffer *input){

    }

    QueryFriendListResultMessage::QueryFriendListResultMessage(EA<EString> _friendList) : friendList(_friendList) {}

    EIoBuffer* QueryFriendListResultMessage::getEncodedMessage(){

    }

    EString QueryFriendListResultMessage::toString(){
        
    }
/* --------------------------------------------------------------------------------------------------
 *      16. LogOutMessage
 * -------------------------------------------------------------------------------------------------- */  
    unsigned int LogOutMessage::type_num = 16;
    LogOutMessage* LogOutMessage::decodeBytes(EIoBuffer *input){

    }

    LogOutMessage::LogOutMessage() {}

    EIoBuffer* LogOutMessage::getEncodedMessage(){

    }

    EString LogOutMessage::toString(){
        
    }

}