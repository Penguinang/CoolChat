#include "loginwindow.h"
#include "registerwindow.h"
#include "mainwindow.h"
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


LoginWindow::LoginWindow(QWidget *parent)
    :QWidget(parent)
{
    //m_server = new Server();   //实例化服务类

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    this->setMaximumSize(580,350);
    this->setMinimumSize(580,350);

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

//登陆按钮slot函数
void LoginWindow::slotLogin()
{
    getUserName();
    //对输入的处理，例如对密码的要求不能输入中文等
    if(checkUserName(g_username)==false)
    {
        //提示错误（不能为空 或 不能为中文 或 长度太长 或 长度太短）
        return;
    }
    void (LoginWindow::*pCallback)(bool,std::string)= &LoginWindow::callback;
    //通知服务器登录
    //m_server->Login(g_username.toStdString(),g_password.toStdString(),pCallback);
    MainWindow* mainwin = new MainWindow();
    mainwin->show();
    this->close();
}

void LoginWindow::slotRegister()
{
    registerWindow = new RegisterWindow();
    registerWindow ->show();
}

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

void LoginWindow::getUserName()
{
    g_username = userNameLineEdit->text();
    qDebug("%s",qPrintable(g_username));
}

void LoginWindow::getPassWord()
{
    g_password = passWordLineEdit->text();
    qDebug("%s",qPrintable(g_password));

}

void LoginWindow::callback(bool success,std::string extra)
{
    if(success == true)
    {
        MainWindow* mainwin = new MainWindow();
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

//检查用户名格式是否输入正确
bool LoginWindow::checkUserName(QString string)
{
    return true;
}

