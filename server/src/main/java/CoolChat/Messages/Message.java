package CoolChat.Messages;

import java.util.HashMap;

import CoolChat.Data.*;
import org.apache.mina.core.buffer.IoBuffer;
import org.apache.mina.core.session.IoSession;


/**
 * Class Message
 */
abstract public class Message {

	public Message () { };

    /**
     * 返回对该消息的处理结果
     * @param        sessions 已经登录的所有会话
     * @param        session 当前用户的会话
     * @param        dataManager 管理所有的数据
     */
    public abstract Message getResult(HashMap<String, IoSession> sessions, IoSession session,DataManager dataManager);


    /**
     * 获得编码后的消息
     */
    public abstract byte[] getProtocolEncodedBytes();


    /**
     * 将字节数组解码为Message对象。
     * @param        in 原始字节数组
     */
    public static Message getDecodedMessage(IoBuffer input) throws Exception
    {
    	//对消息进行解码
    	//TODO：这个地方要仔细检查检查
    	byte messageType = input.get();
    	
    	switch(messageType) {
    	case 0://SignUpMessage
    		int userNameLength=input.getInt();
     	    byte[] userName=new byte[userNameLength];
     	    input.get(userName);
     	    
     	    int e_mailLength=input.getInt();
     	    byte[] e_mail=new byte[e_mailLength];
     	    input.get(e_mail);
     	    
     	    int passwordLength=input.getInt();
    	    byte[] password=new byte[passwordLength];
    	    input.get(password);
    	    
    	    return new SignUpMessage(new String(userName),new String(e_mail),new String(password));
    		
    	case 1://SignUpResult
    		return new SignUpResultMessage();
    		
    	case 2://loginMessage
    		int loginUserNameLength=input.getInt();
     	    byte[] loginUserName=new byte[loginUserNameLength];
     	    input.get(loginUserName);
     	    
     	    int loginPasswordLength=input.getInt();
    	    byte[] loginPassword=new byte[loginPasswordLength];
    	    input.get(loginPassword);
    	    
    	    return new LoginMessage(new String(loginUserName),new String(loginPassword));
    	    
    	case 3://LoginResultMessage
    		int returnCode = input.getInt();
    		
    		return new LoginResultMessage(returnCode);
    		
    	case 4:// PullMessage
    		return new PullMessage();
    		
    	case 5://PullResultMessage
    		int messageNumber=input.getInt();
    		String[] userNames=new String[messageNumber];
    		String[] contents=new String[messageNumber];
    		for(int i=0;i<messageNumber;i++) {
    			int pullUserNameLength=input.getInt();
         	    byte[] pullUserName=new byte[pullUserNameLength];
         	    input.get(pullUserName);
         	    
         	    int contentLength=input.getInt();
        	    byte[] content=new byte[contentLength];
        	    input.get(content);
        	    
        	    userNames[i]=new String(pullUserName);
        	    contents[i]=new String(content);
    		}
    		
    		return new PullResultMessage(messageNumber,userNames,contents);
    	
    	case 6://TextMessage
    		int textNameLength=input.getInt();
     	    byte[] textUserName=new byte[textNameLength];
     	    input.get(textUserName);
     	    
     	    int textContentLength=input.getInt();
    	    byte[] textContent=new byte[textContentLength];
    	    input.get(textContent);
    	    
    	    return new TextMessage(new String(textUserName),new String(textContent));
    	    
    	case 7://QueryUserInformantion
    		int keywordLength=input.getInt();
     	    byte[] keyword=new byte[keywordLength];
     	    input.get(keyword);
     	    
     	    return new QueryUserInformationMessage(new String(keyword));
     	    
    	case 8://QueryUerResultMessage
    		int userNumber=input.getInt();
    		String[] queryUserNames=new String[userNumber];
    		
    		for(int i=0;i<userNumber;i++) {
    			int queryUserNameLength=input.getInt();
         	    byte[] queryUserName=new byte[queryUserNameLength];
         	    input.get(queryUserName);
         	   queryUserNames[i]=new String(queryUserName);
    		}
    		
    		return new QueryUserResultMessage(userNumber,queryUserNames);
    	case 9://requestFriendMessage
    		int targetUserNameLength=input.getInt();
     	    byte[] targetUserName=new byte[targetUserNameLength];
     	    input.get(targetUserName);
     	    
     	    int remarkLength=input.getInt();
    	    byte[] remark=new byte[remarkLength];
    	    input.get(remark);
    	    
    	    return new RequestFriendMessage(new String(targetUserName),new String(remark));
    	    
    	case 10://sendRequestMessage
    		int sourceUserNameLength=input.getInt();
     	    byte[] sourceUserName=new byte[sourceUserNameLength];
     	    input.get(sourceUserName);
     	    
     	    int SendRequestRemarkLength=input.getInt();
    	    byte[] SendRequestRemark=new byte[SendRequestRemarkLength];
    	    input.get(SendRequestRemark);
    	    
    	    return new SendRequestMessage(new String(sourceUserName),new String(SendRequestRemark));
    	    
    	case 11://ReplyPermissionMessage
    		byte rIsAgree=input.get();
    		
    		int ReplyPermissionTargetUserNameLength=input.getInt();
     	    byte[] ReplyPermissionTargetUserName=new byte[ReplyPermissionTargetUserNameLength];
     	    input.get(ReplyPermissionTargetUserName);
     	    
     	    int ReplyPermissionyRemarkLength=input.getInt();
    	    byte[] ReplyPermissionyRemark=new byte[ReplyPermissionyRemarkLength];
    	    input.get(ReplyPermissionyRemark);
    	    
    	    return new SendReplyMessage(rIsAgree,new String(ReplyPermissionTargetUserName),new String(ReplyPermissionyRemark));
    		
    	case 12://SendReplyMessage
    		byte sIsAgree=input.get();
    		
    		int SendReplySourceUserNameLength=input.getInt();
     	    byte[] SendReplySourceUserName=new byte[SendReplySourceUserNameLength];
     	    input.get(SendReplySourceUserName);
     	    
     	    int SendReplyRemarkLength=input.getInt();
    	    byte[] SendReplyRemark=new byte[SendReplyRemarkLength];
    	    input.get(SendReplyRemark);
    	    
    	    return new SendReplyMessage(sIsAgree,new String(SendReplySourceUserName),new String(SendReplyRemark));
    	    
    	case 13://DeleteFriendMessage
    	    int DUserNameLength=input.getInt();
    	    byte[] DUserName=new byte[DUserNameLength];
    	    input.get(DUserName);
    	    return new DeleteFriendMessage(new String(DUserName));
    	    
    	case 14://QueryFreindListMessage
    		return new QueryFriendListMessage();
    		
    	case 15://QueryFrienfListResultMessage
    		int QuserNumber=input.getInt();
    		String[] QueryFriendListResultUserNames=new String[QuserNumber];
    		
    		for(int i=0;i<QuserNumber;i++) {
    			int QueryFriendListResultUserNameLength=input.getInt();
         	    byte[] QueryFriendListResultUserName=new byte[QueryFriendListResultUserNameLength];
         	    input.get(QueryFriendListResultUserName);
         	   QueryFriendListResultUserNames[i]=new String(QueryFriendListResultUserName);
    		}
    		
    		return new QueryFriendListResultMessage(QuserNumber, QueryFriendListResultUserNames);
    		
    	case 16://LogOutMessage
    		return new LogOutMessage();
    		default :
    			throw new Exception("Not implemented");
    	}
    	
    	
    }


    /**
     * @param        rawBytes 原始字节数组
     */
    protected void internalGetDecodedMessage(byte[] rawBytes)
    {
    }


}
