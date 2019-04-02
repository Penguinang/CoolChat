package CoolChat.Messages;

import java.util.HashMap;

import org.apache.mina.core.buffer.IoBuffer;
import org.apache.mina.core.session.IoSession;

import CoolChat.Data.DataManager;

/**
 * Class ReplyPermissionMessage
 */
public class ReplyPermissionMessage extends Message {
	private byte isAgree;
	private String targetUserName;
	private String remark;//备注
  
    public ReplyPermissionMessage (byte isAgree,String targetUserName,String remark) {
    	this.isAgree=isAgree;
    	this.targetUserName=targetUserName;
    	this.remark=remark;
    }

	@Override
	public Message getResult(HashMap<String, IoSession> sessions, IoSession session, DataManager dataManager) {
		String sourceUserName=session.getAttribute("userName").toString();
		
		if(sessions.get(targetUserName)!=null) {
			if(isAgree==1) {
				dataManager.changeUserRelation(sourceUserName, targetUserName, true);
				dataManager.changeUserRelation(targetUserName, sourceUserName, true);
			}
			sessions.get(targetUserName).write(new SendReplyMessage(this.isAgree, sourceUserName,this.remark));
		}
		else {
			System.out.println("the user don't online");
		}
		return null;
	}

	@Override
	public byte[] getProtocolEncodedBytes() {
		// 编号11，请求好友第三阶段
		byte messageType=11;
		int targetUserNameLength=this.targetUserName.length();
		byte[] targetUserNameB=this.targetUserName.getBytes();
		int remarkLength=remark.length();
		byte[] remarkB=remark.getBytes();
		
		IoBuffer ret=IoBuffer.allocate(1+4+4+targetUserNameLength+4+remarkLength);
		ret.put(messageType);
		ret.put(isAgree);
		ret.putInt(targetUserNameLength);
		ret.put(targetUserNameB);
		ret.putInt(remarkLength);
		ret.put(remarkB);
		
		return ret.array();
	}
    
 

}
