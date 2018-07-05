#include "registerwindow.h"
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

//注册界面
RegisterWindow::RegisterWindow(QWidget *parent) : QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setMaximumSize(580,500);
    this->setMinimumSize(580,500);

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

    QLabel *usernameLabel = new QLabel(QString("Username:"));
    QLabel *passwordLabel = new QLabel(QString("Password:"));
    QLabel *confirmLabel = new QLabel(QString("PW Confirm:"));
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

    QLineEdit *usernameEdit = new QLineEdit;
    QLineEdit *passwordEdit = new QLineEdit;
    QLineEdit *confirmEdit = new QLineEdit;
    QLineEdit *emailEdit = new QLineEdit;

    usernameEdit->setFont(QFont("Microsoft YaHei",14,0));
    usernameEdit->setFixedWidth(250);
    passwordEdit->setFont(QFont("Microsoft YaHei",14,0));
    passwordEdit->setFixedWidth(250);
    passwordEdit->setEchoMode(QLineEdit::Password);
    confirmEdit->setFont(QFont("Microsoft YaHei",14,0));
    confirmEdit->setFixedWidth(250);
    confirmEdit->setEchoMode(QLineEdit::Password);
    emailEdit->setFont(QFont("Microsoft YaHei",14,0));
    emailEdit->setFixedWidth(250);

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
    //TODO:对用户输入信息进行判断，做出反馈，通知服务器进行注册
}
