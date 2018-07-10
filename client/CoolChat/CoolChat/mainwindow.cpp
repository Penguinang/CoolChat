#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addfriend.h"
#include "chatwindow.h"
#include <server.h>
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
ChatWindow* chatWindow[20];
SystemWindow *systemWindow;
AddFriend *addWindow;

using namespace std;

MainWindow::MainWindow(QWidget *parent,Server* server) :
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

    list = new QListWidget(this);
    list->setMinimumSize(220,500);
    list->setMaximumSize(220,500);
    list->move(0,0);
    connect(list,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(singleclicked(QListWidgetItem*)));

    //添加好友按钮制作
    QPushButton *addBtn;
    addBtn = new QPushButton(this);
    addBtn->setGeometry(QRect(160,440,40,40));
    addBtn->setIconSize(QSize(40,40));////根据实际调整图片大小
    addBtn->setIcon(add);
    addBtn->setFlat(true);// 去掉边框
    connect(addBtn,SIGNAL(clicked(bool)),this,SLOT(AnotherWindow()));
    auto callback=std::bind(&MainWindow::callback,this,placeholders::_1);
    m_server->GetFriendList (callback);
}

MainWindow::~MainWindow()
{
}

void MainWindow::AnotherWindow()
{
    addWindow=new AddFriend(0,m_server,this);
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
    QListWidgetItem *systemItem;
    systemItem=new QListWidgetItem;
    systemItem->setText("server friend reply");
    systemItem->setFont(font1);
    systemWindow = new SystemWindow(0,"server friend reply",500,560,m_server);
    systemItem->setSizeHint(QSize(220,50));
    list->addItem(systemItem);
    m_cStackedWidget->addWidget(systemWindow);
    m_map.insert("server friend reply",0);
    for(int i=0;i<friends_list.size();i++)
    {
        QListWidgetItem* item = new QListWidgetItem;
        item->setText(QString::fromStdString(friends_list[i].username);
        item->setSizeHint(QSize(220,50));
        list->addItem(item);
        chatWindow[i]=new ChatWindow(0,QString::fromStdString(friends_list[i].username),500,560,this);
        m_cStackedWidget->addWidget(chatWindow[i]);
        m_map.insert(QString::fromStdString(friends_list[i].username),i+1);
    }
}

void MainWindow::singleclicked(QListWidgetItem *item)
{
    item->setBackgroundColor(Qt::white);
    m_cStackedWidget->setCurrentIndex(m_map[item->text()]);
    m_cStackedWidget->show();
}

void MainWindow::get_text_callback(string username,string time,string content)
{
    if(username!="server friend reply")
    {
        if((m_cStackedWidget->isHidden()==true)||(m_cStackedWidget->currentIndex()!=m_map[QString::fromStdString(username)]))
        {
            chatWindow[m_map[QString::fromStdString(username)]]->recvMsgShow(QString::fromStdString(content),NULL);
            list->item(m_map[QString::fromStdString(username)])->setBackgroundColor(Qt::red);
        }
        else
            chatWindow[m_map[QString::fromStdString(username)]]->recvMsgShow(QString::fromStdString(content),NULL);
    }
    else
    {
        this->systemWindow->username = time;
        this->systemWindow->newmsg = true;
        if((m_cStackedWidget->isHidden()==true)||(m_cStackedWidget->currentIndex()!=0))
        {
            systemWindow->recvMsgShow(QString::fromStdString(content+"请求添加你为好友"),NULL);
            list->item(m_map[QString::fromStdString(username)])->setBackgroundColor(Qt::red);
        }
        else
            systemWindow->recvMsgShow(QString::fromStdString(content+"请求添加你为好友"),NULL);
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

void MainWindow::addFriend(string friendname)
{
    QListWidgetItem* item = new QListWidgetItem;
    item->setText(QString::fromStdString(friendname);
    item->setSizeHint(QSize(220,50));
    list->addItem(item);
    chatWindow[list->count()+1]=new ChatWindow(0,QString::fromStdString(friendname),500,560,this);
    m_cStackedWidget->addWidget(chatWindow[list->count()]);
    m_map.insert(QString::fromStdString(friendname),list->count()+1);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    m_server->Logout();
    event->accept();
}
