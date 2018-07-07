package CoolChat.Messages;

import java.util.HashMap;

import org.apache.mina.core.buffer.IoBuffer;
import org.apache.mina.core.session.IoSession;

import CoolChat.Data.DataManager;

/**
 * Class LogOutMessage
 */
public class LogOutMessage extends Message {

    public LogOutMessage () { }

	@Override
	public Message getResult(HashMap<String, IoSession> sessions, IoSession session, DataManager dataManager) {
		// 把用户的状态改一下,将这个session从Hashmap 中删除；
		session.replaceAttribute("login", true, false);
		sessions.remove(session.getAttribute("userName").toString());
		return null;
	}

	@Override
	public byte[] getProtocolEncodedBytes() {
		// 编号16
		byte messageType = 16;
		
		IoBuffer ret = IoBuffer.allocate(1);
		ret.put(messageType);
		
		return ret.array();
	};
  

}
