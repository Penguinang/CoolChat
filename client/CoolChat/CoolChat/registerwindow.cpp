#include "Server.h"
#include "registerwindow.h"
#include "string.h"
#include <QPainter>
#include <QRect>
#include <QPushButton>
#include <QMouseEvent>
#include <QGridLayout>
#include <QLabel>
#include <QString>
#include <QLineEdit>
#include <QWidget>
#include <QPalette>
#include <QGraphicsOpacityEffect>
#include <QTimer>
#include <QByteArray>
#include <QDebug>

//中文乱码处理
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

//注册界面
RegisterWindow::RegisterWindow(QWidget *parent,Server *server) : QWidget(parent)
{
    parent = 0;
    this->m_server = server;

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setMaximumSize(580,500);
    this->setMinimumSize(580,500);

    this->m_tips = false;

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

    QWidget* grid = new QWidget(this);
    grid->setMinimumWidth(400);
    grid->setMaximumWidth(400);
    grid->setMinimumHeight(300);
    grid->setMaximumHeight(300);
    grid->move(90,100);

    QGridLayout* gridLayout = new QGridLayout(grid);

    QLabel *usernameLabel = new QLabel(QString("用户名："));
    QLabel *passwordLabel = new QLabel(QString("密码："));
    QLabel *confirmLabel = new QLabel(QString("确认密码："));
    QLabel *emailLabel = new QLabel(QString("E-mail:"));

    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);

    usernameLabel->setFont(QFont("Microsoft YaHei",12,0));
    usernameLabel->setPalette(pa);
    passwordLabel->setFont(QFont("Microsoft YaHei",12,0));
    passwordLabel->setPalette(pa);
    confirmLabel->setFont(QFont("Microsoft YaHei",12,0));
    confirmLabel->setPalette(pa);
    emailLabel->setFont(QFont("Microsoft YaHei",12,0));
    emailLabel->setPalette(pa);

    usernameEdit = new QLineEdit;
    passwordEdit = new QLineEdit;
    confirmEdit = new QLineEdit;
    emailEdit = new QLineEdit;

    usernameEdit->setFont(QFont("Microsoft YaHei",10,0));
    usernameEdit->setFixedWidth(250);
    usernameEdit->setPlaceholderText(tr("用户名由1-10个字符组成"));
    passwordEdit->setFont(QFont("Microsoft YaHei",10,0));
    passwordEdit->setFixedWidth(250);
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setPlaceholderText(tr("密码由6-16位数字和字母组成"));
    confirmEdit->setFont(QFont("Microsoft YaHei",10,0));
    confirmEdit->setFixedWidth(250);
    confirmEdit->setEchoMode(QLineEdit::Password);
    confirmEdit->setPlaceholderText(tr("请再次输入密码"));
    emailEdit->setFont(QFont("Microsoft YaHei",10,0));
    emailEdit->setFixedWidth(250);
    emailEdit->setPlaceholderText(tr("请输入正确的邮箱"));

    gridLayout->addWidget(usernameLabel,0,0);
    gridLayout->addWidget(passwordLabel,1,0);
    gridLayout->addWidget(confirmLabel,2,0);
    gridLayout->addWidget(emailLabel,3,0);
    gridLayout->addWidget(usernameEdit,0,1);
    gridLayout->addWidget(passwordEdit,1,1);
    gridLayout->addWidget(confirmEdit,2,1);
    gridLayout->addWidget(emailEdit,3,1);

    registerBtn = new QPushButton(tr("Register"),this);
    registerBtn->setFont(QFont("Microsoft YaHei",12,0));
    registerBtn -> move((this->width()-registerBtn->width())/2,420);
    registerBtn->setMinimumHeight(50);
    registerBtn->setMinimumWidth(150);
    registerBtn->setStyleSheet("QPushButton{border:2px groove white;border-radius:10px;padding:2px 4px;color:white;}"
                         "QPushButton:hover{background-color:white;color:rgb(107,107,107);}"
                         "QPushButton:pressed{background-color:rgb(107,107,107);color:white;}");

    connect(registerBtn,SIGNAL(clicked()),this,SLOT(slotRegister()));
}

