package CoolChat.Messages;

import java.util.HashMap;
import java.util.List;

import org.apache.mina.core.buffer.IoBuffer;
import org.apache.mina.core.session.IoSession;

import CoolChat.Data.DataManager;
import enity.User;

/**
 * Class QueryUserInformationMessage
 */
public class QueryUserInformationMessage extends Message{
	private String keyword;
   
    public QueryUserInformationMessage (String keyword) {
    	this.keyword=keyword;
    }

	@Override
	public Message getResult(HashMap<String, IoSession> sessions, IoSession session, DataManager dataManager) {
		// 将包含关键字的用户从数据库中拿出来，放在相应的result类中
		List<User> list=dataManager.queryUser(keyword);
		
		int userNumber=list.size();
		String[] userNames=new String[userNumber];
		for(int i=0;i<userNumber;i++) {
			userNames[i]=list.get(i).getUserName();
		}
		
		return new QueryUserResultMessage(userNumber, userNames);
	}

	@Override
	public byte[] getProtocolEncodedBytes() {
		// 编号7
		byte messageType=7;
		int keywordLength=keyword.length();
		byte[] keywordB=keyword.getBytes();
		
		IoBuffer ret=IoBuffer.allocate(1+4+keywordLength);
		ret.putInt(messageType);
		ret.put(keywordB);
		
		return ret.array();
	};
    
    

}
