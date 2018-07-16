package enity;
/*
 * 消息类：发送消息的数据结构
 * author：任昆仑
 * 20180703创建
 * 最后更改：20180703
 */

public class Message {
//	private int Id;//这条信息的Id
	private String date;//消息发送的时间
	private String receiveUser;//接受人
	private String sentUser;//这条消息的发送人
	private String content;//消息的内容
	
	
//	public int getId() {
//		return Id;
//	}
//	public void setId(int id) {
//		Id = id;
//	}
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
	
	

}
