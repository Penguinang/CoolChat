package dao;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class JdbcUtils {
	private String userName;
	private String password;
	private String url;
	private static String dburl = "jdbc:mysql://localhost:3306/CoolChat?characterEncoding=utf8&useSSL=false&serverTimezone=GMT";

	public JdbcUtils() {
		this.userName = "root";
		this.password = "Ren@123";
		this.url = dburl;
	}

	public Connection getConnection() {
		Connection conn = null;

		try {
			conn = DriverManager.getConnection(url, userName, password);

		} catch (SQLException e) {
			e.printStackTrace();
		}

		return conn;
	}

	public static void setDburl(String newurl) {
		if (newurl != null)
			dburl = newurl;
	}
}
