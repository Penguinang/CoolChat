package CoolChat.Server;

import java.net.InetSocketAddress;

import org.apache.mina.core.session.IdleStatus;
import org.apache.mina.filter.codec.ProtocolCodecFilter;
import org.apache.mina.filter.logging.LoggingFilter;
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
        acceptor.getFilterChain().addLast("logger", new LoggingFilter());

        acceptor.setHandler(new ServerHandler());
        acceptor.getSessionConfig().setReadBufferSize(2048);
        acceptor.getSessionConfig().setIdleTime(IdleStatus.BOTH_IDLE, 10);//璁剧疆session鐨処dle鐨勭姸鎬侊紝both涓哄湪瑙勫畾鐨勬椂闂村唴娌℃湁鏁版嵁鍙鍜屽彲鍐�
        try{
            acceptor.bind( new InetSocketAddress("172.16.136.7",9123) );
        }
        catch (Exception e){
            e.printStackTrace();
            return;
        }
        System.out.println("Server Start");
    }
}
//
//import java.io.IOException;
//import java.net.InetSocketAddress;
//import java.nio.charset.Charset;
//
//import org.apache.mina.core.service.IoAcceptor;
//import org.apache.mina.core.session.IdleStatus;
//import org.apache.mina.filter.codec.ProtocolCodecFilter;
//import org.apache.mina.filter.codec.textline.TextLineCodecFactory;
//import org.apache.mina.filter.logging.LoggingFilter;
//import org.apache.mina.transport.socket.nio.NioSocketAcceptor;
//
//public class App
//{
//    private static final int PORT = 9123;
//    public static void main( String[] args ) throws IOException
//    {
//        IoAcceptor acceptor = new NioSocketAcceptor();
//        acceptor.getFilterChain().addLast( "logger", new LoggingFilter() );
//        acceptor.getFilterChain().addLast( "codec", new ProtocolCodecFilter( new TextLineCodecFactory( Charset.forName( "UTF-8" ))));
//        acceptor.setHandler( new TimeServerHandler() );
//        acceptor.getSessionConfig().setReadBufferSize( 2048 );
//        acceptor.getSessionConfig().setIdleTime( IdleStatus.BOTH_IDLE, 10 );
//        acceptor.bind( new InetSocketAddress("172.16.136.7", 9123));
//    }
//}
