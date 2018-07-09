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

//中文乱码处理
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

QMap<QString,int> m_map;

using namespace std;


//登录后主页面
MainWindow::MainWindow(QWidget *parent,Server *server) :
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

    //添加好友按钮制作
    QPushButton *addBtn;
    addBtn = new QPushButton(this);
    addBtn->setGeometry(QRect(160,440,40,40));
    addBtn->setIconSize(QSize(40,40));////根据实际调整图片大小
    addBtn->setIcon(add);
    addBtn->setFlat(true);// 去掉边框

    connect(addBtn,SIGNAL(clicked(bool)),this,SLOT(AnotherWindow()));

    //Logo图标制作
    QIcon log;
    log.addFile(tr(":/new/img/img/1.png"));

    QPushButton *logo;
    logo=new QPushButton(this);
    logo->setGeometry(QRect(0,0,40,50));
    logo->setIcon(log);
    logo->setIconSize(QSize(40,50));
    logo->setFlat(true);
    connect(logo,&QPushButton::clicked,this,&MainWindow::chat);

    //聊天窗口QStackedWidget
    m_cStackedWidget = new QStackedWidget(this);
    m_cStackedWidget->setMinimumSize(560,500);
    m_cStackedWidget->move(220,0);
    m_cStackedWidget->hide();

    callback();


}

MainWindow::~MainWindow()
{
}

void MainWindow::chat()
{
    QMessageBox::information(this, tr("CoolChat"), tr("Chat"));
}

void MainWindow::AnotherWindow()
{
    addWindow=new AddFriend();
    addWindow->show();
}

void MainWindow::ShowChatWindow(string string,int index)
{
    m_cStackedWidget->setCurrentIndex(index);
    chatWindow=new ChatWindow();
    chatWindow->show();
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

void MainWindow::buttonOnClicked()
{
    QPushButton* btn= qobject_cast<QPushButton*>(sender());
    m_cStackedWidget->setCurrentIndex(m_map[btn->text()]);
    m_cStackedWidget->show();
}

void MainWindow::callback(vector<struct userinfo> &friends_list)
{
    string friends[5]={"Bob","Tom","Jerry","Smith","Tim"};
    ChatWindow* chatWindow[sizeof(friends)/sizeof(friends[0])];
    QFont font1("Microsoft YaHei",15,50);
    for(int i=0;i<sizeof(friends)/sizeof(friends[0]);i++)
    {
        button[i]=new QPushButton(this);
        button[i]->setGeometry(0,0+50*i,220,50);
        button[i]->setText(QString::fromStdString(friends[i]));
        button[i]->setFont(font1);
        button[i]->setStyleSheet("background-color:rgb(255,240,245)");
        chatWindow[i]=new ChatWindow(0,QString::fromStdString(friends[i]),500,560);
        m_cStackedWidget->addWidget(chatWindow[i]);
        m_map.insert(QString::fromStdString(friends[i]),i);
        connect(button[i],SIGNAL(clicked()),this,SLOT(buttonOnClicked()));
    }
}



