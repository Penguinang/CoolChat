package Class.Data;
import Class.lib.LinkedList_string_;


/**
 * Class DataManager
 */
public class DataManager {

    //
    // Fields
    //

    
    //
    // Constructors
    //
    public DataManager () { };
    
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
     * 用户注册
     * @return       boolean
     * @param        name 待检用户名
     * @param        email 注册邮箱
     * @param        password 密码
     */
    public boolean signUp(String name, String email, String password)
    {
    }


    /**
     * 登录，检查用户名和密码是否匹配，成功返回真，否则返回假
     * @return       boolean
     * @param        userName 用户名
     * @param        password 密码
     */
    public boolean login(String userName, String password)
    {
    }


    /**
     * 拉取某用户未接受的所有消息，若有消息返回真,否则返回假
     * @return       boolean
     * @param        userName 查询的用户名
     * @param        sourceUserNameList 发送消息的用户数组
     * @param        contentList 消息内容的数组
     */
    public boolean pullUserMessage(String userName, Class.lib.LinkedList<string> sourceUserNameList, Class.lib.LinkedList<string> contentList)
    {
    }


    /**
     * 将消息记录下来
     * @param        sourceUserName 发出消息用户
     * @param        destUserName 目标用户
     * @param        content 消息内容，包含一个时间前缀
     */
    public void sendText(String sourceUserName, String destUserName, String content)
    {
    }


    /**
     * 按照关键字查询用户
     * @param        keyword 查询目标关键字
     * @param        userNameList 查询结果的数组
     */
    public void queryUser(String keyword, Class.lib.LinkedList<string> userNameList)
    {
    }


    /**
     * 修改用户之间的好友关系
     * @param        user1 用户甲
     * @param        user2 用户乙
     * @param        isFriend 新的好友关系：是否是好友
     */
    public void changeUserRelation(String user1, String user2, boolean isFriend)
    {
    }


    /**
     * 查找该用户的所有好友名单
     * @param        userName 目标用户名
     * @param        friendList 查询的结果，一个好友名单的数组
     */
    public void queryFriendList(String userName, Class.lib.LinkedList<string> friendList)
    {
    }


}
