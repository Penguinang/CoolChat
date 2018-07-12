#include "Server.h"
#include "systemwindow.h"
#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QString>
#include <QPushButton>
#include <QFont>
#include <QPaintEvent>
#include <QPainter>
#include <QRect>
#include <QPalette>
#include <QPen>
#include <QPixmap>
#include <QTimer>
#include <QGraphicsOpacityEffect>
#include <QSplitter>
#include <QWebEngineView>
#include <QSizePolicy>
#include <QKeyEvent>
#include "mainwindow.h"

/*
 * 聊天窗口Constructor
 * @param parent 窗口父类
 * @param chatID 当前聊天对象
 * @param chatHeight 窗口高度
 * @param chatWidth 窗口宽度
 */

//中文乱码处理
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

SystemWindow::SystemWindow(Server *server,QWidget *parent,QString chatID,int chatHeight,int chatWidth,MainWindow* mainwin)
    :QWidget(parent)
{
    this->mainwin = mainwin;
    this->m_server = server;
    this->chatID = chatID;
    this->setWindowFlags(Qt::FramelessWindowHint| Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setMaximumSize(chatWidth,chatHeight);
    this->setMinimumSize(chatWidth,chatHeight);

    this->m_tips = false;
    this->newmsg = false;
    this->m_head = QString("<img class='header' src=qrc:/new/img/img/FaceQ.jpg>");
    this->f_head = QString("<img class='header' src=qrc:/new/img/img/FaceQ.jpg>");

    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);

    //退出与最小化
    exit = new QPushButton(this);
    exit->setStyleSheet("QPushButton{border-image:url(:/new/img/img/exit.png);}"
                        "QPushButton:hover{border-image:url(:/new/img/img/exit1.png);}"
                        "QPushButton:pressed{border-image:url(:/new/img/img/exit.png);}");
    exit->setMinimumHeight(40);
    exit->setMinimumWidth(50);
    exit->move(chatWidth-50,0);
    min = new QPushButton(this);
    min->setStyleSheet("QPushButton{border-image:url(:/new/img/img/min.png);}"
                       "QPushButton:hover{border-image:url(:/new/img/img/min2.png);}"
                       "QPushButton:pressed{border-image:url(:/new/img/img/min.png);}");
    min->setMinimumHeight(40);
    min->setMinimumWidth(50);
    min->move(chatWidth-100,0);

    connect(exit,SIGNAL(clicked()),this,SLOT(windowclosed()));
    connect(min,SIGNAL(clicked()),this,SLOT(windowmin()));

    //好友名称标签
    friendName = new QLabel(chatID,this);
    friendName -> setFont(QFont("Microsoft YaHei", chatHeight/30, 0));
    friendName -> adjustSize();
    friendName -> move(0,10);

    //消息显示框和消息编辑框
    QWidget* w_splitter = new QWidget(this);
    w_splitter->setMaximumHeight(chatHeight-friendName->height()-100);
    w_splitter->setMaximumWidth(chatWidth);
    w_splitter->setMinimumHeight(chatHeight-friendName->height()-100);
    w_splitter->setMinimumWidth(chatWidth);
    w_splitter->move(5,friendName->height()+20);

    QSplitter* chatSplitter = new QSplitter(Qt::Vertical,w_splitter);
    chatSplitter->setMinimumWidth(w_splitter->width()-10);
    chatSplitter->setMaximumWidth(w_splitter->width()-10);
    chatSplitter->setMinimumHeight(w_splitter->height()-10);
    chatSplitter->setMaximumHeight(w_splitter->height()-10);
    msgShowWindow = new QWebEngineView;
    msgEditWindow = new QTextEdit;
    chatSplitter->addWidget(msgShowWindow);
    chatSplitter->addWidget(msgEditWindow);
    chatSplitter->adjustSize();
    msgEditWindow->setStyleSheet("QTextEdit{border:rgb(100,100,100)}");
    chatSplitter->setStretchFactor(0,7);
    chatSplitter->setStretchFactor(1,3);


    QFile source(":/new/html/html/chat.html");
    source.open(QIODevice::ReadOnly);
    m_html = QString::fromUtf8(source.readAll());
    msgShowWindow->setHtml(m_html+"</div>");
    source.close();

    msgShowWindow->setFocusPolicy(Qt::NoFocus);
    msgEditWindow->setFocusPolicy(Qt::StrongFocus);
    msgEditWindow->setFocus();
    msgEditWindow->installEventFilter(this);

    //发送按钮
    QFont *font=new QFont("Microsoft YaHei",12,0);
    font->setLetterSpacing(QFont::AbsoluteSpacing,0.5);
    agreeBtn = new QPushButton(tr("同意"),this);
    agreeBtn->setFont(*font);
    agreeBtn->setPalette(pa);
    agreeBtn->setStyleSheet("QPushButton{background-color:rgb(0,162,232);border:2px groove white;border-radius:10px;padding:2px 4px;color:white;}"
                           "QPushButton:pressed{background-color:rgb(153,217,234);}");
    agreeBtn->setMinimumHeight(40);
    agreeBtn->setMinimumWidth(100);
    agreeBtn->move(chatWidth-120,chatHeight-60);

    connect(agreeBtn,SIGNAL(clicked()),this,SLOT(agreeBtnOnClicked()));

    //拒绝按钮
    refuseBtn = new QPushButton(tr("拒绝"),this);
    refuseBtn->setFont(*font);
    refuseBtn->setPalette(pa);
    refuseBtn->setStyleSheet("QPushButton{background-color:rgb(0,162,232);border:2px groove white;border-radius:10px;padding:2px 4px;color:white;}"
                           "QPushButton:pressed{background-color:rgb(153,217,234);}");
    refuseBtn->setMinimumHeight(40);
    refuseBtn->setMinimumWidth(100);
    refuseBtn->move(chatWidth-240,chatHeight-60);

    connect(refuseBtn,SIGNAL(clicked()),this,SLOT(refuseBtnOnClicked()));
}

