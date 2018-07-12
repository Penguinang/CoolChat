#include "Server.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addfriend.h"
#include "chatwindow.h"
#include <QPushButton>
#include <QFont>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QPainter>
#include <QDebug>
#include <QString>
#include <string>
#include <QMap>
#include "systemwindow.h"

//中文乱码处理
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

QMap<QString,int> m_map;
QMap<QString, QString> messagesQueue;
ChatWindow* chatWindow[20];
SystemWindow *systemWindow;
QPushButton *systemBtn;
AddFriend *addWindow;
QPushButton *friends[5];
int friend_count = 0;

using namespace std;


MainWindow::MainWindow(Server *server, QWidget *parent):
    QWidget(parent)
{
    this->m_server = server;

    setWindowTitle(tr("CoolChat"));
    this->setMaximumSize(780,500);
    this->setMinimumSize(780,500);


    QPushButton *buttonChat;                        //"开始聊天吧！"按钮制作
    buttonChat = new QPushButton(this);
    buttonChat->setGeometry(QRect(400,160,200,80));
    buttonChat->setText("开始聊天吧!");

    QFont font("Microsoft YaHei",22,75);        //设置按钮字体大小并影藏按钮框
    buttonChat->setFont(font);
    buttonChat->setFlat(true);

    //添加好友按钮图标制作
    QIcon add;
    add.addFile(tr(":/new/img/img/2.png"));

    //Logo图标制作
    QIcon log;
    log.addFile(tr(":/new/img/img/1.png"));
    QPushButton *logo;
    logo=new QPushButton(this);
    logo->setGeometry(QRect(0,0,40,50));
    logo->setIcon(log);
    logo->setIconSize(QSize(40,50));
    logo->setFlat(true);


    //聊天窗口QStackedWidget
    m_cStackedWidget = new QStackedWidget(this);
    m_cStackedWidget->setMinimumSize(560,500);
    m_cStackedWidget->move(220,0);
    m_cStackedWidget->hide();

    // list = new QListWidget(this);
    // list->setMinimumSize(220,300);
    // list->setMaximumSize(220,300);
    // list->move(0,0);
    // connect(list,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(singleclicked(QListWidgetItem*)));

    //添加好友按钮
    QPushButton *addBtn;
    addBtn = new QPushButton(this);
    addBtn->setGeometry(QRect(160,440,40,40));
    addBtn->setIconSize(QSize(40,40));////根据实际调整图片大小
    addBtn->setIcon(add);
    addBtn->setFlat(true);// 去掉边框
    connect(addBtn,SIGNAL(clicked(bool)),this,SLOT(AnotherWindow()));

    systemBtn = new QPushButton(this); 
    systemBtn->setMinimumSize(220, 50);
    systemBtn->move(0, 0);
    systemBtn->setText(QString::fromStdString("system"));
    systemBtn->show();
    systemBtn->update();
    systemWindow = new SystemWindow(m_server,0,"System",500,560,this);
    m_cStackedWidget->addWidget(systemWindow);
    m_map.insert(QString::fromStdString("server friend reply"), 0);
    connect(systemBtn, SIGNAL(clicked(bool)),this,SLOT(friendBtnOnClicked()));

    for(int i=0;i<5;i++)
    {
        friends[i]=new QPushButton(this);
        friends[i]->setMinimumSize(220,50);
        friends[i]->move(0,(i+1)*50);
        friends[i]->setText(QString::fromStdString("0"));
        friends[i]->show();
        friends[i]->update();

        char buf[3] = {0};
        sprintf(buf, "%d", i);
        chatWindow[i]=new ChatWindow(m_server,0,QString::fromStdString(string(buf)),500,560,this);
        m_cStackedWidget->addWidget(chatWindow[i]);
        //m_map.insert(QString::fromStdString("0"),i);
        connect(friends[i],SIGNAL(clicked(bool)),this,SLOT(friendBtnOnClicked()));
        friends[i]->hide();
    }
    this->update();
}

MainWindow::~MainWindow()
{
}

