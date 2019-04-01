package enity;
/*
 * 用户类：用来定义用户的数据结构
 * author：任昆仑
 * 20180703 创建
 * 最后更改：20180703
 */

public class User {
	//private int Id;//用户Id
	private String userName;//用户名
	private String E_mail;
	private String passWord;//用户密码
	//private String friends;//用户好友
	
	
	public String getUserName() {
		return userName;
	}
	public void setUserName(String userName) {
		this.userName = userName;
	}
	public String getE_mail() {
		return E_mail;
	}
	public void setE_mail(String e_mail) {
		E_mail = e_mail;
	}
	public String getPassWord() {
		return passWord;
	}
	public void setPassWord(String passWord) {
		this.passWord = passWord;
	}
	

	
	
}
