package CoolChat.Messages;

import java.util.HashMap;

import org.apache.mina.core.buffer.IoBuffer;
import org.apache.mina.core.session.IoSession;

import CoolChat.Data.DataManager;

/**
 * Class SendRequestMessage
 */
public class SendRequestMessage extends Message {
	private String sourceUserName;
	private String remark;//备注
   
    public SendRequestMessage (String sourceUserName,String remark) {
    	this.sourceUserName=sourceUserName;
    	this.remark=remark;
    }

	@Override
	public Message getResult(HashMap<String, IoSession> sessions, IoSession session, DataManager dataManager) {
		// TODO 同前面那几个
		return null;
	}

	@Override
	public byte[] getProtocolEncodedBytes() {
		//编号10，请求好友第二阶段
		byte messageType=10;
		int sourceUserNameLength=this.sourceUserName.length();
		byte[] sourceUserNameB=this.sourceUserName.getBytes();
		int remarkLength=remark.length();
		byte[] remarkB=remark.getBytes();
		
		IoBuffer ret=IoBuffer.allocate(1+4+sourceUserNameLength+4+remarkLength);
		ret.put(messageType);
		ret.putInt(sourceUserNameLength);
		ret.put(sourceUserNameB);
		ret.putInt(remarkLength);
		ret.put(remarkB);
		
		return ret.array();
	};
    

}
