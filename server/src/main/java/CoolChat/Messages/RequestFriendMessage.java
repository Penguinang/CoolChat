package CoolChat.Messages;

import java.util.HashMap;

import org.apache.mina.core.buffer.IoBuffer;
import org.apache.mina.core.session.IoSession;

import CoolChat.Data.DataManager;

/**
 * Class RequestFriendMessage
 */
public class RequestFriendMessage extends Message {
	private String targetUserName;
	private String remark;

	public RequestFriendMessage(String targetUserName, String remark) {
		this.targetUserName = targetUserName;
		this.remark = remark;
	}

	@Override
	public Message getResult(HashMap<String, IoSession> sessions, IoSession session, DataManager dataManager) {
		// 返回发送请求消息
		System.out.println(targetUserName + " " + remark);

		String sourceUserName = session.getAttribute("userName").toString();
		if (sessions.get(targetUserName) == null) {
			// 查询数据库
			if (dataManager.queryUserByName(targetUserName) == null) {
				System.out.println("there is no user named " + targetUserName);
			} else {
				// TODO 对方不在线时候保存消息，对于其他所有类型的消息都要这样做
				dataManager.addReceivingMessage(targetUserName, session.getAttribute("userName").toString(),
						new String(this.getProtocolEncodedBytesZeroEnded()));
			}

		} else {
			sessions.get(targetUserName).write(new SendRequestMessage(sourceUserName, this.remark));
		}
		return null;
	}

	@Override
	public byte[] getProtocolEncodedBytes() {
		// 编号9 请求好友一阶段
		byte messageType = 9;
		int targetUserNameLength = this.targetUserName.length();
		byte[] targetUserNameLengthB = this.targetUserName.getBytes();
		int remarkLength = this.remark.length();
		byte[] remarkB = this.remark.getBytes();

		IoBuffer ret = IoBuffer.allocate(1 + 4 + targetUserNameLength + 4 + remarkLength);
		ret.put(messageType);
		ret.putInt(targetUserNameLength);
		ret.put(targetUserNameLengthB);
		ret.putInt(remarkLength);
		ret.put(remarkB);

		return ret.array();
	};

	public byte[] getProtocolEncodedBytesZeroEnded() {
		// 编号9 请求好友一阶段
		byte messageType = 9;
		int targetUserNameLength = this.targetUserName.length();
		byte[] targetUserNameLengthB = this.targetUserName.getBytes();
		int remarkLength = this.remark.length();
		byte[] remarkB = this.remark.getBytes();

		IoBuffer ret = IoBuffer.allocate(1 + 4 + targetUserNameLength + 4 + remarkLength+2);
		ret.put(messageType);
		ret.putInt(targetUserNameLength + 1);
		ret.put(targetUserNameLengthB);
		ret.put((byte) '\0');
		ret.putInt(remarkLength + 1);
		ret.put(remarkB);
		ret.put((byte) '\0');

		return ret.array();
	};
}
