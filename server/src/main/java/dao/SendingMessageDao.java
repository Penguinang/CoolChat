package dao;
/*
 * MessageDao类：对数据库中的信息表进行操作
 */

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import enity.Message;
import enity.User;

public class SendingMessageDao {
	private JdbcUtils util;
	
	public SendingMessageDao() {
		util=new JdbcUtils();
	}
	/*
	 * 将信息插入到信息表中
	 */
	public void addMessage(Message message) {
		//TODO 将用户插入数据库中的表
		PreparedStatement ps =null;
		Connection conn = util.getConnection();
		String sql ="insert into s_message(date,sentUser,receiveUser,content) values(?,?,?,?)";
		
		try {
			ps=conn.prepareStatement(sql);
			ps.setString(1,message.getDate());
			ps.setString(2, message.getSentUser());
			ps.setString(3, message.getReceiveUser());
			ps.setString(4, message.getContent());
			ps.execute();
			ps.close();
			conn.close();
		}catch(SQLException e) {
			e.printStackTrace();
		}
	}
	
	/*
	 * 把所有的信息都列出来
	 */
	/*
	public List<Message> listAllMessageOfUser(User user){
		List<Message> list =null;
		PreparedStatement ps = null;
		Connection conn = util.getConnection();
		String sql = "select * from s_message where sentUser=? or receiveUser=?";
		Message message = null;
		ResultSet rs = null;
		try {
			ps=conn.prepareStatement(sql);
			list=new ArrayList<Message>();
			ps.setString(1, user.getUserName());
			ps.setString(2, user.getUserName());
			rs =ps.executeQuery();
			
			while(rs.next()) {
				message=new Message();
//				message.setId(rs.getInt("id"));
				message.setDate(rs.getString("date"));
				message.setSentUser(rs.getString("sentUser"));
				message.setReceiveUser(rs.getString("receiveUser"));
				message.setContent(rs.getString("content"));
				list.add(message);
				}
			
			ps.close();
			conn.close();
			
			}catch(SQLException e){
			e.printStackTrace();
			}
			
			return list;
		
		}
	*/
	
	/**
	 *把要送出去的消息都列出来 
	 */
	public List<Message> listAllMessageOfReceiveUser(User user){
		List<Message> list =null;
		PreparedStatement ps = null;
		Connection conn = util.getConnection();
		String sql = "select * from s_message where receiveUser=?";
		Message message = null;
		ResultSet rs = null;
		try {
			ps=conn.prepareStatement(sql);
			
			list=new ArrayList<Message>();
			
			ps.setString(1, user.getUserName());
			
			rs =ps.executeQuery();
			while(rs.next()) {
				message=new Message();
//				message.setId(rs.getInt("id"));
				message.setDate(rs.getString("date"));
				message.setSentUser(rs.getString("sentUser"));
				message.setReceiveUser(rs.getString("receiveUser"));
				message.setContent(rs.getString("content"));
				list.add(message);
				}
			
			ps.close();
			conn.close();
			
			}catch(SQLException e){
			e.printStackTrace();
			}
			
			return list;
		
		}
	
	
	
	 public void deleteMessageByUser(String userName) {
		//TODO 删除特定用户的待接受消息
		PreparedStatement ps =null;
		Connection conn = util.getConnection();
		String sql="delete from s_message where receiveUser=?";
		
		try {
			ps=conn.prepareStatement(sql);
			ps.setString(1,userName);
			ps.execute();
			ps.close();
			conn.close();
		}catch(SQLException e) {
			e.printStackTrace();
		}
	}
	
	/*public void updateUser(User user) {
		//TODO 更新用户信息
		PreparedStatement ps = null;
		Connection conn = util.getConnection();
		String sql = "update t_user set userName=? password=? where id=?";
		
		try {
			ps = conn.prepareStatement(sql);
			ps.setString(1, user.getUserName());
			ps.setString(2, user.getUserName());
			ps.setString(2, user.getPassWord());
			ps.execute();
			ps.close();
			conn.close();
		}catch(SQLException e) {
			e.printStackTrace();
		}
	}
	*/
	/*public User getUserById(int Id) {
		//TODO 通过用户Id查找用户
		PreparedStatement ps = null;
		Connection conn = util.getConnection();
		User user = null;
		ResultSet rs = null;
		String sql = "select * from t_user where id=?";
		
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
	}*/
	
	/*public User getUsetByName(String userName) {
		//TODO 通过用户名查找用户
		PreparedStatement ps = null;
		Connection conn = util.getConnection();
		String sql ="select * from t_user where userName=?";
		ResultSet rs = null;
		User user = null;
		try {
			ps = conn.prepareStatement(sql);
			ps.setString(1, userName);
			rs = ps.executeQuery();
			
			while(rs.next()) {
				user = new User();
				user.setId(rs.getInt("Id"));
				user.setPassWord(rs.getString("password"));
				user.setUserName(rs.getString("userName"));
			}
		}catch(SQLException e) {
			e.printStackTrace();
		}
		
		return user;
		
	}*/
	 
}

