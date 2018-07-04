package Class.Messages;
import Class.lib.HashMap_String_IoSession_;
import Class.lib.IoSession;
import Class.Data.DataManager;
import Class.lib.byte_;


/**
 * Class Message
 */
public class Message {

    //
    // Fields
    //

    
    //
    // Constructors
    //
    public Message () { };
    
    //
    // Methods
    //


    //
    // Accessor methods
    //

    //
    // Other methods
    //

    /**
     * 返回对该消息的处理结果
     * @param        sessions 已经登录的所有会话
     * @param        session 当前用户的会话
     * @param        dataManager 管理所有的数据
     */
    public void getResult(Class.lib.HashMap<String, IoSession> sessions, Class.lib.IoSession session, Class.Data.DataManager dataManager)
    {
    }


    /**
     * 获得编码后的消息
     */
    public void getProtocolEncodedBytes()
    {
    }


    /**
     * 将字节数组解码为Message对象。
     * @param        rawBytes 原始字节数组
     */
    public static void getDecodedMessage(Class.lib.byte[] rawBytes)
    {
    }


    /**
     * @param        rawBytes 原始字节数组
     */
    protected void internalGetDecodedMessage(Class.lib.byte[] rawBytes)
    {
    }


}