void MainWindow::AnotherWindow()
{
    addWindow=new AddFriend(m_server,0,this);
    addWindow->show();
}


void MainWindow::paintEvent(QPaintEvent*)
{
    paint=new QPainter;
    paint->begin(this);
    paint->setPen(QPen(Qt::white,4,Qt::SolidLine));//设置画笔形式
    paint->setBrush(QBrush(Qt::white,Qt::SolidPattern));//设置画刷形式
    paint->drawRect(0,0,218,500);
    paint->end();
}

void MainWindow::callback(vector<struct userinfo> &friends_list)
{
    for(int i=0;i<friends_list.size();i++)
    {
        string name = friends_list[i].username;
        friends[i]->setText(QString::fromStdString(name));
        chatWindow[i]->friendName->setText(QString::fromStdString(name));
        friends[i]->show();
        friends[i]->setStyleSheet("background-color: rgb(255, 255, 255);");
        m_map.insert(QString::fromStdString(friends_list[i].username),i+1);
        connect(friends[i],SIGNAL(clicked(bool)),this,SLOT(friendBtnOnClicked()));
        friend_count ++;
    }
    this->update();    
}

void MainWindow::friendBtnOnClicked()
{
    QPushButton *btn=qobject_cast<QPushButton*>(sender());
    btn->setStyleSheet("background-color: rgb(255, 255, 255);");
    string a = btn->text().toStdString();
    string username = a.substr(1, a.length()).c_str();
    m_cStackedWidget->setCurrentIndex(m_map[QString::fromStdString(username)]);
    m_cStackedWidget->show();
    if(messagesQueue[QString::fromStdString(username)] != ""){
        int index = m_map[QString::fromStdString(username)] - 1;
        if (index==-1) 
            systemWindow->recvMsgShow(messagesQueue[QString::fromStdString(username)],NULL);
        else
            chatWindow[index]->recvMsgShow(messagesQueue[QString::fromStdString(username)],NULL);
    }
    messagesQueue[QString::fromStdString(username)] = "";
}

void MainWindow::get_text_callback(string username,string time,string content)
{
    printf("Get a message\n");
    if(username!="server friend reply" && username != "server friend request")
    {
        messagesQueue.insert(QString::fromStdString(username), QString::fromStdString(content));
    }
    else
    {
        if(username == "server friend reply"){
            printf("Server message\n");
            if(content == "success"){
                printf("Server reply\n");
                friends[friend_count]->setText(QString::fromStdString(time));
                chatWindow[friend_count]->friendName->setText(QString::fromStdString(time));
                friends[friend_count]->show();
                friends[friend_count]->setStyleSheet("background-color: rgb(255, 255, 255);");
                m_map.insert(QString::fromStdString(time),friend_count+1);
                connect(friends[friend_count],SIGNAL(clicked(bool)),this,SLOT(friendBtnOnClicked()));
                friend_count ++;                
            }
        }
        else if (username == "server friend request"){
            messagesQueue.insert(QString::fromStdString("system"), QString::fromStdString(time+" Request add friend"));
            systemWindow->username = time;
        }
    }
}

//从好友列表删除好友
void MainWindow::deleteFriend(string friendname)
{
    this->list->removeItemWidget(this->list->item(m_map[QString::fromStdString(friendname)]));
    this->m_cStackedWidget->removeWidget(this->m_cStackedWidget->currentWidget());
    this->update();
    this->m_cStackedWidget->hide();
}

//添加好友到列表
void MainWindow::addFriend(string friendname)
{
    friends[friend_count]->setText(QString::fromStdString(friendname));
    chatWindow[friend_count]->friendName->setText(QString::fromStdString(friendname));
    friends[friend_count]->show();
    friends[friend_count]->setStyleSheet("background-color: rgb(255, 255, 255);");
    m_map.insert(QString::fromStdString(friendname),friend_count+1);
    connect(friends[friend_count],SIGNAL(clicked(bool)),this,SLOT(friendBtnOnClicked()));
    friend_count ++;   
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    m_server->Logout();
    event->accept();
}
