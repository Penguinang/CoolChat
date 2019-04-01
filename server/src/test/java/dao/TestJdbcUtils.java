package dao;

import org.junit.Test;

import static org.junit.Assert.*;

import java.sql.Connection;

import org.junit.Before;

public class TestJdbcUtils {
    JdbcUtils jdbutil;

    @Before
    public void setUp() {
        jdbutil = new JdbcUtils();
    }

    @Test
    public void testGetConnection() {
        Connection conn = jdbutil.getConnection();
        assertTrue("Connection get error", conn != null);
    }
}