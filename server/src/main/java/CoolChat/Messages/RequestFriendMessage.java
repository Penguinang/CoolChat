package CoolChat.Messages;

import java.util.HashMap;

import org.apache.mina.core.buffer.IoBuffer;
import org.apache.mina.core.session.IoSession;

import CoolChat.Data.DataManager;

/**
 * Class RequestFriendMessage
 */
public class RequestFriendMessage extends Message {
	private String targetUserName;
	private String remark;
 
    public RequestFriendMessage (String targetUserName,String remark) {
    	this.targetUserName=targetUserName;
    	this.remark=remark;
    }

	@Override
	public Message getResult(HashMap<String, IoSession> sessions, IoSession session, DataManager dataManager) {
		// 返回发送请求消息
		String sourceUserName=session.getAttribute("userName").toString();
		
		return new SendRequestMessage(sourceUserName, this.remark);
	}

	@Override
	public byte[] getProtocolEncodedBytes() {
		// 编号9 请求好友一阶段
		byte messageType=9;
		int targetUserNameLength=this.targetUserName.length();
		byte[] targetUserNameLengthB=this.targetUserName.getBytes();
		int remarkLength=this.remark.length();
		byte[] remarkB = this.remark.getBytes();
		
		IoBuffer ret=IoBuffer.allocate(1+4+targetUserNameLength+4+remarkLength);
		ret.put(messageType);
		ret.putInt(targetUserNameLength);
		ret.put(targetUserNameLengthB);
		ret.putInt(remarkLength);
		ret.put(remarkB);
		
		return ret.array();
	};
    
 

}
