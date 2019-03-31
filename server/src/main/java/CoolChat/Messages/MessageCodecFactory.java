package CoolChat.Messages;

import org.apache.mina.core.session.IoSession;
import org.apache.mina.filter.codec.ProtocolCodecFactory;
import org.apache.mina.filter.codec.ProtocolDecoder;
import org.apache.mina.filter.codec.ProtocolEncoder;

public class MessageCodecFactory implements ProtocolCodecFactory{
    private ProtocolEncoder encoder;
    private ProtocolDecoder decoder;

    public MessageCodecFactory(){
        encoder = new MessageEncoder();
        decoder = new MessageDecoder();
    }

    public ProtocolEncoder getEncoder(IoSession session)throws Exception{
        return encoder;
    }

    public ProtocolDecoder getDecoder(IoSession session)throws Exception{
        return decoder;
    }
}