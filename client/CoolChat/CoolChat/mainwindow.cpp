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

//中文乱码处理
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    this->setMaximumSize(780,500);
    this->setMinimumSize(780,500);

    QPushButton *button;                        //"开始聊天吧！"按钮制作
    button = new QPushButton(this);
    button->setGeometry(QRect(400,160,200,80));
    button->setText("开始聊天吧!");

    QFont font("Microsoft YaHei",22,75);        //设置按钮字体大小并影藏按钮框
    button->setFont(font);
    button->setFlat(true);

    QFont font1("Microsoft YaHei",15,50);
    QPushButton *person;                        //列表顶端
    person = new QPushButton(this);
    person->setGeometry(QRect(0,0,220,80));
    person->setText("小明");
    person->setStyleSheet("background-color:white");
    person->setFont(font1);

    //小红
    QPushButton *person1;
    person1=new QPushButton(this);
    person1->setGeometry(QRect(0,80,220,50));
    person1->setText("小红");
    person1->setStyleSheet("background-color:white");
    person1->setFont(font1);
    //qDebug()<<person1->text()<<endl;获取联系人姓名

    //小强
    QPushButton *person2;
    person2=new QPushButton(this);
    person2->setGeometry(QRect(0,130,220,50));
    person2->setText("小强");
    person2->setStyleSheet("background-color:white");
    person2->setFont(font1);

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

    /*手动添加聊天窗口仅测试，之后需要修改
     *
    *solution：
    *从后台获取好友信息，建立QListWidget(https://blog.csdn.net/wcknxx/article/details/76497519?locationNum=9&fps=1)
    *遍历后台传来的好友信息，添加好友Item到QListWidget
    *并设置名称和ID（按顺序）的QMap映射
    *并调用ChatWindow构造函数创建聊天页面添加到QStackedWidget中(按顺序编ID号的意义即在于此）
    *
    *当点击某个好友按钮时，获取该按钮（https://blog.csdn.net/anjicun/article/details/38846659）
    *QPushButton->text()获取该好友名称
    *通过QMap找到ID
    *QStackedWidget->setCurrentWidget(ID)
    *QStackedWidget->show()
    */
    ChatWindow* chat_1 = new ChatWindow(0,"小红",500,560);
    ChatWindow* chat_2 = new ChatWindow(0,"小强",500,560);

    m_cStackedWidget->addWidget(chat_1);
    m_cStackedWidget->addWidget(chat_2);

    connect(person1,SIGNAL(clicked()),this,SLOT(ShowChatWindow_1()));
    connect(person2,SIGNAL(clicked()),this,SLOT(ShowChatWindow_2()));

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

void MainWindow::ShowChatWindow_1()
{
    m_cStackedWidget->show();
    m_cStackedWidget->setCurrentIndex(0);
}

void MainWindow::ShowChatWindow_2()
{
    m_cStackedWidget->show();
    m_cStackedWidget->setCurrentIndex(1);
}

void MainWindow::paintEvent(QPaintEvent*)
//paintEvent函数由系统自动调用，用不着我们人为的去调用。
{
    paint=new QPainter;
    paint->begin(this);
    paint->setPen(QPen(Qt::white,4,Qt::SolidLine));//设置画笔形式
    paint->setBrush(QBrush(Qt::white,Qt::SolidPattern));//设置画刷形式
    paint->drawRect(0,0,220,500);
    paint->end();

}

