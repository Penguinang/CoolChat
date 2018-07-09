#include "chatwindow.h"
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
#include "Server.h"

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

ChatWindow::ChatWindow(QWidget *parent,QString chatID,int chatHeight,int chatWidth,Server* server)
    :QWidget(parent)
{
    this->m_server = server;
    this->chatID = chatID;
    this->setWindowFlags(Qt::FramelessWindowHint| Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setMaximumSize(chatWidth,chatHeight);
    this->setMinimumSize(chatWidth,chatHeight);

    this->m_tips = false;
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
    sentBtn = new QPushButton(tr("SEND"),this);
    sentBtn->setFont(*font);
    sentBtn->setPalette(pa);
    sentBtn->setStyleSheet("QPushButton{background-color:rgb(0,162,232);border:2px groove white;border-radius:10px;padding:2px 4px;color:white;}"
                           "QPushButton:pressed{background-color:rgb(153,217,234);}");
    sentBtn->setMinimumHeight(40);
    sentBtn->setMinimumWidth(100);
    sentBtn->move(chatWidth-120,chatHeight-60);

    connect(sentBtn,SIGNAL(clicked()),this,SLOT(sentBtnOnClicked()));
}

ChatWindow::~ChatWindow()
{

}

void ChatWindow::windowclosed()
{
    this->close();
}

void ChatWindow::windowmin()
{
    this->showMinimized();
}

void ChatWindow::paintEvent(QPaintEvent *event)
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

void ChatWindow::sentBtnOnClicked()
{
    if(msgEditWindow->toPlainText()==NULL&&m_tips == false)
    {
        m_tips = true;
        this->showFailureTips(tr("Massage can't be empty!"));
        QTimer::singleShot(3000,this,SLOT(hideFailureTips()));
        QTimer::singleShot(2700,this,SLOT(hideFailureTips_1()));
        QTimer::singleShot(2800,this,SLOT(hideFailureTips_2()));
        QTimer::singleShot(2900,this,SLOT(hideFailureTips_3()));
        return;
    }
    ChatWindow c;
    auto callback=std::bind(&ChatWindow::callback,c,placeholders::_1);
    //发送消息
    m_server->SendText(this->chatID.toStdString(),msgEditWindow->toPlainText().toStdString(),callback);
}

void ChatWindow::callback(bool success)
{
    //若消息发送失败，显示消息框提醒
    if(success == false&&m_tips == false)
    {
        m_tips = true;
        this->showFailureTips(tr("Send Massage Failed!"));
        QTimer::singleShot(3000,this,SLOT(hideFailureTips()));
        QTimer::singleShot(2700,this,SLOT(hideFailureTips_1()));
        QTimer::singleShot(2800,this,SLOT(hideFailureTips_2()));
        QTimer::singleShot(2900,this,SLOT(hideFailureTips_3()));
    }
    //若消息发送成功，在消息显示框中显示消息
    else
    {
        sendMsgShow(msgEditWindow->toPlainText(),NULL);
        msgEditWindow->clear();
    }
}

//提示消息发送失败
void ChatWindow::showFailureTips(QString tipMsg)
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
}

//提示消息框渐变隐藏消失
void ChatWindow::hideFailureTips()
{
    tips->hide();
    m_tips=false;
}

void ChatWindow::hideFailureTips_1()
{
    QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
    tips->setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(0.8);
}

void ChatWindow::hideFailureTips_2()
{
    QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
    tips->setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(0.5);
}

void ChatWindow::hideFailureTips_3()
{
    QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
    tips->setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(0.2);
}

void ChatWindow::sendMsgShow(QString msg, QString head)
{

    //将换行转换成<br>,否则html仅显示为空格
    msg.replace("\n","<br>");
    QString html = QString("<div class='msg-wrap right'><img class='header' src='qrc:/new/img/img/FaceQ.jpg' ><div class='msg'>%1<span class='trigon'></span></div></div>").arg(msg);
    m_html.append(html);
    msgShowWindow->setHtml(m_html+"</div>");
    msgShowWindow->show();

}

void ChatWindow::recvMsgShow(QString msg, QString head)
{
    QString html = QString("<div class='msg-wrap left'><img class='header' src='qrc:/new/img/img/FaceQ.jpg' ><div class='msg'>%1<span class='trigon'></span></div></div>").arg(msg);
    m_html.append(html);
    msgShowWindow->setHtml(m_html+"</div>");
    msgShowWindow->show();
}

//按下Ctrl+Enter发送消息
bool ChatWindow::eventFilter(QObject *obj, QEvent *e)
{
    Q_ASSERT(obj == msgEditWindow);
    if (e->type() == QEvent::KeyPress)
    {
        QKeyEvent *event = static_cast<QKeyEvent*>(e);
        if (event->key() == Qt::Key_Return && (event->modifiers() & Qt::ControlModifier))
        {
            sentBtnOnClicked();
            return true;
        }
    }
    return false;
}
