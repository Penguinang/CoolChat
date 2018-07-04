package learn.mina;

import java.util.HashMap;

import org.apache.mina.core.service.IoHandlerAdapter;
import org.apache.mina.core.session.IdleStatus;
import org.apache.mina.core.session.IoSession;

import learn.DataBase.DBManager;
import learn.Messages.Message;

public class ServerHandler extends IoHandlerAdapter{
    private HashMap<String, IoSession> sessions;
    private DBManager dbManager;

    public ServerHandler(){
        super();
        sessions = new HashMap<String,IoSession>();
        dbManager = new DBManager();
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
            session.write(result);
    }

    @Override
    public void sessionIdle(IoSession session, IdleStatus status) throws Exception{
        // System.out.println("Idle");
    }
}