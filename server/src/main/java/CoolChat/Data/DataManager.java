package CoolChat.Data;

import java.util.ArrayList;
import java.util.List;

import dao.*;
import enity.*;

/**
 * Class DataManager
 */
public class DataManager {

	public DataManager() {
	};

	/**
	 * 用户注册
	 * 
	 * @return boolean
	 * @param name     待检用户名
	 * @param email    注册邮箱
	 * @param password 密码
	 */
	public boolean signUp(String name, String email, String password) {
		User user = new User();
		user.setUserName(name);
		user.setPassWord(password);
		user.setE_mail(email);
		UserDao userDao = new UserDao();
		if (userDao.getUserByName(user.getUserName()) == null) {
			userDao.addUser(user);
			return true;
		} else {
			return false;
		}
	}

	/**
	 * 登录，检查用户名和密码是否匹配，成功返回真，否则返回假
	 * 
	 * @return boolean
	 * @param userName 用户名
	 * @param password 密码
	 */
	public boolean login(String userName, String password) {
		UserDao userDao = new UserDao();
		if (userDao.getUserByNameAndPass(userName, password) == null) {
			System.out.println("Wrong username or password");
			return false;
		} else {
			return true;
		}
	}

	/**
	 * ���δ���ܵ���Ϣ
	 * 
	 */
	public void addReceivingMessage(String receiveUser, String sentUser, String content) {
		SendingMessageDao sendingMessageDao = new SendingMessageDao();
		Message message = new Message();
		message.setReceiveUser(receiveUser);
		message.setSentUser(sentUser);
		message.setContent(content);
		message.setDate("");
		sendingMessageDao.addMessage(message);
	}

	/**
	 * 拉取某用户未接受的所有消息，若有消息返回真,否则返回假
	 * 
	 * @return boolean
	 * @param userName           查询的用户名
	 * @param sourceUserNameList 发送消息的用户数组
	 * @param contentList        消息内容的数组
	 */
	public boolean pullUserMessage(String userName, List<String> sourceUserNameList, List<String> contentList) {
		SendingMessageDao sendingMessageDao = new SendingMessageDao();
		User user = null;
		UserDao userDao = new UserDao();
		user = userDao.getUserByName(userName);

		List<Message> list = null;
		if (user != null && (list = sendingMessageDao.listAllMessageOfReceiveUser(user)) != null) {
			for (int i = 0; i < list.size(); i++) {
				Message message = list.get(i);
				sourceUserNameList.add(i, message.getSentUser());
				contentList.add(i, message.getDate() + message.getContent());
			}

			sendingMessageDao.deleteMessageByUser(userName);
			return true;
		} else {
			return false;
		}
	}

	/**
	 * 将消息记录下来
	 * 
	 * @param sourceUserName 发出消息用户
	 * @param destUserName   目标用户
	 * @param content        消息内容，包含一个时间前缀
	 */
	public void sentText(String sourceUserName, String destUserName, String content) {
		MessageDao messageDao = new MessageDao();
		Message message = new Message();
		message.setReceiveUser(destUserName);
		message.setSentUser(sourceUserName);
		int endIndex = "YYYY-MM-DD-HH-mm-ss".length();
		message.setDate(content.substring(0, endIndex));
		message.setContent(content.substring(endIndex));

		messageDao.addMessage(message);
	}

	/**
	 * 按照关键字查询用户
	 * 
	 * @param keyword      查询目标关键字
	 * @param userNameList 查询结果的数组
	 */
	public List<User> queryUser(String keyword) {

		UserDao userDao = new UserDao();
		List<User> list = new ArrayList<User>();
		int length = userDao.getAllUser().size();
		User user = null;
		for (int i = 0; i < length; i++) {
			user = userDao.getAllUser().get(i);
			if (user.getUserName().contains(keyword)) {
				list.add(user);
			}
		}

		return list;
	}

	/**
	 * 
	 * @param userName 要查询的用户名
	 * @return 如果存在返回用户对象，不存在返回空
	 */
	public User queryUserByName(String userName) {
		UserDao userDao = new UserDao();
		return userDao.getUserByName(userName);
	}

	/**
	 * 修改用户之间的好友关系
	 * 
	 * @param user1    用户甲
	 * @param user2    用户乙
	 * @param isFriend 新的好友关系：是否是好友
	 */
	public void changeUserRelation(String user1, String user2, boolean isFriend) {
		FriendDao friendDao = new FriendDao();
		Friend friend = new Friend();
		friend.setUserName(user1);
		friend.setFriendName(user2);
		if (isFriend) {
			friendDao.addFriendToUser(friend);
		} else {
			friendDao.deleteFriendOfUser(friend);
		}
	}

	/**
	 * 查找该用户的所有好友名单
	 * 
	 * @param userName   目标用户名
	 * @param friendList 查询的结果，一个好友名单的数组
	 */
	public List<Friend> queryFriendList(String userName) {
		FriendDao friendDao = new FriendDao();
		List<Friend> list = new ArrayList<Friend>();
		User user = new User();
		user.setUserName(userName);
		list = friendDao.listAllFriendOfUser(user);

		return list;
	}

}
