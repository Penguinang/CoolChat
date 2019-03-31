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
     * 杩斿洖瀵硅娑堟伅鐨勫鐞嗙粨鏋�
     * @param        sessions 宸茬粡鐧诲綍鐨勬墍鏈変細璇�
     * @param        session 褰撳墠鐢ㄦ埛鐨勪細璇�
     * @param        dataManager 绠＄悊鎵�鏈夌殑鏁版嵁
     */
    public abstract Message getResult(HashMap<String, IoSession> sessions, IoSession session,DataManager dataManager);


    /**
     * 鑾峰緱缂栫爜鍚庣殑娑堟伅
     */
    public abstract byte[] getProtocolEncodedBytes();


    /**
     * 灏嗗瓧鑺傛暟缁勮В鐮佷负Message瀵硅薄銆�
     * @param        in 鍘熷瀛楄妭鏁扮粍
     */
    public static Message getDecodedMessage(IoBuffer input) throws Exception
    {
    	//瀵规秷鎭繘琛岃В鐮�
    	//TODO锛氳繖涓湴鏂硅浠旂粏妫�鏌ユ鏌�
    	byte messageType = input.get();
    	
    	switch(messageType) {
    	//把字符串最后的0去掉
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
    	    
    	    
    	    return new SignUpMessage(removeLastChar(new String(userName)),new String(e_mail).substring(0, e_mailLength-1),new String(password).substring(0, passwordLength-1));
    		
    	case 1://SignUpResult
    		return new SignUpResultMessage();
    		
    	case 2://loginMessage
    		int loginUserNameLength=input.getInt();
     	    byte[] loginUserName=new byte[loginUserNameLength];
     	    input.get(loginUserName);
     	    
     	    int loginPasswordLength=input.getInt();
    	    byte[] loginPassword=new byte[loginPasswordLength];
    	    input.get(loginPassword);
    	    
    	    return new LoginMessage(removeLastChar( new String(loginUserName)),removeLastChar( new String(loginPassword)));
    	    
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
        	    
        	    userNames[i]=removeLastChar(new String(pullUserName));
        	    contents[i]=removeLastChar(new String(content));
    		}
    		
    		return new PullResultMessage(messageNumber,userNames,contents);
    	
    	case 6://TextMessage
    		int textNameLength=input.getInt();
     	    byte[] textUserName=new byte[textNameLength];
     	    input.get(textUserName);
     	    
     	    int textContentLength=input.getInt();
    	    byte[] textContent=new byte[textContentLength];
    	    input.get(textContent);
    	    
    	    return new TextMessage(removeLastChar(new String(textUserName)),removeLastChar(new String(textContent)));
    	    
    	case 7://QueryUserInformantion
    		int keywordLength=input.getInt();
     	    byte[] keyword=new byte[keywordLength];
     	    input.get(keyword);
     	    
     	    return new QueryUserInformationMessage(removeLastChar(new String(keyword)));
     	    
    	case 8://QueryUerResultMessage
    		int userNumber=input.getInt();
    		String[] queryUserNames=new String[userNumber];
    		
    		for(int i=0;i<userNumber;i++) {
    			int queryUserNameLength=input.getInt();
         	    byte[] queryUserName=new byte[queryUserNameLength];
         	    input.get(queryUserName);
         	   queryUserNames[i]=removeLastChar(new String(queryUserName));
    		}
    		
    		return new QueryUserResultMessage(userNumber,queryUserNames);
    		
    	case 9://requestFriendMessage
    		int targetUserNameLength=input.getInt();
     	    byte[] targetUserName=new byte[targetUserNameLength];
     	    input.get(targetUserName);
     	    
     	    int remarkLength=input.getInt();
    	    byte[] remark=new byte[remarkLength];
    	    input.get(remark);
    	    
    	    return new RequestFriendMessage(removeLastChar(new String(targetUserName)),removeLastChar(new String(remark)));
    	    
    	case 10://sendRequestMessage
    		int sourceUserNameLength=input.getInt();
     	    byte[] sourceUserName=new byte[sourceUserNameLength];
     	    input.get(sourceUserName);
     	    
     	    int SendRequestRemarkLength=input.getInt();
    	    byte[] SendRequestRemark=new byte[SendRequestRemarkLength];
    	    input.get(SendRequestRemark);
    	    
    	    return new SendRequestMessage(removeLastChar(new String(sourceUserName)),removeLastChar(new String(SendRequestRemark)));
    	    
    	case 11://ReplyPermissionMessage
    		byte rIsAgree=input.get();
    		
    		int ReplyPermissionTargetUserNameLength=input.getInt();
     	    byte[] ReplyPermissionTargetUserName=new byte[ReplyPermissionTargetUserNameLength];
     	    input.get(ReplyPermissionTargetUserName);
     	    
     	    int ReplyPermissionyRemarkLength=input.getInt();
    	    byte[] ReplyPermissionyRemark=new byte[ReplyPermissionyRemarkLength];
    	    input.get(ReplyPermissionyRemark);
    	    
    	    //return new Re(rIsAgree,removeLastChar(new String(ReplyPermissionTargetUserName)),removeLastChar(new String(ReplyPermissionyRemark)));
    		return new ReplyPermissionMessage(rIsAgree, removeLastChar(new String(ReplyPermissionTargetUserName)),removeLastChar(new String(ReplyPermissionyRemark)) );
    	    
    	case 12://SendReplyMessage
    		byte sIsAgree=input.get();
    		
    		int SendReplySourceUserNameLength=input.getInt();
     	    byte[] SendReplySourceUserName=new byte[SendReplySourceUserNameLength];
     	    input.get(SendReplySourceUserName);
     	    
     	    int SendReplyRemarkLength=input.getInt();
    	    byte[] SendReplyRemark=new byte[SendReplyRemarkLength];
    	    input.get(SendReplyRemark);
    	    
    	    return new SendReplyMessage(sIsAgree,new String(SendReplySourceUserName),removeLastChar(new String(SendReplyRemark)));
    	    
    	case 13://DeleteFriendMessage
    	    int DUserNameLength=input.getInt();
    	    byte[] DUserName=new byte[DUserNameLength];
    	    input.get(DUserName);
    	    return new DeleteFriendMessage(removeLastChar(new String(DUserName)));
    	    
    	case 14://QueryFreindListMessage
    		return new QueryFriendListMessage();
    		
    	case 15://QueryFrienfListResultMessage
    		int QuserNumber=input.getInt();
    		String[] QueryFriendListResultUserNames=new String[QuserNumber];
    		
    		for(int i=0;i<QuserNumber;i++) {
    			int QueryFriendListResultUserNameLength=input.getInt();
         	    byte[] QueryFriendListResultUserName=new byte[QueryFriendListResultUserNameLength];
         	    input.get(QueryFriendListResultUserName);
         	   QueryFriendListResultUserNames[i]=removeLastChar(new String(QueryFriendListResultUserName));
    		}
    		
    		return new QueryFriendListResultMessage(QuserNumber, QueryFriendListResultUserNames);
    		
    	case 16://LogOutMessage
    		return new LogOutMessage();
    		default :
    			throw new Exception("Not implemented");
    	}
    	
    	
    }


    /**
     * @param        rawBytes 鍘熷瀛楄妭鏁扮粍
     */
    protected void internalGetDecodedMessage(byte[] rawBytes)
    {
    }

    
    public static String removeLastChar(String string) {
    	return string.substring(0, string.length()-1);
    }

}
