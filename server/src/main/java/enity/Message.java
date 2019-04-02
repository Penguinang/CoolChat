package enity;
/*
 * 消息类：发送消息的数据结构
 * author：任昆仑
 * 20180703创建
 * 最后更改：20180703
 */

public class Message {
	// private int Id;//这条信息的Id
	private String date;// 消息发送的时间
	private String receiveUser;// 接受人
	private String sentUser;// 这条消息的发送人
	private String content;// 消息的内容

	public Message() {

	}

	public Message(String _date, String receiver, String sender, String _content) {
		date = _date;
		receiveUser = receiver;
		sentUser = sender;
		content = _content;
	}

	public String getDate() {
		return date;
	}

	public void setDate(String date) {
		this.date = date;
	}

	public String getReceiveUser() {
		return receiveUser;
	}

	public void setReceiveUser(String receiveUser) {
		this.receiveUser = receiveUser;
	}

	public String getSentUser() {
		return sentUser;
	}

	public void setSentUser(String sentUser) {
		this.sentUser = sentUser;
	}

	public String getContent() {
		return content;
	}

	public void setContent(String content) {
		this.content = content;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((content == null) ? 0 : content.hashCode());
		result = prime * result + ((date == null) ? 0 : date.hashCode());
		result = prime * result + ((receiveUser == null) ? 0 : receiveUser.hashCode());
		result = prime * result + ((sentUser == null) ? 0 : sentUser.hashCode());
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
		Message other = (Message) obj;
		if (content == null) {
			if (other.content != null)
				return false;
		} else if (!content.equals(other.content))
			return false;
		if (date == null) {
			if (other.date != null)
				return false;
		} else if (!date.equals(other.date))
			return false;
		if (receiveUser == null) {
			if (other.receiveUser != null)
				return false;
		} else if (!receiveUser.equals(other.receiveUser))
			return false;
		if (sentUser == null) {
			if (other.sentUser != null)
				return false;
		} else if (!sentUser.equals(other.sentUser))
			return false;
		return true;
	}
}
