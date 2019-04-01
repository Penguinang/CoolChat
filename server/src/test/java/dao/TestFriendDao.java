package dao;

import static org.junit.Assert.assertTrue;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.SQLIntegrityConstraintViolationException;

import org.junit.Before;
import org.junit.Test;

import enity.Friend;

public class TestFriendDao {
    private FriendDao fdao;
    private JdbcUtils util;

    @Before
    public void setUp() {
        fdao = new FriendDao();
        util = new JdbcUtils();
    }

    @Test
    public void testAddFriendToUser() throws SQLException {
        Friend friend1 = new Friend("testuser1xxx", "testuser2xxx");
        fdao.addFriendToUser(friend1);

        PreparedStatement ps = null;
        Connection conn = util.getConnection();
        String sql = "select userName, friendName from friend where userName='testuser1xxx' and friendName='testuser2xxx'";
        ps = conn.prepareStatement(sql);
        ResultSet rs = ps.executeQuery();
        assertTrue("Insertion fail ", rs.next() != false);

        sql = "delete from friend where userName='testuser1xxx' and friendName='testuser2xxx'";
        ps = conn.prepareStatement(sql);
        assertTrue(ps.execute());
    }

    @Test
    public void deleteFriendOfUser() throws SQLException {
        PreparedStatement ps = null;
        Connection conn = util.getConnection();
        String sql = null;
        try {
            sql = "insert into friend values('testuser1xxx', 'testuser2xxx')";
            ps = conn.prepareStatement(sql);
            ps.execute();
        } catch (SQLIntegrityConstraintViolationException e) {

        } catch (SQLException e) {
            e.printStackTrace();
        }

        Friend friend1 = new Friend("testuser1xxx", "testuser2xxx");
        fdao.deleteFriendOfUser(friend1);

        sql = "select userName, friendName from friend where userName='testuser1xxx' and friendName='testuser2xxx'";
        ps = conn.prepareStatement(sql);
        ResultSet rs = ps.executeQuery();
        assertTrue("Delete fail ", rs.next() == false);
    }

    @Test
    public void listAllFriendOfUser() throws SQLException {
    }
}