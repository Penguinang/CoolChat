package enity;
/*
 * 鐢ㄦ埛绫伙細鐢ㄦ潵瀹氫箟鐢ㄦ埛鐨勬暟鎹粨鏋�
 * author锛氫换鏄嗕粦
 * 20180703 鍒涘缓
 * 鏈�鍚庢洿鏀癸細20180703
 */

public class User {
	//private int Id;//鐢ㄦ埛Id
	private String userName;//鐢ㄦ埛鍚�
	private String E_mail;
	private String passWord;//鐢ㄦ埛瀵嗙爜
	//private String friends;//鐢ㄦ埛濂藉弸
	
	
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
