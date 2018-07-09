package CoolChat.Server;

import java.util.HashMap;

import org.apache.mina.core.service.IoHandlerAdapter;
import org.apache.mina.core.session.IdleStatus;
import org.apache.mina.core.session.IoSession;

import CoolChat.Data.*;
import CoolChat.Messages.*;

public class ServerHandler extends IoHandlerAdapter{
    private HashMap<String, IoSession> sessions;
    private DataManager dbManager;

    public ServerHandler(){
        super();
        sessions = new HashMap<String,IoSession>();
        dbManager = new DataManager();
    }

    @Override
    public void sessionOpened(IoSession session) throws Exception {
        super.sessionOpened(session);
    }

    @Override
    public void exceptionCaught(IoSession session, Throwable cause) throws Exception{
        cause.printStackTrace();
    }

    @Override
    public void messageReceived(IoSession session, Object message) throws Exception{
        Message result = ((Message)message).getResult(sessions, session, dbManager);
        if(result != null)
        {
            session.write(result);
        }
        System.out.println("messageRecevied 中的getResult运行了，并把结果写进去了");
    }

    @Override
    public void sessionIdle(IoSession session, IdleStatus status) throws Exception{
        // System.out.println("Idle");
    }
}