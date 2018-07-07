package CoolChat.Messages;

import org.apache.mina.core.buffer.IoBuffer;
import org.apache.mina.core.session.IoSession;
import org.apache.mina.filter.codec.ProtocolEncoder;
import org.apache.mina.filter.codec.ProtocolEncoderOutput;

public class MessageEncoder implements ProtocolEncoder{
    public void encode(IoSession session, Object message, ProtocolEncoderOutput out) throws Exception{
        if(message == null){
            return;
        }
        Message msg_obj = (Message)message;
        out.write(IoBuffer.wrap(msg_obj.getProtocolEncodedBytes()));
    }

    public void dispose(IoSession session){

    }
}