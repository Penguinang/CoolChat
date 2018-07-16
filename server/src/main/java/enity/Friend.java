package enity;
/*
 * 用户好友类：用来表示用户的好友,用外键这种东西
 */

public class Friend {
//	private int id;
	private String name;
	private String userName;//是哪个用户的好友
	
	
//	public int getId() {
//		return id;
//	}
//	public void setId(int id) {
//		this.id = id;
//	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getUserName() {
		return userName;
	}
	public void setUserName(String userName) {
		this.userName = userName;
	}
	
	
	
}
