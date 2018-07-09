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
     * ע��
     * @return       boolean
     * @param        name �û���
     * @param        email �û��ʼ�
     * @param        password �û�����
     */
    public boolean signUp(String name, String email, String password)
    {
    	User user = new User();
    	user.setUserName(name);
    	user.setPassWord(password);
    	user.setE_mail(email);
    	UserDao userDao = new UserDao();
    	if(userDao.getUserByName(user.getUserName())==null) {//TODO������ط��ж��Ƿ���ȷ��
    		userDao.addUser(user);
    		return true;
    	}
    	else {
    		return false;
    	}
    }


    /**
     * ��¼�������ݿ���鿴�Ƿ��д��û�
     * @return       boolean
     * @param        userName �û���
     * @param        password �û�����
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
     * ��ȡ�û�δ���յ���Ϣ���ŵ�sourceUserNameList��contentList��
     * @return       boolean
     * @param        userName ������ȡδ������Ϣ���û����û���
     * @param        sourceUserNameList �õ���˭�������͵��û�����List
     * @param        contentList ����List���������sourceUserһһ��Ӧ
     */
    public boolean pullUserMessage(String userName,List<String> sourceUserNameList, List<String> contentList)
    {
    	//TODO ������߼��Ƿ���ȷ��
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
     * ���ݿⷽ���sendText�轫ÿ�η��͵���Ϣ�浽���ݿ�����Ϊ��Ϣ��¼
     * @param        sourceUserName ������Ϣ���û�
     * @param        destUserName ������Ϣ���û�
     * @param        content ��Ϣ����
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
     * ͨ���ؼ����������û�
     * @return        List<User> ������ؼ�����ص��û�List
     * @param        keyword �ؼ���
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
     * �ı���ѵĹ�ϵ��ʵ���������ݿ���ɾ���������Ӧ�ļ�¼
     * @param        user1 �û���
     * @param        user2 �û���
     * @param        isFriend �Ƿ��Ǻ���
     */
    public void changeUserRelation(String user1, String user2, boolean isFriend)
    {
    	FriendDao friendDao = new FriendDao();
    	Friend friend = new Friend();
    	User user = new User();
    	friend.setName(user2);//user2�Ǻ���
    	user.setUserName(user1);//user1�Ǳ���ӻ�ɾ�����ѵ��û�
    	if(isFriend) {
    		friendDao.addFriendToUser(friend, user);
    	}
    	else {
    		friendDao.deleteFriendOfUser(friend, user);
    	}
    }


    /**
     * ͨ���û�����������û������к���
     * @param        userName ����ȡ���ѵ��û���
     * @return       List<Friend> ��������û������к��ѣ�����List�� 
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
