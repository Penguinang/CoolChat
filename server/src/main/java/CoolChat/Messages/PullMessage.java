package CoolChat.Messages;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import org.apache.mina.core.buffer.IoBuffer;
import org.apache.mina.core.session.IoSession;

import CoolChat.Data.DataManager;

/**
 * Class PullMessage
 */
public class PullMessage extends Message {

	public PullMessage() {
	}

	@Override
	public Message getResult(HashMap<String, IoSession> sessions, IoSession session, DataManager dataManager) {
		// pullMessage 的result，从数据库中把未发送的消息拿出来， 应该是放在pullResultmessage中
		String userName = session.getAttribute("userName").toString();
		List<String> sourceUserNameList = new ArrayList<String>();
		List<String> contentList = new ArrayList<String>();

		dataManager.pullUserMessage(userName, sourceUserNameList, contentList);

		int messageNumber = sourceUserNameList.size();
		String[] sourceUserName = new String[messageNumber];
		String[] content = new String[messageNumber];

		for (int i = 0; i < messageNumber; i++) {
			sourceUserName[i] = sourceUserNameList.get(i);
			content[i] = contentList.get(i);
			dataManager.sentText(sourceUserName[i], userName, content[i]);
		}

		return new PullResultMessage(messageNumber, sourceUserName, content);
	}

	@Override
	public byte[] getProtocolEncodedBytes() {
		// 编号为4
		byte messageType = 4;

		IoBuffer ret = IoBuffer.allocate(1);
		ret.put(messageType);

		return ret.array();
	};

}
