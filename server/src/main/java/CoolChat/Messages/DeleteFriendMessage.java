package CoolChat.Messages;

import java.util.HashMap;

import org.apache.mina.core.buffer.IoBuffer;
import org.apache.mina.core.session.IoSession;

import CoolChat.Data.DataManager;

/**
 * Class DeleteFriendMessage
 */
public class DeleteFriendMessage extends Message {
	private String userName;

    public DeleteFriendMessage (String userName) {
    	this.userName=userName;//要删除的好友
    }

	@Override
	public Message getResult(HashMap<String, IoSession> sessions, IoSession session, DataManager dataManager) {
		// 从这个用户的相应好友表中删除指定用户
		dataManager.changeUserRelation(session.getAttribute("userName").toString(), userName, false);
		
		return null;
	}

	@Override
	public byte[] getProtocolEncodedBytes() {
		// 编号	13
		byte messageType=13;
		int userNameLength = userName.length();
		byte[] userNameB=userName.getBytes();
		
		IoBuffer ret = IoBuffer.allocate(1+4+userNameLength);
		ret.putInt(messageType);
		ret.putInt(userNameLength);
		ret.put(userNameB);
		
		return ret.array();
	};
    
   

}
