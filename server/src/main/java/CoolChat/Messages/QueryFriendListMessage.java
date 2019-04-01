package CoolChat.Messages;

import java.util.HashMap;
import java.util.List;

import org.apache.mina.core.buffer.IoBuffer;
import org.apache.mina.core.session.IoSession;

import CoolChat.Data.DataManager;
import enity.*;

/**
 * Class QueryFriendListMessage
 */
public class QueryFriendListMessage extends Message {

	public QueryFriendListMessage() {
	}

	@Override
	public Message getResult(HashMap<String, IoSession> sessions, IoSession session, DataManager dataManager) {
		// TODO 把当前用户的好友从数据库中拿出来， 放在那个qfresult中
		String userName = session.getAttribute("userName").toString();
		List<Friend> list = dataManager.queryFriendList(userName);

		int number = list.size();
		String[] userNames = new String[number];
		for (int i = 0; i < number; i++) {
			userNames[i] = list.get(i).getUserName();
		}

		return new QueryFriendListResultMessage(number, userNames);
	}

	@Override
	public byte[] getProtocolEncodedBytes() {
		// 编号为14
		byte messageType = 14;

		IoBuffer ret = IoBuffer.allocate(1);
		ret.put(messageType);

		return ret.array();
	};

}
