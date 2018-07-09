#include "addfriend.h"
#include <QLineEdit>
#include <QIcon>
#include <QPushButton>
#include <QDebug>
#include <QString>
#include <QFont>
#include <QPalette>
#include <vector>
#include <QGridLayout>
#include "applicationwindow.h"
//#include "Server.h"

//中文乱码处理
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

using namespace std ;



AddFriend::AddFriend(QWidget *parent): QWidget(parent)
{

    //m_server = new Server();
    setWindowTitle(tr("CoolChat"));
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setMaximumSize(550,400);
    this->setMinimumSize(550,400);

    input=new QLineEdit(this);
    input->setPlaceholderText("好友账号");
    input->setFocus();
    input->setGeometry(QRect(100,100,200,40));

    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);

    //查找按钮制作
    QFont *font=new QFont("Microsoft YaHei",12,0);
    font->setLetterSpacing(QFont::AbsoluteSpacing,0.5);
    QPushButton *searchBtn;
    searchBtn=new QPushButton(tr("Search"),this);
    searchBtn->setFont(*font);
    searchBtn->setPalette(pa);
    searchBtn->setStyleSheet("QPushButton{background-color:rgb(0,162,232);border:2px groove white;border-radius:10px;padding:2px 4px;color:white;}"
                           "QPushButton:pressed{background-color:rgb(153,217,234);}");
    searchBtn->setMinimumHeight(40);
    searchBtn->setMinimumWidth(100);
    searchBtn->move(350,100);
    connect(searchBtn,SIGNAL(clicked(bool)),this,SLOT(SearchFriend()));

    exit = new QPushButton(this);
    exit->setStyleSheet("QPushButton{border-image:url(:/new/img/img/exit.png);}"
                        "QPushButton:hover{border-image:url(:/new/img/img/exit1.png);}"
                        "QPushButton:pressed{border-image:url(:/new/img/img/exit.png);}");
    exit->setMinimumHeight(40);
    exit->setMinimumWidth(50);
    exit->move(500,0);
    min = new QPushButton(this);
    min->setStyleSheet("QPushButton{border-image:url(:/new/img/img/min.png);}"
                       "QPushButton:hover{border-image:url(:/new/img/img/min2.png);}"
                       "QPushButton:pressed{border-image:url(:/new/img/img/min.png);}");
    min->setMinimumHeight(40);
    min->setMinimumWidth(50);
    min->move(452,0);

    connect(exit,SIGNAL(clicked()),this,SLOT(windowclosed()));
    connect(min,SIGNAL(clicked()),this,SLOT(windowmin()));
    pWidget = new QWidget(this);
    pLayout = new QGridLayout(pWidget);

    pix = QPixmap(":/new/img/img/FaceQ.png");

}

AddFriend::~AddFriend()
{
}


void AddFriend::SearchFriend()
{
    void (AddFriend::*pCallback)(std::vector<struct userinfo> &user_list)= &AddFriend::callback;
    //向服务器查询用户列表
    //m_server->QueryInformationByID(input->text().toStdString(),pCallback);
    qDebug()<<"查找成功"<<input->text();
}

void AddFriend::callback(std::vector<struct userinfo> &user_list)
{
    delete pLayout;
    delete pWidget;
    pLayout = new QGridLayout(this);
    QLabel* labelList[10];
    QPushButton* buttonList[10];
    /*
    for(int i=0;i<user_list.size();i++)
    {
        labelList[i]->setPixmap(pix);
        pLayout->addWidget(labelList[i],i,0);
        //buttonList[i]->setText(QString::fromStdString(user_list[i]));
        connect(buttonList[i],SIGNAL(clicked()),this,SLOT(BtnListOnClicked()));
        pLayout->addWidget(buttonList[i],i,1);
    }
    pWidget->setMaximumSize(500,250);
    pWidget->setMinimumSize(500,250);
    pWidget->move(0,150);*/
}

void AddFriend::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(255,255,255));
    QRect rect = this->rect();
    rect.setWidth(rect.width()-1);
    rect.setHeight(rect.height()-1);
    p.drawRoundedRect(rect,15,15);
    p.setPen(QPen(QColor(200,200,200),1));
    p.drawRoundedRect(rect,15,15);
}

void AddFriend::windowclosed()
{
    this->close();
}

void AddFriend::windowmin()
{
    this->showMinimized();
}

void AddFriend::BtnListOnClicked()
{
    QPushButton* btn= qobject_cast<QPushButton*>(sender());
    ApplicationWindow* aWindow = new ApplicationWindow(0,btn->text());
    aWindow->show();
}

