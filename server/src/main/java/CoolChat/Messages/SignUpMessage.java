package CoolChat.Messages;

import java.util.HashMap;

import org.apache.mina.core.buffer.IoBuffer;
import org.apache.mina.core.session.IoSession;

import CoolChat.Data.DataManager;

/**
 * Class SignUpMessage
 */
public class SignUpMessage extends Message {
	private String userName;
	private String e_mail;
	private String password;
	

    public SignUpMessage (String userName,String password,String e_mail) {
    	this.userName=userName;
    	this.password=password;
    	this.e_mail=e_mail;
    }

	@Override
	public Message getResult(HashMap<String, IoSession> sessions, IoSession session, DataManager dataManager) {
		// TODO Auto-generated method stub
		if(dataManager.signUp(this.userName, this.e_mail, this.password)) {
			return new SignUpResultMessage();
		}
		else {
			return null;
			}
		
		}

	@Override
	public byte[] getProtocolEncodedBytes() {
		// 编号为0
		byte messageType = 0;
		int userNameLength=userName.length();
		byte[] userNameB=userName.getBytes();
		int e_mailLength=e_mail.length();
		byte[] e_mailB=e_mail.getBytes();
		int passwordLength=password.length();
		byte[] passwordB=password.getBytes();
		
		IoBuffer ret=IoBuffer.allocate(1+4+userNameLength+4+e_mailLength+4+passwordLength);
		ret.put(messageType);
		ret.putInt(userNameLength);
		ret.put(userNameB);
		ret.putInt(e_mailLength);
		ret.put(e_mailB);
		ret.putInt(passwordLength);
		ret.put(passwordB);
	
		return ret.array();
	};
    
   

}
