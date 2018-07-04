0. SignUpMessage
0. SignUpResultMessage
0. LoginMessage
0. LoginResultMessage
0. PullMessage
0. PullResultMessage
0. TextMessage
0. QueryUserInformationMessage
0. QueryUserResultMessage
0. RequestFriendMessage (请求好友一阶段，点击添加按钮)
0. SendRequestMessage (请求好友二阶段)
0. ReplyPermissionMessage (请求好友三阶段)
0. SendReplyMessage (请求好友四阶段)
0. DeleteFriendMessage
0. QueryFriendListMessage
0. QueryFriendListResultMessage
0. LogOutMessage

## SignUpMessage

 Length  |  Content | 
 -------- | ------- | 
  1 bytes  | Messsage Type  |
  4 bytes  | 用户名长度 |
   变长     | 用户名 |
   4 bytes | 邮件地址长度
   变长     | 邮件地址
  4 bytes  | 密码长度  |
   变长  | 密码  |

## SignUpResultMessage

 Length  |  Content | 
 -------- | ------- | 
  1 bytes  | Messsage Type  |

## LoginMessage

 Length  |  Content | 
 -------- | ------- | 
  1 bytes  | Messsage Type  |
  4 bytes  | 用户名长度 |
   变长  | 用户名 |
  4 bytes  | 密码长度  |
   变长  | 密码  |

## LoginResultMessage

 Length  |  Content | 
 -------- | ------- | 
  1 bytes  | Messsage Type  |
  4bytes  | 返回码

## PullMessage

 Length  |  Content | 
 -------- | ------- | 
  1 bytes  | Messsage Type  |

## PullResultMessage

 Length  |  Content | 
 -------- | ------- | 
  1 bytes  | Messsage Type  |
  4 bytes  | 消息个数 |
  4 bytes  | 用户名长度 |
  变长| 用户名|
  4 bytes  | 文本长度 |
  变长| 文本内容 |
  ... | ... |

## TextMessage

 Length  |  Content | 
 -------- | ------- | 
  1 bytes  | Messsage Type  |
  4 bytes  | 目标(来源)用户名长度 |
   变长  | 目标(来源)用户名 |
  4 bytes  | 消息长度  |
   变长  | 消息内容(附带时间戳前缀YYYY-MM-DD-hh-mm-ss)  |

## QueryUserInformationMessage

 Length  |  Content | 
 -------- | ------- | 
  1 bytes  | Messsage Type  |
  4 bytes  | 关键字长度 |
   变长  | 关键字内容 |

## QueryUserResultMessage

 Length  |  Content | 
 -------- | ------- | 
  1 bytes  | Messsage Type  |
  4 bytes | 返回用户个数 |
  4 bytes  | 用户名长度 |
  变长 | 用户名内容 |
  ...     |       ...     |

## RequestFriendMessage (请求好友一阶段，点击添加按钮)

 Length  |  Content | 
 -------- | ------- | 
  1 bytes  | Messsage Type  |
  4 bytes | 目标用户名长度 |
  变长  | 目标用户名内容 |
  4 bytes | 附注长度 |
  变长 | 附注内容  |

## SendRequestMessage (请求好友二阶段)

 Length  |  Content | 
 -------- | ------- | 
  1 bytes  | Messsage Type  |
  4 bytes | 来源用户名长度 |
  变长  | 来源用户名内容 |
  4 bytes | 附注长度 |
  变长 | 附注内容  |

## ReplyPermissionMessage (请求好友三阶段)

 Length  |  Content | 
 -------- | ------- | 
  1 bytes  | Messsage Type  |
  1 byte   | 同意 |
  4 bytes | 目标用户名长度 |
  变长  | 目标用户名内容 |
  4 bytes | 附注长度 |
  变长 | 附注内容  |

## SendReplyMessage (请求好友四阶段)

 Length  |  Content | 
 -------- | ------- | 
  1 bytes  | Messsage Type  |
  1 byte   | 同意 |
  4 bytes | 来源用户名长度 |
  变长  | 来源用户名内容 |
  4 bytes | 附注长度 |
  变长 | 附注内容  |

## DeleteFriendMessage

 Length  |  Content | 
 -------- | ------- | 
  1 bytes  | Messsage Type  |
  4 bytes | 目标用户名长度 |
  变长  | 目标用户名内容 |

## QueryFriendListMessage

 Length  |  Content | 
 -------- | ------- | 
  1 bytes  | Messsage Type  |

## QueryFriendListResultMessage

 Length  |  Content | 
 -------- | ------- | 
  1 bytes  | Messsage Type  |
  4 bytes  | 好友个数 |
  4 bytes  | 用户名长度
  变长      | 用户名
  ...       | ...

## LogOutMessage

 Length  |  Content | 
 -------- | ------- | 
  1 bytes  | Messsage Type  |
