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

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((friendName == null) ? 0 : friendName.hashCode());
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
		Friend other = (Friend) obj;
		if (friendName == null) {
			if (other.friendName != null)
				return false;
		} else if (!friendName.equals(other.friendName))
			return false;
		if (userName == null) {
			if (other.userName != null)
				return false;
		} else if (!userName.equals(other.userName))
			return false;
		return true;
	}
}
