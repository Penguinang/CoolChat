package CoolChat.Server;

import java.net.InetSocketAddress;

import org.apache.mina.core.session.IdleStatus;
import org.apache.mina.filter.codec.ProtocolCodecFilter;
import org.apache.mina.filter.logging.LoggingFilter;
import org.apache.mina.transport.socket.nio.NioSocketAcceptor;

import CoolChat.Messages.MessageCodecFactory;

/**
 * Start server
 *
 */
public class App {
    public static void main(String[] args) {
        NioSocketAcceptor acceptor = new NioSocketAcceptor();

        acceptor.getFilterChain().addLast("protocol", new ProtocolCodecFilter(new MessageCodecFactory()));
        acceptor.getFilterChain().addLast("logger", new LoggingFilter());

        acceptor.setHandler(new ServerHandler());
        acceptor.getSessionConfig().setReadBufferSize(2048);
        // set session Idle,both means both write and read
        acceptor.getSessionConfig().setIdleTime(IdleStatus.BOTH_IDLE, 10);
        String ip = args.length >= 1 ? args[1] : "127.0.0.1";
        int port = args.length >= 2 ? Integer.parseInt(args[2]) : 9123;
        try {
            acceptor.bind(new InetSocketAddress(ip, port));
            // acceptor.bind( new InetSocketAddress("10.11.182.60",9123) );
            // acceptor.bind( new InetSocketAddress("localhost",9123) );
        } catch (Exception e) {
            e.printStackTrace();
            return;
        }
        System.out.println("Server Started");
    }
}
