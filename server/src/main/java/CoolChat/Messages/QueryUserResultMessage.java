package CoolChat.Messages;

import java.util.HashMap;

import org.apache.mina.core.buffer.IoBuffer;
import org.apache.mina.core.session.IoSession;

import CoolChat.Data.DataManager;

/**
 * Class QueryUserResultMessage
 */
public class QueryUserResultMessage extends Message {
	private int userNumber;
	private String[] userNames;
  
    public QueryUserResultMessage (int userNumber,String[] userNames) {
    	this.userNumber=userNumber;
    	this.userNames=userNames;
    }

	@Override
	public Message getResult(HashMap<String, IoSession> sessions, IoSession session, DataManager dataManager) {
		return null;
	}

	@Override
	public byte[] getProtocolEncodedBytes() {
		// 编号为8
		byte messageType=8;
		int size=5;//message'type and userNumber's size
		for(int i=0;i<this.userNumber;i++) {
			size=size+4;
			size=size+userNames[i].length();
		}
		
		IoBuffer ret = IoBuffer.allocate(size);
		ret.put(messageType);
		ret.putInt(userNumber);
		for(int i=0;i<userNumber;i++) {
			ret.putInt(userNames[i].length());
			ret.put(userNames[i].getBytes());
		}
		return ret.array();
	};
    
  

}
