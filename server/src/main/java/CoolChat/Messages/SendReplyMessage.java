package CoolChat.Messages;

import java.util.HashMap;

import org.apache.mina.core.buffer.IoBuffer;
import org.apache.mina.core.session.IoSession;

import CoolChat.Data.DataManager;

/**
 * Class SendReplyMessage
 */
public class SendReplyMessage extends Message {
	private byte isAgree;
	private String sourceUserName;
	private String remark;//备注
   
    public SendReplyMessage (byte isAgree,String sourceUserName,String remark) {
    	this.isAgree=isAgree;
    	this.sourceUserName=sourceUserName;
    	this.remark=remark;
    }

	@Override
	public Message getResult(HashMap<String, IoSession> sessions, IoSession session, DataManager dataManager) {
		return null;
	}

	@Override
	public byte[] getProtocolEncodedBytes() {
		// 编号12,请求好友第四阶段
		byte messageType=12;
		int sourceUserNameLength=this.sourceUserName.length();
		byte[] sourceUserNameB=this.sourceUserName.getBytes();
		int remarkLength=remark.length();
		byte[] remarkB=remark.getBytes();
		
		IoBuffer ret=IoBuffer.allocate(1+4+4+sourceUserNameLength+4+remarkLength);
		ret.put(messageType);
		ret.put(isAgree);
		ret.putInt(sourceUserNameLength);
		ret.put(sourceUserNameB);
		ret.putInt(remarkLength);
		ret.put(remarkB);
		
		return ret.array();
	};
   

}
