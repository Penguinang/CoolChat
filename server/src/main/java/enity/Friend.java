package enity;
/*
 * 用户好友类：用来表示用户的好友,用外键这种东西
 */

public class Friend {

	// 是哪个用户的好友
	private String userName;
	// 好友名字叫什么
	private String friendName;

	public Friend() {
	}

	public Friend(String uname, String fname) {
		userName = uname;
		friendName = fname;
	}

	public String getUserName() {
		return userName;
	}

	public void setUserName(String name) {
		this.userName = name;
	}

	public String getFriendName() {
		return friendName;
	}

	public void setFriendName(String userName) {
		this.friendName = userName;
	}
}
