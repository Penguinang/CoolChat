package CoolChat.Data;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;

import java.io.IOException;
import java.sql.Connection;
import java.util.ArrayList;
import java.util.List;

import org.junit.Before;
import org.junit.Test;

import dao.JdbcUtils;
import dao.SendingMessageDao;
import dao.UserDao;
import enity.Message;
import enity.User;

public class TestDataManager {
    private DataManager dataManager;
    private Connection dbConn;

    @Before
    public void setUp() throws IOException {
        dataManager = new DataManager();
        dbConn = new JdbcUtils().getConnection();
        Runtime.getRuntime().exec("mysql testdb < database/testdb.sql");
        JdbcUtils.setDburl("jdbc:mysql://localhost:3306/testdb?characterEncoding=utf8&useSSL=false&serverTimezone=GMT");
    }

    @Test
    public void testSignUp() {
        String name = "Name1", email = "Email1", password = "Password1";
        dataManager.signUp("Name1", "Email1", "Password1");

        UserDao udao = new UserDao();
        assertNotNull(udao.getUserByNameAndPass(name, password));
        assertEquals(udao.getUserByName(name).getE_mail(), email);
        udao.deleteUser(new User(name));
    }

    @Test
    public void testLogin() {
        assertTrue(dataManager.login("foo", "password"));
        assertFalse(dataManager.login("foo", "notasd"));
    }

    @Test
    public void testAddReceivingMessage() {
        String name1 = "Name1", name2 = "Name2", content = "testcontent";
        dataManager.addReceivingMessage(name1, name2, content);
        SendingMessageDao sdao = new SendingMessageDao();
        List<Message> msgs = sdao.listAllMessageOfReceiveUser(new User(name1));
        assertTrue(msgs.indexOf(new Message("", name1, name2, content)) != -1);
    }

    @Test
    public void testPullUserMessage() {
        SendingMessageDao sdao = new SendingMessageDao();
        String date = "1999-01-02-23-10", name1 = "Name1", name2 = "Name2", content = "testcontent";
        sdao.addMessage(new Message(date, name1, name2, content));

        ArrayList<String> sources = new ArrayList<String>(), contents = new ArrayList<String>();
        dataManager.pullUserMessage(name1, sources, contents);
        assertTrue(sources.indexOf(name2) != -1);
        assertTrue(contents.indexOf(content) != -1);
    }

    @Test
    public void sentText(){
        
    }
}