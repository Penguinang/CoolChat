package CoolChat.Data;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNotEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import org.junit.Before;
import org.junit.Test;

import dao.FriendDao;
import dao.JdbcUtils;
import dao.MessageDao;
import dao.SendingMessageDao;
import dao.UserDao;
import enity.Friend;
import enity.Message;
import enity.User;

public class TestDataManager {
    private DataManager dataManager;

    // @Before
    @Before
    public void setUp() throws IOException, InterruptedException {
        JdbcUtils.setDburl("jdbc:mysql://localhost:3306/testdb?characterEncoding=utf8&useSSL=false&serverTimezone=GMT");
        dataManager = new DataManager();
        String cmds[] = { "/bin/zsh", "-c", "mysql testdb < database/testdb.sql" };
        Process p = Runtime.getRuntime().exec(cmds);
        p.waitFor();
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
        String date = "1999-01-02-23-10-40", name1 = "Name1", name2 = "Name2", content = "testcontent";
        sdao.addMessage(new Message(date, name2, name1, content));

        ArrayList<String> sources = new ArrayList<String>(), contents = new ArrayList<String>();
        dataManager.pullUserMessage(name2, sources, contents);
        assertTrue(sources.indexOf(name1) != -1);
        assertTrue(contents.indexOf(date + content) != -1);
    }

    @Test
    public void testSentText() {
        String date = "1999-01-02-23-10-40", name1 = "Name1", name2 = "Name2", content = "testcontent";
        dataManager.sentText(name1, name2, date + content);

        MessageDao msdao = new MessageDao();
        List<Message> msgs = msdao.listAllMessageOfUser(new User(name2));
        assertTrue(msgs.indexOf(new Message(date, name2, name1, content)) != -1);
    }

    @Test
    public void testQueryUser() {
        UserDao udao = new UserDao();
        udao.addUser(new User("queryName1"));
        assertNotNull(dataManager.queryUser("ryName1"));
        assertTrue(dataManager.queryUser("_____XXX-asdsadnotusername").isEmpty());
    }

    @Test
    public void testQueryUserByName(){
        UserDao udao = new UserDao();
        udao.addUser(new User("queryName1"));
        assertNotNull(dataManager.queryUserByName("queryName1"));
        assertNull(dataManager.queryUserByName("eryName1"));
        assertNull(dataManager.queryUserByName("queryName1asd"));
    }

    @Test 
    public void testChangeUserRelation(){
        FriendDao fdao = new FriendDao();
        String name1 = "Name1", name2 = "Name2";
        List<Friend> frs = null;
        
        fdao.addFriendToUser(new Friend(name1, name2));

        frs = fdao.listAllFriendOfUser(new User(name1));
        assertTrue(frs != null);
        assertTrue(frs.indexOf(new Friend(name1, name2)) != -1);
        frs = fdao.listAllFriendOfUser(new User(name2));
        assertTrue(frs != null);
        assertTrue(frs.indexOf(new Friend(name2, name1)) != -1);

        dataManager.changeUserRelation(name1, name2, false);

        frs = fdao.listAllFriendOfUser(new User(name1));
        assertTrue(frs == null || frs.indexOf(new Friend(name1, name2)) == -1);
        frs = fdao.listAllFriendOfUser(new User(name2));
        assertTrue(frs == null || frs.indexOf(new Friend(name2, name1)) == -1);

        dataManager.changeUserRelation(name1, name2, true);                

        frs = fdao.listAllFriendOfUser(new User(name1));
        assertTrue(frs != null);
        assertTrue(frs.indexOf(new Friend(name1, name2)) != -1);
        frs = fdao.listAllFriendOfUser(new User(name2));
        assertTrue(frs != null);
        assertTrue(frs.indexOf(new Friend(name2, name1)) != -1);
    }

    @Test
    public void testQueryFriendList(){
        String name1 = "Name1", name2 = "Name2", name3 = "Name3";
        FriendDao fdao = new FriendDao();
        List<Friend> frs = null;

        fdao.addFriendToUser(new Friend(name1, name2));
        fdao.addFriendToUser(new Friend(name1, name3));

        frs = dataManager.queryFriendList(name1);
        assertNotEquals(frs.indexOf(new Friend(name1, name2)), -1);
        assertNotEquals(frs.indexOf(new Friend(name1, name3)), -1);
        assertEquals(frs.indexOf(new Friend(name2, name1)), -1);
        assertEquals(frs.indexOf(new Friend(name3, name1)), -1);
        assertEquals(frs.indexOf(new Friend(name3, name2)), -1);
        assertEquals(frs.indexOf(new Friend(name2, name3)), -1);
    }
}