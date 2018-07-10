package CoolChat.Messages;

import java.util.HashMap;

import org.apache.mina.core.buffer.IoBuffer;
import org.apache.mina.core.session.IoSession;

import CoolChat.Data.DataManager;
import dao.SendingMessageDao;

import enity.*;

/**
 * Class TextMessage
 */
public class TextMessage extends Message {
	private String userName;
	private String content;
  
    public TextMessage (String userName,String content) {
    	this.userName=userName;
    	this.content=content;
    }

	@Override
	public Message getResult(HashMap<String, IoSession> sessions, IoSession session, DataManager dataManager) {
		
		IoSession aSession = sessions.get(userName);
		if(aSession== null) {
			System.out.println("this user isn't online or don't exist.");
		}
		if(aSession.containsAttribute("login")) {
			TextMessage resultMessage=new TextMessage(session.getAttribute("userName").toString(),content);
			session.write(resultMessage);
		}
		else {
			//SendingMessageDao sMessageDao=new SendingMessageDao();
			//SendingMessage sMessage=new SendingMessage();
			//sMessageDao.addMessage();
			dataManager.addReceivingMessage(userName,session.getAttribute("userName").toString(),content);
		}
		
		return null;
	}

	@Override
	public byte[] getProtocolEncodedBytes() {
		//messageType is 6
		byte messageType=6;
		int userNameLength=this.userName.length();
		byte[] userNameB=this.userName.getBytes();
		int contentLength=this.content.length();
		byte[] contentB=this.content.getBytes();
		
		IoBuffer ret=IoBuffer.allocate(1+4+userNameLength+4+contentLength);
		ret.put(messageType);
		ret.putInt(userNameLength);
		ret.put(userNameB);
		ret.putInt(contentLength);
		ret.put(contentB);
		
		return ret.array();
	};
   

}
