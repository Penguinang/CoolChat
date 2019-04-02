package CoolChat.Messages;

import static org.junit.Assert.*;

import java.util.ArrayList;
import java.util.HashMap;

import org.apache.mina.core.buffer.IoBuffer;
import org.apache.mina.core.session.DummySession;
import org.apache.mina.core.session.IoSession;
import org.junit.Before;
import org.junit.Test;

import CoolChat.Data.DataManager;
import dao.JdbcUtils;

public class TestTextMessage {
    private HashMap<String, IoSession> sessions;
    private DataManager dataManager;

    @Before
    public void setUp() {
        JdbcUtils.setDburl("jdbc:mysql://localhost:3306/testdb?characterEncoding=utf8&useSSL=false&serverTimezone=GMT");
        sessions = new HashMap<String, IoSession>();
        dataManager = new DataManager();
    }

    @Test
    public void testGetResult() throws Exception {
        String name1 = "Name1", content = "testcontent", name2 = "Name2";
        IoSession session = null;


        // 目标用户不在线
        session = new DummySession();
        session.setAttribute("userName", name2);
        session.getAttribute("userName");
        TextMessage sent = new TextMessage(name1, content);
        sent.getResult(sessions, session, dataManager);

        ArrayList<String> sourceList = new ArrayList<String>(), contentList = new ArrayList<String>();
        dataManager.pullUserMessage(name1, sourceList, contentList);
        assertFalse(content.isEmpty());
        IoBuffer ib = IoBuffer.allocate(contentList.get(0).length());
        ib.put(contentList.get(0).getBytes());
        ib.position(0);
        
        Message msg = Message.getDecodedMessage(ib);
        assertEquals(msg.getClass(), TextMessage.class);
        assertEquals(msg, new TextMessage(name1, content));
    }
}