#include "Server.h"
#include "applicationwindow.h"
#include "mainwindow.h"
#include <QTextEdit>
#include <QPushButton>
#include <QString>
#include <QFont>
#include <QPalette>
#include <QPainter>
#include <functional>
#include <QListWidgetItem>

//中文乱码处理
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

//好友申请界面
ApplicationWindow::ApplicationWindow(Server *server,QWidget *parent, QString string, MainWindow *mainwin):QWidget(parent)
{
    this->mainwin = mainwin;
    this->m_server = server;
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setMaximumSize(500,500);
    this->setMinimumSize(500,500);

    this->userId = string;

    QFont *font=new QFont("Microsoft YaHei",12,0);
    font->setLetterSpacing(QFont::AbsoluteSpacing,0.5);

    application=new QTextEdit(this);
    application->setFont(*font);
    application->setPlaceholderText("您将添加"+string+"为好友，请填写申请理由…");
    application->setFocus();
    application->setGeometry(QRect(50,100,400,300));

    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);


    QPushButton *sendBtn;
    sendBtn=new QPushButton(tr("Send"),this);
    sendBtn->setFont(*font);
    sendBtn->setPalette(pa);
    sendBtn->setStyleSheet("QPushButton{background-color:rgb(0,162,232);border:2px groove white;border-radius:10px;padding:2px 4px;color:white;}"
                           "QPushButton:pressed{background-color:rgb(153,217,234);}");
    sendBtn->setMinimumHeight(40);
    sendBtn->setMinimumWidth(100);
    sendBtn->move(350,430);
    connect(sendBtn,SIGNAL(clicked()),this,SLOT(sendBtnOnClicked()));

    exit = new QPushButton(this);
    exit->setStyleSheet("QPushButton{border-image:url(:/new/img/img/exit.png);}"
                        "QPushButton:hover{border-image:url(:/new/img/img/exit1.png);}"
                        "QPushButton:pressed{border-image:url(:/new/img/img/exit.png);}");
    exit->setMinimumHeight(40);
    exit->setMinimumWidth(50);
    exit->move(450,0);
    min = new QPushButton(this);
    min->setStyleSheet("QPushButton{border-image:url(:/new/img/img/min.png);}"
                       "QPushButton:hover{border-image:url(:/new/img/img/min2.png);}"
                       "QPushButton:pressed{border-image:url(:/new/img/img/min.png);}");
    min->setMinimumHeight(40);
    min->setMinimumWidth(50);
    min->move(402,0);

    connect(exit,SIGNAL(clicked()),this,SLOT(windowclosed()));
    connect(min,SIGNAL(clicked()),this,SLOT(windowmin()));
}

void ApplicationWindow::paintEvent(QPaintEvent *event)
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

void ApplicationWindow::windowclosed()
{
    this->close();
}

void ApplicationWindow::windowmin()
{
    this->showMinimized();
}

void ApplicationWindow::sendBtnOnClicked()
{
    m_server->RequestAddFriend(userId.toStdString(),application->toPlainText().toStdString());
    this->close();
}


