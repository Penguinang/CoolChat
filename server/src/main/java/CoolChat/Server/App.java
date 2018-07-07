package CoolChat.Server;

import java.net.InetSocketAddress;

import org.apache.mina.core.session.IdleStatus;
import org.apache.mina.filter.codec.ProtocolCodecFilter;
import org.apache.mina.transport.socket.nio.NioSocketAcceptor;

import CoolChat.Messages.MessageCodecFactory;

/**
 * Hello world!
 *
 */
public class App 
{
    public static void main( String[] args )
    {
        NioSocketAcceptor acceptor = new NioSocketAcceptor();

        acceptor.getFilterChain().addLast("protocol", new ProtocolCodecFilter(new MessageCodecFactory()));
        // acceptor.getFilterChain().addLast("logger", new LoggingFilter());

        acceptor.setHandler(new ServerHandler());
        acceptor.getSessionConfig().setReadBufferSize(2048);
        acceptor.getSessionConfig().setIdleTime(IdleStatus.BOTH_IDLE, 10);//设置session的Idle的状态，both为在规定的时间内没有数据可读和可写
        try{
            acceptor.bind( new InetSocketAddress("localhost",9123) );
        }
        catch (Exception e){
            e.printStackTrace();
            return;
        }
        System.out.println("Server Start");
    }
}
