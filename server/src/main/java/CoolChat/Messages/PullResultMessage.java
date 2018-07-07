package CoolChat.Messages;

import java.util.HashMap;

import org.apache.mina.core.buffer.IoBuffer;
import org.apache.mina.core.session.IoSession;

import CoolChat.Data.DataManager;

/**
 * Class PullResultMessage
 */
public class PullResultMessage extends Message {
	private int messageNumber;
	private String[] userName;
	private String[] content;
	
    public PullResultMessage (int messageNumber,String[] userName,String[] content) {
    	this.messageNumber=messageNumber;
    	this.userName=userName;
    	this.content=content;
    }

	@Override
	public Message getResult(HashMap<String, IoSession> sessions, IoSession session, DataManager dataManager) {
		return null;
	}

	@Override
	public byte[] getProtocolEncodedBytes() {
		// 编号为5
		byte messageType = 5;
		int size=5;//messageType's size and messageNumber's size
		
		for(int i=0;i<this.messageNumber;i++) {
			size=size+4;
			size=size+userName[i].length();
			size=size+4;
			size=size+content[i].length();
		}
		
		IoBuffer ret=IoBuffer.allocate(size);
		ret.put(messageType);
		ret.putInt(messageNumber);
		for(int i=0;i<this.messageNumber;i++) {
			ret.putInt(userName[i].length());
			ret.put(userName[i].getBytes());
			ret.putInt(content[i].length());
			ret.put(content[i].getBytes());
		}
		
		return ret.array();
	};
    


}
