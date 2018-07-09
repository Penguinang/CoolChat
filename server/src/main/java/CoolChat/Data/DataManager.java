package CoolChat.Data;
import java.util.ArrayList;
import java.util.List;

import dao.*;
import enity.*;


/**
 * Class DataManager
 */
public class DataManager {

    public DataManager () { };
    
    /**
     * 注册
     * @return       boolean
     * @param        name 用户名
     * @param        email 用户邮件
     * @param        password 用户密码
     */
    public boolean signUp(String name, String email, String password)
    {
    	User user = new User();
    	user.setUserName(name);
    	user.setPassWord(password);
    	user.setE_mail(email);
    	UserDao userDao = new UserDao();
    	if(userDao.getUserByName(user.getUserName())==null) {//TODO：这个地方判断是否正确？
    		userDao.addUser(user);
    		return true;
    	}
    	else {
    		return false;
    	}
    }


    /**
     * 登录从数据库里查看是否有此用户
     * @return       boolean
     * @param        userName 用户名
     * @param        password 用户密码
     */
    public boolean login(String userName, String password)
    {
    	UserDao userDao =new UserDao();
    	if(userDao.getUserByName(userName).getPassWord().equals(password)) {
    		return true;
    	}
    	else {
    		return false;
    	}
    }


    /**
     * 拉取用户未接收的信息，放到sourceUserNameList和contentList中
     * @return       boolean
     * @param        userName 请求拉取未接受消息的用户的用户名
     * @param        sourceUserNameList 得到的谁给他发送的用户名的List
     * @param        contentList 内容List，与上面的sourceUser一一对应
     */
    public boolean pullUserMessage(String userName,List<String> sourceUserNameList, List<String> contentList)
    {
    	//TODO 这里的逻辑是否正确？
    	SendingMessageDao sendingMessageDao = new SendingMessageDao();
    	User user  = null;
    	UserDao userDao =new UserDao();
    	user=userDao.getUserByName(userName);
    	
    	if(sendingMessageDao.listAllMessageOfReceiveUser(user)!=null) {
    		List<Message> list=sendingMessageDao.listAllMessageOfReceiveUser(user);
    		
    		for(int i=0;i<list.size();i++) {
    			Message message=list.get(i);
    			sourceUserNameList.set(i, message.getSentUser());
    			contentList.set(i, message.getDate()+message.getContent());
    		}
    		
    		sendingMessageDao.deleteMessageByUser(userName);
    		
    		return true;
    	}
    	else {
    		return false;
    	}
    }


    /**
     * 数据库方面的sendText将每次发送的消息存到数据库中作为消息记录
     * @param        sourceUserName 发送消息的用户
     * @param        destUserName 接收消息的用户
     * @param        content 消息内容
     */
    public void sendText(String sourceUserName, String destUserName, String content)
    {
    	MessageDao messageDao = new MessageDao();
    	Message message = new Message();
    	message.setReceiveUser(destUserName);
    	message.setSentUser(sourceUserName);
    	int endIndex=17;
    	message.setDate(content.substring(0, endIndex));
    	
    	messageDao.addMessage(message);
    }


    /**
     * 通过关键字来查找用户
     * @return        List<User> 和这个关键字相关的用户List
     * @param        keyword 关键字
     */
    public List<User> queryUser(String keyword)
    {
    	
    	UserDao userDao = new UserDao(); 
    	List<User> list = new ArrayList<User>();
    	int length = userDao.getAllUser().size();
    	User user = null;
    	for(int i=0;i<length;i++) {
    		user = userDao.getAllUser().get(i);
    		if(user.getUserName().contains(keyword)) {
    			list.add(user);
    		}
    	}
    	
    	return list;
    }


    /**
     * 改变好友的关系，实际是在数据库中删除或添加相应的记录
     * @param        user1 用户甲
     * @param        user2 用户乙
     * @param        isFriend 是否是好友
     */
    public void changeUserRelation(String user1, String user2, boolean isFriend)
    {
    	FriendDao friendDao = new FriendDao();
    	Friend friend = new Friend();
    	User user = new User();
    	friend.setName(user2);//user2是好友
    	user.setUserName(user1);//user1是被添加或删除好友的用户
    	if(isFriend) {
    		friendDao.addFriendToUser(friend, user);
    	}
    	else {
    		friendDao.deleteFriendOfUser(friend, user);
    	}
    }


    /**
     * 通过用户名查找这个用户的所有好友
     * @param        userName 被拉取好友的用户名
     * @return       List<Friend> 返回这个用户的所有好友，放在List中 
     */
    public List<Friend> queryFriendList(String userName)
    {
    	FriendDao friendDao = new FriendDao();
    	List<Friend> list = new ArrayList<Friend>();
    	User user = new User();
    	user.setUserName(userName);
    	list = friendDao.listAllFriendOfUser(user);
    	
    	return list;
    }


}
