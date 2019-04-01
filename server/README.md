1. 关于数据库
    * -u root -p Ren@123 -P 3306
    * 名字: CoolChat
        * 表 user(userName char(20),E_mail char(20),password char(20));
        * 表 friend (name char(20), userName char(20));
        * 表 message(date char(19),sentUser char(20),receiveUser char(20),content varchar(1024));
        * 表 s_message(date char(19),sentUser char(20),receiveUser char(20),content varchar(1024));