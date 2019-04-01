package CoolChat.Messages;

import java.util.HashMap;

import org.apache.mina.core.buffer.IoBuffer;
import org.apache.mina.core.session.IoSession;

import CoolChat.Data.DataManager;
import CoolChat.Messages.LoginResultMessage;

/**
 * Class LoginMessage
 */
public class LoginMessage extends Message {
	private String userName;
	private String password;

    public LoginMessage (String userName,String password) {
    	this.userName=userName;
    	this.password=password;
    }

	@Override
	public Message getResult(HashMap<String, IoSession> sessions, IoSession session, DataManager dataManager) {
		if(!sessions.containsKey(userName)){
			//如果sessions中没有这个用户了
            sessions.put(userName, session);
        }
        if(!sessions.get(userName).containsAttribute("login") || sessions.get(userName).getAttribute("login") == new Boolean(false)){
            //如果没登录
        	boolean success = dataManager.login(userName, password);
            if(success){
                sessions.get(userName).setAttribute("login", new Boolean(true));
                sessions.get(userName).setAttribute("userName", userName);
                return new LoginResultMessage(0) ;    
            }
            else
                return new LoginResultMessage(-1);//-1：用户名或密码错误
        }
        else{
            return new LoginResultMessage( -2);//-2：用户已登录
        }
	}


	@Override
	public byte[] getProtocolEncodedBytes() {
		byte messageType = 2;
		int sourceUserNameLength = userName.length();
		byte[] sourceUserName = userName.getBytes();
		int passwordLength = password.length();
		byte[] passwordB = password.getBytes();
		
		IoBuffer ret = IoBuffer.allocate(1+4+sourceUserNameLength+4+passwordLength);
		ret.put(messageType);
		ret.putInt(sourceUserNameLength);
		ret.put(sourceUserName);
		ret.putInt(passwordLength);
		ret.put(passwordB);
		
		return ret.array();
	};
    
}
