package dao;
/*
 * dao鍖呮槸瀵瑰簲涓庢暟鎹簱绫荤殑鍖�
 * UserDao绫伙細瀵瑰簲鏁版嵁搴撲腑鐢ㄦ埛琛ㄧ殑鎿嶄綔锛�
 * 
 */

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import enity.User;

public class UserDao {
	private JdbcUtils util;
	
	public UserDao() {
		util =new JdbcUtils();
	}

	/*
	 *  灏嗙敤鎴锋彃鍏ユ暟鎹簱涓殑鐢ㄦ埛琛�
	 */
	public void addUser(User user) {
		PreparedStatement ps =null;
		Connection conn = util.getConnection();
		String sql ="insert into user(userName,E_mail,password) values(?,?,?)";
		
		try {
			ps=conn.prepareStatement(sql);
			ps.setString(1,user.getUserName());
			ps.setString(2, user.getE_mail());
			ps.setString(3, user.getPassWord());
			
			ps.execute();
			ps.close();
			conn.close();
		}catch(SQLException e) {
			e.printStackTrace();
		}
	}
	
	/*
	 * 浠庣敤鎴疯〃涓垹闄ょ敤鎴�
	 */
	public void deleteUser(User user) {
		PreparedStatement ps =null;
		Connection conn = util.getConnection();
		String sql="delete from user where userName=?";
		
		try {
			ps=conn.prepareStatement(sql);
			ps.setString(1,user.getUserName());
			ps.execute();
			ps.close();
			conn.close();
		}catch(SQLException e) {
			e.printStackTrace();
		}
	}
	
	/*
	 * 鏇存柊鐢ㄦ埛琛ㄤ腑鐨勪俊鎭紝鍙兘鐢ㄤ笉鍒颁簡锛岀幇鍦ㄨ繖鍐欑潃鍚�
	 */
	public void updateUser(User user) {
		PreparedStatement ps = null;
		Connection conn = util.getConnection();
		String sql = "update user set userName=? password=? where userName=?";
		
		try {
			ps = conn.prepareStatement(sql);
			ps.setString(1, user.getUserName());
			ps.setString(2, user.getPassWord());
			ps.setString(3, user.getUserName());
			ps.execute();
			ps.close();
			conn.close();
		}catch(SQLException e) {
			e.printStackTrace();
		}
	}
	
	/*
	 * 閫氳繃Id鏌ユ壘鐢ㄦ埛锛屽彲鑳戒細鍦ㄤ慨鏀硅繖涓粨鏋�
	 * 鏁版嵁搴撲細鑷姩鐢熸垚ID锛岃繖鏄垜璁剧疆鐨勶紝浣嗗鐢ㄦ埛璧嬪�肩殑鏃跺�欐病鏈夊ID璧嬪��
	 */
	/*
	public User getUserById(int Id) {
		PreparedStatement ps = null;
		Connection conn = util.getConnection();
		User user = null;
		ResultSet rs = null;
		String sql = "select * from user where id=?";
		
		try {
			
			ps = conn.prepareStatement(sql);
			ps.setInt(1,Id);
			rs = ps.executeQuery();
			while(rs.next()) {
				user=new User();//杩欓噷鍙笉鍙互鍦ㄥ闈㈠啓
				user.setId(rs.getInt("Id"));
				user.setUserName(rs.getString("userName"));
				user.setPassWord(rs.getString("password"));
			}
			
			ps.close();
			conn.close();
		}catch(SQLException e) {
			e.printStackTrace();
		}
	
		return user;
	}
	*/
	
	/*
	 * 閫氳繃鐢ㄦ埛鍚嶆煡鎵剧敤鎴�
	 */
	public User getUserByName(String userName) {
		PreparedStatement ps = null;
		Connection conn = util.getConnection();
		String sql ="select * from user where userName=?";
		ResultSet rs = null;
		User user = null;
		try {
			ps = conn.prepareStatement(sql);
			ps.setString(1, userName);
			rs = ps.executeQuery();
			
			while(rs.next()) {
				user = new User();
//				user.setId(rs.getInt("Id"));
				user.setPassWord(rs.getString("password"));
				user.setUserName(rs.getString("userName"));
				user.setE_mail(rs.getString("E_mail"));
			}
			rs.close();
			ps.close();
			conn.close();
		}catch(SQLException e) {
			e.printStackTrace();
		}
		
		return user;
		
	}
	
	public List<User> getAllUser(){
		PreparedStatement ps = null;
		Connection conn= util.getConnection();
		String sql = "select * from user";
		
		ResultSet rs =null;
		
		List<User> list = new ArrayList<User>();
		User user= new User();
		
		try {
			ps=conn.prepareStatement(sql);
			rs = ps.executeQuery();
			
			while(rs.next()) {
				user = new User();
				user.setUserName(rs.getString("userName"));
				user.setPassWord(rs.getString("password"));
				user.setE_mail(rs.getString("E_mail"));
				
				list.add(user);
			}
			
			rs.close();
			ps.close();
			conn.close();
		}catch(SQLException	e) {
			e.printStackTrace();
		}
		
		return list;
	}
	
}