RegisterWindow::~RegisterWindow()
{

}

void RegisterWindow::paintEvent(QPaintEvent *event)
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
}

void RegisterWindow::windowclosed()
{
    this->close();
}

void RegisterWindow::windowmin()
{
    this->showMinimized();
}

void RegisterWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(mbKeepPressed)
    {
        this->move(this->geometry().topLeft()+event->globalPos()-mPntStart);
        mPntStart = event->globalPos();
    }
}

void RegisterWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        mbKeepPressed = true;
        mPntStart = event->globalPos();
    }
}

void RegisterWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        mbKeepPressed = false;
    }
}

void RegisterWindow::slotRegister()
{
    //通知服务器注册
    if(getUsername()&&getPassword()&&getConfirmpw()&&getEmail() == true)
    {
       m_server->SignUp(r_username.toStdString(),r_email.toStdString(),r_password.toStdString());
    }
}

//获取用户填写的用户名并对格式进行判断
bool RegisterWindow::getUsername()
{
    r_username = usernameEdit->text();
    if(r_username == NULL && m_tips == false)
    {
        showTips(tr("用户名不能为空！"));
        return false;
    }
    if(r_username.size()>10 && m_tips == false)
    {
        showTips(tr("用户名不能超过10个字！"));
        return false;
    }
    return true;
}

//获取用户填写的密码并对格式进行判断
bool RegisterWindow::getPassword()
{
    r_password = passwordEdit->text();
    if(r_password == NULL && m_tips == false)
    {
        showTips(tr("密码不能为空！"));
        return false;
    }
    if(r_password.size()<6 && m_tips == false)
    {
        showTips(tr("密码小于6位！"));
    }
    if(r_password.size()>16 && m_tips == false)
    {
        showTips(tr("密码大于16位！"));
    }
    int lenth = r_password.length();
    QByteArray by = r_password.toLocal8Bit();
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

//获取用户填写的确认密码并第一次输入进行判断
bool RegisterWindow::getConfirmpw()
{
    r_confirmpw = confirmEdit->text();
    int password_len = r_password.length();
    int confirmpw_len = r_confirmpw.length();
    if((password_len!=confirmpw_len)&&(m_tips==false))
    {
        showTips(tr("两次密码长度不一致！"));
        return false;
    }
    else
    {
        QByteArray password_array = r_password.toLocal8Bit();
        QByteArray confirm_array = r_confirmpw.toLocal8Bit();
        for(int index=0;index<password_len;index++)
        {
            char password_c = password_array.at(index);
            char confirm_c = confirm_array.at(index);
            if((password_c!=confirm_c)&&(m_tips==false))
            {
                showTips(tr("两次密码第%1位不一致").arg(index+1));
                return false;
            }
        }
    }
    return true;
}

//获取用户填写的邮箱并判断格式是否正确
bool RegisterWindow::getEmail()
{
    r_email = emailEdit->text();
    if(r_email == NULL && m_tips == false)
    {
        showTips(tr("请输入邮箱！"));
        return false;
    }
    int lenth = r_email.length();
    QByteArray by = r_email.toLocal8Bit();
    for(int index=0;index<lenth;index++)
    {
        char c = by.at(index);
        if((c>=48&&c<=57) || (c>=64&&c<=90) || (c>=97&&c<=122) || c==95 || c==46)
        {
        }
        else
        {
            showTips(tr("请检查您的邮箱格式！"));
            return false;
        }
    }
    return true;
}

//显示提示消息框并渐变效果隐藏消失
void RegisterWindow::showTips(QString tipMsg)
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
void RegisterWindow::hideTips()
{
    tips->hide();
    m_tips=false;
}

void RegisterWindow::hideTips_1()
{
    QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
    tips->setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(0.8);
}

void RegisterWindow::hideTips_2()
{
    QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
    tips->setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(0.5);
}

void RegisterWindow::hideTips_3()
{
    QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
    tips->setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(0.2);
}
