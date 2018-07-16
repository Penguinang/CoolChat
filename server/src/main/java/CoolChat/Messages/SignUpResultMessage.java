package CoolChat.Messages;

import java.util.HashMap;

import org.apache.mina.core.buffer.IoBuffer;
import org.apache.mina.core.session.IoSession;

import CoolChat.Data.DataManager;

/**
 * Class SignUpResultMessage
 */
public class SignUpResultMessage extends Message {

    public SignUpResultMessage () { }

	@Override
	public Message getResult(HashMap<String, IoSession> sessions, IoSession session, DataManager dataManager) {
		return null;
	}

	@Override
	public byte[] getProtocolEncodedBytes() {
		// 编号为1
		byte messageType = 1;
		
		IoBuffer ret = IoBuffer.allocate(1);
		ret.put(messageType);
	
		return ret.array();
	};
    
   

}
