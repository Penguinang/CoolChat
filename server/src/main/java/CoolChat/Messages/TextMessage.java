package CoolChat.Messages;

import java.util.HashMap;

import org.apache.mina.core.buffer.IoBuffer;
import org.apache.mina.core.session.IoSession;

import CoolChat.Data.DataManager;

/**
 * Class TextMessage
 */
public class TextMessage extends Message {
	private String userName;
	private String content;

	public TextMessage(String userName, String content) {
		this.userName = userName;
		this.content = content;
	}

	@Override
	public Message getResult(HashMap<String, IoSession> sessions, IoSession session, DataManager dataManager) {

		if (sessions.get(userName) == null) {
			if (dataManager.queryUserByName(userName) != null) {
				System.out.println("this user isn't online");
				dataManager.addReceivingMessage(userName, session.getAttribute("userName").toString(),
						new String(this.getProtocolEncodedBytesZeroEnded()));
			} else {
				System.out.println("this user doesn't exist");
			}
		} else {
			TextMessage resultMessage = new TextMessage(session.getAttribute("userName").toString(), content);
			if (sessions.get(userName) != null) {
				sessions.get(userName).write(resultMessage);
				dataManager.sentText(session.getAttribute("userName").toString(), userName, content);
			}
		}

		return null;
	}

	@Override
	public byte[] getProtocolEncodedBytes() {
		// messageType is 6
		byte messageType = 6;
		int userNameLength = this.userName.length();
		byte[] userNameB = this.userName.getBytes();
		int contentLength = this.content.length();
		byte[] contentB = this.content.getBytes();

		IoBuffer ret = IoBuffer.allocate(1 + 4 + userNameLength + 4 + contentLength);
		ret.put(messageType);
		ret.putInt(userNameLength);
		ret.put(userNameB);
		ret.putInt(contentLength);
		ret.put(contentB);

		return ret.array();
	};

	public byte[] getProtocolEncodedBytesZeroEnded() {
		// messageType is 6
		byte messageType = 6;
		int userNameLength = this.userName.length();
		byte[] userNameB = this.userName.getBytes();
		int contentLength = this.content.length();
		byte[] contentB = this.content.getBytes();

		IoBuffer ret = IoBuffer.allocate(1 + 4 + userNameLength + 4 + contentLength + 2);
		ret.put(messageType);
		ret.putInt(userNameLength + 1);
		ret.put(userNameB);
		ret.put((byte) '\0');
		ret.putInt(contentLength + 1);
		ret.put(contentB);
		ret.put((byte) '\0');

		return ret.array();
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((content == null) ? 0 : content.hashCode());
		result = prime * result + ((userName == null) ? 0 : userName.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		TextMessage other = (TextMessage) obj;
		if (content == null) {
			if (other.content != null)
				return false;
		} else if (!content.equals(other.content))
			return false;
		if (userName == null) {
			if (other.userName != null)
				return false;
		} else if (!userName.equals(other.userName))
			return false;
		return true;
	};
}
