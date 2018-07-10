#include "loginwindow.h"
#include "registerwindow.h"
#include "mainwindow.h"
#include "server.h"
#include <QPainter>
#include <QColor>
#include <QLabel>
#include <QString>
#include <QLineEdit>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QPixmap>
#include <QRect>
#include <QMouseEvent>
#include <QString>
#include <QDebug>
#include <QGraphicsOpacityEffect>
#include <functional>
#include <iostream>


//中文乱码处理
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif


using namespace std;
using namespace std::placeholders;

//登录界面
LoginWindow::LoginWindow(QWidget *parent)
    :QWidget(parent)
{
    auto get_text_callback=std::bind(&MainWindow::get_text_callback,mainwin,placeholders::_1,placeholders::_2,placeholders::_3);
    m_server = new Server("localhost",port,get_text_callback);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    this->setMaximumSize(580,350);
    this->setMinimumSize(580,350);

    m_tips = false;

    QLabel* titleLabel = new QLabel(QString("CoolChat"),this);
    QFont ft("Microsoft YaHei",30,63);
    titleLabel->setFont(ft);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    titleLabel->setPalette(pa);
    titleLabel->adjustSize();
    titleLabel->move((this->width()-titleLabel->width()) / 2,( this->height() - titleLabel->height() ) / 5);

    userNameLabel = new QLabel(tr("UserName:"));
    userNameLabel->setFont(QFont("Microsoft YaHei",12,0));
    userNameLabel->setPalette(pa);
    passWordLabel = new QLabel(tr("PassWord:"));
    passWordLabel->setFont(QFont("Microsoft YaHei",12,0));
    passWordLabel->setPalette(pa);

    registerBtn = new QPushButton(tr("Register"));
    QFont *font=new QFont("Microsoft YaHei",12,0);
    font->setUnderline(true);
    font->setLetterSpacing(QFont::AbsoluteSpacing,0.5);
    registerBtn ->setFont(*font);
    registerBtn ->setPalette(pa);
    registerBtn ->setStyleSheet("QPushButton{background:transparent;color:white;}"
                                "QPushButton:hover{color:rgb(153,217,234);}");

    userNameLineEdit = new QLineEdit;
    userNameLineEdit->setFont(QFont("Microsoft YaHei",12,0));
    userNameLineEdit->setFixedWidth(180);
    passWordLineEdit = new QLineEdit;
    passWordLineEdit->setEchoMode(QLineEdit::Password);
    passWordLineEdit->setFont(QFont("Microsoft YaHei",12,0));
    passWordLineEdit->setFixedWidth(180);

    QWidget* widget = new QWidget(this);
    widget->setMaximumSize(420,120);
    widget->setMinimumSize(420,120);
    widget->move((this->width()-widget->width()) /1.5,( this->height() - widget->height() ) / 5*3);

    QGridLayout *gridLayout = new QGridLayout(widget);
    gridLayout -> addWidget(userNameLabel,0,0,1,1);
    gridLayout -> addWidget(passWordLabel,1,0,1,1);
    gridLayout -> addWidget(userNameLineEdit,0,1,1,2);
    gridLayout -> addWidget(passWordLineEdit,1,1,1,2);
    gridLayout -> addWidget(registerBtn,0,3);
    gridLayout -> setHorizontalSpacing(10);
    gridLayout -> setVerticalSpacing(10);

    login = new QPushButton(tr("Login"),this);
    font->setUnderline(false);
    login->setFont(*font);
    login -> move((this->width()-login->width())/2,280);
    login->setMinimumHeight(50);
    login->setMinimumWidth(150);
    login->setStyleSheet("QPushButton{border:2px groove white;border-radius:10px;padding:2px 4px;color:white;}"
                         "QPushButton:hover{background-color:white;color:rgb(107,107,107);}"
                         "QPushButton:pressed{background-color:rgb(107,107,107);color:white;}");

    exit = new QPushButton(this);
    exit->setStyleSheet("QPushButton{border-image:url(:/new/img/img/exit.png);}"
                        "QPushButton:hover{border-image:url(:/new/img/img/exit1.png);}"
                        "QPushButton:pressed{border-image:url(:/new/img/img/exit.png);}");
    exit->setMinimumHeight(40);
    exit->setMinimumWidth(50);
    exit->move(530,0);
    min = new QPushButton(this);
    min->setStyleSheet("QPushButton{border-image:url(:/new/img/img/min.png);}"
                       "QPushButton:hover{border-image:url(:/new/img/img/min2.png);}"
                       "QPushButton:pressed{border-image:url(:/new/img/img/min.png);}");
    min->setMinimumHeight(40);
    min->setMinimumWidth(50);
    min->move(482,0);

    connect(exit,SIGNAL(clicked()),this,SLOT(windowclosed()));
    connect(min,SIGNAL(clicked()),this,SLOT(windowmin()));
    connect(registerBtn,SIGNAL(clicked()),this,SLOT(slotRegister()));
    connect(login,SIGNAL(clicked()),this,SLOT(slotLogin()));
}
LoginWindow::~LoginWindow()
{

}


void LoginWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(107,107,107));
    QRect rect = this->rect();
    rect.setWidth(rect.width()-1);
    rect.setHeight(rect.height()-1);
    p.drawRoundedRect(rect,15,15);
    QPixmap pixmap;
    pixmap.load(":/new/img/img/picture.png");
    p.drawPixmap(40,165,58,63,pixmap);
}

//关闭按钮slot函数
void LoginWindow::windowclosed()
{
    this->close();
}

//最小化按钮slot函数
void LoginWindow::windowmin()
{
    this->showMinimized();
}

//登录按钮slot函数
void LoginWindow::slotLogin()
{
    //初步判断用户输入格式，并通知服务器登录
    if((getUserName()==true )&& (getPassWord()==true))
    {
    auto callback=std::bind(&LoginWindow::callback,this,placeholders::_1,placeholders::_2);
    m_server->Login(g_username.toStdString(),g_password.toStdString(),callback);
    MainWindow* mainwin = new MainWindow();
    mainwin->show();
    this->close();
    }
}

//注册按钮slot函数
void LoginWindow::slotRegister()
{
    registerWindow = new RegisterWindow();
    registerWindow ->show();
}

//重写鼠标事件，页面位置随鼠标拖拽改变
void LoginWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(mbKeepPressed)
    {
        this->move(this->geometry().topLeft()+event->globalPos()-mPntStart);
        mPntStart = event->globalPos();
    }
}

void LoginWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        mbKeepPressed = true;
        mPntStart = event->globalPos();
    }
}

void LoginWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        mbKeepPressed = false;
    }
}

//获取用户名输入，并对格式进行初步判断
bool LoginWindow::getUserName()
{
    g_username = userNameLineEdit->text();
    if(((g_username == "")||(g_username==NULL))&& (m_tips == false))
    {
        showTips(tr("用户名不能为空！"));
        return false;
    }
    if(g_username.size()>10 && m_tips == false)
    {
        showTips(tr("用户名输入有误！"));
        return false;
    }
    return true;
}

//获取用户密码输入，并对格式进行初步判断
bool LoginWindow::getPassWord()
{
    g_password = passWordLineEdit->text();
    if(((g_password == "" )||(g_password == NULL))&& (m_tips == false))
    {
        showTips(tr("密码不能为空！"));
        return false;
    }
    if((g_password.size()<6||g_password.size()>16) && m_tips == false)
    {
        showTips(tr("密码长度有误！"));
    }
    int lenth = g_password.length();
    QByteArray by = g_password.toLocal8Bit();
    for(int index=0;index<lenth;index++)
    {
        char c = by.at(index);
        if((c>=48&&c<=57) || (c>=65&&c<=90) || (c>=97&&c<=122))
        {
        }
        else
        {
            showTips(tr("密码中含有非法字符！"));
            return false;
        }
    }
    return true;
}

void LoginWindow::callback(bool success,std::string extra)
{
    if(success == true)
    {
        mainwin = new MainWindow();
        mainwin->show();
        this->close();
    }
    if(success == false && extra!="")
    {
        QLabel* inf = new QLabel(QString::fromStdString(extra),this);
        inf->move((this->width()-inf->width())/2,250);
        inf->setFont(QFont("宋体",12,0));
        QPalette pa;
        pa.setColor(QPalette::WindowText,Qt::red);
        inf->setPalette(pa);
    }
}

//显示提示消息框并渐变效果隐藏消失
void LoginWindow::showTips(QString tipMsg)
{
    tips = new QLabel(this);
    tips->setMaximumHeight(50);
    tips->setMinimumHeight(50);
    QFont *font=new QFont("Microsoft YaHei",12,0);
    tips->setFont(*font);
    tips->setText(tipMsg);
    tips->setStyleSheet("QLabel{background-color:red;color:white;border-radius:10px;padding:2px 4px;}");
    tips->adjustSize();
    tips->move((this->width()-tips->width())/2,(this->height()-tips->height())/2);
    tips->show();
    m_tips = true;
    QTimer::singleShot(3000,this,SLOT(hideTips()));
    QTimer::singleShot(2700,this,SLOT(hideTips_1()));
    QTimer::singleShot(2800,this,SLOT(hideTips_2()));
    QTimer::singleShot(2900,this,SLOT(hideTips_3()));
}

//提示消息框渐变隐藏消失
void LoginWindow::hideTips()
{
    tips->hide();
    m_tips=false;
}

void LoginWindow::hideTips_1()
{
    QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
    tips->setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(0.8);
}

void LoginWindow::hideTips_2()
{
    QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
    tips->setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(0.5);
}

void LoginWindow::hideTips_3()
{
    QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
    tips->setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(0.2);
}



