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

//中文乱码处理
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{

    setWindowTitle(tr("CoolChat"));
    this->setMaximumSize(780,500);
    this->setMinimumSize(780,500);

    QPushButton *button;                        //"开始聊天吧！"按钮制作
    button = new QPushButton(this);
    button->setGeometry(QRect(400,160,200,80));
    button->setText("开始聊天吧!");

    QFont font("Microsoft YaHei",22,75);        //设置按钮字体大小并影藏按钮框
    button->setFont(font);
    button->setFlat(true);

    QListWidget *list = new QListWidget(this);  //建立好友列表
    list->setGeometry(0,50,220,500);

    QListWidgetItem *person1 = new QListWidgetItem; //向好友列表中添加好友
    QListWidgetItem *person2 = new QListWidgetItem;
    person1->setText("    小明");
    person2->setText("    小红");
    list->addItem(person1);
    list->addItem(person2);
    QFont font1("Microsoft YaHei",15,50);
    person1->setFont(font1);
    person2->setFont(font1);

    QPushButton *person;                        //列表顶端
    person = new QPushButton(this);
    person->setGeometry(QRect(0,0,220,50));
    person->setText("小明");
    person->setStyleSheet("background-color:white");
    person->setFont(font1);


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

    //手动添加聊天窗口仅测试，之后需要修改
    ChatWindow* chat_1 = new ChatWindow(0,"小明",560,500);
    ChatWindow* chat_2 = new ChatWindow(0,"小红",560,500);

    m_cStackedWidget->addWidget(chat_1);
    m_cStackedWidget->addWidget(chat_2);

}

//openAction = new QAction(QIcon("D:/Program/Qt/CoolChat/img/1.png"), tr("&Open..."), this);
//openAction->setShortcuts(QKeySequence::Open);
//openAction->setStatusTip(tr("Chat!"));
//connect(openAction, &QAction::triggered, this, &MainWindow::chat);
//    QToolBar *toolBar = addToolBar(tr("&File"));
//    toolBar->addAction(openAction);
//    statusBar() ;

//    QPushButton *person1;
//    person1 = new QPushButton(this);
//    person1->setText("小明");
//    QFont font1("Microsoft YaHei",15,50);
//    person1->setFont(font1);

//    QPushButton *person2;
//    person2 = new QPushButton(this);
//    person2->setText("小红");
//    person2->setFont(font1);
//    QVBoxLayout *layoutLeft=new QVBoxLayout;
//    QVBoxLayout *layoutRight=new QVBoxLayout;
//    layoutLeft->addWidget(toolBar);
//    layoutLeft->addWidget(person);
//    layoutLeft->addWidget(person1);
//    layoutLeft->addWidget(person2);
//    layoutRight->addWidget(button);

//    QHBoxLayout *layout=new QHBoxLayout;

//    layout->addLayout(layoutLeft);
//    layout->addLayout(layoutRight);
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

void MainWindow::ShowChatWindow(QString string,int index)
{
    m_cStackedWidget->setCurrentIndex(index);
}
