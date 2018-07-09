#include "addfriend.h"
#include <QLineEdit>
#include <QIcon>
#include <QPushButton>
#include <QDebug>
#include <QString>

//中文乱码处理
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

AddFriend::AddFriend(QWidget *parent): QWidget(parent)
{
    setWindowTitle(tr("CoolChat"));
    //this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    //this->setAttribute(Qt::WA_TranslucentBackground);
    this->setMaximumSize(600,500);
    this->setMinimumSize(600,500);

    input=new QLineEdit(this);
    input->setPlaceholderText("好友账号");
    input->setFocus();
    input->setGeometry(QRect(100,100,200,40));

    //查找图标制作
    QIcon search;
    //search.addFile(tr("D:/Program/Qt/CoolChat/img/3.png"));
    //将图片路径改为资源文件路径
    search.addFile(tr(":/new/img/img/3.png"));

    //查找按钮制作
    QPushButton *searchBtn;
    searchBtn=new QPushButton(this);
    searchBtn->setGeometry(QRect(350,95,100,50));
    searchBtn->setIcon(search);
    searchBtn->setIconSize(QSize(100,50));
    searchBtn->setFlat(true);
    connect(searchBtn,SIGNAL(clicked(bool)),this,SLOT(SearchFriend()));

}

AddFriend::~AddFriend()
{
}


void AddFriend::SearchFriend()
{
    //TODO查找朋友按钮响应事件
    qDebug()<<"查找成功"<<input->text();
}
