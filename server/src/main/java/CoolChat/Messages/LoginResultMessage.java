package CoolChat.Messages;

import java.util.HashMap;

import org.apache.mina.core.buffer.IoBuffer;
import org.apache.mina.core.session.IoSession;

import CoolChat.Data.DataManager;

/**
 * Class LoginResultMessage
 */
public class LoginResultMessage extends Message {
	private int returnCode;
    
    public LoginResultMessage (int returnCode) {
    	this.returnCode=returnCode;
    }

	@Override
	public Message getResult(HashMap<String, IoSession> sessions, IoSession session, DataManager dataManager) {
		return null;
	}

	@Override
	public byte[] getProtocolEncodedBytes() {
		byte messageType = 3;
		
		IoBuffer ret = IoBuffer.allocate(1+4);
		ret.put(messageType);
		ret.putInt(returnCode);
		
		return ret.array();
	};
	
	public String toString() {
		String returnInfo=null;
		switch(this.returnCode){
			case 0:returnInfo="success";break;
			case -1:returnInfo="wrong userName or password!";break;
			case -2:returnInfo="user has logged in";break;
			
			default:returnInfo="unkonwn reason";break;
		}
		
		return ": "+returnInfo;
	}
    
  

}
