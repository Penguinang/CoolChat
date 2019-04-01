package CoolChat.Server;

import java.net.InetSocketAddress;
import java.util.ArrayList;
import java.util.List;

import javax.swing.plaf.synth.SynthSpinnerUI;

import org.apache.mina.core.session.IdleStatus;
import org.apache.mina.filter.codec.ProtocolCodecFilter;
import org.apache.mina.filter.logging.LoggingFilter;
import org.apache.mina.transport.socket.nio.NioSocketAcceptor;

import CoolChat.Data.DataManager;
import CoolChat.Messages.MessageCodecFactory;
import enity.Friend;
import enity.User;

/**
 * Hello world!
 *
 */
public class App {
    public static void main(String[] args) {
        NioSocketAcceptor acceptor = new NioSocketAcceptor();

        acceptor.getFilterChain().addLast("protocol", new ProtocolCodecFilter(new MessageCodecFactory()));
        acceptor.getFilterChain().addLast("logger", new LoggingFilter());

        acceptor.setHandler(new ServerHandler());
        acceptor.getSessionConfig().setReadBufferSize(2048);
        acceptor.getSessionConfig().setIdleTime(IdleStatus.BOTH_IDLE, 10);// set session Idle,both means both write and
                                                                          // read
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
        System.out.println("Server Start");

        // System.out.println("test the dataBase:");
        //
        // DataManager dataManager=new DataManager();

        // dataManager.addReceivingMessage("Tom", "Jarry", "Good evening");

        // List<String> sourceUserNameList=new ArrayList<String>();
        // List<String> contentList=new ArrayList<String>();
        // String userName="Tom";
        // dataManager.pullUserMessage(userName, sourceUserNameList, contentList);
        // System.out.println(sourceUserNameList.get(0));
        // System.out.println(contentList.get(0));

        // dataManager.changeUserRelation("Mike", "Tom", true);
        // System.out.println("query friends:");
        // List<Friend> friends=new ArrayList<Friend>();
        // friends=dataManager.queryFriendList("Mike");
        // System.out.println(friends.get(0).getName());
        //
        // System.out.println("serach users by the keyword:");
        // List<User> users=dataManager.queryUser("Mi");
        // System.out.println(users.get(0).getUserName());

        System.out.println("test the session:");
    }
}

//
// import java.io.IOException;
// import java.net.InetSocketAddress;
// import java.nio.charset.Charset;
//
// import org.apache.mina.core.service.IoAcceptor;
// import org.apache.mina.core.session.IdleStatus;
// import org.apache.mina.filter.codec.ProtocolCodecFilter;
// import org.apache.mina.filter.codec.textline.TextLineCodecFactory;
// import org.apache.mina.filter.logging.LoggingFilter;
// import org.apache.mina.transport.socket.nio.NioSocketAcceptor;
//
// public class App
// {
// private static final int PORT = 9123;
// public static void main( String[] args ) throws IOException
// {
// IoAcceptor acceptor = new NioSocketAcceptor();
// acceptor.getFilterChain().addLast( "logger", new LoggingFilter() );
// acceptor.getFilterChain().addLast( "codec", new ProtocolCodecFilter( new
// TextLineCodecFactory( Charset.forName( "UTF-8" ))));
// acceptor.setHandler( new TimeServerHandler() );
// acceptor.getSessionConfig().setReadBufferSize( 2048 );
// acceptor.getSessionConfig().setIdleTime( IdleStatus.BOTH_IDLE, 10 );
// acceptor.bind( new InetSocketAddress("172.16.136.7", 9123));
// }
// }
