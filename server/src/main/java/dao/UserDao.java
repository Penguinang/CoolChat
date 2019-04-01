package dao;
/*
 * dao包是对应与数据库类的包
 * UserDao类：对应数据库中用户表的操作；
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
	 *  将用户插入数据库中的用户表
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
	 * 从用户表中删除用户
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
	 * 更新用户表中的信息，可能用不到了，现在这写着吧
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
	 * 通过Id查找用户，可能会在修改这个结构
	 * 数据库会自动生成ID，这是我设置的，但对用户赋值的时候没有对ID赋值
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
				user=new User();//这里可不可以在外面写
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
	 * 通过用户名查找用户
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
