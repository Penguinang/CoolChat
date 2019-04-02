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
	public void addFriendToUser(Friend friend) {
		PreparedStatement ps = null;
		Connection conn = util.getConnection();
		String sql = "insert into friend (userName, friendName) values(?,?)";
		try {
			ps = conn.prepareStatement(sql);
			ps.setString(1, friend.getUserName());
			ps.setString(2, friend.getFriendName());
			ps.execute();			
			ps.close();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		try {
			ps = conn.prepareStatement(sql);
			ps.setString(2, friend.getUserName());
			ps.setString(1, friend.getFriendName());
			ps.execute();			
			ps.close();
			conn.close();
		} catch (SQLException e) {
			e.printStackTrace();
		}		
	}

	/*
	 * 从指定用户的表中删除好友
	 */
	public void deleteFriendOfUser(Friend friend) {
		PreparedStatement ps = null;
		Connection conn = util.getConnection();
		String sql = "delete from friend where (userName=? and friendName=?) or (friendName=? and userName=?)";

		try {
			ps = conn.prepareStatement(sql);
			ps.setString(1, friend.getUserName());
			ps.setString(2, friend.getFriendName());
			ps.setString(3, friend.getUserName());
			ps.setString(4, friend.getFriendName());

			ps.execute();
			ps.close();
			conn.close();
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}

	/*
	 * 列出指定用户的所有好友
	 */
	public List<Friend> listAllFriendOfUser(User user) {
		PreparedStatement ps = null;
		Connection conn = util.getConnection();
		List<Friend> list = null;
		ResultSet rs = null;
		String sql = "select * from friend where userName=?";

		Friend friend = null;
		try {
			list = new ArrayList<Friend>();
			ps = conn.prepareStatement(sql);
			ps.setString(1, user.getUserName());
			rs = ps.executeQuery();
			while (rs.next()) {
				friend = new Friend();
				friend.setUserName(rs.getString("userName"));
				friend.setFriendName(rs.getString("friendName"));
				list.add(friend);
			}

			ps.close();
			conn.close();
		} catch (SQLException e) {
			e.printStackTrace();
		}

		return list;
	}

}
