package dao;
/*
 * FriendDao类：对数据库中的好友表进行操作
 */

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;


import enity.Friend;
import enity.User;

public class FriendDao {
   private JdbcUtils util;
   
   public FriendDao() {
	   util = new JdbcUtils();
   }
   
   /*
    * 向指定用户的表中添加好友
    */
   public void addFriendToUser(Friend friend ,User user) {
	   PreparedStatement ps = null;
	   Connection conn = util.getConnection();
	   String sql = "insert into friend (name,userName) values(?,?)";
	   try {
		   ps=conn.prepareStatement(sql);
		   ps.setString(1, friend.getName());
		   ps.setString(2, user.getUserName());
		   ps.execute();
		   ps.close();
		   conn.close();
	   }catch(SQLException e) {
		   e.printStackTrace();
	   }
   }
   
   /*
    * 从指定用户的表中删除好友
    */
   public void deleteFriendOfUser(Friend friend,User user) {
	   PreparedStatement ps=null;
	   Connection conn=util.getConnection();
	   String sql="delete from friend where name=? and userName=?";
	   
	   try {
		   ps=conn.prepareStatement(sql);
		   ps.setString(1, friend.getName());
		   ps.setString(2,user.getUserName());
	   }catch(SQLException e) {
		  e.printStackTrace();
	   }
   }
   
   /*
    * 列出指定用户的所有好友
    */
   public List<Friend> listAllFriendOfUser(User user){
	   PreparedStatement ps =null;
	   Connection conn=util.getConnection();
	   List<Friend> list =null;
	   ResultSet rs=null;
	   String sql="select * from friend where userName=?";
	   
	   Friend friend=null;
	   try {
		   list=new ArrayList<Friend>();
		   ps=conn.prepareStatement(sql);
		   ps.setString(1, user.getUserName());
		   rs=ps.executeQuery();
		   while(rs.next()) {
			   friend=new Friend();
//			   friend.setId(rs.getInt("id"));
			   friend.setName(rs.getString("name"));
			   friend.setUserName(rs.getString("userName"));
	           list.add(friend);
		   }
		   
		   ps.close();
		   conn.close();
	   }catch(SQLException e) {
		   e.printStackTrace();
	   }
	   
	   return list;
   }
   
   
}