SystemWindow::~SystemWindow()
{

}

void SystemWindow::windowclosed()
{
    this->close();
}

void SystemWindow::windowmin()
{
    this->showMinimized();
}

void SystemWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(255,255,255));
    QRect rect = this->rect();
    rect.setWidth(rect.width()-1);
    rect.setHeight(rect.height()-1);
    p.drawRect(rect);
    p.setPen(QPen(QColor(200,200,200),1));
    p.drawRect(0,0,this->width(),this->height());
}

void SystemWindow::agreeBtnOnClicked()
{
    if(m_tips == false)
    {
        printf("agree request\n");
        m_tips = true;
        this->showTips(tr("已同意！"));
        QTimer::singleShot(3000,this,SLOT(hideFailureTips()));
        QTimer::singleShot(2700,this,SLOT(hideFailureTips_1()));
        QTimer::singleShot(2800,this,SLOT(hideFailureTips_2()));
        QTimer::singleShot(2900,this,SLOT(hideFailureTips_3()));
        m_server->ReplyFriendRequest(username,true,msgEditWindow->toPlainText().toStdString());
        mainwin->addFriend(username);
        
        mainwin->update();
    }
    this->newmsg = false;
}

void SystemWindow::refuseBtnOnClicked()
{
    if(m_tips == false)
    {
        printf("Refuse request\n");
        m_tips = true;
        this->showTips(tr("已拒绝！"));
        QTimer::singleShot(3000,this,SLOT(hideFailureTips()));
        QTimer::singleShot(2700,this,SLOT(hideFailureTips_1()));
        QTimer::singleShot(2800,this,SLOT(hideFailureTips_2()));
        QTimer::singleShot(2900,this,SLOT(hideFailureTips_3()));
        m_server->ReplyFriendRequest(username,false,msgEditWindow->toPlainText().toStdString());
    }
    this->newmsg = false;
}

//显示提示消息框并渐变效果隐藏消失
void SystemWindow::showTips(QString tipMsg)
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
void SystemWindow::hideTips()
{
    tips->hide();
    m_tips=false;
}

void SystemWindow::hideTips_1()
{
    QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
    tips->setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(0.8);
}

void SystemWindow::hideTips_2()
{
    QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
    tips->setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(0.5);
}

void SystemWindow::hideTips_3()
{
    QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
    tips->setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(0.2);
}

void SystemWindow::recvMsgShow(QString msg, QString head)
{
    QString html = QString("<div class='msg-wrap left'><img class='header' src='qrc:/new/img/img/FaceQ.jpg' ><div class='msg'>%1<span class='trigon'></span></div></div>").arg(msg);
    m_html.append(html);
    msgShowWindow->setHtml(m_html+"</div>");
    msgShowWindow->show();
}

