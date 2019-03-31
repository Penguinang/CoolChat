package dao;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class JdbcUtils {
	private String userName;
	private String password;
	private String url;

	public JdbcUtils() {
		this.userName = "root";
		this.password="Ren@123";
		this.url="jdbc:mysql://localhost:3306/CoolChat?characterEncoding=utf8&useSSL=false&serverTimezone=GMT";
		
		try {
			Class.forName("com.mysql.cj.jdbc.Driver");
		}catch(ClassNotFoundException e) {
			e.printStackTrace();
		}
	}
	
	public Connection getConnection() {
		Connection conn =null;
		
		try {
			conn=DriverManager.getConnection(url,userName,password);
			
		}catch(SQLException e){
			e.printStackTrace();
		}
		
		return conn;
	}
	
	
}
